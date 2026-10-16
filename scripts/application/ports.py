"""Persistence contract; application/domain do not depend on the file-store adapter."""
from pathlib import Path
from typing import Protocol
from app.domain.workspace.model import Snapshot


class WorkspaceRepository(Protocol):
    root: Path

    def create(self, name: str) -> Snapshot: ...
    def load(self) -> Snapshot: ...
    def save(self, snapshot: Snapshot, proposed: dict) -> Snapshot: ...
