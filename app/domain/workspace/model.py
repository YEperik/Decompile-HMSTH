"""Strict schema v1; deliberately contains no filesystem or UI operations."""
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import PurePosixPath, PureWindowsPath
import json
import re
from uuid import UUID, uuid4


class WorkspaceError(Exception):
    code = "workspace_error"


class ValidationError(WorkspaceError):
    code = "invalid_manifest"


class UnsupportedSchema(ValidationError):
    code = "unsupported_schema"


class ConflictError(WorkspaceError):
    code = "conflict"


class PathError(WorkspaceError):
    code = "unsafe_path"


def now():
    return datetime.now(timezone.utc).isoformat()


def require(condition, message):
    if not condition:
        raise ValidationError(message)


def identifier(value):
    require(isinstance(value, str), "ID harus berupa UUID string.")
    try:
        require(str(UUID(value)) == value, "ID UUID tidak kanonik.")
    except (ValueError, AttributeError) as exc:
        raise ValidationError("ID UUID invalid.") from exc


def unicode_text(value):
    require(isinstance(value, str), "Nilai harus string.")
    try:
        value.encode("utf-8")
    except UnicodeError as exc:
        raise ValidationError("String mengandung Unicode invalid.") from exc


def timestamp(value):
    require(isinstance(value, str), "Timestamp harus string ISO-8601 UTC.")
    try:
        parsed = datetime.fromisoformat(value)
        require(parsed.utcoffset() is not None and parsed.utcoffset().total_seconds() == 0,
                "Timestamp harus UTC.")
        return parsed
    except ValueError as exc:
        raise ValidationError("Timestamp invalid.") from exc


def validate(data):
    require(type(data) is dict, "Manifest harus object JSON.")
    version = data.get("schema_version")
    require(type(version) is int, "schema_version harus integer.")
    if version != 1:
        raise UnsupportedSchema(f"Schema {version} tidak didukung; file tidak diubah.")
    keys = {"schema_version", "workspace_id", "revision", "name", "created_at",
            "updated_at", "inputs", "build_profiles", "integrations", "status"}
    require(set(data) == keys, "Field manifest kurang atau tidak dikenal.")
    identifier(data["workspace_id"])
    require(type(data["revision"]) is int and data["revision"] >= 0, "Revision invalid.")
    name = data["name"]
    unicode_text(name)
    require(isinstance(name, str) and bool(name.strip()) and len(name) <= 160
            and not any(ord(c) < 32 for c in name), "Nama harus 1–160 karakter tanpa kontrol.")
    require(timestamp(data["updated_at"]) >= timestamp(data["created_at"]),
            "updated_at sebelum created_at.")
    require(data["status"] == "configured", "Status belum didukung.")
    require(data["build_profiles"] == [] and type(data["build_profiles"]) is list,
            "Profil build belum didukung Tahap 1A.")
    require(data["integrations"] == {} and type(data["integrations"]) is dict,
            "Integrasi belum didukung Tahap 1A.")
    require(type(data["inputs"]) is list and len(data["inputs"]) <= 1000, "Daftar input invalid.")
    ids = set()
    for item in data["inputs"]:
        require(type(item) is dict and set(item) == {
            "id", "path_kind", "path", "sha256", "size_bytes", "registered_at", "validation"},
            "Record input invalid.")
        identifier(item["id"])
        require(item["id"] not in ids, "ID input duplikat.")
        ids.add(item["id"])
        path = item["path"]
        unicode_text(path)
        require(isinstance(path, str) and 0 < len(path) <= 4096 and "\0" not in path,
                "Path input invalid.")
        kind = item["path_kind"]
        require(kind in ("absolute", "workspace_relative"), "Jenis path invalid.")
        if kind == "workspace_relative":
            p = PurePosixPath(path)
            require(not p.is_absolute() and ".." not in p.parts and "\\" not in path
                    and len(p.parts) >= 2 and p.parts[0] == "inputs"
                    and p.as_posix() == path and not PureWindowsPath(path).drive,
                    "Input relatif harus berada di inputs/ tanpa traversal.")
        else:
            require(PurePosixPath(path).is_absolute() or PureWindowsPath(path).is_absolute(),
                    "Path absolute tidak absolut.")
        require(isinstance(item["sha256"], str) and
                re.fullmatch(r"[0-9a-f]{64}", item["sha256"]) is not None, "SHA-256 invalid.")
        require(type(item["size_bytes"]) is int and item["size_bytes"] >= 0, "Ukuran invalid.")
        timestamp(item["registered_at"])
        require(item["validation"] == "format_unchecked", "Validasi ELF belum didukung.")
    return data


def _unique_pairs(pairs):
    result = {}
    for key, value in pairs:
        require(key not in result, f"Field JSON duplikat: {key}")
        result[key] = value
    return result


def decode(raw):
    try:
        return validate(json.loads(raw.decode("utf-8"), object_pairs_hook=_unique_pairs))
    except (UnicodeError, ValueError, RecursionError) as exc:
        raise ValidationError("Manifest bukan JSON UTF-8 valid.") from exc


def encode(data):
    validate(data)
    return (json.dumps(data, ensure_ascii=False, indent=2, allow_nan=False) + "\n").encode("utf-8")


def new_workspace(name):
    date = now()
    return validate(dict(schema_version=1, workspace_id=str(uuid4()), revision=0,
                         name=name, created_at=date, updated_at=date, inputs=[],
                         build_profiles=[], integrations={}, status="configured"))


@dataclass(frozen=True)
class Snapshot:
    data: dict
    token: str  # SHA-256 of exact manifest bytes; guards same-revision edits too.
