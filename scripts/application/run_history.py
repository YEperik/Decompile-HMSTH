"""Read existing run artifacts without a GUI, mutation or tool execution."""
from uuid import UUID
from app.infrastructure.persistence.store import read_bytes


def latest_run(store):
    store.load()
    candidates = []
    runs = store.managed('runs')
    if runs.exists():
        for folder in runs.iterdir():
            try:
                if str(UUID(folder.name)) != folder.name:
                    continue
            except ValueError:
                continue
            path = store.managed(f'runs/{folder.name}/result.json')
            if path.is_file():
                candidates.append(path)
    if not candidates:
        return {'found': False, 'run_id': None, 'history': 'Belum ada run nyata.'}
    # Preserve old GUI selection by filesystem mtime; tie-breaking is now explicit.
    path = max(candidates, key=lambda p: (p.stat().st_mtime_ns, p.parent.name))
    chunks = []
    for name in ('result.json', 'events.jsonl', 'stdout.txt', 'stderr.txt'):
        artifact = store.managed(f'runs/{path.parent.name}/{name}')
        if artifact.exists():
            chunks.append(name + '\n' + read_bytes(artifact).decode('utf-8', errors='replace'))
    return {'found': True, 'run_id': path.parent.name, 'history': '\n\n'.join(chunks)}
