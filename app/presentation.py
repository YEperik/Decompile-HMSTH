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
        'PS2 Workbench — decompilation research tooling',
        'usage: python -m app [--json | --text] COMMAND ...',
        '',
        'Workspace : create, open, validate, add-input, verify-inputs, recover',
        'ELF       : inspect-elf, inspect-symbols, baseline, list-functions, symbols',
        'Analysis  : function-refs, preview-hi-lo, preview-word32, compare-functions, target-words',
        'Ghidra    : ghidra-check, ghidra-plan, ghidra-decompile, ghidra-batch, check-decompile',
        'Drafts    : export-target, verify-target, draft-add, draft-show, draft-history, draft-diff',
        'Build     : plan-build, show-build-plan, stage-build, verify-build-stage, import-build-candidate',
        'Review    : queue-add, queue-list, queue-update, queue-history',
        'Tools     : run-tool, tools-detect, toolchain-check, build-smoke, doctor',
        'COMMAND --help   Show command-specific options',
        '--help-all       Show all commands and descriptions',
        '--json           Full machine-readable JSON output',
        '--text           Compact human-readable output'))


def compact(value,max_lines=18):
    lines=[];omitted=False
    metadata=value.get('metadata') if isinstance(value,dict) else None
    if isinstance(metadata,dict) and isinstance(metadata.get('section'),dict):
        section=metadata['section']
        value={'status':value.get('status'),'section':section.get('name'),
               'section_index':section.get('index'),'bytes':metadata.get('payload_size'),
               'storage':metadata.get('storage'),'output':value.get('bundle_dir')}
        if metadata.get('elf_warnings'):value['warnings']=metadata['elf_warnings']
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
            if not item:
                lines.append(f'{path}: []')
            elif len(item) > 5 and all(isinstance(child, dict) for child in item):
                statuses = {}
                for child in item:
                    status = child.get('status')
                    if isinstance(status, str):
                        statuses[status] = statuses.get(status, 0) + 1
                summary = f'{len(item)} items'
                if statuses:
                    counts = ', '.join(f'{name}: {count}' for name, count in sorted(statuses.items()))
                    summary += f' ({counts})'
                lines.append(f'{path}: {summary}')
                omitted = True
            else:
                for index,child in enumerate(item[:5]):visit(child,f'{path}[{index}]',depth+1)
                if len(item)>5:omitted=True
        else:
            text=json.dumps(item,ensure_ascii=True) if not isinstance(item,str) else item
            # Escape control characters so file/symbol names cannot alter the terminal.
            text=text.encode('unicode_escape').decode('ascii')
            if len(text)>180:text=text[:177]+'...';omitted=True
            lines.append(f'{path}: {text}')
    visit(value)
    if omitted:lines.append('Full details: add --json before COMMAND.')
    return '\n'.join(lines) or '(kosong)'


def emit(value,json_output=False):
    print(json.dumps(value,ensure_ascii=False,indent=2) if json_output else compact(value))
