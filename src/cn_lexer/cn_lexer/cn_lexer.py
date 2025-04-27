from pygments.lexer import Lexer
from pygments.lexers import CLexer
from pygments.token import Text, Comment
import re, sys

from cn_lexer.cn_spec_lexer import CNSpecLexer

# Disclaimer: ChatGPT helped write this. It may be a silly way to code a
# Pygments lexer. That being said, it works.

class CNLexer(Lexer):
    name = 'cn'
    aliases = ['cn']
    filenames = ['*.c', '*.h']

    def __init__(self, **options):
        super().__init__(**options)
        self.clexer = CLexer(**options)
        self.speclexer = CNSpecLexer(**options)

        # Precompile regex: find start of /*@ ... @*/
        self.splitter = re.compile(r'/\*@.*?@\*/', re.DOTALL)

    def get_tokens_unprocessed(self, text):
        pos = 0

        for match in self.splitter.finditer(text):
            start, end = match.span()

            # Handle normal C code before the match
            if start > pos:
                for i, t, v in self.clexer.get_tokens_unprocessed(text[pos:start]):
                    yield i + pos, t, v

            # Yield the comment token for /*@
            yield start, Comment.Spec, "/*@"

            # Handle the matched spec comment
            spec_comment = text[start:end]
            # Strip the /*@ and @*/ before feeding
            spec_inner = spec_comment[3:-3]

            for i, t, v in self.speclexer.get_tokens_unprocessed(spec_inner):
                yield i + start + 3, t, v

            # Yield the comment token for @*/
            yield end - 3, Comment.Spec, "@*/"

            pos = end

        # Handle remaining C code after last match
        if pos < len(text):
            for i, t, v in self.clexer.get_tokens_unprocessed(text[pos:]):
                yield i + pos, t, v
