# C carver tooling to pull out pKVM-relevant parts of the Linux source tree

pKVM code lives in the Linux source repository and includes standard Linux
headers for common data structures (such as the doubly-linked lists used in the
buddy allocator), operations and architecture specific macros. It also includes
a large number of non-standard C extensions and syntax (e.g. for enforcing
compile-time asserts amongst other things).

This setup makes it challenging to run any given file through a tool such as
Cerberus (and consequently, CN), because of (a) the volume of code to be parsed
(thousands of lines) and (b) the number of unsupported constructs. Thankfully,
almost all of these lines of code and constructs are _irrelevant_ to the
functions which we wish to verify. Thus, if we had a tool to systematically
filter out those things, and only retain the relevant parts, we could
feed that tool's output into CN and proceed unimpeded.

Without such a tool, we would have to manually carve out the appropriate subset
of C source tree to feed into CN. Having done this twice for the buddy
allocator (once initially, once for updating the code), we realised that the
multiple researcher days spent on this mundane and error-prone task should be
automatable.

In the last deliverable, we mentioned a "c-simplifier" tool which was able to
take a root function (the example tested was `kvm_pgtable_walk` in `pgtable.c`)
and a `compile_commands.json` file (generated using
[Bear](https://github.com/rizsotto/Bear/) in the existing pKVM build system)
and produce a directory structure with all relevant files and symbols included.
However, although it demonstrated the feasibility of the approach, the tool was
not "production-ready" in the sense of being an transparent part of the
pipeline of running CN on larger parts of the pKVM code base.

In this deliverable, we achieved this (and renamed the tool). As before,
c-tree-carver is forked from an [existing tool for
C++](https://github.com/logicmachine/cpp-simplifier/); we continue to license
new source code under the usual BSD 2-Clause License, whereas source code
shared with the C++ tool is under its original MIT License.

## Details

The c-tree-carver now extracts the definitions of a user-specified set of
functions and their minimal dependencies (from a larger C code base) into a
self-contained _directory_, whilst preserving macros and line-numbers, thus
enabling accurate error messages. It also runs faster and preserves comments,
thus enabling CN to be run directly within the Linux repository, removing the
need for working on extracted files and reducing merge conflicts. Tarball
`d4a_c-tree-carver.tar.gz` contains the source code, which can also be found in
its [GitHub repository](https://github.com/rems-project/c-tree-carver).

To achieve this, we added several features:
* Regression testing.
* Support for newer versions of Clang - closer to the versions used by the
  build system.
* Macro dependency inclusion - if code uses a macro, then the definitions of
  that macro and all the macros it refers to must also be included.
* Commenting out instead of omitting irrelevant lines - for accurate error
  messages for the rest of the pipeline (by preserving line numbers).
* Comment retention - CN annotations are in the form of comments, and these
  must be preserved by the tool unaffected, with good error messages.
* `#include` retention - if a file has `#include <used.h>` and uses a macro or
  a symbol from it (or any of the files it includes), then that include must be
  retained. Conversely, if nothing is used from that file (or any of its
  dependents) then that include must be commented out.
* Build-system integration - comment retention is written in OCaml but
  declaration and macro inclusion is in C++, so different build systems were
  combined to produce and easy to install executable.
* Input validation for top-level declarations - the tool checks that a line
  contains at most one top-level, and produces an error message if not.

Below is a small input-output example which illustrates some of the features.

First, a header file containing struct definitions (with some comments, as well
as attributes). It also includes a block comments of different kinds, as well
as a line comment.

```
// struct_fields.h
struct s1 {
    int s1_field;
    char UNUSED;
};

typedef struct {
    int s2_field;
} s2;

enum e1 {
    ONE=5,
    TWO=(7 << (2-1))
};

typedef struct {
 int s3_field;
} __attribute__((__aligned__((1 << (6))))) s3;
/* multiline
   block
   comment */

extern struct s2 thing2; /* single-line block comment */

extern __attribute__((section(".data..percpu" "..shared_aligned"))) __typeof__(s3) irq_stat __attribute__((__aligned__((1 << (6)))));


typedef struct {
    s2 (*s4_field)(s3);
} s4;

enum e5 {
    THREE=3
};
```

The header is included by a simple C file. Note that the main function uses a
macro, which must be retained in the output. It also uses comments, which must
remain unaffected. It uses the `enum e1` and `struct s6` only indirectly, via
function `f`. Furthermore, `struct s6` is used after its (forward) declaration,
but before it is defined - the actual definition is used separately.  Only
`s1_field` of `struct s1` is used, not `char UNUSED`. Additionally, the `enum
e5` is referred to only via the use of the constant `THREE` in the type of the
parameter to `g`.

```
// struct_fields.c
//#define PLUS_FIVE(x) (x+5)

#define MACRO_TEST 1

#include "struct_fields.h"

s3 g(struct s1 s1, s4 arr[THREE])
{
    return irq_stat;
}

struct s6;

int f(enum e1 z, struct s6* z2) {
    return z;
}

struct s6 {
    int s6_field;
};

// Typedef-ing on the struct type directly creates a new type
typedef struct s6 s6;

int main() {
    enum e1 main1 = ONE;
    struct s6 main6 = { .s6_field = MACRO_TEST };
    struct s1 main2 = { .s1_field = f(main1, &main6) };
    s3 main3 = { .s3_field = 1 };
    s4 main4 = { .s4_field = (void*)0 };
    s4 main5[3];
    return g(main2, main5).s3_field;
}
```

From the root of `c-tree-carver` repository, run `cd cpp`
and then create a `compile_commands.json` file with the following
contents.

```
[
  {
      "directory": "/home/dhruv/c-tree-carver/cpp",
      "command": "clang -c test/to-add/struct_fields.c",
      "file": "test/to-add/struct_fields.c"
  }
]
```

Then run `c-tree-carve test/to-add/struct_fields.c` to get a directory printed
out along the lines of `/tmp/c-tree-carver-81648e`. Run `cat
/tmp/c-tree-carver-81648e/test/to-add/*`, to see the resulting file contents.

What we see in the output is that all comments are preserved unaffected.
Furthermore, unused lines are prefixed with `//-`.

```
// struct_fields.h
struct s1 {
    int s1_field;
//-    char UNUSED;
};

typedef struct {
    int s2_field;
} s2;

enum e1 {
    ONE=5,
    TWO=(7 << (2-1))
};

typedef struct {
 int s3_field;
} __attribute__((__aligned__((1 << (6))))) s3;
/* multiline
   block
   comment */

//-extern struct s2 thing2; /* single-line block comment */

extern __attribute__((section(".data..percpu" "..shared_aligned"))) __typeof__(s3) irq_stat __attribute__((__aligned__((1 << (6)))));


typedef struct {
    s2 (*s4_field)(s3);
} s4;

enum e5 {
    THREE=3
};
```

Similarly in the C file, we see that the comments are correctly unaffected, but
the macros, the `#include`, the functions and the used types are left
uncommented, whereas the unused `typedef struct s6 s6` is commented out.


```
// struct_fields.c
//#define PLUS_FIVE(x) (x+5)

#define MACRO_TEST 1

#include "struct_fields.h"

s3 g(struct s1 s1, s4 arr[THREE])
{
    return irq_stat;
}

struct s6;

int f(enum e1 z, struct s6* z2) {
    return z;
}

struct s6 {
    int s6_field;
};

// Typedef-ing on the struct type directly creates a new type
//-typedef struct s6 s6;

int main() {
    enum e1 main1 = ONE;
    struct s6 main6 = { .s6_field = MACRO_TEST };
    struct s1 main2 = { .s1_field = f(main1, &main6) };
    s3 main3 = { .s3_field = 1 };
    s4 main4 = { .s4_field = (void*)0 };
    s4 main5[3];
    return g(main2, main5).s3_field;
}
```
