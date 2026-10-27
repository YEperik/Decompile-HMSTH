# Legal and public-release policy

This policy describes repository hygiene for an independent reverse-engineering research project. It is designed to avoid obvious distribution and platform-policy problems, but it cannot guarantee immunity from a copyright claim, takedown, or other legal dispute. It is not legal advice.

## Always exclude from public repository and releases

- Original game disc images, ROMs, executable dumps, firmware, BIOS files, console keys, save files, and full or partial copies of commercial game data.
- Extracted or repackaged game textures, models, maps, audio, video, dialogue, scripts, and other proprietary assets/data.
- Archives or patches containing original copyrighted material, even if the files have been renamed, compressed, split, or placed inside source archives.
- Credentials, API keys, personal data, private dumps, and logs that disclose sensitive local paths or material.
- Third-party binaries, proprietary dependencies, or language packs unless their distribution license clearly permits inclusion and the license/notice is retained. Prefer documented installation instructions instead.

The `.gitignore` and release checker provide guardrails only. They do not replace manual review, and files already tracked by Git remain tracked even after an ignore rule is added.

## Use local inputs responsibly

Use only files you are authorized to access. Obtain the target executable or other input from a lawful copy you control and keep it outside this public repository. Describe required input files by role and expected version; do not link to unauthorized downloads or tell readers where to find them. The project does not bundle or provide those inputs.

This policy does not make a blanket claim that every form of reverse engineering, extraction, or use is lawful in every jurisdiction or circumstance. Follow applicable law, license terms, platform rules, and the terms of the tools used.

## Keep technical work reproducible

- Prefer synthetic fixtures over real commercial samples in tests.
- Publish parser logic, project-authored scripts, tests, structural observations, and sufficiently abstract notes rather than extracted commercial bytes or assets.
- Clearly separate observed facts, inferences, assumptions, and unknowns.
- Record the input's target identity and hash in local reports; do not publish the input itself.
- Do not claim a binary match, gameplay compatibility, or hardware verification without a repeatable procedure and evidence.

## Brand and affiliation

Use the game title and serial only to identify the research target. Do not use publisher logos, game artwork, or official-looking branding in project artwork. State prominently that the project is unofficial and unaffiliated with the rights holders.

## Licenses and third parties

The repository's MIT license applies only to project-authored material that contributors are entitled to license. It does not grant rights to the commercial game, extracted material, trademarks, or third-party tools. Review and retain all third-party licenses separately.

## Before each public release

1. Run the complete test suite and the public-release checker.
2. Review every staged and tracked file, including nested ZIP/TAR archives, generated output, test fixtures, and binary diffs.
3. Run `git status --short` and `git diff --cached --stat`; inspect the full staged diff.
4. Confirm that no game code, game data, asset, BIOS, key, save, or local output is included.
5. Confirm that README target identity, status, known limitations, and release notes match the implementation.
6. Confirm that project and third-party notices are accurate.
7. If uncertain whether a file may be redistributed, keep it out until the rights and license are resolved.
