"""Single background task + queue. UI callbacks are never invoked from worker threads."""
import queue
import threading

from app.domain.workspace.model import ConflictError


class TaskController:
    def __init__(self):
        self.events = queue.Queue()
        self.cancel_event = threading.Event()
        self.busy = False
        self.thread = None

    def submit(self, operation):
        if self.busy:
            raise ConflictError('Masih ada tugas aktif.')
        self.busy = True
        self.cancel_event = threading.Event()

        def worker():
            try:
                result = operation(self.cancel_event, lambda e: self.events.put(('event', e)))
                self.events.put(('done', result))
            except Exception as exc:
                self.events.put(('error', {'error': getattr(exc, 'code', 'task_error'), 'message': str(exc)}))
            finally:
                self.events.put(('idle', None))

        self.thread = threading.Thread(target=worker, daemon=False)
        self.thread.start()

    def cancel(self):
        self.cancel_event.set()

    def poll(self):
        items = []
        while True:
            try:
                event = self.events.get_nowait()
            except queue.Empty:
                break
            if event[0] == 'idle':
                self.busy = False
            items.append(event)
        return items
