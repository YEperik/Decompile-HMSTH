"""Read-only installation audit and explicit headless import plans, never execution.

Runtime verification and automated analysis/export await an actual Ghidra installation.
"""
import hashlib
import json
import os
from pathlib import Path
import shutil
import xml.etree.ElementTree as ET
from uuid import uuid4

from app.application.baselines import inspect_file
from app.application.workspaces import resolve_input
from app.domain.workspace.model import ValidationError, ConflictError, now
from app.infrastructure.persistence.store import read_bytes, MAX_MANIFEST


def _asset(directory, name):
    result = {'reference': name, 'status': 'MISSING_REFERENCE'}
    if not name:
        return result
    relative = Path(name)
    if relative.is_absolute() or '..' in relative.parts or '\\' in name:
        return dict(result, status='UNSAFE_REFERENCE')
    path = directory / relative
    if not path.resolve().is_relative_to(directory.resolve()):
        return dict(result, status='UNSAFE_REFERENCE')
    if not path.is_file():
        return dict(result, status='NOT_FOUND')
    before = path.stat()
    if not 0 < before.st_size <= 64 * 1024**2:
        return dict(result, status='INVALID_SIZE')
    digest = hashlib.sha256()
    total = 0
    with path.open('rb') as stream:
        opened = os.fstat(stream.fileno())
        while True:
            chunk = stream.read(1024 * 1024)
            if not chunk:
                break
            total += len(chunk)
            if total > 64 * 1024**2:
                return dict(result, status='INVALID_SIZE')
            digest.update(chunk)
        after = os.fstat(stream.fileno())
    def identity(st):
        return (st.st_dev, st.st_ino, st.st_size, st.st_mtime_ns, st.st_ctime_ns)
    if not identity(before) == identity(opened) == identity(after) == identity(path.stat()):
        return dict(result, status='CHANGED_DURING_READ')
    return dict(result, status='PRESENT', path=str(path), size=total, sha256=digest.hexdigest(),
                semantics_verified=False)


def check_install(home=None, language_dirs=()):
    if home is None:
        home = os.environ.get('GHIDRA_INSTALL_DIR')
        launcher = shutil.which('analyzeHeadless')
        if not home and launcher:
            home = str(Path(launcher).resolve().parent.parent)
    base = {'runtime_verified': False, 'executed': False,
            'java_path_candidate': shutil.which('java'),
            'scope': 'Installation declarations only; Java compatibility, loader and PS2 language semantics unverified'}
    if not home:
        return dict(base, status='NOT_FOUND', home=None, languages=[],
                    hint='Berikan --ghidra-home ke instalasi Ghidra tepercaya; tidak ada auto-install.')
    root = Path(home).absolute()
    properties = root/'Ghidra/application.properties'
    launcher = root/'support'/('analyzeHeadless.bat' if os.name == 'nt' else 'analyzeHeadless')
    if not properties.is_file() or not launcher.is_file():
        return dict(base,status='INCOMPLETE',home=str(root),languages=[],
                    hint='application.properties atau launcher headless tidak tersedia.')
    raw = read_bytes(properties)
    props = {}
    try:
        text = raw.decode('utf-8')
    except UnicodeDecodeError as exc:
        raise ValidationError('application.properties bukan UTF-8 valid.') from exc
    for line in text.splitlines():
        if '=' in line and not line.lstrip().startswith(('#','!')):
            key,value = line.split('=',1);props[key.strip()] = value.strip()
    version = props.get('application.version')
    if not version:
        raise ValidationError('Versi deklarasi Ghidra tidak ditemukan.')
    if len(language_dirs) > 16:
        raise ValidationError('Maksimum 16 direktori language tambahan.')
    core = list((root/'Ghidra/Processors').glob('*/data/languages/*.ldefs'))
    extensions = list((root/'Ghidra/Extensions').glob('*/data/languages/*.ldefs'))
    extra = []
    for directory in language_dirs:
        folder = Path(directory).absolute()
        if not folder.is_dir():
            raise ValidationError('Direktori language tidak ditemukan: ' + str(folder))
        extra.extend(folder.glob('*.ldefs'))
    files = sorted({file.resolve() for file in core + extensions + extra})
    if len(files) > 512:
        raise ValidationError('Jumlah ldefs melebihi batas audit 512 file.')
    languages = []
    for file in files:
        content = read_bytes(file)
        if b'<!DOCTYPE' in content or b'<!ENTITY' in content:
            raise ValidationError('DTD/entity pada ldefs tidak didukung.')
        try:
            tree = ET.fromstring(content)
        except ET.ParseError as exc:
            raise ValidationError('ldefs XML invalid: ' + file.name) from exc
        for lang in tree.findall('language'):
            if lang.get('processor','').upper() not in ('MIPS', 'MIPS-R5900'):
                continue
            if len(languages) >= 2048:
                raise ValidationError('Katalog MIPS melebihi batas 2048 language.')
            assets = {'sla': _asset(file.parent, lang.get('slafile')),
                      'pspec': _asset(file.parent, lang.get('processorspec'))}
            specs = [{'id': c.get('id'), 'asset': _asset(file.parent, c.get('spec'))}
                     for c in lang.findall('compiler')]
            languages.append({'id': lang.get('id'), 'processor': lang.get('processor'),
                              'endian': lang.get('endian'), 'size': lang.get('size'),
                              'variant': lang.get('variant'),
                              'compiler_specs': [c['id'] for c in specs],
                              'compiler_assets': specs, 'language_assets': assets,
                              'catalog_in_installation': file.is_relative_to(root.resolve()),
                              'ldefs_path': str(file), 'ldefs_sha256': hashlib.sha256(content).hexdigest()})
    return dict(base,status='DECLARED',home=str(root),launcher=str(launcher),
                launcher_executable=os.access(launcher,os.X_OK),declared_version=version,
                declared_java_min=props.get('application.java.min'),
                properties_sha256=hashlib.sha256(raw).hexdigest(),languages=languages,
                extension_catalog_scanned=True, extra_language_dirs=[str(Path(x).absolute()) for x in language_dirs],
                asset_validation='Presence and SHA-256 only; includes, SLEIGH compatibility and runtime not verified')


