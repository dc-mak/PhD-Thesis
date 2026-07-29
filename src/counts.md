# Word counts

Counts are `text + headers + captions`. **Own** is the prose directly under a heading; **Total** rolls up all descendants.

## Chapters

| Chapter | Total | Own |
| :-- | --: | --: |
| Introduction | **5997** | 16 |
| Example: queues in CN | **2797** | 52 |
| Background: Cerberus and CN design | **6997** | 32 |
| Kernel CN: Grammar | **4247** | 158 |
| Kernel CN: Static semantics | **3892** | 340 |
| Kernel CN: Proof of soundness | **1522** | 169 |
| Informing implementation discussions | **1267** | 142 |
| An alternative presentation | **2077** | 92 |
| Memory object models, explained | **6739** | 395 |
| CN-VIP | **3141** | 107 |
| Epilogue on CN-VIP | **2843** | 45 |
| Tree-carving: Taming C Repositories | **2817** | 125 |
| Proof maintenance for pKVM buddy allocator | **3438** | 82 |
| CN Comparison and Feedback | **4203** | 177 |
| Not-so-great expectations | **5234** | 97 |
| Future Directions | **3285** | 22 |
| Conclusion | **1334** | 545 |

| **Document total** | **61830** | |

## Introduction

**Chapter total: 5997** (own 16)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Context |  |  | 620 |
| Thesis statement |  |  | 87 |
| Background |  | 3632 | 1 |
|  | The C programming language |  | 853 |
|  | Verification with Separation Logic |  | 1615 |
|  | CN: C, No bugs! |  | 1163 |
| Contributions of this thesis |  | 1642 | 66 |
|  | Formalisation of CN |  | 236 |
|  | Memory object model: design, formalisation and implementation |  | 231 |
|  | Engineering: will the real-world C, please stand up? |  | 326 |
|  | Contributions in published papers |  | 783 |

## Example: queues in CN

**Chapter total: 2797** (own 52)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| CN Syntax |  |  | 370 |
| Queue definitions |  |  | 779 |
| Queue implementation |  |  | 797 |
| Proofs of lemmas |  |  | 799 |

## Background: Cerberus and CN design

**Chapter total: 6997** (own 32)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| CN design goals and constraints |  |  | 980 |
| Cerberus and Core for a usable and accurate C semantics |  |  | 266 |
| Core grammar |  |  | 828 |
| Elaboration example: list append |  | 1258 | 997 |
|  | Discussion |  | 261 |
| Decidable refinements for retrofitting and counter-examples |  |  | 548 |
| Bidirectionality for taming subtyping |  |  | 494 |
| Linearity to manage (non-leaky) resources |  |  | 693 |
| Section |  | 1111 | 517 |
|  | Precise assertions |  | 594 |
| Monadic syntax for mode-correctness |  |  | 374 |
| Iterated separating conjunctions to handle arrays |  |  | 413 |

## Kernel CN: Grammar

**Chapter total: 4247** (own 158)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Kernel CN types |  |  | 576 |
| Desugaring CN types into kernel types |  |  | 727 |
| ResCore |  |  | 856 |
| Permissions resource terms |  |  | 1039 |
| Core to ResCore example |  |  | 891 |

## Kernel CN: Static semantics

**Chapter total: 3892** (own 340)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Contexts |  |  | 66 |
| Pure values and expressions |  |  | 257 |
| Pure statements |  |  | 201 |
| Resource terms |  | 682 | 63 |
|  | Synthesis for resource terms |  | 205 |
|  | Synthesis for predicate operations |  | 141 |
|  | Checking for resource terms |  | 273 |
| Memory actions and pointer operations |  |  | 420 |
| Spine judgement |  |  | 228 |
| Effectful values and expressions |  |  | 69 |
| pattern-matching |  |  | 385 |
| Effectful statements |  |  | 128 |
| Elaboration |  | 1116 | 538 |
|  | Normalised resource contexts |  | 171 |
|  | Synthesising output arguments |  | 246 |
|  | Synthesising indices for iterated predicates |  | 161 |

## Kernel CN: Proof of soundness

**Chapter total: 1522** (own 169)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Substitution and contexts |  |  | 359 |
| Heaps and their types |  |  | 508 |
| Soundness |  |  | 486 |

## Informing implementation discussions

**Chapter total: 1267** (own 142)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Supporting loads of partially initialised structs/unions |  |  | 305 |
| Automatic unfolding scheme for logical functions |  |  | 218 |
| Higher-order resources |  |  | 105 |
| Restrictions on branching |  |  | 211 |
| Removing the pointer first restriction on predicates |  |  | 137 |
| Unifying the syntax of functions, predicates and specifications |  |  | 149 |

## An alternative presentation

**Chapter total: 2077** (own 92)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| MiniC and MiniCN |  |  | 250 |
| Aliasing requires linear resources |  |  | 259 |
| Implicit resource terms intertwine elaboration and typing |  |  | 146 |
| Early-returns intertwine normalising, synthesising and checking |  |  | 255 |
| Lack of let-normalisation requires join-points |  |  | 94 |
| Discussion |  |  | 981 |

