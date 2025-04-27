from pygments.lexer import DelegatingLexer, bygroups, inherit
from pygments.lexers import CLexer
from pygments.token import Comment, Other
from cn_lexer.cn_spec_lexer import CNSpecLexer

import re

class CMagicLexer(CLexer):
    name = 'cmagic'
    aliases = ['cmagic']
    filenames = ['*.c', '*.h']

    flags = re.DOTALL
    tokens = {
        'root': [
            ('(/\*@)(.*?)(@\*/)', bygroups(Comment, Other.Magic, Comment)),
            inherit,
        ],
    }

    def __init__(self, **options):
        super().__init__(**options)

class CNLexer(DelegatingLexer):
    name = 'cn'
    aliases = ['cn']
    filenames = ['*.c', '*.h']

    def __init__(self, **options):
        super().__init__(CMagicLexer, CNSpecLexer, Other.Magic, **options)
