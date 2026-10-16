"""Services shared by the CLI and future desktop UI."""
import copy
import hashlib
from pathlib import Path
import stat
from uuid import uuid4

from app.domain.workspace.model import PathError, ValidationError, now
from app.application.ports import WorkspaceRepository


def resolve_input(store: WorkspaceRepository, item):
    if item["path_kind"] == "workspace_relative":
        base = store.root / "inputs"
        if base.is_symlink():
            raise PathError("Folder inputs tidak boleh symlink.")
        path = store.root / item["path"]
        if not path.resolve().is_relative_to(base.resolve()):
            raise PathError("Input relatif keluar folder inputs.")
    else:
        path = Path(item["path"])
        if not path.is_absolute():
            raise PathError("Path absolute berasal dari OS lain; relokasi manual diperlukan.")
    resolved = path.resolve(strict=True)
    if resolved.is_relative_to(store.root) and not resolved.is_relative_to(store.root / "inputs"):
        raise PathError("Input tidak boleh memakai file metadata/output workspace.")
    return resolved


def fingerprint(path):
    # Do not read devices/FIFOs or execute files. Hardlinks rejected to avoid metadata aliases.
    before = path.stat()
    if not stat.S_ISREG(before.st_mode) or before.st_nlink != 1:
        raise PathError("Input harus regular file tanpa hardlink.")
    with path.open("rb") as stream:
        import os
        opened = os.fstat(stream.fileno())
        h = hashlib.sha256()
        count = 0
        while block := stream.read(1024 * 1024):
            h.update(block)
            count += len(block)
        after_fd = os.fstat(stream.fileno())
    after = path.stat()
    identity = lambda s: (s.st_dev, s.st_ino, s.st_size, s.st_mtime_ns, s.st_ctime_ns)
    if not identity(before) == identity(opened) == identity(after_fd) == identity(after) \
            or count != before.st_size:
        raise ValidationError("Input berubah saat hashing; ulangi ketika file stabil.")
    return h.hexdigest(), count


def rename(store: WorkspaceRepository, name):
    snapshot = store.load()
    data = copy.deepcopy(snapshot.data)
    data["name"] = name
    return store.save(snapshot, data)


def add_input(store: WorkspaceRepository, value, relative=False):
    snapshot = store.load()
    item = {"id": str(uuid4()), "path_kind": "workspace_relative" if relative else "absolute",
            "path": value if relative else str(Path(value).absolute()),
            "sha256": "0" * 64, "size_bytes": 0, "registered_at": now(),
            "validation": "format_unchecked"}
    data = copy.deepcopy(snapshot.data)
    data["inputs"].append(item)
    from app.domain.workspace.model import validate
    validate(data)  # reject traversal before opening the referenced file
    target = resolve_input(store, item)
    for existing in snapshot.data["inputs"]:
        try:
            if resolve_input(store, existing) == target:
                raise ValidationError("Input sudah terdaftar.")
        except FileNotFoundError:
            continue
    item["sha256"], item["size_bytes"] = fingerprint(target)
    return store.save(snapshot, data)


def verify_inputs(store: WorkspaceRepository):
    results = []
    for item in store.load().data["inputs"]:
        try:
            sha, size = fingerprint(resolve_input(store, item))
            ok = sha == item["sha256"] and size == item["size_bytes"]
            results.append({"id": item["id"], "status": "unchanged" if ok else "changed",
                            "sha256": sha, "size_bytes": size})
        except (OSError, PathError, ValidationError) as exc:
            results.append({"id": item["id"], "status": "error", "reason": str(exc)})
    return results
