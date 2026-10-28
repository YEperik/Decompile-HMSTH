"""Sequential, bounded exports with a durable outcome for every selected function."""
import re
import sys
from uuid import uuid4

from app.application.decompile import decompile_function, GhidraExportError, LANGUAGE
from app.application.targets import encoded
from app.domain.binary.elf import checkpoint, Cancelled
from app.domain.workspace.model import ValidationError, ConflictError, now
from app.infrastructure.process_runner.runner import Command


def decompile_batch(store, input_id, symbol_ids, ghidra_home, jdk_home,
                    timeout=180, cancel=None, analysis='bounded'):
    if (not isinstance(symbol_ids, (list, tuple)) or not 1 <= len(symbol_ids) <= 100
            or any(not isinstance(s, str) or not re.fullmatch(r'[0-9]{1,6}:[0-9]{1,6}', s)
                   for s in symbol_ids) or len(set(symbol_ids)) != len(symbol_ids)):
        raise ValidationError('Pilih 1–100 symbol-id unik dengan format table:index.')
    if analysis not in ('bounded', 'recommended'):
        raise ValidationError('Profil analisis harus bounded atau recommended.')
    Command((sys.executable,), timeout=timeout).validate()
    checkpoint(cancel)
    snapshot = store.load()
    item = next((x for x in snapshot.data['inputs'] if x['id'] == input_id), None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan.')
    job = 'decompile-batches/' + str(uuid4())
    report = {'status': 'RUNNING', 'input_id': input_id, 'source_sha256': item['sha256'],
              'language': LANGUAGE, 'analysis': analysis, 'timeout_per_function': timeout,
              'created_at': now(), 'report_file': str(store.managed(job + '/batch.json')),
              'semantics_verified': False,
              'functions': [{'symbol_id': s, 'status': 'NOT_RUN'} for s in symbol_ids]}

    def save():
        rows = report['functions']
        report['counts'] = {key: sum(r['status'] == key for r in rows)
                            for key in ('NOT_RUN', 'RUNNING', 'DECOMPILED_UNVERIFIED',
                                        'EXPORT_FAILED', 'GHIDRA_RUN_FAILED', 'ABORTED')}
        report['updated_at'] = now()
        store.atomic(job + '/batch.json', encoded(report))

    with store.lock():
        if store.load().token != snapshot.token:
            raise ConflictError('Manifest berubah selama persiapan batch.')
        store.managed('decompile-batches').mkdir(exist_ok=True)
        store.managed(job).mkdir()
        save()
    row = None
    try:
        for row in report['functions']:
            checkpoint(cancel)
            if store.load().token != snapshot.token:
                raise ConflictError('Manifest berubah; batch dihentikan.')
            row['status'] = 'RUNNING'
            save()
            try:
                result = decompile_function(store, input_id, row['symbol_id'], ghidra_home,
                                            jdk_home, timeout, cancel, analysis)
                row.update(result)
            except GhidraExportError as exc:
                row.update(status='EXPORT_FAILED', error=exc.code, message=str(exc),
                           artifact_dir=getattr(exc, 'artifact_dir', None),
                           run_dir=getattr(exc, 'run_dir', None))
            save()
            if row.get('run_status') == 'cancelled':
                report['status'] = 'CANCELLED'
                save()
                return report
        successes = report['counts']['DECOMPILED_UNVERIFIED']
        report['status'] = ('COMPLETED_UNVERIFIED' if successes == len(symbol_ids)
                            else 'PARTIAL' if successes else 'FAILED')
        save()
        return report
    except (Exception, KeyboardInterrupt) as exc:
        if row is not None and row['status'] == 'RUNNING':
            row.update(status='ABORTED', error=getattr(exc, 'code', type(exc).__name__),
                       message=str(exc))
        report['status'] = 'CANCELLED' if isinstance(exc, (Cancelled, KeyboardInterrupt)) else 'ABORTED'
        report['error'] = {'code': getattr(exc, 'code', type(exc).__name__), 'message': str(exc)}
        save()
        exc.batch_report_file = report['report_file']
        raise
