# Third-party notices and provenance register

This file records third-party components known to be relevant to the current public source archive. It is not a legal opinion and does not replace review of any future contribution or dependency.

## Components included in this repository

| Component | Included material | License / handling |
|---|---|---|
| Python standard library | Used by the Python workbench at runtime | Supplied with the selected Python distribution; no separate vendored copy is included |
| Ghidra | `app/ghidra_scripts/*.java` are workbench automation scripts that call Ghidra APIs; the Ghidra application and its binaries are not included | Install Ghidra separately from its official distribution and review the license for that exact release |
| JDK | Not bundled | Install separately and follow the selected distribution's license |
| PS2SDK / ps2dev | No PS2SDK source tree, headers, libraries, binaries, or copied license file are included in this archive | PS2SDK's upstream repository describes its license as Academic Free License 2.0. If future work incorporates PS2SDK code, retain upstream copyright and license notices, record exact source paths/revision, and review license compatibility before committing it. See the [upstream PS2SDK README](https://github.com/ps2dev/ps2sdk/blob/master/README.md) and [license file](https://github.com/ps2dev/ps2sdk/blob/master/LICENSE). |
| Target game | No game executable, disc image, BIOS, extracted game data, or commercial asset is included intentionally | The repository license does not grant rights to the game or associated intellectual property |

## License scope

The root `LICENSE` applies only to project-authored code and documentation that the contributors have the right to license under that license. It does not relicense third-party tools, their APIs, the target game, extracted game data, or materials from other projects. Do not add external code merely because it is publicly accessible. Before accepting third-party code, identify its exact source, version/commit, license, notice requirements, and compatibility with this repository's distribution model.

## Provenance rule for future contributions

For every newly introduced third-party source file, add a row to this register containing the source URL, exact revision or version, file paths, license, modifications, and notice requirements. When provenance cannot be established, keep the material out of the public repository until reviewed.

## Excluded historical material

A historical GUI source fixture was removed from the public test tree because the current CLI does not require it and its standalone source/license provenance was not needed for the tests. The current test suite validates history records against the current service using synthetic workspace artifacts instead. Reintroduce historical code only after confirming ownership, source origin, and license/notice requirements.
