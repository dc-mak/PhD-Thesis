# Background

Pointers in C are a tuple of @i (provenance/allocation id) and addresses.

Relational operations (<, <=) require provenances to be equal to be used.

Pointer equality rules in VIP ignore provenances, and only compare addresses.

This is unsound to use as a logic.

Pointer equality in PNVI-ae-udi is 
prov eq,  addr eq  = true
prov eq,  addr neq = false
prov neq, addr neq = false
prov neq, addr eq  = { true, false } ie. ambiguous

# Typing rule post-condition for pointer equality
```
In the PNVI... paper,  p = (π, a)
addr(p) = fst(p)
prov(p) = snd(p)




{emp} 
p1 == p2 
{b. (addr(p1) = 0 ∧ addr(p2) = 0 ⇒ b = true) ∧
    (prov(p1) = prov(p2) ⇒ b = (addr(p1) = addr(p2))) ∧
    (prov(p1) ≠ prov(p2) ⇒ (b = (addr(p1) = addr(p2))) ∨ b = false) ∧
    ((¬(addr(p1) = 0 ∧ addr(p2) = 0) ∧
     ¬(prov(p1) = prov(p2) ⇒ b = (addr(p1) = addr(p2))) ∧
     ¬((prov(p1) ≠ prov(p2)))) ⇒ b = false) }

```

For now, we have decided that `==` in the specification language must mean
tuple equality (otherwise things would break mathematically) and if the
user writes this, they should be warned, since it is not clear whether
the user intended to opt in to C equality, or mathematical equality.

We must also provide functions such as `addr_eq` or `prov_addr_eq` so that it
the issue is made obvious to the writer and readers of specifications.

