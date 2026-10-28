"""Read-only material triage and observed runtime capabilities. Never runs tools."""
import os
import platform
import re
import sys
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError

MAX_DETAILS=64
# Deliberately lexical: comments, macros and conditional compilation are not parsed.
RULES=(('assembly.s','ASM_EXTERNAL_FILE',re.compile(r'^\s*\.(?:include|incbin)\b',re.I)),
       ('assembly.s','ASM_PREPROCESSOR',re.compile(r'^\s*#\s*(?:include|include_next|import)\b')),
       ('assembly.s','ASM_MACRO',re.compile(r'^\s*\.(?:macro|rept|irp|irpc)\b',re.I)),
       ('context.h','CONTEXT_INCLUDE',re.compile(r'^\s*#\s*(?:include|include_next|import)\b')),
       ('context.h','CONTEXT_CONDITIONAL',re.compile(r'^\s*#\s*(?:if|ifdef|ifndef|elif)\b')))


def runtime_report():
    version=tuple(sys.version_info[:3]);minimum=version>=(3,12,0)
    windows=os.name=='nt';posix=os.name=='posix'
    return {'schema':1,'observed':{'os_name':os.name,'system':platform.system(),
                                 'python_version':platform.python_version(),'implementation':platform.python_implementation()},
            'python_minimum_met':minimum,'python_required':'>=3.12',
            'file_workflow':'REQUIRES_LOCAL_VERIFICATION' if minimum else 'PYTHON_TOO_OLD',
            'process_runner':'UNSUPPORTED_WINDOWS' if windows else ('IMPLEMENTED_POSIX' if posix else 'UNSUPPORTED_PLATFORM'),
            'runtime_test_evidence':f'Observed runtime only: {platform.system()} Python {platform.python_version()}; this probe is not CI test evidence and does not certify other environments.',
            'external_tools_probed':False,'external_tools_executed':False,
            'notes':['Minimum Python version is not a compatibility certification',
                     'No PATH, environment values, usernames or filesystem inventory collected',
                     'No tool installation or administrator access requested']}


def assess(bundle,cancel=None):
    """Input comes only from verified material-show within the draft validation lock."""
    checkpoint(cancel)
    manifest=bundle['manifest'];texts=bundle['texts']
    if manifest['status']!='USER_SUPPLIED_UNVERIFIED':raise ValidationError('Status bahan tidak didukung.')
    counts={};details=[];stats={}
    for filename in ('assembly.s','context.h'):
        text=texts[filename];lines=text.split('\n')
        if lines[-1]=='':lines.pop()
        stats[filename]={'size_bytes':len(text.encode('utf-8')),'lf_lines':len(lines),
                         'ends_with_lf':text.endswith('\n'),'crlf_count':text.count('\r\n')}
        for number,line in enumerate(lines,1):
            checkpoint(cancel)
            for target,code,pattern in RULES:
                if filename==target and pattern.search(line):
                    counts[code]=counts.get(code,0)+1
                    if len(details)<MAX_DETAILS:details.append({'file':filename,'line':number,'code':code})
    total=sum(counts.values())
    return {'schema':1,'engine':'material-readiness-1','status':'MANUAL_REVIEW_REQUIRED',
            'bundle_id':bundle['bundle_id'],'binding':manifest['binding'],
            'integrity_verified':True,'automatic_execution_ready':False,
            'syntax_verified':False,'assembly_matches_target':False,'context_verified':False,
            'external_files_opened':False,'tools_executed':False,'statistics':stats,
            'lexical_findings':{'counts':counts,'total':total,'details':details,
                                'details_omitted':max(0,total-len(details))},
            'unresolved_gates':['Verify assembly instructions and addresses against ELF bytes',
                                'Review context types, ABI and any external file references',
                                'Validate a concrete m2c/toolchain configuration and runtime'],
            'limitations':['Lexical triage only: not an assembler, C preprocessor or syntax validator',
                           'Comments and conditional code may produce false positives; absence of findings is not proof of safety or completeness',
                           'Finding detail limit is 64; all matching lines still counted'],
            'runtime':runtime_report()}
