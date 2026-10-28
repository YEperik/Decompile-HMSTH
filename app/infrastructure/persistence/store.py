"""Local single-writer store. Atomic replace is not a hostile-filesystem sandbox."""
from contextlib import contextmanager
import hashlib
import os
from pathlib import Path
import stat
import tempfile

from app.domain.workspace.model import (
    ConflictError, PathError, Snapshot, UnsupportedSchema, ValidationError,
    decode, encode, new_workspace, now,
)

MAX_MANIFEST = 1024 * 1024


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def regular(path):
    """Reject links for managed metadata; do not follow a link to another file."""
    if path.is_symlink():
        raise PathError(f"Symlink metadata ditolak: {path.name}")
    if path.exists():
        s = path.stat()
        if not stat.S_ISREG(s.st_mode) or s.st_nlink != 1:
            raise PathError(f"Metadata bukan regular file tunggal: {path.name}")


def read_bytes(path):
    regular(path)
    with path.open("rb") as stream:
        raw = stream.read(MAX_MANIFEST + 1)
    if len(raw) > MAX_MANIFEST:
        raise ValidationError("Manifest melebihi batas 1 MiB.")
    return raw


class Store:
    def __init__(self, root):
        path = Path(root).absolute()
        if path.is_symlink():
            raise PathError("Root workspace tidak boleh symlink.")
        self.root = path.resolve()

    def managed(self, relative):
        p = Path(relative)
        if p.is_absolute() or ".." in p.parts:
            raise PathError("Path output harus relatif tanpa traversal.")
        target = self.root / p
        cursor = self.root
        for part in p.parts:
            cursor /= part
            if cursor.is_symlink():
                raise PathError("Symlink di path metadata ditolak.")
        if not target.resolve().is_relative_to(self.root):
            raise PathError("Output keluar workspace.")
        return target

    @contextmanager
    def lock(self):
        """Kernel lock released on exit/crash; persistent lock file is never unlinked."""
        path = self.managed(".writer.lock")
        regular(path)
        fd = os.open(path, os.O_RDWR | os.O_CREAT | getattr(os, "O_NOFOLLOW", 0), 0o600)
        acquired = False
        try:
            info = os.fstat(fd)
            if not stat.S_ISREG(info.st_mode) or info.st_nlink != 1:
                raise PathError("Lock file invalid.")
            if os.name == "nt":
                import msvcrt
                # Lock a fixed byte. An empty file can be locked beyond EOF on Windows.
                os.lseek(fd, 0, os.SEEK_SET)
                try:
                    msvcrt.locking(fd, msvcrt.LK_NBLCK, 1)
                except OSError as exc:
                    raise ConflictError("Workspace sedang ditulis proses lain.") from exc
            else:
                import fcntl
                try:
                    fcntl.flock(fd, fcntl.LOCK_EX | fcntl.LOCK_NB)
                except BlockingIOError as exc:
                    raise ConflictError("Workspace sedang ditulis proses lain.") from exc
            acquired = True
            yield
        finally:
            if acquired:
                if os.name == "nt":
                    import msvcrt
                    os.lseek(fd, 0, os.SEEK_SET)
                    msvcrt.locking(fd, msvcrt.LK_UNLCK, 1)
                else:
                    import fcntl
                    fcntl.flock(fd, fcntl.LOCK_UN)
            os.close(fd)

    def atomic(self, relative, raw):
        if len(raw) > MAX_MANIFEST:
            raise ValidationError("Metadata melebihi batas 1 MiB.")
        target = self.managed(relative)
        regular(target)
        fd, temporary = tempfile.mkstemp(prefix=".pending-", dir=target.parent)
        try:
            with os.fdopen(fd, "wb") as stream:
                stream.write(raw)
                stream.flush()
                os.fsync(stream.fileno())
            os.replace(temporary, target)
            if os.name == "posix":
                folder = os.open(target.parent, os.O_RDONLY | getattr(os, "O_DIRECTORY", 0))
                try:
                    os.fsync(folder)
                finally:
                    os.close(folder)
        finally:
            if os.path.exists(temporary):
                os.unlink(temporary)

    def create(self, name):
        data = new_workspace(name)  # validate before making any directories
        self.root.mkdir(parents=False, exist_ok=False)
        # Failure leaves a visible partial directory; never delete arbitrary user content.
        with self.lock():
            self.managed("backups").mkdir()
            self.managed("inputs").mkdir()
            self.atomic("workspace.json", encode(data))
        return self.load()

    def load(self):
        raw = read_bytes(self.managed("workspace.json"))
        return Snapshot(decode(raw), digest(raw))

    def backup(self, raw, data):
        name = f"r{data['revision']:08d}-{digest(raw)}.json"
        path = self.managed("backups")
        if not path.is_dir():
            raise PathError("Folder backups hilang; pulihkan folder sebelum menyimpan.")
        target = self.managed(f"backups/{name}")
        if target.exists():
            if read_bytes(target) != raw:
                raise ConflictError("Backup yang sudah ada berbeda; tidak ditimpa.")
        else:
            self.atomic(f"backups/{name}", raw)

    def save(self, snapshot, proposed):
        # Public service permits edits only through this revision-guarded operation.
        encode(proposed)
        with self.lock():
            current_raw = read_bytes(self.managed("workspace.json"))
            current = decode(current_raw)
            if digest(current_raw) != snapshot.token:
                raise ConflictError("Manifest berubah. Buka ulang sebelum menyimpan.")
            for key in ("workspace_id", "created_at", "schema_version", "revision"):
                if proposed[key] != current[key]:
                    raise ConflictError(f"Field immutable berubah: {key}")
            updated = dict(proposed, revision=current["revision"] + 1, updated_at=now())
            raw = encode(updated)
            self.backup(current_raw, current)
            self.atomic("workspace.json", raw)
            return Snapshot(decode(raw), digest(raw))

    def recovery_info(self):
        path = self.managed("workspace.json")
        raw = read_bytes(path) if path.exists() else None
        items = []
        folder = self.managed("backups")
        for p in sorted(folder.glob("r*.json")):
            try:
                backup_raw = read_bytes(p)
                data = decode(backup_raw)
                if p.name != f"r{data['revision']:08d}-{digest(backup_raw)}.json":
                    raise ValidationError("Nama/hash backup tidak sesuai isinya.")
                items.append({"file": p.name, "valid": True, "revision": data["revision"],
                              "workspace_id": data["workspace_id"]})
            except (ValidationError, PathError, OSError) as exc:
                items.append({"file": p.name, "valid": False, "reason": str(exc)})
        return {"current_token": digest(raw) if raw is not None else "missing", "backups": items}

    def recover(self, backup_name, expected_token):
        if Path(backup_name).name != backup_name or not backup_name.startswith("r") \
                or not backup_name.endswith(".json") or "\\" in backup_name:
            raise PathError("Pilih nama backup dari recovery-info.")
        with self.lock():
            path = self.managed("workspace.json")
            raw = read_bytes(path) if path.exists() else None
            token = digest(raw) if raw is not None else "missing"
            if token != expected_token:
                raise ConflictError("Manifest berubah sejak recovery-info.")
            if raw is not None:
                try:
                    decode(raw)
                except UnsupportedSchema:
                    raise  # never downgrade a future schema
                except ValidationError:
                    pass
                else:
                    raise ConflictError("Manifest masih valid; recovery bukan perintah rollback.")
            backup_raw = read_bytes(self.managed(f"backups/{backup_name}"))
            data = decode(backup_raw)
            expected_name = f"r{data['revision']:08d}-{digest(backup_raw)}.json"
            if backup_name != expected_name:
                raise ValidationError("Nama/hash backup tidak sesuai isinya.")
            # Preserve corrupt bytes before repair. Backup files themselves never change.
            if raw is not None:
                artifact = f"backups/corrupt-{token}.bin"
                old = self.managed(artifact)
                if old.exists():
                    if read_bytes(old) != raw:
                        raise ConflictError("Arsip korup berbeda; recovery dibatalkan.")
                else:
                    self.atomic(artifact, raw)
            data = dict(data, revision=data["revision"] + 1, updated_at=now())
            repaired = encode(data)
            self.atomic("workspace.json", repaired)
            return Snapshot(decode(repaired), digest(repaired))
