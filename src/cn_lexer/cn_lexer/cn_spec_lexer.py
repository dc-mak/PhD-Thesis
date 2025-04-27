from pygments.lexer import RegexLexer, bygroups
from pygments.token import Keyword, Name, Number, Operator, Punctuation, Text, Comment, String

class CNSpecLexer(RegexLexer):
    name = 'cn-spec'
    aliases = ['cn-spec']

    tokens = {
        'root': [
            # Handle line comments inside spec code
            (r'//[^\n]*', Comment.Single),
            # Keywords
            (r'\b(datatype|function|predicate|lemma|requires|ensures|take|assert|match|return|if|else)\b', Keyword),
            # Types
            (r'\b(i32|pointer|struct|Owned|Nil|Cons)\b', Name.Class),
            # Identifiers
            (r'[A-Za-z_][A-Za-z0-9_]*', Name),
            # Numbers
            (r'\b\d+i32\b', Number.Integer),
            (r'\b\d+\b', Number.Integer),
            # Operators and punctuation
            (r'[\{\}\[\]\(\)\.,:;]', Punctuation),
            (r'==|=|->|=>|\|\||&&|!|[-+*/<>]', Operator),
            # Whitespace
            (r'\s+', Text),
            # Anything else (fallback)
            (r'.', Text),
        ]
    }