## Memory object models, explained

**Chapter total: 6739** (own 395)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| PNVI-ae-udi |  | 1183 | 47 |
|  | Provenance not tracked via integers |  | 623 |
|  | Ae: Considering only exposed |  | 334 |
|  | Udi: symbolic provenances for one-past |  | 179 |
| VIP: Verified Integer-Pointer Casts |  |  | 686 |
| Design space |  | 4475 | 22 |
|  | Symbolic provenances |  | 314 |
|  | Exposure tracking |  | 383 |
|  | Provenance in integers and bytes |  | 1064 |
|  | Non-deterministic pointer equality |  | 825 |
|  | Allocation history |  | 360 |
|  | SMT representations |  | 1268 |
|  | Summary |  | 239 |

## CN-VIP

**Chapter total: 3141** (own 107)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| malloc and free |  |  | 358 |
| Converting to and from bytes |  |  | 249 |
| Unions and padding |  |  | 508 |
| memcpy and memcmp |  |  | 158 |
| Checking pointer shifts |  |  | 523 |
| Pointer liveness and bounds checks |  |  | 127 |
| CN-VIP soundness |  | 1111 | 127 |
|  | Extending the dynamic semantics |  | 325 |
|  | State typing |  | 101 |
|  | Updating the soundness proof |  | 322 |
|  | Linking CN-VIP to VIP |  | 236 |

## Epilogue on CN-VIP

**Chapter total: 2843** (own 45)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Performance |  |  | 511 |
| Updating existing code |  | 452 | 219 |
|  | Non-deterministic pointer equality |  | 233 |
| Lemma proofs within C |  |  | 502 |
| Lemma proofs in a proof-assistant |  |  | 519 |
| Better foundations for CN |  |  | 814 |

## Tree-carving: Taming C Repositories

**Chapter total: 2817** (own 125)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Need for tree-carving |  |  | 600 |
| Challenging preprocessor and C features |  |  | 412 |
| Demonstration |  |  | 232 |
| Implementation |  |  | 1261 |
| Limitations and future work |  |  | 187 |

## Proof maintenance for pKVM buddy allocator

**Chapter total: 3438** (own 82)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Successful update to intrusive free lists |  | 1477 | 357 |
|  | Carving and integrated the upstream code |  | 128 |
|  | Deleting old fields |  | 125 |
|  | Adding new fields |  | 113 |
|  | Physical to virtual address |  | 193 |
|  | Helper functions |  | 174 |
|  | Indexing and signed bit-vector division |  | 271 |
|  | Stuck in complexity |  | 116 |
| Successful update to experimental VIP |  |  | 221 |
| Failed update to support bit-vectors |  |  | 92 |
| Key takeaways |  | 1566 | 2 |
|  | Features |  | 900 |
|  | Handling large changes |  | 204 |
|  | Error messages |  | 460 |

## CN Comparison and Feedback

**Chapter total: 4203** (own 177)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Early allocator |  | 1883 | 49 |
|  | Early allocator in CN |  | 326 |
|  | Early allocator in VeriFast |  | 1273 |
|  | Early allocator in Frama-C and RefinedC |  | 235 |
| Other symbolic execution verifiers |  | 1185 | 119 |
|  | Gillian-C |  | 479 |
|  | Viper-based: VerCors and Gradual C0 |  | 335 |
|  | Soteria-C |  | 252 |
| Industry feedback |  |  | 875 |
| Summary |  |  | 83 |

## Not-so-great expectations

**Chapter total: 5234** (own 97)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Work backwards from examples |  |  | 183 |
| Design with a formalism |  | 1353 | 90 |
|  | Calling conventions affect syntax |  | 146 |
|  | Error reporting |  | 857 |
|  | Elaborate with care |  | 260 |
| Software engineering |  | 1715 | 54 |
|  | Test for any visible regressions |  | 247 |
|  | Profile early and often, at the right level |  | 228 |
|  | Error with pride, do not crash |  | 643 |
|  | Log, do not debug |  | 297 |
|  | Miscellaneous |  | 246 |
| Get source locations right |  | 1560 | 76 |
|  | Keep lexer and parser simple |  | 105 |
|  | Investigate strange source locations |  | 109 |
|  | Actually use source locations once you have them |  | 390 |
|  | Write parser error messages if feasible |  | 375 |
|  | Consider a custom pre-processor |  | 505 |
| Process counter-examples smartly |  |  | 326 |

## Future Directions

**Chapter total: 3285** (own 22)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Inferring frames |  |  | 962 |
| Weak sequencing |  |  | 613 |
| Join-points |  |  | 491 |
| Integers and bit-vectors |  |  | 484 |
| Higher-order predicates |  |  | 310 |
| Predicate definition checks |  |  | 403 |

## Conclusion

**Chapter total: 1334** (own 545)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| More expressiveness |  |  | 213 |
| More performance |  |  | 250 |
| More user-friendliness |  |  | 326 |

