#!/usr/bin/env python3
"""Validate repository links and source structure without running project code."""
import ast
import re
import subprocess
import sys
import tokenize
import xml.etree.ElementTree as ET
from pathlib import Path
from urllib.parse import unquote, urlsplit

ROOT = Path(__file__).resolve().parents[1]


def candidate_files():
    if (ROOT / '.git').is_dir():
        result = subprocess.run(
            ['git', '-C', str(ROOT), 'ls-files', '--cached', '--others', '--exclude-standard', '-z'],
            check=True, stdout=subprocess.PIPE,
        )
        return sorted({ROOT / p.decode('utf-8') for p in result.stdout.split(b'\0') if p})
    return sorted(p for p in ROOT.rglob('*') if p.is_file()
                  and not any(x in p.parts for x in ('.local-archive', '.git', '__pycache__')))


def slug(text):
    return re.sub(r'[^\w\u4e00-\u9fff -]', '', text.lower()).replace(' ', '-')


def main():
    errors = []
    files = candidate_files()
    markdown_count = python_count = 0
    for file in files:
        if not file.is_file():
            continue
        relative = file.relative_to(ROOT)
        if file.stat().st_size > 100 * 1024 * 1024:
            errors.append(f'{relative}: file exceeds repository 100 MiB size budget')
        if file.suffix == '.py':
            python_count += 1
            try:
                with tokenize.open(file) as stream:
                    ast.parse(stream.read(), filename=str(relative))
            except (SyntaxError, UnicodeError) as exc:
                errors.append(f'{relative}: Python syntax/encoding error: {exc}')
        if file.suffix != '.md':
            continue
        markdown_count += 1
        text = file.read_text(encoding='utf-8')
        if len(re.findall(r'^```', text, re.M)) % 2:
            errors.append(f'{relative}: unclosed fenced code block')
        visible = re.sub(r'^```[^\n]*\n.*?^```\s*$', '', text, flags=re.M | re.S)
        for link in re.findall(r'!?\[[^\]]*\]\(([^\n)]+)\)', visible):
            link = link.strip().strip('<>')
            parts = urlsplit(link)
            if parts.scheme or parts.netloc:
                continue
            target = (file.parent / unquote(parts.path)).resolve() if parts.path else file
            if not target.exists():
                errors.append(f'{relative}: broken relative link: {link}')
                continue
            if parts.fragment and target.suffix == '.md':
                anchors = {slug(x) for x in re.findall(r'^#{1,6} (.+)$', target.read_text(), re.M)}
                if unquote(parts.fragment) not in anchors:
                    errors.append(f'{relative}: missing heading: {link}')
    project = ROOT / 'firmware/stm32/Project.uvprojx'
    try:
        tree = ET.parse(project)
        refs = tree.findall('.//FilePath')
        for ref in refs:
            target = project.parent / ref.text.replace('\\', '/')
            if not target.is_file():
                errors.append(f'Keil file reference missing: {ref.text}')
    except (ET.ParseError, OSError) as exc:
        errors.append(f'Cannot read Keil project: {exc}')
        refs = []
    guide = ROOT / 'docs/build-guide.md'
    image_count = len(re.findall(r'!\[[^\]]*\]\(([^)]+)\)', guide.read_text()))
    if image_count != 70:
        errors.append(f'Expected 70 guide images, found {image_count}')
    if errors:
        print('\n'.join(errors), file=sys.stderr)
        return 1
    print(f'PASS: {markdown_count} Markdown files, {python_count} Python files, '
          f'{len(refs)} Keil references, {image_count} guide images.')
    print('Static validation only: no hardware access, model loading, or firmware compilation.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
