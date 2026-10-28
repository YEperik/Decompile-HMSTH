# HMSTH-PC — Decomp

**An independent decompilation-research and tooling project for _Harvest Moon: Save the Homeland_ (PlayStation 2, North American release).**

> **Status: In Progress — research tooling only.** This repository does not currently provide a verified, playable PC build or a completed matching decompilation. The long-term goal is to investigate whether a clean PC implementation is feasible; that goal is not a claim of completion.

[Recompedia submission requirements](https://recompedia.com/submit) · [Project policy](docs/LEGAL_AND_RELEASE_POLICY.md) · [Architecture](docs/ARCHITECTURE.md) · [Verification guide](docs/VERIFICATION.md) · [CI diagnostics](docs/CI_DIAGNOSTICS.md) · [GitHub migration guide](MIGRATION_TO_GITHUB.md) · [Roadmap](ROADMAP.md)

## At a glance

| Item | Current information |
|---|---|
| Target game | Harvest Moon: Save the Homeland |
| Platform / region | PlayStation 2 / North America (USA) |
| Target serial | `SLUS_202.51` |
| CPU research target | Emotion Engine, MIPS R5900 |
| Project type today | Decompilation / reverse-engineering workbench and research tooling |
| Project status | In Progress; not a playable game release |
| Runtime requirements | Python 3.12+; external analysis tools are optional |
| Game files in this repository | None intentionally included |
| Original assets / BIOS / disc images | Not distributed; supply permitted local inputs yourself |

The target serial is also identified as the USA release in public PS2 compatibility references and in existing HMSTH research tooling. See [References](#references). This repository's configured target does not imply that other regions or revisions are already supported.

## What this project does

The current codebase is a modular CLI workbench for studying user-supplied PS2 executable files and recording reverse-engineering work. Its implemented areas include:

- **Workspace and input integrity:** create and validate research workspaces, register input files by reference, and verify recorded hashes.
- **ELF inspection:** inspect ELF metadata, sections, segments, and symbols without executing the target file.
- **Symbol and byte-range analysis:** inventory symbols, inspect function ranges, and export bounded evidence for further analysis.
- **Relocation research:** inspect references and produce non-destructive previews for selected MIPS relocation cases.
- **Ghidra integration:** check a local Ghidra installation and R5900 language assets, prepare analysis plans, and run explicitly selected analysis workflows.
- **Research records:** preserve drafts, analysis materials, comparisons, work history, and verification reports in a workspace.
- **Safety checks:** hash inputs, constrain output paths, bound external process execution, and keep the target game executable as data rather than running it as a host program.

The supported command surface is available from `python -m app --help`; use `python -m app --help-all` for every command and its description. Experimental VU/COP2 tracing and guest-startup commands are intentionally not exposed in this release because their implementation modules are not present in this source snapshot. A command's existence does not mean that every PS2 file format has been decoded or that any result is semantically or hardware verified.

## What this project does not claim

- It is **not currently a playable PC port, recompilation, or finished decompilation**.
- It does not claim full gameplay, a complete asset pipeline, matching recompilation progress, or compatibility with all regional revisions.
- It does not include the commercial game executable, disc image, BIOS, extracted textures, models, sound, dialogue, maps, save files, or other original game data.
- It does not provide links to unofficial downloads of game files, BIOS files, or copyrighted assets.
- It does not bypass DRM, console security, or access controls. No such bypass is an objective of this repository.

Format names in `config/formats.yaml` are **research targets**, not a statement that complete parsers or repackers for those formats are already implemented.

## Quick start

### 1. Requirements

- Python **3.12 or newer**.
- A terminal (Windows PowerShell, Windows Terminal, Linux shell, or macOS Terminal).
- Optional: a separately installed Ghidra distribution with an appropriate MIPS R5900 language definition and a compatible JDK, if you want to use Ghidra workflows.

No third-party Python runtime dependency is required for the basic CLI and unit tests. This release is a Python-only research workbench; it does not ship a native Windows runtime or an experimental PS2 runtime implementation.

### 2. Run from a source checkout

```bash
python --version
python -m app --help
python -m app doctor
python -m unittest discover -s tests/unit -t . -v
python tools/check_public_release.py
```

On Windows, use `py -3.12 -m app --help` if `python` points at a different interpreter.

### 3. Optional local installation

```bash
python -m pip install .
ps2-workbench --help
```

Use a virtual environment for an isolated installation. The workbench can inspect synthetic ELF fixtures without a game disc; target-game analysis should use only input files you are authorized to access.

## Typical research workflow

The following is a workflow outline; exact options are shown by `--help` for each command.

1. **Create a workspace** to keep one investigation's metadata and evidence together.
2. **Register an input** by path. The workbench records its identity and hash so later steps can detect changes.
3. **Inspect the ELF** and record a structural baseline before interpreting symbols or instruction ranges.
4. **Audit Ghidra and the R5900 language definition** before generating an analysis plan or running a decompilation task.
5. **Create an evidence-backed draft** for a bounded function or data range. Keep observed bytes, tool output, interpretation, and assumptions distinguishable.
6. **Verify every claim** against a reproducible input hash and report. Static output alone is not proof of correct game behavior.
7. **Publish only project-authored code, documentation, and permissible research notes**. Keep original game data and local exports outside the public repository.

For data model details, process execution guarantees, and limitations, read [Architecture](docs/ARCHITECTURE.md) and [Verification](docs/VERIFICATION.md).

## Repository structure

```text
app/
  application/       Use cases and orchestration
  domain/            Binary and workspace models
  infrastructure/    Persistence, logging, and process runner
  ghidra_scripts/    Project automation scripts for an external Ghidra install
  cli.py             Command-line interface
  presentation.py    Human-readable and JSON output
config/              Target, format, and build metadata
docs/                Project, legal, architecture, and verification guides
tests/               Unit tests and synthetic fixtures
tools/               Release-hygiene checks
.github/workflows/   Automated test and release-hygiene checks
```

## Quality and release verification

Every proposed public release should pass all of the following locally and in CI:

```bash
python -m unittest discover -s tests/unit -t . -v
python tools/check_public_release.py
python -m app --help
```

The automated release check rejects common game-dump and proprietary-asset extensions, including those inside archives. It is a guardrail, not a legal determination or a perfect detector; maintainers must still manually review the complete diff, archives, test fixtures, release artifacts, and commit history before publishing.

GitHub Actions runs compile checks, tests, wheel build/install smoke tests, and release hygiene on supported Python versions. Each run writes a summary and uploads diagnostics when available. See [CI Diagnostics](docs/CI_DIAGNOSTICS.md) when a check fails and [Verification](docs/VERIFICATION.md) for the meaning of a passing test and known gaps.

## Contributing

Start with [CONTRIBUTING.md](CONTRIBUTING.md), then open an issue describing the question, target input/version, evidence, expected result, and actual result. Do not submit dumps, extracted commercial data, or private files in an issue or pull request. Synthetic fixtures are preferred. See [Security](SECURITY.md) for responsible reporting.

Reverse-engineering results should label:

- **Observed:** directly supported by bytes, tool output, or a repeatable experiment.
- **Inferred:** a reasoned interpretation with its evidence and confidence noted.
- **Unverified:** plausible but not yet confirmed.

Do not report guesses as confirmed findings. Do not describe a feature as complete without a reproducible test or clearly stated limitation.

## Project status and roadmap

The work is actively scoped as research tooling. Current functionality and limitations are documented in [Project Status](docs/PROJECT_STATUS.md); planned milestones are in [ROADMAP.md](ROADMAP.md). A playable release, full decompilation percentage, and PC gameplay support will only be announced when backed by evidence and a published verification procedure.

## Legal and intellectual-property notice

This is an independent, unofficial research project and is not affiliated with or endorsed by Natsume, Victor Interactive Software, TOYBOX, Sony, or their partners. _Harvest Moon: Save the Homeland_ and related marks and original game materials belong to their respective rights holders. Use of a game title and serial is solely to identify the research target.

The repository's MIT license applies to project-authored code and documentation to the extent that the contributors have the rights to license them. It does **not** grant rights to the original game, third-party tools, third-party files, or extracted game data. See [NOTICE.md](NOTICE.md), [Third-Party Notices](THIRD_PARTY_NOTICES.md), and [Legal and Release Policy](docs/LEGAL_AND_RELEASE_POLICY.md). Compliance measures reduce avoidable risk but cannot guarantee that a platform or rights holder will never raise a complaint. This documentation is not legal advice.

## AI assistance disclosure

AI assistance was used to help revise documentation, repository hygiene, and the packaging/test setup. Reverse-engineering conclusions, compatibility claims, and future feature claims must be independently reviewed and supported by reproducible evidence; this disclosure is not a substitute for that review.

## References

- [Recompedia — Submit a Project](https://recompedia.com/submit): public repository, clear target/status, and no distributed game code or assets.
- [Recompedia — About](https://recompedia.com/about): project status conventions and requirements for decompilation listings.
- [HMSTHModdingTool research notes](https://github.com/DarthKrayt333/HMSTHModdingTool): community reference identifying `SLUS_202.51` as the USA executable; not a dependency of this workbench.
- [HDATextTool](https://github.com/gdkchan/HDATextTool): related public research for HMSTH file formats; not bundled here.
- [decomp-toolkit project template](https://github.com/encounter/dtk-template): an example of a documented decompilation workflow and progress tooling; this project does not currently use decomp-toolkit.
