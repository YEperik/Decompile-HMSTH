<div align="center">

# Harvest Moon: Save the Homeland — Recompilation Research

**An independent community research project exploring PlayStation 2 recompilation and native PC execution.**

<br>

[![Project Status](https://img.shields.io/badge/status-experimental-orange)](#project-status)
[![Platform](https://img.shields.io/badge/target-Windows-blue)](#target-environment)
[![Build System](https://img.shields.io/badge/build-CMake-064F8C)](#building)
[![Language](https://img.shields.io/badge/language-C%2B%2B-00599C)](#)
[![Project Type](https://img.shields.io/badge/type-community%20research-lightgrey)](#about)

</div>

<p align="center">
  <img src="https://placehold.co/1400x420/111827/e5e7eb?text=HARVEST+MOON%3A+SAVE+THE+HOMELAND" alt="Harvest Moon: Save the Homeland — Recompilation Research">
</p>

---

## About

**Harvest Moon: Save the Homeland — Recompilation Research** is an independent, fan-made research project investigating the technical feasibility of recompiling the PlayStation 2 version of *Harvest Moon: Save the Homeland* and executing the resulting code within a modern PC environment.

The project is primarily intended as a technical experiment and learning exercise surrounding:

- PlayStation 2 recompilation
- Reverse engineering research
- Decompiled and recompiled game code
- Runtime compatibility
- Platform abstraction
- Native PC execution
- Build-system modernization
- Software preservation and analysis

The project does **not** represent an official PC port, remake, remaster, or commercial product.

There is no guarantee that the research will ultimately result in a fully playable PC version.

---

## Project Status

**Experimental / Research**

This repository should be considered an ongoing technical investigation rather than a finished software product.

The primary objective is to determine how far the recompilation process can be taken and what technical work is required to execute the resulting code outside of its original PlayStation 2 environment.

| Area | Status |
|---|:---:|
| Project infrastructure | In progress |
| Recompiled source integration | In progress |
| Build system | In progress |
| PC executable research | In progress |
| Runtime compatibility | Research |
| Rendering | Research |
| Input | Research |
| Audio | Research |
| File system | Research |
| Save compatibility | Not started |
| Widescreen support | Not started |
| Resolution scaling | Not started |
| Controller support | Not started |
| Linux support | Not started |

Project status will only be marked complete when functionality has been verified.

---

## Research Objectives

The project is organized around several technical questions:

1. Can the available PlayStation 2 recompiled code be built reliably with a modern PC toolchain?
2. What platform-specific functionality must be reproduced or abstracted?
3. Can the original runtime behavior be preserved outside the PS2 environment?
4. Which components can be mapped directly to modern PC systems?
5. Which systems require compatibility implementations?
6. What changes are necessary before the recompiled program can execute reliably?
7. Which optional PC improvements can be introduced without unnecessarily altering the original behavior?

The project intentionally separates **research required for execution** from **optional PC enhancements**.

---

## Technical Scope

The initial scope is focused on the original PlayStation 2 software and its recompiled representation.

```text
Original PS2 Software
        |
        v
Recompilation / Analysis
        |
        v
Recompiled Code
        |
        v
Platform Compatibility
        |
        v
PC Runtime
        |
        v
Native PC Execution
```

The intended architecture is to keep recompiled game logic as independent as practical from platform-specific PC implementations.

```text
                 Recompiled Game Code
                          |
                          v
              +-----------------------+
              | Compatibility Layer   |
              +-----------------------+
                          |
          +---------------+---------------+
          |               |               |
          v               v               v
      Rendering         Input           Audio
          |               |               |
          +---------------+---------------+
                          |
                          v
                 PC Platform Layer
                          |
                          v
                  Native Executable
```

This structure is subject to change as technical findings are made during development.

---

## Target Environment

The initial development target is:

| Component | Target |
|---|---|
| Operating System | Windows |
| Architecture | x64 |
| Compiler | MSVC / Visual Studio |
| Build System | CMake |
| Language | C / C++ |
| Development Model | Native PC |

Other platforms may be investigated in the future if the core research reaches a sufficiently stable state.

---

## Building

### Requirements

The initial development environment is expected to include:

- Windows 10 or later
- Git
- CMake
- Visual Studio 2022
- Windows SDK
- Python 3.x where required by project tooling
- The appropriate PS2 recompilation toolchain
- Legally obtained game data where required

Exact tool versions will be documented as the build process becomes reproducible.

### Clone

```bash
git clone --recursive https://github.com/YOUR_USERNAME/harvest-moon-save-the-homeland-recompilation-research.git

cd harvest-moon-save-the-homeland-recompilation-research
```

### Configure

```bash
cmake -B build -S .
```

### Build

```bash
cmake --build build --config Release
```

Detailed build documentation will be maintained under:

```text
docs/
├── BUILDING.md
├── DEVELOPMENT.md
├── RECOMPILATION.md
└── TROUBLESHOOTING.md
```

> Build instructions are expected to evolve during the research phase.

---

## Repository Structure

```text
harvest-moon-save-the-homeland-recompilation-research/
│
├── .github/
│   ├── workflows/
│   │   └── build.yml
│   ├── ISSUE_TEMPLATE/
│   └── pull_request_template.md
│
├── config/
│   └── Project configuration
│
├── docs/
│   ├── BUILDING.md
│   ├── DEVELOPMENT.md
│   ├── RECOMPILATION.md
│   └── TROUBLESHOOTING.md
│
├── include/
│   └── Project headers
│
├── src/
│   └── Recompiled / project source
│
├── patches/
│   └── Research and compatibility patches
│
├── scripts/
│   └── Build and development scripts
│
├── tools/
│   └── Development utilities
│
├── third_party/
│   └── External dependencies
│
├── CMakeLists.txt
├── LICENSE
├── README.md
└── .gitignore
```

---

## Development Roadmap

### Phase 0 — Research Setup

- [ ] Establish repository structure
- [ ] Document the recompilation environment
- [ ] Identify required dependencies
- [ ] Document source provenance
- [ ] Establish reproducible build procedures

### Phase 1 — Recompiled Code

- [ ] Integrate recompiled source
- [ ] Configure compiler environment
- [ ] Resolve compilation issues
- [ ] Resolve generated-code dependencies
- [ ] Produce an initial executable

### Phase 2 — Platform Compatibility

- [ ] Identify PS2-specific runtime dependencies
- [ ] Implement required compatibility interfaces
- [ ] Establish memory/runtime behavior
- [ ] Initialize filesystem functionality
- [ ] Initialize rendering
- [ ] Initialize input
- [ ] Initialize audio

### Phase 3 — Execution Research

- [ ] Launch executable
- [ ] Reach initialization sequence
- [ ] Reach main menu
- [ ] Investigate game startup
- [ ] Investigate scene loading
- [ ] Investigate core gameplay systems
- [ ] Investigate save/load behavior

### Phase 4 — Optional PC Improvements

Only after the core execution research is sufficiently stable:

- [ ] Keyboard support
- [ ] Controller support
- [ ] Configurable resolution
- [ ] Widescreen support
- [ ] Windowed / fullscreen modes
- [ ] Configuration file
- [ ] Improved diagnostics

### Phase 5 — Stability

- [ ] Automated builds
- [ ] Regression testing
- [ ] Crash diagnostics
- [ ] Performance profiling
- [ ] Documentation cleanup
- [ ] Reproducible release builds

---

## Screenshots & Demonstrations

Screenshots, technical findings, and development demonstrations will be added as meaningful milestones are reached.

At this stage, the project should be considered a work in progress.

```text
No public build available yet.
```

---

## Contributing

This is a community research project, and technical contributions are welcome.

Useful contributions may include:

- Recompilation research
- Reverse-engineering documentation
- Runtime compatibility work
- Build-system improvements
- Debugging
- Testing
- Documentation
- Tooling
- Reproducibility improvements

### Contribution Guidelines

Before submitting a pull request:

1. Keep changes focused.
2. Explain the technical reason for the change.
3. Avoid committing generated build artifacts.
4. Do not commit proprietary game assets or game dumps.
5. Verify that the project still builds when practical.
6. Include reproduction information for bug fixes.
7. Document significant changes to the architecture or build process.

Suggested branch naming:

```text
feature/<name>
fix/<name>
research/<name>
refactor/<name>
docs/<name>
tooling/<name>
```

---

## Issue Reporting

When opening an issue, please provide reproducible technical information whenever possible.

Recommended information:

```text
Operating System:
CPU:
GPU:
Compiler:
CMake Version:
Project Commit:
Build Configuration:

Steps to Reproduce:

Expected Behavior:

Actual Behavior:

Logs / Crash Information:
```

Research findings that help identify undocumented behavior are also welcome.

---

## Legal & Intellectual Property

**Harvest Moon: Save the Homeland** and all associated intellectual property are owned by their respective rights holders.

This project is an **unofficial, independent, fan-made community project**.

It is:

- Not affiliated with the original developers.
- Not affiliated with the original publishers.
- Not endorsed by the rights holders.
- Not a commercial product.
- Not an official PC release.
- Not intended to replace the original game.

This repository does not intentionally distribute original proprietary game assets or commercially distributed game data, including:

- Game ISO images
- Disc images
- Original executable distributions
- Original textures
- Original models
- Original audio
- Original movies
- Proprietary game archives
- Other copyrighted game content

Where external game data is required for research or execution, users are responsible for obtaining and using that data lawfully.

Nothing in this repository should be interpreted as a claim of ownership over the original game's intellectual property.

---

## Relationship to the Original Game

This project exists independently of the original commercial release.

The purpose is to study and experiment with the technical process of recompilation and execution of legacy PlayStation 2 software in a modern development environment.

The project does not attempt to recreate the original intellectual property from scratch.

Where technically possible, the research aims to preserve the behavior of the original software rather than redesign its underlying game systems.

---

## Project Philosophy

The project follows a simple principle:

```text
Research first.
Reproduce second.
Understand the runtime.
Improve only when appropriate.
```

The primary value of the project is the technical knowledge gained during the process.

A fully playable PC build is a possible outcome of the research, but it is **not assumed or promised**.

---

## Acknowledgements

This project builds upon the broader community effort surrounding PlayStation 2 reverse engineering, recompilation, software preservation, and low-level game research.

Specific upstream projects, tools, libraries, and contributors will be credited here as their relationship to the project is established.

---

## Disclaimer

This is an experimental community project.

The repository may contain incomplete, unstable, or research-oriented code. Nothing here should be considered a finished product or an official release.

The project may be discontinued, substantially redesigned, or redirected depending on technical findings.

---

<div align="center">

### Harvest Moon: Save the Homeland — Recompilation Research

**Independent • Community-driven • Experimental**

Researching the technical feasibility of bringing recompiled PS2 software into a modern PC environment.

</div>
