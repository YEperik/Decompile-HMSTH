"""Compact terminal output; complete JSON remains available for automation."""
import argparse
import json


class CompactParser(argparse.ArgumentParser):
    def error(self,message):
        if 'invalid choice:' in message:
            message=message.split(' (choose from',1)[0]
        super().error(message)


def root_help():
    return '\n'.join((
        'PS2 Workbench',
        'usage: python -m app [--json | --text] COMMAND ...',
        '',
        'Workspace : create, open, add-input, verify-inputs',
        'ELF       : inspect-elf, list-functions, list-data-symbols',
        'Ekstraksi : extract-function, extract-section, extract-data',
        'Analisis  : function-refs, compare-functions, target-words',
        'Decompiler: ghidra-decompile, ghidra-batch, check-decompile',
        'Draft     : draft-add, draft-history, draft-show, vector-draft',
        'COP2/EE   : ghidra-cop2-audit, ghidra-cop2-trace, ee-cop2-trace, ee-startup',
        'VU/GIF    : vu-micro-trace, vif-dma-trace, gif-gs-trace',
        'Antrean   : queue-add, queue-list, queue-update',
        'COMMAND --help   Opsi perintah',
        '--help-all       Semua perintah',
        '--json           Hasil lengkap'))


def compact(value,max_lines=18):
    lines=[];omitted=False
    if isinstance(value, dict) and value.get('status') == 'EE_STARTUP_BLOCKED':
        value = {key: value[key] for key in ('status', 'executed_instructions', 'stop', 'initialization_complete', 'report_file') if key in value}
        omitted = True
    metadata=value.get('metadata') if isinstance(value,dict) else None
    if isinstance(metadata,dict) and isinstance(metadata.get('section'),dict):
        section=metadata['section']
        value={'status':value.get('status'),'section':section.get('name'),
               'section_index':section.get('index'),'bytes':metadata.get('payload_size'),
               'storage':metadata.get('storage'),'output':value.get('bundle_dir')}
        if metadata.get('elf_warnings'):value['warnings']=metadata['elf_warnings']
        omitted=True
    if isinstance(value, dict) and 'report_file' in value and 'functions' in value and 'counts' in value:
        value = {key: value[key] for key in ('status', 'counts', 'report_file', 'semantics_verified')}
        omitted = True
    if isinstance(value, dict) and value.get('status') == 'VECTOR_STORAGE_DRAFT_UNVERIFIED':
        value = {'status': value['status'], 'changes': len(value['changes']),
                 'implemented_transfer_kinds': len(value.get('implemented_value_transfers', {})),
                 'implemented_conversion_kinds': len(value.get('implemented_value_conversions', {})),
                 'unimplemented_userop_kinds': len(value['unimplemented_userops']),
                 'compiled': value['compiled'], 'semantics_verified': value['semantics_verified'],
                 'report_file': value['report_file']}
        omitted = True
    if isinstance(value, dict) and value.get('status') in ('VECTOR_SYNTAX_ACCEPTED_UNVERIFIED', 'BLOCKED_VECTOR_SYNTAX', 'VECTOR_CHECK_FAILED'):
        value = {key: value[key] for key in ('status', 'syntax_accepted', 'exit_code', 'run_dir', 'report_dir', 'semantics_verified', 'warnings')}
        omitted = True
    if isinstance(value, dict) and value.get('status') == 'VU_CLIP_TRACE_COMPUTED_UNVERIFIED':
        value = {key: value[key] for key in ('status', 'visible_clip', 'history_clip', 'pending', 'hardware_verified', 'report_dir')}
        omitted = True
    if isinstance(value, dict) and value.get('status') == 'VU_FLAG_TRACE_COMPUTED_UNVERIFIED':
        value = {key: value[key] for key in ('status', 'visible_clip', 'visible_mac', 'visible_status', 'pending', 'arithmetic_executed', 'arithmetic_profile', 'hardware_verified', 'report_dir')}
        omitted = True
    if isinstance(value, dict) and value.get('status') in ('EE_COP2_TRACE_BLOCKED', 'EE_COP2_TRACE_COMPUTED_UNVERIFIED'):
        micro = value.get('micro_execution')
        value = {key: value[key] for key in ('status', 'executed_instructions', 'stall_cycles', 'blocked_reason', 'microprogram_executed', 'hardware_verified', 'report_dir')}
        if micro is not None:value.update(micro_steps=micro['steps'], micro_cycle=micro['cycle'], micro_running=micro['running'])
        omitted = True
    if isinstance(value, dict) and value.get('status', '').startswith('GHIDRA_COP2_'):
        coverage = value['coverage']
        value = {'status': value['status'], 'supported_instructions': coverage['supported_instructions'], 'total_instructions': coverage['total_instructions'], 'executed_instructions': value.get('execution', {}).get('executed_instructions', 0), 'blocked_reason': value.get('execution', {}).get('blocked_reason'), 'report_dir': value['report_dir']}
        omitted = True
    if isinstance(value,dict) and value.get('status','').startswith(('VU_MICRO_','VIF_DMA_')):
        original=value;micro=value.get('micro_execution',{})
        value={k:original[k] for k in ('status','blocked_reason','hardware_verified','report_dir') if k in original}
        value.update(unit=micro.get('unit',original.get('unit')),micro_steps=micro.get('steps',original.get('micro_steps')),vu_cycle=micro.get('cycle',original.get('vu_cycle')))
        omitted=True
    if isinstance(value,dict) and value.get('status','').startswith('GIF_TRACE_'):
        original=value
        value={k:original[k] for k in ('status','blocked_reason','words_consumed','rendered','report_dir') if k in original}
        value.update(tags=len(original['tags']),register_writes=len(original['register_writes']),images=len(original['image_packets']))
        omitted=True
    skip={'limitations','scope','validation_scope','evidence','order','payload_validation_scope'}
    priority={'status','error','message','warnings','warning','association','binary_matching_claimed',
              'semantics_verified','relocations_applied','executed','standalone','result','comparison'}
    def visit(item,path='',depth=0):
        nonlocal omitted
        if len(lines)>=max_lines:
            omitted=True;return
        if isinstance(item,dict):
            keys=sorted(item,key=lambda k:0 if k in priority else 1)
            for key in keys:
                if key in skip:
                    omitted=True;continue
                visit(item[key],f'{path}.{key}' if path else key,depth+1)
        elif isinstance(item,list):
            if not item:lines.append(f'{path}: []')
            for index,child in enumerate(item[:5]):visit(child,f'{path}[{index}]',depth+1)
            if len(item)>5:omitted=True
        else:
            text=json.dumps(item,ensure_ascii=True) if not isinstance(item,str) else item
            # Escape control characters so file/symbol names cannot alter the terminal.
            text=text.encode('unicode_escape').decode('ascii')
            if len(text)>180:text=text[:177]+'...';omitted=True
            lines.append(f'{path}: {text}')
    visit(value)
    if omitted:lines.append('Detail lengkap: gunakan --json sebelum COMMAND.')
    return '\n'.join(lines) or '(kosong)'


def emit(value,json_output=False):
    print(json.dumps(value,ensure_ascii=False,indent=2) if json_output else compact(value))
