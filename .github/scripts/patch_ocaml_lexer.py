"""Patch Pygments' OCaml lexer so a leading run of underscores (e.g. the
"__" in "__FUNCTION__") is treated as part of the identifier instead of
being split into standalone wildcard-pattern '_' tokens.

Pygments' OcamlLexer.keyopts matches a bare '_' with no boundary check, so
it always wins the wildcard-pattern match even when it is part of a longer
identifier. OCaml's own grammar defines the wildcard as a *standalone* '_'
token, so this only matches '_' when it is not followed by another
identifier character. A plain \\b boundary is not enough: OCaml identifiers
may continue with a prime (e.g. "_'"), and ' is not a \\w character, so \\b
would still misfire on that case.

`pip install pygments` is not enough to fix this for real builds: TeX
Live's `setup-texlive-action` ships its own self-contained `latexminted`
executable, bundled with its own `pygments-*.whl` sitting next to it on
disk. That executable's launcher script prepends its bundled wheels to
`sys.path` itself, so it never sees a separately pip-installed Pygments
regardless of PATH order -- and forcing a *different* latexminted onto
PATH breaks minted's own version-compatibility check instead (it expects
the exact latexminted build TeX Live shipped). So this patches the
OCaml lexer directly inside that bundled wheel (a zip file), in place,
without touching which `latexminted` executable actually runs or its
declared version.

Run this once latexminted is available on PATH (i.e. after "Setup TeX
Live"). It fails loudly if pygments' internals, or the bundled wheel
layout, no longer match what is expected here, so CI breaks visibly
instead of silently reverting to the old (buggy) behaviour.
"""

import shutil
import sys
import zipfile
from pathlib import Path

latexminted_path = shutil.which("latexminted")
assert latexminted_path, "latexminted not found on PATH"

latexminted_dir = Path(latexminted_path).resolve().parent
wheel_paths = list(latexminted_dir.glob("pygments*.whl"))
assert wheel_paths, f"no pygments*.whl found next to {latexminted_path}"
assert len(wheel_paths) == 1, f"expected exactly one pygments wheel, found {wheel_paths}"
wheel_path = wheel_paths[0]

with zipfile.ZipFile(wheel_path, "r") as zf:
    names = zf.namelist()
    ml_names = [n for n in names if n.endswith("pygments/lexers/ml.py")]
    assert len(ml_names) == 1, f"expected exactly one pygments/lexers/ml.py entry, found {ml_names}"
    ml_name = ml_names[0]
    contents = {n: zf.read(n) for n in names}
    infos = {n: zf.getinfo(n) for n in names}

text = contents[ml_name].decode("utf-8")

old = "']', '_', '`',"
new = "']', r\"_(?![\\w'])\", '`',"
assert old in text, f"OcamlLexer keyopts text not found in {ml_name}; pygments internals changed"
text = text.replace(old, new, 1)
contents[ml_name] = text.encode("utf-8")

tmp_path = wheel_path.with_suffix(".whl.tmp")
with zipfile.ZipFile(tmp_path, "w", zipfile.ZIP_DEFLATED) as zf:
    for name, data in contents.items():
        zf.writestr(infos[name], data)
tmp_path.replace(wheel_path)

print(f"Patched {ml_name} inside {wheel_path}", file=sys.stderr)
