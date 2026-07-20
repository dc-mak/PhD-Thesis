# Word counts

Counts are `text + headers + captions`. **Own** is the prose directly under a heading; **Total** rolls up all descendants.

## Chapters

| Chapter | Total | Own |
| :-- | --: | --: |
| Introduction | **5993** | 16 |
| Example: queues in CN | **2797** | 52 |
| Background: Cerberus and CN design | **7875** | 32 |
| Kernel CN: Grammar | **4298** | 167 |
| Kernel CN: Static semantics | **4675** | 349 |
| Kernel CN: Proof of soundness | **1642** | 188 |
| Informing implementation discussions | **1458** | 156 |
| An alternative presentation | **2241** | 91 |
| Memory object models, explained | **7245** | 394 |
| CN-VIP | **3292** | 118 |
| Epilogue on CN-VIP | **3478** | 61 |
| Tree-carving: Taming C Repositories | **2921** | 132 |
| Proof maintenance for pKVM buddy allocator | **3438** | 82 |
| CN Comparison and Feedback | **4203** | 177 |
| Not-so-great expectations | **5234** | 97 |
| Future Directions | **3285** | 22 |
| Conclusion | **1334** | 545 |

| **Document total** | **65409** | |

## Introduction

**Chapter total: 5993** (own 16)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Context |  |  | 620 |
| Thesis statement |  |  | 87 |
| Background |  | 3628 | 1 |
|  | The C programming language |  | 854 |
|  | Verification with Separation Logic |  | 1612 |
|  | CN: C, No bugs! |  | 1161 |
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

**Chapter total: 7875** (own 32)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| CN design goals and constraints |  |  | 980 |
| Cerberus and Core for a usable and accurate C semantics |  |  | 266 |
| Core grammar |  |  | 822 |
| Elaboration example: list append |  | 1258 | 997 |
|  | Discussion |  | 261 |
| Decidable refinements for retrofitting and counter-examples |  |  | 782 |
| Bidirectionality for taming subtyping |  |  | 673 |
| Linearity to manage (non-leaky) resources |  |  | 887 |
| Section |  | 1346 | 694 |
|  | Precise assertions |  | 652 |
| Monadic syntax for mode-correctness |  |  | 385 |
| Iterated separating conjunctions to handle arrays |  |  | 444 |

## Kernel CN: Grammar

**Chapter total: 4298** (own 167)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Kernel CN types |  |  | 588 |
| Desugaring CN types into kernel types |  |  | 729 |
| ResCore |  |  | 885 |
| Resource terms |  |  | 1038 |
| Core to ResCore example |  |  | 891 |

## Kernel CN: Static semantics

**Chapter total: 4675** (own 349)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Contexts |  |  | 75 |
| Pure values and expressions |  |  | 362 |
| Pure statements |  |  | 268 |
| Resource terms |  | 855 | 85 |
|  | Synthesis for resource terms |  | 313 |
|  | Synthesis for predicate operations |  | 135 |
|  | Checking for resource terms |  | 322 |
| Memory actions and pointer operations |  |  | 470 |
| Spine judgement |  |  | 305 |
| Effectful values and expressions |  |  | 144 |
| Pattern matching |  |  | 501 |
| Effectful statements |  |  | 154 |
| Elaboration |  | 1192 | 609 |
|  | Normalised resource contexts |  | 170 |
|  | Synthesising output arguments |  | 246 |
|  | Synthesising indices for iterated predicates |  | 167 |

## Kernel CN: Proof of soundness

**Chapter total: 1642** (own 188)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Substitution and contexts |  |  | 377 |
| Heaps and their types |  |  | 586 |
| Soundness |  |  | 491 |

## Informing implementation discussions

**Chapter total: 1458** (own 156)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Supporting partially initialised reads of structs/unions |  |  | 332 |
| Automatic unfolding scheme for logical functions |  |  | 242 |
| Higher-order resources |  |  | 124 |
| Restrictions on branching |  |  | 238 |
| Removing the pointer first restriction on predicates |  |  | 172 |
| Unifying the syntax of functions, predicates and specifications |  |  | 194 |

## An alternative presentation

**Chapter total: 2241** (own 91)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| MiniC and MiniCN |  |  | 248 |
| Aliasing requires linear resources |  |  | 260 |
| Implicit resource terms intertwine elaboration and typing |  |  | 169 |
| Early returns intertwine normalising, synthesising and checking |  |  | 264 |
| Lack of let-normalisation requires join-points |  |  | 96 |
| Discussion |  |  | 1113 |

## Memory object models, explained

**Chapter total: 7245** (own 394)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| PNVI-ae-udi |  | 1324 | 48 |
|  | Provenance not tracked via integers |  | 658 |
|  | Subsection |  | 618 |
| VIP: Verified Integer Pointer Casts |  |  | 722 |
| Design space |  | 4805 | 23 |
|  | Symbolic provenances |  | 346 |
|  | Exposure tracking |  | 399 |
|  | Provenance in integers and bytes |  | 1197 |
|  | Non-deterministic pointer equality |  | 851 |
|  | Allocation history |  | 386 |
|  | SMT representations |  | 1363 |
|  | Summary |  | 240 |

## CN-VIP

**Chapter total: 3292** (own 118)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| malloc and free |  |  | 369 |
| Converting to and from bytes |  |  | 247 |
| Unions and padding |  |  | 526 |
| memcpy and memcmp |  |  | 155 |
| Checking pointer shifts |  |  | 537 |
| Pointer liveness and bounds checks |  |  | 143 |
| Soundness |  | 1197 | 132 |
|  | Extending the dynamic semantics |  | 372 |
|  | State typing |  | 130 |
|  | Updating the soundness proof |  | 333 |
|  | Linking CN-VIP to VIP |  | 230 |

## Epilogue on CN-VIP

**Chapter total: 3478** (own 61)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Performance |  |  | 480 |
| Updating existing code |  | 524 | 284 |
|  | Non-deterministic pointer equality |  | 240 |
| Lemma proofs within C |  |  | 555 |
| Lemma proofs in a proof-assistant |  |  | 644 |
| Better foundations for CN |  |  | 1214 |

## Tree-carving: Taming C Repositories

**Chapter total: 2921** (own 132)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Need for tree-carving |  |  | 599 |
| Challenging preprocessor and C features |  |  | 466 |
| Demonstration |  |  | 263 |
| Implementation |  |  | 1274 |
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

