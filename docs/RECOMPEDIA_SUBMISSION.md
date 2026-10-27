# Recompedia submission readiness

Reviewed against Recompedia's public [Submit a Project](https://recompedia.com/submit) and [About](https://recompedia.com/about) pages on 2026-10-27. Re-check the live pages immediately before submitting, as catalog rules can change.

## Published requirements relevant to this project

- The repository must be public and target one identifiable console game.
- The README or release notes must state the current project status.
- The repository must not distribute game code, ROMs/disc images, BIOS files, or game assets.
- For a decompilation listing, the target game version must be named and the repository must have a commit within the past 12 months.
- For a recompilation or source port, Recompedia asks for a tagged release or a README that states the game reaches its menus or gameplay. This repository currently makes no playable-build claim, so that criterion is not currently met.

Recompedia states that submissions can be sent with the public repository URL and, when needed, the target game version/region to `submit@recompedia.com`. Include the repository line that proves the version/region when making a correction. Do not send private game files.

## Current readiness assessment

| Check | Current state | Action before submission |
|---|---|---|
| One named target game | Documented | Keep the title consistent across README and `config/game.yaml` |
| Target platform and region | PS2, North America (USA) | Keep `SLUS_202.51` documented and do not imply other versions are supported |
| Status in README | In Progress | Update it from evidence after any meaningful milestone |
| No intentional game data/asset distribution | Policy, ignore rules, checker, and CI added | Manually inspect all tracked files, archives, and Git history before publishing |
| Public repository URL | Not available in this working copy | Publish a clean repository before contacting Recompedia |
| Recent commit | Cannot be verified from a ZIP file | Ensure the public repository has a recent real commit; do not fabricate history |
| Named decompilation progress | Not yet demonstrated as a game-wide decompilation | Provide a real game-specific decompilation milestone and reproducible evidence before claiming progress |
| Playable recompilation/source port | Not available | Do not submit or label it as playable; this project currently has no verified PC game build |
| Tagged release | Not available | Tag a release only when there is a meaningful reviewed release artifact; do not create an empty tag solely to imply playability |

## Important eligibility caveat

This repository currently provides reverse-engineering tooling and workflows; it does not yet demonstrate a completed game-specific source reconstruction or a playable PC implementation. Although the target and status are now documented, Recompedia may still decide that the repository does not yet qualify as a decompilation/recompilation project. The correct next step is to establish and document a genuine target-specific decompilation milestone, not to relabel the workbench as a completed game project.

## Pre-submission checklist

- [ ] Push this project to a public GitHub repository under the intended owner.
- [ ] Ensure the default branch contains the final README, status, and legal policy.
- [ ] Run `python -m unittest discover -s tests/unit -t . -v` on the default branch.
- [ ] Run `python tools/check_public_release.py` and manually review every flagged or archive-contained file.
- [ ] Inspect `git ls-files`, the full diff, releases, and repository history for original game data and extracted assets. Ignore rules alone do not remove already tracked files or old history.
- [ ] Confirm the current target serial and region using a lawful, locally available reference and keep claims limited to the tested version.
- [ ] Link to a real code/progress artifact if claiming decompilation progress; do not invent percentages or playable status.
- [ ] Review third-party tool licenses and this repository's license scope.
- [ ] Send only the public repository URL and target/version details to Recompedia. Never attach or link to game files.

## Suggested submission message

> Repository: `<public repository URL>`
>
> Target: _Harvest Moon: Save the Homeland_ (PlayStation 2, North America / USA, serial `SLUS_202.51`).
>
> Current status: In Progress. The repository contains reverse-engineering research tooling and synthetic tests only; it does not distribute game code, disc images, BIOS files, or original game assets. It does not currently claim a playable PC build. The target version and current limitations are documented in the README.
>
> Please let me know whether the current project scope qualifies for a listing or what additional target-specific evidence is needed.
