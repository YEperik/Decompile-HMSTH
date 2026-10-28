"""Index validated relocation locations; no pointer or addend interpretation."""
from bisect import bisect_left
from app.domain.binary.elf import UnsupportedELF


class ReferenceIndex:
    def __init__(self):
        self.sections = {}
        self.locations = {}

    def add(self, section_index, location, record):
        self.sections.setdefault(section_index, []).append((location, record))

    def finish(self):
        for section_index, rows in self.sections.items():
            rows.sort(key=lambda row: row[0])
            self.locations[section_index] = [row[0] for row in rows]

    def within(self, resolved, elf_type):
        keys = [resolved['section_index']]
        if elf_type != 'REL':
            keys.append(0)
        selected = []
        for key in keys:
            positions = self.locations.get(key, [])
            left = bisect_left(positions, resolved['start'])
            right = bisect_left(positions, resolved['end_exclusive'])
            if right - left > 1024 - len(selected):
                raise UnsupportedELF('Lebih dari 1024 relokasi dalam satu OBJECT.')
            for location, record in self.sections.get(key, [])[left:right]:
                selected.append(dict(record, location=location))
        return selected
