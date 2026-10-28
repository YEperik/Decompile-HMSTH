# Applying this source package to the existing GitHub repository

The CI logs supplied on 2026-10-27 show that the workflow tried to execute `python -m app --help`, but the checked-out tree did not contain an importable `app` package. Both Python 3.12 and 3.13 failed at the same first step, so the unit tests and package-build checks did not run.

This release package is a complete source-tree layout with `app/`, `pyproject.toml`, `tests/`, `tools/`, and `.github/workflows/ci.yml`. It must replace the repository's source layout as a set; adding the ZIP or its outer directory as a new subfolder does not replace the root workflow that GitHub Actions already executes.

## Safe replacement procedure

1. Make a backup or clone of the current repository before changing files.
2. Extract the contents of the release ZIP into the actual repository root. The root should directly contain `README.md`, `pyproject.toml`, `app/`, `tests/`, `tools/`, and `.github/`.
3. Confirm `.github/workflows/ci.yml` at the repository root is the updated workflow from this package. GitHub only discovers workflows in the repository's root `.github/workflows/` directory.
4. Commit `.github/workflows/ci.yml` and `tests/unit/test_ci_workflow.py` together. The workflow contract tests deliberately fail if one file is newer than the other; inspect the commit SHA shown in every Actions run to ensure GitHub actually tested the intended commit.
5. Review old files before removing them. The old `scripts/` layout should not be left as a second, conflicting implementation, but check the diff for unique work before deleting it. Do not rely on `.gitignore` to remove files that are already tracked.
6. From the repository root, run:

   ```bash
   python --version
   python -m app --help
   python -m app doctor
   python -m unittest discover -s tests/unit -t . -v
   python tools/check_public_release.py
   python -m pip wheel --no-deps --wheel-dir /tmp/hmsth-wheel .
   ```

7. Inspect `git status --short` and `git diff --cached` before committing. Do not commit private game files, local analysis output, private logs, or generated binaries.
8. Commit and push the reviewed change. Then open **Actions → CI** and inspect both Python matrix jobs. If a check fails, download its `ci-diagnostics-python-3.12` or `ci-diagnostics-python-3.13` artifact and use `docs/CI_DIAGNOSTICS.md` to find the matching log.

A successful local check is not a claim that the project is a playable port or a completed decompilation. It only validates the tooling and repository checks that were actually run.
