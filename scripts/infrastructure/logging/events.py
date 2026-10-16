"""Small per-run JSONL log; no global environment dump or unlimited stream logging."""
import json
import os
import re
from app.domain.workspace.model import now
from app.infrastructure.persistence.store import regular


class Redactor:
    def __init__(self, secrets=()):
        self.secrets = sorted((s for s in secrets if isinstance(s, str) and s), key=len, reverse=True)

    def text(self, text):
        for secret in self.secrets:
            text = text.replace(secret, "[REDACTED]")
        # Best effort only: callers must supply exact known secrets for reliable redaction.
        return re.sub(r'(?i)((?:password|token|api[_-]?key|authorization)\s*[:=]\s*)[^\s,;]+',
                      r'\1[REDACTED]', text)

    def value(self, value):
        if isinstance(value, str):
            return self.text(value)
        if isinstance(value, dict):
            return {k: self.value(v) for k, v in value.items()}
        if isinstance(value, (list, tuple)):
            return [self.value(v) for v in value]
        return value

    def argv(self, argv):
        result = []
        hide_next = False
        for arg in argv:
            result.append("[REDACTED]" if hide_next else self.text(arg))
            hide_next = arg.lower().lstrip('-') in {"password", "token", "api-key", "api_key", "authorization"}
        return result


class EventLog:
    def __init__(self, path, run_id, redactor):
        self.path, self.run_id, self.redactor = path, run_id, redactor

    def emit(self, event, **fields):
        row = self.redactor.value(dict(timestamp=now(), run_id=self.run_id, event=event, **fields))
        raw = (json.dumps(row, ensure_ascii=False) + "\n").encode("utf-8")
        regular(self.path)
        fd = os.open(self.path, os.O_WRONLY | os.O_CREAT | os.O_APPEND | getattr(os, 'O_NOFOLLOW', 0), 0o600)
        with os.fdopen(fd, "ab") as stream:
            stream.write(raw)
            stream.flush()
            os.fsync(stream.fileno())
