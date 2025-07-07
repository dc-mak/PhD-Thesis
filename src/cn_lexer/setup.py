from setuptools import setup

setup(
    name="cn-lexer",
    version="0.1",
    packages=["cn_lexer"],
    entry_points={
        "pygments.lexers": [
            "cn = cn_lexer.cn_lexer:CNLexer",
            "cn-spec = cn_lexer.cn_spec_lexer:CNSpecLexer",
        ],
    },
)

