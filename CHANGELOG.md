# Changelog

Changes are recorded by release. Unreleased work should be described in the pull request or commit history until a tagged release exists.

## Unreleased

- Corrected the Python package layout so the `app` module used by the CLI and test suite is present in the repository.
- Added package metadata and the `ps2-workbench` command entry point.
- Expanded project documentation with explicit status, target revision, architecture, verification limits, release hygiene, and legal/redistribution policy.
- Added a public-release hygiene checker and CI workflow.
- Removed cached Python bytecode from the public source tree and replaced the project `.gitignore` with clean, relevant ignore rules.
- Removed experimental CLI commands whose implementation modules are absent from this source snapshot, rather than exposing commands that fail at runtime.
- Removed unverified experimental C runtime headers with incomplete include dependencies and added a third-party provenance register, including explicit PS2SDK handling guidance.
- Updated CLI help output and release checks to reflect the supported tool surface and inspect selected file signatures/archive entries.
- Modernized package license metadata to SPDX format and added wheel-build, isolated-install, and installed-CLI smoke checks to CI.
- Fixed the CI root-layout failure reported by GitHub Actions: the workflow now discovers the package root before invoking `app`, handles accidental nested extraction, and records concise step outcomes.
- Added bounded test execution, compile checks, isolated virtual-environment installation, diagnostic log artifacts, and a workflow summary that remains available when validation fails.
- Added CI troubleshooting documentation and a structured feature-request issue form with game-data safety checks.
- Removed the unused historical GUI source fixture with unneeded provenance; CLI history behavior is now tested directly against the current service and synthetic artifacts.
- Renamed the test-only task controller helper to avoid implying it vendors a legacy GUI implementation.
