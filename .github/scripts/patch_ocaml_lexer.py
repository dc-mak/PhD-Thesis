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

Run this after installing pygments, before any minted-based build. It
edits the installed package in place and fails loudly if pygments'
internals no longer match what is expected here, so CI breaks visibly
instead of silently reverting to the old (buggy) behaviour.
"""

import pygments.lexers.ml as m

path = m.__file__
text = open(path, encoding="utf-8").read()

start = text.index("class OcamlLexer(RegexLexer):")
end = text.index("class OpaLexer(RegexLexer):", start)
body = text[start:end]

old = "']', '_', '`',"
new = "']', r\"_(?![\\w'])\", '`',"
assert old in body, "OcamlLexer keyopts text not found; pygments internals changed"
body = body.replace(old, new, 1)

text = text[:start] + body + text[end:]
open(path, "w", encoding="utf-8").write(text)
print(f"Patched OcamlLexer wildcard handling in {path}")
