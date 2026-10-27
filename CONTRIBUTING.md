# Contributing

Thanks for helping improve the HMSTH-PC reverse-engineering workbench. Contributions should improve reproducibility, correctness, documentation, or tooling without redistributing commercial game material.

## Before opening a pull request

1. Explain the question or bug and identify the tested input type/version. Never attach a disc image, game executable dump, BIOS, extracted game data, save file, or copyrighted asset.
2. Add or update synthetic tests for changed behavior.
3. Keep observed facts separate from interpretation; include the evidence and any unresolved assumptions.
4. Run:

   ```bash
   python -m unittest discover -s tests/unit -t . -v
   python tools/check_public_release.py
   python -m app --help
   ```

5. Review the complete diff and verify no local outputs, logs, private paths, or proprietary data are staged.

## Code expectations

- Use Python 3.12+ and the standard library where practical.
- Keep CLI parsing, application use cases, domain rules, infrastructure, and presentation separate.
- Prefer small functions with explicit inputs/outputs and clear validation.
- Do not execute a target game binary. External analysis tools must be invoked explicitly with bounded execution and output.
- Avoid claiming semantic correctness based solely on a successful parse or process exit.

## Research quality labels

- **Observed:** directly backed by a repeatable experiment or source/tool output.
- **Inferred:** a reasoned explanation supported by identified evidence.
- **Unverified:** a hypothesis needing additional testing.

AI-assisted contributions are allowed but must be reviewed by a human maintainer. Do not present generated explanations as confirmed reverse-engineering findings without independent validation.

## Licensing

By contributing, you confirm that you have the right to submit the contribution under the repository's MIT license. Do not contribute third-party code or artifacts without confirming license compatibility and retaining required notices.
