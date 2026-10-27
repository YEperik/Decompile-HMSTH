#!/usr/bin/env python3
"""Conservative public-release hygiene checks for game-data leakage.

This is a heuristic guardrail, not a copyright, malware, or license scanner.
Unknown archive formats fail closed and require manual review or removal.
"""
from __future__ import annotations

import argparse
import io
import re
import tarfile
import zipfile
from pathlib import Path

DEFAULT_ROOT = Path(__file__).resolve().parents[1]
IGNORED_DIRS = {
    ".git", ".venv", "venv", "env", "__pycache__", ".pytest_cache",
    ".mypy_cache", ".ruff_cache",
}
PROTECTED_SUFFIXES = {
    ".iso", ".img", ".chd", ".cue", ".bin", ".elf", ".rom", ".ps2",
    ".sav", ".srm", ".mcr", ".hda", ".gdtb", ".rdtb", ".srdb", ".vag",
    ".dds", ".wav", ".mp3", ".ogg", ".flac", ".mp4", ".mkv", ".webm",
    ".png", ".jpg", ".jpeg", ".bmp", ".tga", ".obj", ".fbx", ".glb",
    ".gltf", ".pak", ".wad", ".bik", ".usm", ".sfd", ".pss", ".dat",
    ".exe", ".dll", ".so", ".dylib", ".o", ".a", ".lib", ".pdb",
}
SENSITIVE_BASENAME = re.compile(
    r"^(?:SLUS|SLES|SLPS|SLPM|SCUS|SCES|SCPS)[_-]?\d{3}[._-]\d{2}$",
    re.IGNORECASE,
)
ARCHIVE_SUFFIXES = {
    ".zip", ".tar", ".tgz", ".gz", ".bz2", ".xz", ".7z", ".rar", ".zst",
}
MAX_ARCHIVE_BYTES = 128 * 1024 * 1024
MAX_NESTING = 5
SIGNATURE_BYTES = 40 * 1024


def is_protected_name(name: str) -> bool:
    path = Path(name)
    return path.suffix.lower() in PROTECTED_SUFFIXES or bool(
        SENSITIVE_BASENAME.match(path.name)
    )


def protected_content_reason(data: bytes) -> str | None:
    """Return a reason for selected known binary signatures, if present."""
    if data.startswith(b"\x7fELF"):
        return "ELF executable/object signature"
    if data.startswith(b"MZ"):
        return "Windows executable signature"
    if data.startswith(b"\x89PNG\r\n\x1a\n"):
        return "PNG image signature"
    if data.startswith(b"\xff\xd8\xff"):
        return "JPEG image signature"
    if data.startswith((b"GIF87a", b"GIF89a")):
        return "GIF image signature"
    if data.startswith(b"DDS "):
        return "DDS texture signature"
    if data.startswith(b"RIFF") and len(data) >= 12 and data[8:12] in (b"WAVE", b"AVI "):
        return "RIFF audio/video signature"
    if data.startswith(b"OggS") or data.startswith(b"fLaC") or data.startswith(b"ID3"):
        return "compressed audio signature"
    if data.startswith(b"\x1aE\xdf\xa3"):
        return "EBML/WebM media signature"
    # ISO 9660 primary volume descriptor: type 1, CD001, version 1 at sector 16.
    if len(data) >= 0x8006 and data[0x8000:0x8006] == b"\x01CD001":
        return "ISO 9660 disc-image signature"
    return None


def _archive_kind(data: bytes) -> str | None:
    stream = io.BytesIO(data)
    if zipfile.is_zipfile(stream):
        return "zip"
    try:
        with tarfile.open(fileobj=io.BytesIO(data), mode="r:*"):
            return "tar"
    except (tarfile.TarError, OSError, EOFError):
        pass
    return None


def _looks_like_archive(data: bytes) -> bool:
    return data.startswith((
        b"PK\x03\x04", b"PK\x05\x06", b"PK\x07\x08",
        b"7z\xbc\xaf\x27\x1c", b"Rar!\x1a\x07", b"\x1f\x8b",
        b"BZh", b"\xfd7zXZ\x00", b"(\xb5/\xfd",
    )) or (len(data) >= 262 and data[257:262] == b"ustar")


def _read_member(stream, *, limit: int) -> bytes:
    return stream.read(limit + 1)


