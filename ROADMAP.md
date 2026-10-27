# Roadmap

Milestones describe planned research; they are not claims that a feature is implemented. Progress should be updated only with reproducible evidence and linked tests or reports.

## M0 — Repository and reproducibility
- [x] Establish Python package structure and command entry point
- [x] Document status, target identity, architecture, and redistribution policy
- [x] Add unit-test and release-hygiene CI
- [ ] Publish a public repository and confirm its default branch/commit metadata

## M1 — Input identity and executable structure
- [x] Workspace and input hash tracking
- [x] Read-only ELF inspection and structural baseline
- [ ] Document known USA executable fingerprints from an authorized local input without publishing the executable
- [ ] Define a reviewed evidence format for each research finding

## M2 — Static analysis and decompilation workflow
- [x] Symbol inventory and bounded function export workflow
- [x] Initial relocation reference and preview workflows
- [x] Ghidra installation/language checks and analysis plan
- [ ] Validate R5900 language settings against known synthetic fixtures
- [ ] Record manual review criteria for Ghidra output and false positives
- [ ] Establish a repeatable function-level comparison workflow

## M3 — Game-format research
- [ ] Document HDA container structure with abstract diagrams and synthetic fixtures
- [ ] Research GDTB texture metadata without publishing extracted textures/palettes
- [ ] Research RDTB/SRDB model and scene structures without publishing extracted models/maps
- [ ] Research HD/BD/SQ and text-related formats with clear evidence and compatibility limits
- [ ] Add format parsers only when input bounds and negative tests are defined

## M4 — Feasibility and implementation direction
- [ ] Document system boundaries and behavior from reproducible experiments
- [ ] Evaluate whether a clean PC implementation or a true decompilation is the viable route
- [ ] Define measurable milestones before claiming PC gameplay support

## M5 — Release quality
- [ ] Create a tagged tooling release after test and repository-policy review
- [ ] Publish input requirements without distributing or linking to game files
- [ ] Reassess project status only when a reproducible build/playability milestone is demonstrated
