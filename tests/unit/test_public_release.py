import importlib.util
import io
import tempfile
import unittest
import zipfile
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[2] / "tools" / "check_public_release.py"
spec = importlib.util.spec_from_file_location("public_release_checker", SCRIPT)
checker = importlib.util.module_from_spec(spec)
assert spec and spec.loader
spec.loader.exec_module(checker)


class PublicReleaseCheckerTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)

    def tearDown(self):
        self.temp.cleanup()

    def write(self, relative, data):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
        return path

    def test_clean_source_tree_passes(self):
        self.write("README.md", b"Project documentation\n")
        self.write("src/tool.py", b"print('hello')\n")
        self.assertEqual(checker.scan_root(self.root), [])

    def test_protected_suffix_and_serial_name_are_reported(self):
        self.write("local/game.iso", b"not even a real ISO")
        self.write("SLUS_202.51", b"placeholder")
        findings = checker.scan_root(self.root)
        self.assertTrue(any("game.iso" in item for item in findings))
        self.assertTrue(any("SLUS_202.51" in item for item in findings))

    def test_renamed_elf_signature_is_reported(self):
        self.write("notes.txt", b"\x7fELF" + b"\x00" * 128)
        findings = checker.scan_root(self.root)
        self.assertTrue(any("ELF executable/object signature" in item for item in findings))

    def test_archive_member_binary_signature_is_reported(self):
        archive_path = self.root / "attachments.zip"
        with zipfile.ZipFile(archive_path, "w", compression=zipfile.ZIP_DEFLATED) as archive:
            archive.writestr("readme.txt", "No problem")
            archive.writestr("opaque.datx", b"\x7fELF" + b"\x00" * 128)
        findings = checker.scan_root(self.root)
        self.assertTrue(any("opaque.datx" in item and "ELF" in item for item in findings))

    def test_nested_archive_is_inspected_even_when_renamed(self):
        nested = io.BytesIO()
        with zipfile.ZipFile(nested, "w", compression=zipfile.ZIP_DEFLATED) as inner:
            inner.writestr("mystery.bin", b"private")
        outer_path = self.root / "outer.zip"
        with zipfile.ZipFile(outer_path, "w", compression=zipfile.ZIP_DEFLATED) as outer:
            outer.writestr("attachment.txt", nested.getvalue())
        findings = checker.scan_root(self.root)
        self.assertTrue(any("mystery.bin" in item for item in findings))

    def test_unsupported_archive_fails_closed(self):
        self.write("unknown.7z", b"7z\xbc\xaf\x27\x1c" + b"not inspected")
        findings = checker.scan_root(self.root)
        self.assertTrue(any("unsupported archive format" in item for item in findings))


if __name__ == "__main__":
    unittest.main()