def _scan_archive_data(data: bytes, label: str, findings: list[str], depth: int = 0,
                       hinted_suffix: str = "") -> None:
    if depth > MAX_NESTING:
        findings.append(f"{label} :: archive nesting exceeds {MAX_NESTING} levels")
        return
    if len(data) > MAX_ARCHIVE_BYTES:
        findings.append(f"{label} :: archive exceeds automatic review limit ({MAX_ARCHIVE_BYTES} bytes)")
        return

    kind = _archive_kind(data)
    if kind == "zip":
        try:
            with zipfile.ZipFile(io.BytesIO(data)) as archive:
                for member in archive.infolist():
                    name = member.filename
                    member_label = f"{label} :: {name}"
                    if is_protected_name(name):
                        findings.append(member_label)
                    if member.is_dir():
                        continue
                    if member.file_size > MAX_ARCHIVE_BYTES:
                        if Path(name).suffix.lower() in ARCHIVE_SUFFIXES:
                            findings.append(f"{member_label} :: nested archive exceeds automatic review limit")
                        continue
                    with archive.open(member) as stream:
                        prefix = _read_member(stream, limit=SIGNATURE_BYTES)
                    reason = protected_content_reason(prefix)
                    if reason:
                        findings.append(f"{member_label} :: {reason}")
                    suffix = Path(name).suffix.lower()
                    nested_kind = _archive_kind(prefix) if len(prefix) <= MAX_ARCHIVE_BYTES else None
                    looks_nested = nested_kind is not None or _looks_like_archive(prefix) or suffix in ARCHIVE_SUFFIXES
                    if looks_nested:
                        if member.file_size > MAX_ARCHIVE_BYTES:
                            findings.append(f"{member_label} :: nested archive exceeds automatic review limit")
                        else:
                            with archive.open(member) as stream:
                                nested_data = stream.read(MAX_ARCHIVE_BYTES + 1)
                            if _archive_kind(nested_data) is not None:
                                _scan_archive_data(nested_data, member_label, findings, depth + 1, suffix)
                            elif suffix in {".7z", ".rar", ".zst", ".gz", ".bz2", ".xz"}:
                                findings.append(f"{member_label} :: unsupported or non-tar compressed archive; review manually or remove")
                            else:
                                findings.append(f"{member_label} :: archive-like payload could not be inspected")
        except (OSError, zipfile.BadZipFile, RuntimeError, ValueError) as exc:
            findings.append(f"{label} :: archive could not be reviewed ({exc})")
        return

    if kind == "tar":
        try:
            with tarfile.open(fileobj=io.BytesIO(data), mode="r:*") as archive:
                for member in archive.getmembers():
                    member_label = f"{label} :: {member.name}"
                    if is_protected_name(member.name):
                        findings.append(member_label)
                    if not member.isfile():
                        continue
                    extracted = archive.extractfile(member)
                    if extracted is None:
                        continue
                    with extracted:
                        prefix = _read_member(extracted, limit=SIGNATURE_BYTES)
                    reason = protected_content_reason(prefix)
                    if reason:
                        findings.append(f"{member_label} :: {reason}")
                    suffix = Path(member.name).suffix.lower()
                    nested_kind = _archive_kind(prefix)
                    if nested_kind is not None or _looks_like_archive(prefix) or suffix in ARCHIVE_SUFFIXES:
                        if member.size > MAX_ARCHIVE_BYTES:
                            findings.append(f"{member_label} :: nested archive exceeds automatic review limit")
                            continue
                        extracted = archive.extractfile(member)
                        if extracted is None:
                            continue
                        with extracted:
                            nested_data = extracted.read(MAX_ARCHIVE_BYTES + 1)
                        if _archive_kind(nested_data) is not None:
                            _scan_archive_data(nested_data, member_label, findings, depth + 1, suffix)
                        elif suffix in ARCHIVE_SUFFIXES:
                            findings.append(f"{member_label} :: unsupported or non-tar compressed archive; review manually or remove")
        except (OSError, tarfile.TarError, EOFError, ValueError) as exc:
            findings.append(f"{label} :: archive could not be reviewed ({exc})")
        return

    suffix = hinted_suffix.lower()
    if suffix in ARCHIVE_SUFFIXES or data.startswith((b"7z\xbc\xaf\x27\x1c", b"Rar!\x1a\x07")):
        findings.append(f"{label} :: unsupported archive format cannot be inspected automatically; review manually or remove")
        return
    reason = protected_content_reason(data[:SIGNATURE_BYTES])
    if reason:
        findings.append(f"{label} :: {reason}")


def scan_root(root: Path) -> list[str]:
    findings: list[str] = []
    root = root.resolve()
    for path in root.rglob("*"):
        try:
            relative = path.relative_to(root)
        except ValueError:
            continue
        if any(part in IGNORED_DIRS for part in relative.parts):
            continue
        if path.is_symlink() or not path.is_file():
            continue

        rel = str(relative)
        if is_protected_name(path.name):
            findings.append(rel)
            continue

        suffix = path.suffix.lower()
        archive_by_name = suffix in ARCHIVE_SUFFIXES or path.name.lower().endswith((".tar.gz", ".tar.bz2", ".tar.xz"))
        try:
            # File-format detection also catches common archives that were renamed.
            if archive_by_name or zipfile.is_zipfile(path) or tarfile.is_tarfile(path):
                size = path.stat().st_size
                if size > MAX_ARCHIVE_BYTES:
                    findings.append(f"{rel} :: archive exceeds automatic review limit ({MAX_ARCHIVE_BYTES} bytes)")
                    continue
                data = path.read_bytes()
                _scan_archive_data(data, rel, findings, hinted_suffix=suffix)
            else:
                with path.open("rb") as stream:
                    prefix = stream.read(SIGNATURE_BYTES)
                reason = protected_content_reason(prefix)
                if reason:
                    findings.append(f"{rel} :: {reason}")
        except (OSError, tarfile.TarError, zipfile.BadZipFile) as exc:
            findings.append(f"{rel} :: file could not be reviewed ({exc})")

    return sorted(set(findings))


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Check source-tree hygiene before public release")
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT,
                        help="Repository root to scan (defaults to this source tree)")
    args = parser.parse_args(argv)
    if not args.root.is_dir():
        parser.error(f"not a directory: {args.root}")

    findings = scan_root(args.root)
    if findings:
        print("Public-release check FAILED. Review/remove these files or archive entries:")
        for item in findings:
            print(f"  - {item}")
        print("The check is heuristic. Manually review the full repository and licenses before release.")
        return 1

    print("Public-release check passed: no protected names or selected binary signatures detected.")
    print("Unsupported archive formats and oversized archives fail closed; manual legal and license review remains required.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
