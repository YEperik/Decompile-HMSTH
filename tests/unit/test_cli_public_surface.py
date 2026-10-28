import ast
import contextlib
import io
import unittest
from pathlib import Path

from app.cli import main

ROOT = Path(__file__).resolve().parents[2]


class CLIPublicSurfaceTests(unittest.TestCase):
    def test_help_all_only_advertises_available_commands(self):
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            result = main(["--help-all"])
        self.assertEqual(result, 0)
        help_text = out.getvalue()
        for command in ("inspect-elf", "ghidra-decompile", "queue-add", "check-decompile"):
            self.assertIn(command, help_text)
        for command in (
            "ee-startup", "vector-draft", "ghidra-cop2-audit", "ghidra-program",
            "extract-disc-elf", "vu-micro-trace", "check-vector-draft",
        ):
            self.assertNotIn(command, help_text)

    def test_all_internal_app_imports_resolve(self):
        missing = []
        for source in (ROOT / "app").rglob("*.py"):
            tree = ast.parse(source.read_text(encoding="utf-8"), filename=str(source))
            for node in ast.walk(tree):
                if not isinstance(node, ast.ImportFrom) or not node.module or not node.module.startswith("app."):
                    continue
                module_path = Path(*node.module.split("."))
                module_file = ROOT / module_path.with_suffix(".py")
                package_file = ROOT / module_path / "__init__.py"
                if not module_file.is_file() and not package_file.is_file():
                    missing.append(f"{source.relative_to(ROOT)}:{node.lineno}: {node.module}")
        self.assertEqual(missing, [])

    def test_runtime_headers_are_not_packaged(self):
        self.assertFalse((ROOT / "app" / "runtime").exists())
        metadata = (ROOT / "pyproject.toml").read_text(encoding="utf-8")
        self.assertNotIn('runtime/*.h', metadata)


if __name__ == "__main__":
    unittest.main()
