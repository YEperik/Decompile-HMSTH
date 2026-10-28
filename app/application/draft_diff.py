"""Bounded textual draft comparison, never a compiler/binary match result."""
import difflib
import hashlib
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError

VERSION = 'draft-text-diff-1'
MAX_LINES = 2000
MAX_LINE_PRODUCT = 1_000_000


def lines(text):
    # LF is the only delimiter. Preserve CR bytes and missing final newline.
    chunks=text.split('\n')
    return [x+'\n' for x in chunks[:-1]] + ([chunks[-1]] if chunks[-1] else [])


def compare(left_record,left,right_record,right,cancel=None):
    checkpoint(cancel)
    a,b=lines(left.decode('utf-8')),lines(right.decode('utf-8'))
    if max(len(a),len(b))>MAX_LINES or len(a)*len(b)>MAX_LINE_PRODUCT:
        raise ValidationError('Diff melewati batas 2000 baris/source atau 1000000 pasangan baris; tidak dipotong diam-diam.')
    if left_record['target_index_sha256']!=right_record['target_index_sha256']:
        raise ValidationError('Revisi harus terikat pada target yang sama.')
    matcher=difflib.SequenceMatcher(None,a,b,autojunk=False)
    changes=[];added=removed=0
    for tag,a0,a1,b0,b1 in matcher.get_opcodes():
        checkpoint(cancel)
        if tag=='equal':continue
        removed+=a1-a0;added+=b1-b0
        changes.append({'kind':tag,'before':{'start_line':a0+1,'line_count':a1-a0,'lines':a[a0:a1]},
                        'after':{'start_line':b0+1,'line_count':b1-b0,'lines':b[b0:b1]}})
    def side(record,raw,line_list):
        return {'revision':record['revision'],'parent':record['parent'],'language':record['language'],
                'source_sha256':hashlib.sha256(raw).hexdigest(),'source_size':len(raw),
                'line_count':len(line_list),'ends_with_lf':raw.endswith(b'\n')}
    return {'schema':1,'engine':VERSION,'status':'TEXT_COMPARISON_ONLY',
            'target_index_sha256':left_record['target_index_sha256'],
            'before':side(left_record,left,a),'after':side(right_record,right,b),
            'source_bytes_equal':left==right,'language_equal':left_record['language']==right_record['language'],
            'direct_parent':right_record['parent']==left_record['revision'],
            'lines_added':added,'lines_removed':removed,'changes':changes,
            'compiled':False,'binary_match_verified':False,'semantics_verified':False,
            'limitations':['Text diff only; no C/C++ parsing or build',
                           'Line ranges are 1-based; zero line_count denotes an insertion point',
                           'LF line splitting preserves CR and missing final LF; no normalization']}