def create_plan(store, input_id, home, language, cspec, language_dirs=()):
    install = check_install(home, language_dirs)
    if install['status'] != 'DECLARED':
        raise ValidationError('Instalasi Ghidra belum lengkap/tersedia; rencana tidak dibuat.')
    candidates = [x for x in install['languages'] if x['id'] == language]
    if len(candidates) != 1 or cspec not in candidates[0]['compiler_specs']:
        raise ValidationError('Language/cspec tidak ditemukan secara unik dalam instalasi.')
    selected = candidates[0]
    if not install['launcher_executable'] and os.name != 'nt':
        raise ValidationError('Launcher Ghidra tidak executable pada POSIX.')
    if not selected['catalog_in_installation']:
        raise ValidationError('Katalog eksternal hanya untuk audit; pemasangan/discovery oleh Ghidra belum diverifikasi.')
    specs = [x for x in selected['compiler_assets'] if x['id'] == cspec]
    if len(specs) != 1 or any(x['status'] != 'PRESENT' for x in selected['language_assets'].values()) or specs[0]['asset']['status'] != 'PRESENT':
        raise ValidationError('Berkas language/compiler spec hilang, ambigu atau tidak aman; periksa ghidra-check.')
    if selected['endian'] != 'little' or selected['size'] != '32':
        raise ValidationError('Rencana awal dibatasi deklarasi MIPS little-endian address size 32.')
    for token in (language, cspec):
        if not token or token.startswith('-') or any(ord(c)<32 for c in token):
            raise ValidationError('ID language/cspec tidak aman untuk argv.')
    snapshot = store.load()
    item = next((x for x in snapshot.data['inputs'] if x['id'] == input_id),None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan.')
    source = resolve_input(store,item)
    baseline = inspect_file(source)
    if (baseline['source_sha256'],baseline['source_size']) != (item['sha256'],item['size_bytes']):
        raise ConflictError('Input berubah sejak registrasi; rencana dibatalkan.')
    plan_id = str(uuid4())
    parent = store.managed('ghidra')
    folder = store.managed('ghidra/'+plan_id)
    projects = folder/'projects'
    argv = [install['launcher'],str(projects),'workbench-'+plan_id,
            '-import',str(source),'-processor',language,'-cspec',cspec,
            '-noanalysis','-log',str(folder/'headless.log')]
    result = {'schema_version':1,'id':plan_id,'created_at':now(),'status':'PLAN_ONLY',
              'executed':False,'analysis_enabled':False,'input_id':input_id,
              'source_sha256':item['sha256'],'manifest_token':snapshot.token,
              'installation':install,'selected_language':selected,'compiler_spec':cspec,
              'argv':argv,'plan_path':str(folder/'plan.json'),
              'unverified':['Ghidra runtime and Java compatibility','EE/IOP identity and instruction coverage',
                            'loader address mapping','import and exported analysis'],
              'warning':'Review target first; this is a saved import command, not completed analysis. Revalidate input and installation before execution.'}
    raw = (json.dumps(result,indent=2)+'\n').encode()
    if len(raw) > MAX_MANIFEST:
        raise ValidationError('Rencana Ghidra melebihi batas metadata.')
    with store.lock():
        if store.load().token != snapshot.token:
            raise ConflictError('Manifest berubah saat menyiapkan Ghidra.')
        parent.mkdir(exist_ok=True);folder.mkdir();projects.mkdir()
        store.atomic(f'ghidra/{plan_id}/plan.json',raw)
    return result
