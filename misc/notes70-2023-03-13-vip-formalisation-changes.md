# Changes to formalisation to support VIP
---


Thanks to Kayvan, the pointer operations in the formalisation already live in
the resourceful/effectful fragment of Cerberus/CN-kernel-calculus (`is_exprs`).


Currently, heaps are simply just seperation logic predicates, which we need
to related to VIP heaps `(A, M)` and their transitions.

1. Define a satisfaction relation `(A, M) |= h`.
2. Prove a theorem: `forall memory actions <h, a> -> <h', a'>, (A, M) |= h.
   exists (A', M') |= h'. (A, M) -VIP-> (A', M')`.

## Details
---

Remember from the paper: "Note that this [location & integer] representation of
integers values lets VIP track pointer provenance via integers [...] this
allows supporting round-trip casts in cases where no pointer with a suitable
provenance is available to use as the second argument of the copy_alloc_id
instruction."

What we will to do is take VIP and make it simpler by having integers as the
only "integer values", since we can/expect to have the provenance we want
through annotations.

The changes to the pointer equality and comparison rules should be simple:
add a resource term as evidence of the liveness of allocation(s) used by the
operands - the operational semantics and the typing rules will be adjusted
a bit, but not much.

However, `kill`, `implode`, `congeal` (and maybe `glue`) operations will
all require a bit more effort. This is because all of these relate to
allocation-ids: `kill` requires an allocated object, `implode`/`congeal`
requires all the points-to/`Owned` fields/elements of the struct/array come from
the same struct/array (and maybe glue too).

One way of fixing this is having tokens, something like `struct(pval, tau, f)`
where `f ::= whole | part` as a resource term/types (similarly for fixed-length
arrays). This records the information that `[pval... pval + sizeof(tau))` is a
valid range for the addresses of member pointers, and that the original
allocation is live. It needs to be a resource (rather than a logical
constraint) since it should not outlive the `kill` of the original allocation.
To support this, each points-to/`Owned` would need to be further indexed by
`whole | part`, recording what it came from.

We still remain with an issue around iterated predicates - currently they can span
multiple allocation IDs so long as they are all expressable as steps of the required
size or wrapped in a resource predicated. One proposal is to additionally index 
iterated predicates with `whole | part` and only allow them to be spanning a single
allocation ID.


## How resources get updated 

We are going to index predicates with an extra "token" field, which
indicates whether the predicate holds the `whole` allocation or just
`part` of the allocation. (TODO: find a better name than "token".)

0. We need to add quantification over tokens. We will use `f` as the 
   metavariable for tokens. 

1. How to update `Owned<τ>(p)` 

   It becomes `Owned<τ>(f, p)`   – f is the token, and it is an input

   a. A `create` action gives you `Owned(full, p)`. 
   b. You can only kill `Owned(full, p)`
   c. You can load and store from `Owned(f, p)` for any `f`. 

2. Updating structs. This will mostly affect `implode`/`explode`

   For explode 

       C; L; ϕ; R ⊢ rt ⇒ p ↦^{init}_{struct t, f} v 
       struct t ^ memᵢ:τᵢ ∈ Globals for i ∈ I
       ———————————————————————————————————————————————————————————————
       C; L; ϕ; R ⊢ explode(rt) ⇒ 
         Bigstarᵢ (ptr + offsetof_{tag}(memᵢ) ↦^{init.memᵢ}_{τᵢ, part} v.memᵢ) 
         ∗ 
         struct_frame(τ, f, p)


   To summarise, we are adding token information to each pointsto and 
   we are leaving behind a `struct_frame` assertion which remembers 
   the token-status of the original struct. All of the exploded pointstos 
   have the `part` token status. 

   Implode will work symmetrically....

3. Updating arrays. 
   a. Fixed-size arrays work similarly to structs. 

   b. Iterated conjunctions require adaptation of break, glue etc

    C; L ⊢ t ⇒ int
    C; L; ϕ; R ⊢ rt ⇒ (x; ig){a(ptr + x·step, iargs)}(oarg)
    smt(ϕ ⇒ [t/x]ig)
    qpred = (x; ig ∧ x ≠ t){a(ptr + x·step, iargs)}(oarg)
    pred = a(ptr + t · step, [t/x]iargs)(oarg[term])
    ———————————————————————————————————————————————————————————————
    C; L; ϕ; R ⊢ break(rt, t) ⇒  

   
   


## Actions that need to be updated

from actions (pp. 87-88)

1. create
2. load
3. store
4. kill


from memop (pg. 88)

1. Pointer operations involving memory -- pointer equality/inequality/arithmetic
2. intFromPtr
3. ptrFromInt
4. ptrValidForDeref 
5. ptrArrayShift?


