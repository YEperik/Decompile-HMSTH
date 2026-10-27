# Architecture

## Design intent

The workbench separates the user-facing CLI from use-case orchestration, binary/workspace rules, and operating-system integrations. It is a research tool, not the game's runtime.

## Layers

- `app/cli.py` parses commands and dispatches explicit use cases.
- `app/presentation.py` formats text and JSON output.
- `app/application/` coordinates workspaces, ELF analysis, symbols, relocations, drafts, Ghidra workflows, and reports.
- `app/domain/binary/` contains binary-format parsing and structural rules; `app/domain/workspace/` contains workspace model and validation.
- `app/infrastructure/persistence/` stores manifests and managed reports; `app/infrastructure/logging/` writes bounded, redacted run events; `app/infrastructure/process_runner/` provides the external-process boundary.
- `app/ghidra_scripts/` contains project-authored Ghidra automation scripts.
- `tests/` contains unit tests and synthetic, non-commercial fixtures.

## Data flow

1. The user explicitly selects a local input file.
2. The workspace records the path reference, size, and SHA-256 digest.
3. Read-only inspection validates the file's structural boundaries before analysis.
4. Selected operations create managed reports and research records in the workspace.
5. External commands are passed as argument arrays with timeout/output limits; the workbench does not use a shell command string for that boundary.
6. Verification compares recorded identity and outputs; it does not automatically prove semantic equivalence or original-hardware behavior.

## Trust boundaries

- A game executable, disc image, BIOS, extracted file, project workspace, and output from external tools are untrusted input.
- Do not run target game binaries as host executables.
- Only run external tools that you explicitly selected and trust. A timeout does not make an untrusted executable safe.
- Keep sensitive local paths and all private or proprietary data out of published logs, issues, CI artifacts, and release archives.
- Do not let a local workspace or exported artifact be mistaken for source-controlled project content.

## Current limitations

This architecture supports reproducible research records. It does not yet provide a general PS2 emulator, complete recompiler, full game engine, or complete decoders/rebuilders for every format listed in `config/formats.yaml`. See [Project Status](PROJECT_STATUS.md).
