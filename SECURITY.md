# Security policy

## Scope

Security reports may cover unsafe path handling, workspace integrity, unintended external process execution, secret disclosure in logs, unbounded resource use, or vulnerabilities in the workbench itself.

## Reporting

Do not publish credentials, private data, game dumps, BIOS files, console keys, proprietary game assets, or a weaponized proof of concept in a public issue.

This repository does not publish a verified private security contact. First check whether the hosting repository has private vulnerability reporting enabled. If it does not, submit only a non-sensitive summary requesting a private reporting channel; do not post exploit details or sensitive reproduction data publicly.

When using an approved private channel, include the affected commit/version, Python version, operating system, minimal reproduction using synthetic input, expected behavior, actual behavior, and relevant redacted logs.

## Responsible use

The tool is for offline research on explicitly selected local inputs. Do not use it to access systems or files without authorization. Keep external tools and their dependencies updated, and do not assume that a timeout or parser validation makes an untrusted input or executable harmless.
