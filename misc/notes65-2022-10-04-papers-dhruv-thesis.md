# Discussion about papers and Dhruv's thesis
---


## Paper 1
----
* recently (conditionally) accepted POPL paper
* specifically, formalisation of kernel calculus including soundness


## Paper 2
---
* extended example: page table, recursive functions
* proving stuff about inference


## Paper 3
---
* VIP for pointer provenance
* showing formalisation sound wrt it
* weak sequencing, fractional permissions


# Thesis
---
* "thing to point at to understand CN?" - TOPLAS paper instead?
* "formalising separation logic refinement type system for C"
  - practical stuff is evidence & context for the ideas
  - but the contribution is the formal stuff + anything practical I end up doing
* aspirational: the combination of the two (TOPLAS + thesis) should be enough
  for an expert to re-implement CN
* chapters
    1. Introduction
    2. Context
    3. Kernel calculus design principles & definitions (+ proofs)
    4. Inference system: how it works + why (+ proofs)
    5. Memory model - how it is handled (+ proofs)
        - maybe separate thing about (lack of) fractional permissions?
    6. Evaluation/practical stuff I did/evidence of usefulness
    7. Conclusion
    8. Appendix proofs










## NB: Formalisation as IR
---
* both of these rely on knowing we defs want/need to do this
* either Dhruv or master's student for building proof-checker (+ tools)
* potentially related to mapping assertions down to binary
* potentially related to runtime checking for assertions
