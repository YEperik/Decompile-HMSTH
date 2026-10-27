# Project status

**Status: In Progress.** Last reviewed for this release-preparation pass: 2026-10-27.

## Confirmed scope

This repository provides Python-based PS2 executable research tooling. It includes a command-line workspace, ELF inspection, symbol and relocation analysis, bounded exports, research drafts, selected Ghidra workflows, process-run records, and a unit-test suite.

## Experimental features intentionally excluded from this release

The source snapshot does not include the implementation modules for experimental guest-startup, VU/COP2 tracing, disc-ELF extraction, the Ghidra zero128 patch helper, or whole-program Ghidra export. Their CLI registrations have therefore been removed instead of advertising commands that cannot run. Reintroduce any of these only after the source is present, provenance/license review is complete, and synthetic tests exercise success, failure, cancellation, and input-boundary cases.

## Not yet established

The checked-in project does not contain evidence of a complete PC game implementation. It has no verified playable PC release, no release build that runs the game, no complete target-game asset pipeline, and no defensible whole-game decompilation percentage. These must not be inferred from the existence of analysis commands or from planned milestones.

## Target identity

- Game: Harvest Moon: Save the Homeland
- Platform: PlayStation 2
- Region: North America (USA)
- Serial: `SLUS_202.51`
- CPU research target: Emotion Engine / MIPS R5900

Other serials, regions, revisions, prototypes, or demos are not declared supported until separately tested and recorded.

## Evidence required to change status

- **Announced:** a concrete implementation is planned and described but has not been released.
- **In Progress:** active research or implementation exists, with its limitations documented.
- **Playable:** the project itself can be built and the target game can be played to a clearly defined point, supported by a reproducible setup guide and test evidence.
- **Complete / matching:** use only if the project defines a measurable completeness criterion and publishes the matching or compatibility evidence required by that criterion.

Do not use a status borrowed from a catalog or another project. Re-evaluate it from this repository's code, release artifacts, test evidence, and commit history.
