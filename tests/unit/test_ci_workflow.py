from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[2]
WORKFLOW = ROOT / ".github" / "workflows" / "ci.yml"


class CIWorkflowContractTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.text = WORKFLOW.read_text(encoding="utf-8")

    def test_source_root_is_resolved_before_module_invocation(self):
        resolve = self.text.index("- name: Resolve project source root")
        cli = self.text.index("- name: Show CLI help")
        self.assertLess(resolve, cli)
        self.assertIn("app/__main__.py", self.text)
        self.assertIn("tools/check_public_release.py", self.text)
        self.assertIn("find \"$workspace\"", self.text)

    def test_matrix_covers_supported_python_versions(self):
        self.assertIn('python-version: ["3.12", "3.13"]', self.text)

    def test_failure_diagnostics_are_retained(self):
        self.assertIn("GITHUB_STEP_SUMMARY", self.text)
        self.assertIn("actions/upload-artifact@v7", self.text)
        self.assertIn("if: ${{ always() && !cancelled() }}", self.text)
        self.assertIn("unit-tests.log", self.text)
        self.assertIn("public-release-check.log", self.text)

    def test_unit_test_timeout_is_bounded(self):
        self.assertIn("timeout --signal=TERM --kill-after=15s 12m", self.text)


if __name__ == "__main__":
    unittest.main()
