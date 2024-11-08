# Incorporating the VIP memory model into CN

We have updated the memory model of CN to more closely match de facto C, and
correspondingly updated the verification of the pKVM buddy allocator
(`d3e_cn_vip_example.tar.gz`). It can also also be found
in our [GitHub
repository](https://github.com/rems-project/CN-pKVM-buddy-allocator-case-study)
(branch `vip`). For running CN on it (after installing Cerberus and CN, see
above) run `cn --vip page_alloc.c`.

## Details

One of the ways C compilers try to optimise programs is by alias analysis of
code involving pointers (e.g. to deduce two pointers do not refer to the same
object). Such analysis is built upon the assumption that pointers are constructed
only in "reasonable" ways (otherwise being undefined behaviour; for further
details, see chapter 8, [Memarian, K. (2022). The Cerberus C
semantics](https://doi.org/10.17863/CAM.96843)). Taking into account the
origin of a pointer gives rise to the concept of _provenance_.

If provenance is taken into account, then certain optimisations
by compilers are valid. If it is not, then these optimisations are
invalid. Whether provenance is taken into account, and _how_, are some of the
many choices involved in designing a _memory object model_ for a programming language.
This model acts as a contract between compilers and programmers: programmers
promise to write programs within the rules of the model, and in return,
compilers will optimise code by assuming those rules hold in all code. A memory
model which ignores provenance is called "concrete".

CN's prior implementation assumed a concrete memory model, where pointers were
just a different name for integers. This was because it was not critical to
the buddy allocator (for which the main focus was complex invariants about the
computation of pointers). It was also because the particular memory model
preferred by WG14 standards committee (PNVI-ae-udi) was designed to accurately
capture the behaviour of existing programs (without modification) and compiler
assumptions - work 'out of the box' so to speak.

However, when we are verifying code with annotations, we can relax the
requirement for programs to be modeled accurately out of the box.  In
particular, if we require integer-to-pointer casts to be annotated (as
detailed in the paper [_VIP: Verifying Real-World C Idioms with Integer-Pointer
Casts_ by Lepigre et. al, 2022](https://doi.org/10.1145/3498681)), we can
simplify the implementation for us, and error messages, explanations and
suggestions given to users.

In CN, we require integer-to-pointer casts to be annotated (inherited from VIP)
and model pointers as pairs of pairs of a provenance `@i` and an address `a`
(inherited from PNVI-ae-udi). Using this, CN's memory model defines the
"reasonable" means by which programmers can create and use pointers (and avoid
undefined behaviour). Broadly speaking, the rules serve two related purposes:
(a) ensuring pointer operations correctly preserve or annotate into the program
the provenance information (b) ensuring that `(@i, a)` provenance-address pairs
are always sensible, by checking whether `a` falls within the bounds associated
with `@i`.

Whilst VIP formed the basis of CN's memory model, integrating it into the
existing design and implementation was not obvious nor straightforward. To
understand the complexities involved (before committing substantial resources
to updating CN and the buddy allocator verification), we first worked out the
design theoretically, by updating the pre-existing formalisation of CN's rules
(for a annotated programs with little type-inference). We then proved that
those updates made the design compatible with VIP.

After this, we proceeded to implement the memory model in CN and update the
buddy allocator in two stages, corresponding to the aforementioned two related
purposes provided by the VIP rules. The first stage, ensuring pointer
operations correctly preserve or annotate into the program the provenance
information, is complete in CN and works with a modified version of the buddy
allocator code. The memory-model-related modifications are straightforward to
explain, concerning only integer-to-pointer casts:

1. `u64 __hyp_vmemmap` was changed to `struct hyp_page *__hyp_vmemmap`, thus
   giving it a provenance. This enabled us to enforce the invariant that all
   `struct hyp_page` pointers originate from the virtual memory map array.
2. 5 instances of `hyp_page_to_virt(p)` were changed to
   `CN_COPY_ALLOC_ID(hyp_page_to_virt(p), cn_virt_ptr)`. Allocation IDs are
   simply the VIP name for provenances, and the C function `CN_COPY_ALLOC_ID`
   is coaxing existing C compilers into producing a pointer with address
   `hyp_page_to_virt(p)` but with provenance the same as `cn_virt_ptr`[^1].
   `cn_virt_ptr` is a simply a global pointer with the single provenance which
   all pages donated by Linux should have (from pKVM's point of view). We need
   this because the `hyp_page_to_virt` macro computes an integer address (no
   provenance), and so needs to be assigned the appropriate provenance.

[^1]: It is defined as `void *CN_COPY_ALLOC_ID(uintptr_t i, void *p){
  (uintptr_t) p; return (void*) i; }`, which, for technical reasons, achieves
  the desired effect.

The changes to CN are part of Cerberus, in `d3c_cn_pgtable_tool.tar.gz` in
`cerberus/backend/cn` (also available on the [Cerberus GitHub
repository](https://github.com/rems-project/cerberus)).

The changes the buddy allocator code are in
(`d3e_cn_vip_example.tar.gz`), and can also also be found
in our [GitHub repository](https://github.com/rems-project/CN-pKVM-buddy-allocator-case-study)
(branch `vip`). It can be verified (after installing Cerberus and CN, see
above) by running `cn --vip page_alloc.c`.

The second stage, ensuring that `(@i, a)` provenance-address pairs are always
sensible, by checking whether `a` falls within the bounds associated with `@i`,
is underway in CN, and should only require minor changes to the buddy allocator
specification.

Because the two primary CN developers and users (Christopher Pulte and Thomas
Sewell) were working on bitvector support and page-table verification, these
changes were undertaken in parallel by someone new to the CN and buddy
allocator code bases (Dhruv Makwana, who formerly only worked the formalisation
and c-tree-carver).

The experience showed that it is possible to ramp-up on both projects
relatively independently. This indicates that CN retains the potential to be
usable by non-academic programmers. The biggest roadblock was understanding the
complex invariants maintained by the buddy allocator, which suggests the
complexity is mostly inherent, rather than exacerbated greatly by CN.

The VIP in CN work highlighted some strengths and some weaknesses. The speed of
CN, whilst not reaching the pace required for IDE-integration, was never a
bottleneck. The SMT-solver counter-examples were sometimes useful in diagnosing
and preventing value-assignments that should be impossible. At other times, the
counter-examples were unwieldy and difficult to relate to particular CN
checking steps, with descriptive variable names being the only clue to
diagnosing the problem. We identified a bug where an error message was showing
an unhelpfully broad error location. We could also improve error reporting by
better storing/tracing the state of the typechecker, so we can replay it
line-by-line on the code being verified, like a debugger.

