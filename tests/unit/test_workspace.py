import copy
import hashlib
import json
import os
from pathlib import Path
import queue
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch

from app.application.workspaces import add_input, fingerprint, rename, verify_inputs
from app.domain.workspace.model import (
    ConflictError, PathError, UnsupportedSchema, ValidationError, decode, encode,
)
from app.infrastructure.persistence.store import MAX_MANIFEST, Store

PROJECT = Path(__file__).resolve().parents[2]


class WorkspaceTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="ps2-tests-")
        self.addCleanup(self.temp.cleanup)
        self.parent = Path(self.temp.name)
        self.store = Store(self.parent / "Proyek 日本 spasi")
        self.initial = self.store.create("Game uji 日本")

    def cli(self, *args):
        return subprocess.run([sys.executable, "-m", "app.cli", *map(str, args)],
                              cwd=PROJECT, capture_output=True, text=True, timeout=10)

    def test_create_open_save_unicode_and_backup(self):
        self.assertEqual(self.store.load(), self.initial)
        updated = rename(self.store, "Nama baru 日本")
        self.assertEqual(updated.data["revision"], 1)
        self.assertEqual(updated.data["name"], "Nama baru 日本")
        backup = next((self.store.root / "backups").glob("r*.json"))
        self.assertEqual(decode(backup.read_bytes()), self.initial.data)

    def test_create_existing_refuses_overwrite(self):
        before = (self.store.root / "workspace.json").read_bytes()
        with self.assertRaises(FileExistsError):
            self.store.create("another")
        self.assertEqual((self.store.root / "workspace.json").read_bytes(), before)

    def test_bad_name_no_directory_created(self):
        other = Store(self.parent / "bad")
        with self.assertRaises(ValidationError):
            other.create("  ")
        self.assertFalse(other.root.exists())

    def test_invalid_json_utf8_and_duplicate_fields(self):
        for raw in (b'{', b'\xff', b'{"schema_version":1,"schema_version":1}', b'[]'):
            with self.subTest(raw=raw), self.assertRaises(ValidationError):
                decode(raw)

    def test_strict_schema_types_and_unknown_fields(self):
        for key, value in [("revision", True), ("name", 1), ("inputs", {}),
                           ("created_at", "no"), ("status", "matched"), ("name", "\ud800"),
                           ("integrations", {"token": "secret"}), ("extra", 1)]:
            data = copy.deepcopy(self.initial.data)
            data[key] = value
            with self.subTest(key=key), self.assertRaises(ValidationError):
                encode(data)

    def test_future_schema_not_changed_even_recovery(self):
        rename(self.store, "new")  # creates valid backup
        data = self.store.load().data
        data["schema_version"] = 2
        raw = json.dumps(data).encode()
        (self.store.root / "workspace.json").write_bytes(raw)
        with self.assertRaises(UnsupportedSchema):
            self.store.load()
        info = self.store.recovery_info()
        with self.assertRaises(UnsupportedSchema):
            self.store.recover(info["backups"][0]["file"], info["current_token"])
        self.assertEqual((self.store.root / "workspace.json").read_bytes(), raw)

    def test_oversize_manifest_rejected(self):
        (self.store.root / "workspace.json").write_bytes(b" " * (MAX_MANIFEST + 1))
        with self.assertRaises(ValidationError):
            self.store.load()

    def test_two_snapshots_conflict(self):
        one, two = self.store.load(), self.store.load()
        data = dict(one.data, name="first")
        self.store.save(one, data)
        with self.assertRaises(ConflictError):
            self.store.save(two, dict(two.data, name="second"))
        self.assertEqual(self.store.load().data["name"], "first")

    def test_same_revision_external_edit_conflicts(self):
        snap = self.store.load()
        (self.store.root / "workspace.json").write_bytes(encode(dict(snap.data, name="external")))
        with self.assertRaises(ConflictError):
            self.store.save(snap, dict(snap.data, name="mine"))

    def test_identity_edit_rejected(self):
        data = dict(self.initial.data, revision=42)
        with self.assertRaises(ConflictError):
            self.store.save(self.initial, data)

    def test_process_lock_conflict_and_release(self):
        with self.store.lock():
            result = self.cli("rename", self.store.root, "--name", "child")
            self.assertEqual(result.returncode, 2, result.stderr)
            self.assertEqual(json.loads(result.stderr)["error"], "conflict")
        result = self.cli("rename", self.store.root, "--name", "child")
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_lock_released_after_process_killed(self):
        program = ("import sys,time; from app.infrastructure.persistence.store import Store; "
                   "s=Store(sys.argv[1]);\nwith s.lock():\n print('locked',flush=True)\n time.sleep(20)\n")
        proc = subprocess.Popen([sys.executable, "-c", program, str(self.store.root)],
                                cwd=PROJECT, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        try:
            ready = queue.Queue()
            reader = threading.Thread(target=lambda: ready.put(proc.stdout.readline()), daemon=True)
            reader.start()
            self.assertEqual(ready.get(timeout=5).strip(), "locked")
            reader.join(timeout=1)
        finally:
            proc.kill()
            proc.communicate(timeout=5)
        self.assertEqual(rename(self.store, "after crash").data["revision"], 1)

    def test_failure_before_replace_preserves_manifest_and_cleans_temp(self):
        before = (self.store.root / "workspace.json").read_bytes()
        real_replace = os.replace
        def fail_manifest(src, dst):
            if Path(dst).name == "workspace.json":
                raise OSError("injected disk error before commit")
            return real_replace(src, dst)
        with patch("app.infrastructure.persistence.store.os.replace", side_effect=fail_manifest):
            with self.assertRaises(OSError):
                rename(self.store, "lost")
        self.assertEqual((self.store.root / "workspace.json").read_bytes(), before)
        self.assertEqual(list(self.store.root.rglob(".pending-*")), [])
        self.assertTrue(list((self.store.root / "backups").glob("r*.json")))
        self.assertEqual(rename(self.store, "retry").data["name"], "retry")

    def test_permission_error_does_not_commit(self):
        with patch("app.infrastructure.persistence.store.tempfile.mkstemp", side_effect=PermissionError("read only")):
            with self.assertRaises(PermissionError):
                rename(self.store, "no")
        self.assertEqual(self.store.load(), self.initial)

    @unittest.skipUnless(os.name == "posix", "POSIX permission test")
    def test_actual_read_only_directory(self):
        self.parent.chmod(0o755)
        self.store.root.chmod(0o555)
        lockfile = self.store.root / ".writer.lock"
        lockfile.chmod(0o666)
        (self.store.root / "workspace.json").chmod(0o644)
        (self.store.root / "backups").chmod(0o555)
        demote = (lambda: os.setuid(65534)) if os.geteuid() == 0 else None
        try:
            # Only stdlib and our code; environment contains no secrets passed in argv.
            try:
                result = subprocess.run([sys.executable, "-m", "app.cli", "rename", str(self.store.root),
                                         "--name", "cannot save"], cwd=PROJECT, capture_output=True,
                                        text=True, timeout=10, preexec_fn=demote)
            except subprocess.SubprocessError:
                self.skipTest("Container root cannot drop UID; actual chmod permission test unavailable")
            self.assertEqual(result.returncode, 2, result.stderr)
            self.assertEqual(json.loads(result.stderr)["error"], "filesystem_error")
            self.assertEqual(self.store.load(), self.initial)
        finally:
            self.store.root.chmod(0o755)
            (self.store.root / "backups").chmod(0o755)

    def test_external_input_hashed_but_not_copied_or_modified(self):
        path = self.parent / "input 日本.bin"
        content = b"synthetic bytes, not a PS2 game"
        path.write_bytes(content)
        add_input(self.store, str(path))
        item = self.store.load().data["inputs"][0]
        self.assertEqual(item["sha256"], hashlib.sha256(content).hexdigest())
        self.assertEqual(item["validation"], "format_unchecked")
        self.assertEqual(path.read_bytes(), content)
        self.assertEqual(list((self.store.root / "inputs").iterdir()), [])
        self.assertEqual(verify_inputs(self.store)[0]["status"], "unchanged")
        path.write_bytes(b"changed")
        self.assertEqual(verify_inputs(self.store)[0]["status"], "changed")
        self.assertEqual(self.cli("verify-inputs", self.store.root).returncode, 3)
        path.unlink()
        self.assertEqual(verify_inputs(self.store)[0]["status"], "error")

    def test_relative_input_and_duplicate(self):
        (self.store.root / "inputs" / "file.bin").write_bytes(b"fixture")
        add_input(self.store, "inputs/file.bin", relative=True)
        self.assertEqual(verify_inputs(self.store)[0]["status"], "unchanged")
        with self.assertRaises(ValidationError):
            add_input(self.store, str(self.store.root / "inputs/file.bin"))

    def test_relative_traversal_and_metadata_alias_refused(self):
        for value in ("../outside", "inputs/../workspace.json", "/tmp/file", "workspace.json", "inputs\\file"):
            with self.subTest(value=value), self.assertRaises(ValidationError):
                add_input(self.store, value, relative=True)
        with self.assertRaises(PathError):
            add_input(self.store, str(self.store.root / "workspace.json"))
        self.assertEqual(self.store.load(), self.initial)

    @unittest.skipUnless(os.name == "posix", "Symlink creation may require Windows privileges")
    def test_symlink_metadata_and_backup_directory_refused(self):
        external = self.parent / "precious"
        external.write_bytes(b"keep me")
        path = self.store.root / "workspace.json"
        path.unlink()
        path.symlink_to(external)
        with self.assertRaises(PathError):
            self.store.load()
        path.unlink()
        path.write_bytes(encode(self.initial.data))
        backups = self.store.root / "backups"
        backups.rmdir()
        backups.symlink_to(self.parent, target_is_directory=True)
        with self.assertRaises(PathError):
            rename(self.store, "no")
        self.assertEqual(external.read_bytes(), b"keep me")

    @unittest.skipUnless(os.name == "posix", "POSIX link fixture")
    def test_relative_input_symlink_escape_and_hardlink(self):
        source = self.parent / "outside"
        source.write_bytes(b"outside")
        (self.store.root / "inputs/link").symlink_to(source)
        with self.assertRaises(PathError):
            add_input(self.store, "inputs/link", relative=True)
        os.link(self.store.root / "workspace.json", self.store.root / "inputs/hard")
        with self.assertRaises(PathError):
            fingerprint(self.store.root / "inputs/hard")

    def test_changed_during_hash_rejected(self):
        source = self.parent / "source"
        source.write_bytes(b"before")
        original = hashlib.sha256
        class MutatingHash:
            def __init__(self): self.inner = original()
            def update(self, data):
                self.inner.update(data)
                source.write_bytes(b"after!")
            def hexdigest(self): return self.inner.hexdigest()
        with patch("app.application.workspaces.hashlib.sha256", MutatingHash):
            with self.assertRaises(ValidationError):
                fingerprint(source)

    def test_recover_corrupt_preserves_bytes_and_backup(self):
        rename(self.store, "new")
        backup = next((self.store.root / "backups").glob("r*.json"))
        backup_bytes = backup.read_bytes()
        (self.store.root / "workspace.json").write_bytes(b'{"broken":')
        info = self.store.recovery_info()
        recovered = self.store.recover(backup.name, info["current_token"])
        self.assertEqual(recovered.data["name"], self.initial.data["name"])
        self.assertEqual(backup.read_bytes(), backup_bytes)
        self.assertEqual(next((self.store.root / "backups").glob("corrupt-*.bin")).read_bytes(), b'{"broken":')

    def test_recover_missing_manifest(self):
        rename(self.store, "new")
        backup = next((self.store.root / "backups").glob("r*.json"))
        (self.store.root / "workspace.json").unlink()
        self.store.recover(backup.name, "missing")
        self.assertEqual(self.store.load().data["workspace_id"], self.initial.data["workspace_id"])

    def test_recover_conflict_valid_manifest_and_bad_backup(self):
        rename(self.store, "new")
        backup = next((self.store.root / "backups").glob("r*.json"))
        with self.assertRaises(ConflictError):
            self.store.recover(backup.name, "wrong")
        with self.assertRaises(ConflictError):
            self.store.recover(backup.name, self.store.load().token)
        (self.store.root / "workspace.json").write_bytes(b"broken")
        info = self.store.recovery_info()
        backup.write_bytes(b"bad backup")
        self.assertFalse(self.store.recovery_info()["backups"][0]["valid"])
        with self.assertRaises(ValidationError):
            self.store.recover(backup.name, info["current_token"])
        self.assertEqual((self.store.root / "workspace.json").read_bytes(), b"broken")

    def test_recovery_traversal_refused(self):
        with self.assertRaises(PathError):
            self.store.recover("../outside.json", "missing")

    def test_backup_hash_mismatch_refused(self):
        rename(self.store, "new")
        backup = next((self.store.root / "backups").glob("r*.json"))
        backup.write_bytes(encode(dict(self.initial.data, name="tampered")))
        self.assertFalse(self.store.recovery_info()["backups"][0]["valid"])
        (self.store.root / "workspace.json").write_bytes(b"broken")
        with self.assertRaises(ValidationError):
            self.store.recover(backup.name, self.store.recovery_info()["current_token"])

    def test_cli_roundtrip_and_errors(self):
        path = self.parent / "CLI project"
        result = self.cli("create", path, "--name", "Test")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(json.loads(result.stdout)["revision"], 0)
        self.assertEqual(self.cli("open", path).returncode, 0)
        valid = self.cli("validate", path)
        self.assertFalse(json.loads(valid.stdout)["input_formats_validated"])
        self.assertEqual(self.cli("rename", path, "--name", "Next").returncode, 0)
        self.assertEqual(self.cli("open", self.parent / "missing").returncode, 2)
        self.assertEqual(self.cli("create", path, "--name", "Duplicate").returncode, 2)


if __name__ == "__main__":
    unittest.main()
