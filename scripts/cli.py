"""CLI entry point: workspace, read-only ELF inspection and explicit trusted tools."""
import argparse
import json
import os
import sys
from pathlib import Path

from app.application.workspaces import add_input, rename, verify_inputs
from app.domain.workspace.model import WorkspaceError, ValidationError
from app.infrastructure.persistence.store import Store
from app.presentation import CompactParser, emit, root_help


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or argv in (['--help'], ['-h']):
        print(root_help())
        return 0
    if argv == ['--help-all']:
        argv = ['--help']
    parser = CompactParser(description="PS2 Workbench", usage="%(prog)s [--json | --text] COMMAND ...")
    output = parser.add_mutually_exclusive_group()
    output.add_argument('--json', action='store_true', help='Hasil lengkap JSON')
    output.add_argument('--text', action='store_true', help='Hasil ringkas')
    commands = parser.add_subparsers(dest="command", required=True)
    create = commands.add_parser("create", help="Buat folder workspace baru (tidak overwrite)")
    create.add_argument("root")
    create.add_argument("--name", required=True)
    for command in ("open", "validate", "verify-inputs", "recovery-info"):
        commands.add_parser(command).add_argument("root")
    edit = commands.add_parser("rename")
    edit.add_argument("root")
    edit.add_argument("--name", required=True)
    register = commands.add_parser("add-input", help="Referensi + hash saja; tidak menganalisis ELF")
    register.add_argument("root")
    register.add_argument("path")
    register.add_argument("--relative", action="store_true", help="Path relatif inputs/... dalam workspace")
    repair = commands.add_parser("recover", help="Pulihkan manifest korup/hilang dari backup terpilih")
    repair.add_argument("root")
    repair.add_argument("--backup", required=True)
    repair.add_argument("--expected-token", required=True)
    external = commands.add_parser('run-tool', help='Jalankan command tepercaya yang dipilih eksplisit (POSIX)')
    external.add_argument('root')
    external.add_argument('--argv-json', required=True, help='Array JSON argv; executable pertama harus absolute')
    external.add_argument('--timeout', type=float, default=30)
    external.add_argument('--max-output', type=int, default=262144)
    external.add_argument('--redact-env', action='append', default=[], help='Nama env yang nilainya disensor dalam log')
    commands.add_parser('recover-runs', help='Tandai metadata job terputus; tidak membunuh PID tersimpan').add_argument('root')
    baseline = commands.add_parser('baseline', help='Baca ELF input terdaftar dan simpan baseline struktural')
    baseline.add_argument('root')
    baseline.add_argument('--input-id', required=True)
    inspect = commands.add_parser('inspect-elf', help='Periksa ELF tanpa workspace/output file baru')
    inspect.add_argument('path')
    inspect.add_argument('--format', choices=('text', 'json'), default='text')
    commands.add_parser('run-history', help='Baca artefak run terakhir (read-only, JSON)').add_argument('root')
    commands.add_parser('tools-detect', help='Cari kandidat di PATH tanpa menjalankannya')
    for name in ('toolchain-check', 'build-smoke'):
        tool = commands.add_parser(name, help='Adapter GCC eksplisit; build-smoke membuat fixture dua kali')
        tool.add_argument('root')
        tool.add_argument('--compiler', required=True, help='Path absolute compiler GCC tepercaya')
        tool.add_argument('--profile', choices=('ps2-ee', 'host-elf'), default='ps2-ee')
        tool.add_argument('--timeout', type=float, default=30, help='Batas detik per proses')
    symbols = commands.add_parser('inspect-symbols', help='Baca simbol ELF ke JSON tanpa workspace')
    symbols.add_argument('path')
    inventory = commands.add_parser('symbols', help='Simpan inventaris simbol input terdaftar')
    inventory.add_argument('root')
    inventory.add_argument('--input-id', required=True)
    ghidra_check = commands.add_parser('ghidra-check', help='Audit instalasi/language Ghidra tanpa eksekusi')
    ghidra_check.add_argument('--ghidra-home')
    ghidra_check.add_argument('--language-dir', action='append', default=[], help='Folder berisi .ldefs tambahan (audit)')
    ghidra_plan = commands.add_parser('ghidra-plan', help='Simpan rencana import tanpa menjalankan Ghidra')
    ghidra_plan.add_argument('root')
    ghidra_plan.add_argument('--input-id', required=True)
    ghidra_plan.add_argument('--ghidra-home', required=True)
    ghidra_plan.add_argument('--language', required=True)
    ghidra_plan.add_argument('--cspec', required=True)
    ghidra_plan.add_argument('--language-dir', action='append', default=[])
    functions = commands.add_parser('list-functions', help='Daftar simbol FUNC berhalaman, tanpa Ghidra')
    functions.add_argument('path')
    functions.add_argument('--offset', type=int, default=0)
    functions.add_argument('--limit', type=int, default=20)
    extract = commands.add_parser('extract-function', help='Salin byte simbol FUNC terdaftar, tanpa eksekusi')
    extract.add_argument('root')
    extract.add_argument('--input-id', required=True)
    extract.add_argument('--symbol-id', required=True)
    refs = commands.add_parser('function-refs', help='Petakan relokasi terkait simbol fungsi; tidak menerapkan relokasi')
    refs.add_argument('root')
    refs.add_argument('--input-id', required=True)
    refs.add_argument('--symbol-id', required=True)
    preview = commands.add_parser('preview-hi-lo', help='Pratinjau hipotetis pasangan HI16/LO16 ET_REL; tanpa patch')
    preview.add_argument('root')
    preview.add_argument('--input-id', required=True)
    preview.add_argument('--function-id', required=True)
    preview.add_argument('--hi-reloc-id', required=True)
    preview.add_argument('--symbol-value', required=True, type=lambda value: int(value, 0), help='Nilai S hipotetis, misalnya 0x12348000')
    word = commands.add_parser('preview-word32', help='Pratinjau R_MIPS_32 ET_REL tanpa patch')
    word.add_argument('root')
    word.add_argument('--input-id', required=True)
    word.add_argument('--function-id', required=True)
    word.add_argument('--reloc-id', required=True)
    word.add_argument('--symbol-value', required=True, type=lambda value: int(value, 0))
    for name in ('export-target','verify-target'):
        target = commands.add_parser(name, help='Paket satu fungsi dengan konfigurasi dan verifikasi sumber')
        target.add_argument('root')
        target.add_argument('--input-id', required=True)
        target.add_argument('--symbol-id', required=True)
    for name in ('draft-add','draft-show','draft-history'):
        draft = commands.add_parser(name, help='Revisi source DRAFT untuk satu target terverifikasi')
        draft.add_argument('root')
        draft.add_argument('--input-id', required=True)
        draft.add_argument('--symbol-id', required=True)
        if name == 'draft-add':
            draft.add_argument('--source', required=True)
            draft.add_argument('--language', choices=('c','cpp'), default='c')
            draft.add_argument('--parent')
        if name == 'draft-show':
            draft.add_argument('--revision', required=True)
    diff = commands.add_parser('draft-diff', help='Bandingkan teks dua revisi pada target yang sama; bukan binary matching')
    diff.add_argument('root')
    diff.add_argument('--input-id', required=True)
    diff.add_argument('--symbol-id', required=True)
    diff.add_argument('--from-revision', required=True)
    diff.add_argument('--to-revision', required=True)
    diff.add_argument('--save', action='store_true', help='Simpan laporan JSON immutable')
    for action in ('add','show','list','check','verify-words'):
        material = commands.add_parser('draft-materials-'+action, help='Simpan/baca assembly dan context pengguna; belum diverifikasi semantik')
        material.add_argument('root')
        material.add_argument('--input-id', required=True)
        material.add_argument('--symbol-id', required=True)
        material.add_argument('--revision', required=True)
        if action == 'add':
            material.add_argument('--assembly', required=True)
            material.add_argument('--context', required=True)
        if action in ('show','check','verify-words'):material.add_argument('--bundle-id', required=True)
    commands.add_parser('doctor', help='Laporan runtime aktual tanpa probe/eksekusi tool eksternal')
    words = commands.add_parser('target-words', help='Listing word32 literal dari byte target, bukan disassembly')
    words.add_argument('root')
    words.add_argument('--input-id', required=True)
    words.add_argument('--symbol-id', required=True)
    words.add_argument('--save', action='store_true')
    comparison = commands.add_parser('compare-functions', help='Bandingkan raw byte dua fungsi ELF; bukan bukti build matching')
    comparison.add_argument('root')
    comparison.add_argument('--reference-input', required=True)
    comparison.add_argument('--reference-symbol', required=True)
    comparison.add_argument('--candidate-input', required=True)
    comparison.add_argument('--candidate-symbol', required=True)
    comparison.add_argument('--save', action='store_true')
    for name in ('plan-build','show-build-plan'):
        build = commands.add_parser(name, help='Rencana compile-only immutable; tidak menjalankan compiler')
        build.add_argument('root')
        build.add_argument('--input-id', required=True)
        build.add_argument('--symbol-id', required=True)
        build.add_argument('--revision', required=True)
        build.add_argument('--bundle-id', required=True)
        if name == 'plan-build':
            build.add_argument('--compiler', required=True)
            build.add_argument('--optimization', choices=('0','1','2','3','s'), required=True)
            build.add_argument('--use-context', action='store_true')
        else:build.add_argument('--plan-id', required=True)
    for name in ('stage-build','verify-build-stage','list-build-stages'):
        stage = commands.add_parser(name, help='Staging input build terpisah tanpa eksekusi compiler')
        stage.add_argument('root')
        stage.add_argument('--input-id', required=True)
        stage.add_argument('--symbol-id', required=True)
        stage.add_argument('--revision', required=True)
        stage.add_argument('--bundle-id', required=True)
        stage.add_argument('--plan-id', required=True)
        if name == 'verify-build-stage':stage.add_argument('--stage-id', required=True)
    for name in ('import-build-candidate','show-build-candidate'):
        candidate = commands.add_parser(name, help='Snapshot object ET_REL pilihan pengguna; bukan bukti compiler run')
        candidate.add_argument('root')
        candidate.add_argument('--input-id', required=True)
        candidate.add_argument('--symbol-id', required=True)
        candidate.add_argument('--revision', required=True)
        candidate.add_argument('--bundle-id', required=True)
        candidate.add_argument('--plan-id', required=True)
        candidate.add_argument('--stage-id', required=True)
        if name == 'import-build-candidate':
            candidate.add_argument('--candidate', required=True)
            candidate.add_argument('--candidate-symbol', required=True)
        else:candidate.add_argument('--candidate-id', required=True)
    qlist = commands.add_parser('queue-list', help='Prioritas/status review tersimpan, tanpa eksekusi otomatis')
    qlist.add_argument('root')
    qlist.add_argument('--status', choices=('TODO','ACTIVE','PAUSED','REVIEWED'))
    qlist.add_argument('--min-priority', type=int, default=0)
    qadd = commands.add_parser('queue-add', help='Tambahkan fungsi terverifikasi ke antrean TODO')
    qadd.add_argument('root')
    qadd.add_argument('--input-id', required=True)
    qadd.add_argument('--symbol-id', required=True)
    qadd.add_argument('--priority', type=int, default=50)
    qadd.add_argument('--note', default='')
    qupdate = commands.add_parser('queue-update', help='Ubah antrean dengan token untuk mencegah lost update')
    qupdate.add_argument('root')
    qupdate.add_argument('--item-id', required=True)
    qupdate.add_argument('--expected-token', required=True)
    qupdate.add_argument('--status', choices=('TODO','ACTIVE','PAUSED','REVIEWED'))
    qupdate.add_argument('--priority', type=int)
    qupdate.add_argument('--note')
    history = commands.add_parser('queue-history', help='Daftar snapshot riwayat review, baca-saja')
    history.add_argument('root')
    history.add_argument('--before-revision', type=int)
    history.add_argument('--limit', type=int, default=20)
    show = commands.add_parser('show-queue-history', help='Periksa snapshot satu revisi antrean')
    show.add_argument('root')
    show.add_argument('--revision', type=int, required=True)
    for command in ('extract-section','verify-section'):
        section = commands.add_parser(command, help='Ekstraksi/verifikasi byte section ELF terdaftar')
        section.add_argument('root')
        section.add_argument('--input-id', required=True)
        section.add_argument('--section-index', type=int, required=True)
    data_list = commands.add_parser('list-data-symbols', help='Daftar OBJECT ELF')
    data_list.add_argument('path')
    data_list.add_argument('--offset', type=int, default=0)
    data_list.add_argument('--limit', type=int, default=20)
    for command in ('extract-data','verify-data'):
        data = commands.add_parser(command, help='Ekstraksi/verifikasi OBJECT ELF')
        data.add_argument('root')
        data.add_argument('--input-id', required=True)
        data.add_argument('--symbol-id', required=True)
    for command in ('extract-function-data','verify-function-data'):
        dependencies = commands.add_parser(command, help='Byte fungsi dan OBJECT dari referensi relokasi langsung')
        dependencies.add_argument('root')
        dependencies.add_argument('--input-id', required=True)
        dependencies.add_argument('--symbol-id', required=True)
        dependencies.add_argument('--data-depth', type=int, default=0)
    decompile = commands.add_parser('ghidra-decompile', help='Decompile satu fungsi EE dengan R5900 nyata')
    decompile.add_argument('root')
    decompile.add_argument('--input-id', required=True)
    decompile.add_argument('--symbol-id', required=True)
    decompile.add_argument('--ghidra-home', required=True)
    decompile.add_argument('--jdk-home', required=True)
    decompile.add_argument('--timeout', type=float, default=180)
    decompile.add_argument('--analysis', choices=('bounded', 'recommended'), default='bounded')
    batch = commands.add_parser('ghidra-batch', help='Decompile 1–100 fungsi; simpan hasil dan kegagalan per fungsi')
    batch.add_argument('root')
    batch.add_argument('--input-id', required=True)
    batch.add_argument('--symbol-id', action='append', required=True)
    batch.add_argument('--ghidra-home', required=True)
    batch.add_argument('--jdk-home', required=True)
    batch.add_argument('--timeout', type=float, default=180, help='Batas detik per fungsi')
    batch.add_argument('--analysis', choices=('bounded', 'recommended'), default='bounded')
    check = commands.add_parser('check-decompile', help='Uji sintaks export asli dengan compiler eksplisit')
    check.add_argument('root')
    check.add_argument('--job-id', required=True)
    check.add_argument('--compiler', required=True)
    check.add_argument('--language', choices=('c', 'c++'), default='c++')
    check.add_argument('--timeout', type=float, default=30)
    check.add_argument('--target', choices=('host', 'ps2-ee'), default='host')
    check.add_argument('--strip-debug', action='store_true', help='Simpan object EE tanpa debug terpisah; cek section ALLOC identik')
    check.add_argument('--storage-types', action='store_true', help='Definisi unsigned untuk undefined1/2/4/8; tipe asli belum terverifikasi')
    check.add_argument('--emit-object', action='store_true', help='Compile object host tanpa link atau eksekusi')
    args = parser.parse_args(argv)
    def display(value):
        emit(value, json_output=args.json or (not args.text and not sys.stdout.isatty()))
    try:
        command = args.command
        if command == 'ghidra-batch':
            from app.application.decompile_batch import decompile_batch
            result = decompile_batch(Store(args.root), args.input_id, args.symbol_id,
                                     args.ghidra_home, args.jdk_home, args.timeout, analysis=args.analysis)
            display(result)
            return 0 if result['status'] == 'COMPLETED_UNVERIFIED' else 1
        if command == 'check-decompile':
            from app.application.export_checks import check_export
            result = check_export(Store(args.root), args.job_id, args.compiler, args.language, args.timeout,
                                  storage_types=args.storage_types, emit_object=args.emit_object, target=args.target, strip_debug=args.strip_debug)
            display(result)
            return 0 if result['syntax_accepted'] else 1
        if command == 'ghidra-decompile':
            from app.application.decompile import decompile_function
            result=decompile_function(Store(args.root),args.input_id,args.symbol_id,
                                      args.ghidra_home,args.jdk_home,args.timeout,analysis=args.analysis)
            display(result)
            return 0 if result['status']=='DECOMPILED_UNVERIFIED' else 1
        if command in ('extract-function-data','verify-function-data'):
            from app.application.function_data import function_data
            display(function_data(Store(args.root),args.input_id,args.symbol_id,
                                  verify=command=='verify-function-data',data_depth=args.data_depth))
            return 0
        if command == 'list-data-symbols':
            from app.application.data_symbols import list_data_symbols
            display(list_data_symbols(Path(args.path),args.offset,args.limit))
            return 0
        if command in ('extract-data','verify-data'):
            from app.application.data_symbols import data_bundle
            display(data_bundle(Store(args.root),args.input_id,args.symbol_id,verify=command=='verify-data'))
            return 0
        if command in ('extract-section','verify-section'):
            from app.application.sections import section_bundle
            result=section_bundle(Store(args.root),args.input_id,args.section_index,verify=command=='verify-section')
            display(result)
            return 0
        if command in ('queue-history','show-queue-history'):
            from app.application.queue_history import history_list,history_show
            if command == 'queue-history':result=history_list(Store(args.root),args.before_revision,args.limit)
            else:result=history_show(Store(args.root),args.revision)
            display(result)
            return 0
        if command in ('queue-list','queue-add','queue-update'):
            from app.application.queue import queue_list,mutate
            if command == 'queue-list':result=queue_list(Store(args.root),args.status,args.min_priority)
            elif command == 'queue-add':result=mutate(Store(args.root),'add',input_id=args.input_id,symbol_id=args.symbol_id,priority=args.priority,note=args.note)
            else:result=mutate(Store(args.root),'update',item_id=args.item_id,expected_token=args.expected_token,status=args.status,priority=args.priority,note=args.note)
            display(result)
            return 0
        if command in ('import-build-candidate','show-build-candidate'):
            from app.application.drafts import drafts
            options={'candidate_id':args.candidate_id} if command=='show-build-candidate' else {'path':args.candidate,'symbol_id':args.candidate_symbol}
            result=drafts(Store(args.root),args.input_id,args.symbol_id,revision=args.revision,
                          material_action='build-stage',bundle_id=args.bundle_id,build_options={'plan_id':args.plan_id},
                          stage_action='verify',stage_id=args.stage_id,candidate_options=options)
            display(result)
            return 0
        if command in ('stage-build','verify-build-stage','list-build-stages'):
            from app.application.drafts import drafts
            action={'stage-build':'create','verify-build-stage':'verify','list-build-stages':'list'}[command]
            result=drafts(Store(args.root),args.input_id,args.symbol_id,revision=args.revision,
                          material_action='build-stage',bundle_id=args.bundle_id,build_options={'plan_id':args.plan_id},
                          stage_action=action,stage_id=getattr(args,'stage_id',None))
            display(result)
            return 0
        if command in ('plan-build','show-build-plan'):
            from app.application.drafts import drafts
            options = {'plan_id':args.plan_id} if command == 'show-build-plan' else {'compiler':args.compiler,'optimization':args.optimization,'use_context':args.use_context}
            result=drafts(Store(args.root),args.input_id,args.symbol_id,revision=args.revision,
                          material_action='build-plan',bundle_id=args.bundle_id,build_options=options)
            display(result)
            return 0
        if command == 'compare-functions':
            from app.application.comparisons import compare_functions
            result=compare_functions(Store(args.root),args.reference_input,args.reference_symbol,args.candidate_input,args.candidate_symbol,save=args.save)
            display(result)
            return 0 if result['comparison']['status']=='RAW_RANGE_IDENTICAL' else 1
        if command == 'target-words':
            from app.application.words import target_words
            display(target_words(Store(args.root),args.input_id,args.symbol_id,save=args.save))
            return 0
        if command == 'doctor':
            from app.application.readiness import runtime_report
            display(runtime_report())
            return 0
        if command.startswith('draft-materials-'):
            from app.application.drafts import drafts
            result = drafts(Store(args.root), args.input_id, args.symbol_id, revision=args.revision,
                            material_action=command.removeprefix('draft-materials-'),
                            assembly=getattr(args,'assembly',None),context=getattr(args,'context',None),
                            bundle_id=getattr(args,'bundle_id',None))
            display(result)
            return 1 if command == 'draft-materials-verify-words' and result['status']=='BYTE_DIFFERENT' else 0
        if command == 'draft-diff':
            from app.application.drafts import drafts
            result = drafts(Store(args.root), args.input_id, args.symbol_id,
                            revision=args.from_revision, compare_to=args.to_revision, save_diff=args.save)
            display(result)
            return 0
        if command in ('draft-add','draft-show','draft-history'):
            from app.application.drafts import drafts
            result = drafts(Store(args.root), args.input_id, args.symbol_id,
                            source=getattr(args,'source',None), language=getattr(args,'language','c'),
                            parent=getattr(args,'parent',None), revision=getattr(args,'revision',None))
            display(result)
            return 0
        if command in ('export-target','verify-target'):
            from app.application.targets import target_bundle
            result = target_bundle(Store(args.root), args.input_id, args.symbol_id, verify=command=='verify-target')
            display(result)
            return 0
        if command == 'preview-word32':
            from app.application.word32_preview import create_preview
            result = create_preview(Store(args.root), args.input_id, args.function_id, args.reloc_id, args.symbol_value)
            display(result)
            return 0
        if command == 'preview-hi-lo':
            from app.application.relocation_preview import create_preview
            result = create_preview(Store(args.root), args.input_id, args.function_id, args.hi_reloc_id, args.symbol_value)
            display(result)
            return 0
        if command == 'function-refs':
            from app.application.relocations import create_references
            display(create_references(Store(args.root), args.input_id, args.symbol_id))
            return 0
        if command == 'list-functions':
            from app.application.extractions import list_functions
            display(list_functions(Path(args.path), args.offset, args.limit))
            return 0
        if command == 'extract-function':
            from app.application.extractions import extract_function
            display(extract_function(Store(args.root), args.input_id, args.symbol_id))
            return 0
        if command == 'ghidra-check':
            from app.application.ghidra import check_install
            result = check_install(args.ghidra_home, args.language_dir)
            display(result)
            return 0 if result['status'] == 'DECLARED' else 1
        if command == 'ghidra-plan':
            from app.application.ghidra import create_plan
            result = create_plan(Store(args.root), args.input_id, args.ghidra_home, args.language, args.cspec, args.language_dir)
            display(result)
            return 0
        if command == 'inspect-symbols':
            from app.application.symbols import inspect_symbols
            display(inspect_symbols(Path(args.path)))
            return 0
        if command == 'symbols':
            from app.application.symbols import create_inventory
            display(create_inventory(Store(args.root), args.input_id))
            return 0
        if command == 'tools-detect':
            from app.application.toolchains import detect
            display(detect())
            return 0
        if command in ('toolchain-check', 'build-smoke'):
            from app.application.toolchains import examine, exit_status
            report = examine(Store(args.root), args.compiler, args.profile,
                             build=command == 'build-smoke', timeout=args.timeout)
            display(report)
            return exit_status(report)
        if command == 'inspect-elf':
            from app.application.baselines import inspect_file
            report = inspect_file(Path(args.path))
            if args.format == 'json' or args.json:
                print(json.dumps(report, ensure_ascii=False, indent=2))
            else:
                metadata = report['metadata']
                print(f"Format: {metadata['format']} / {metadata['byte_order']} / {metadata['architecture']}")
                print(f"Type: {metadata['elf_type_name']} | Entry: {metadata['entry_point']}")
                print(f"Size: {report['source_size']} bytes | Segments: {len(metadata['segments'])} | Sections: {len(metadata['sections'])}")
                print(f"SHA-256: {report['source_sha256']}")
                print('Target PS2 EE/IOP/VU: UNKNOWN (UNRESOLVED)')
                for warning in metadata['warnings']:
                    print('Warning: ' + warning)
            return 0
        store = Store(args.root)
        status = 0
        if command == "create":
            result = store.create(args.name).data
        elif command in ("open", "validate"):
            snap = store.load()
            result = snap.data if command == "open" else {
                "manifest_valid": True, "revision": snap.data["revision"], "token": snap.token,
                "input_formats_validated": False}
        elif command == "rename":
            result = rename(store, args.name).data
        elif command == "add-input":
            result = add_input(store, args.path, args.relative).data
        elif command == "verify-inputs":
            result = {"inputs": verify_inputs(store)}
            status = 0 if all(x["status"] == "unchanged" for x in result["inputs"]) else 3
        elif command == "recovery-info":
            result = store.recovery_info()
        elif command == 'recover':
            result = store.recover(args.backup, args.expected_token).data
        elif command == 'recover-runs':
            from app.infrastructure.process_runner.runner import recover_interrupted
            result = {'recovered': recover_interrupted(store)}
        elif command == 'baseline':
            from app.application.baselines import create_baseline
            result = create_baseline(store, args.input_id)
        elif command == 'run-history':
            from app.application.run_history import latest_run
            result = latest_run(store)
        else:
            from app.infrastructure.process_runner.runner import Command, run
            try:
                argv = json.loads(args.argv_json)
            except (ValueError, RecursionError) as exc:
                raise ValidationError('argv-json bukan JSON valid.') from exc
            if not isinstance(argv, list):
                raise ValidationError('argv-json harus array string.')
            request = Command(tuple(argv), timeout=args.timeout, max_output_bytes=args.max_output,
                              secrets=tuple(os.environ[k] for k in args.redact_env if k in os.environ))
            result = run(store, request)
            status = {'succeeded': 0, 'failed': 1, 'timed_out': 124, 'cancelled': 130}[result['status']]
        display(result)
        return status
    except (WorkspaceError, OSError) as exc:
        hint = 'Periksa path/izin; untuk konflik buka ulang. Gunakan recovery-info untuk manifest korup.'
        if args.command in ('inspect-elf', 'baseline'):
            hint = 'Periksa format dan kelengkapan file ELF.'
        if args.command in ('ghidra-decompile', 'ghidra-batch'):
            hint = 'Periksa log run, instalasi R5900, dan rentang fungsi.'
        if isinstance(exc, FileNotFoundError):
            hint = 'Path tidak ditemukan. Periksa ejaan dan gunakan tanda kutip untuk path dengan spasi.'
        elif isinstance(exc, PermissionError):
            hint = 'Akses ditolak. Periksa izin baca input atau izin tulis workspace; jangan menjalankan input.'
        if getattr(exc, 'batch_report_file', None):
            hint += ' Hasil batch: ' + exc.batch_report_file
        print(json.dumps({"error": getattr(exc, "code", "filesystem_error"), "message": str(exc),
                          "hint": hint},
                         ensure_ascii=False), file=sys.stderr)
        return 2
    except KeyboardInterrupt:
        print('{"error":"interrupted","message":"Dihentikan pengguna; periksa manifest sebelum mencoba lagi."}', file=sys.stderr)
        return 130


if __name__ == "__main__":
    raise SystemExit(main())
