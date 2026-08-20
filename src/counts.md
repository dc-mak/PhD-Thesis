# Word counts

Counts are `text + headers + captions`. **Own** is the prose directly under a heading; **Total** rolls up all descendants.

## Chapters

| Chapter | Total | Own |
| :-- | --: | --: |
| Introduction | **5882** | 16 |
| Example: queues in CN | **2769** | 49 |
| Background: Cerberus and CN design | **6899** | 32 |
| Kernel CN: Grammar | **4180** | 161 |
| Kernel CN: Static semantics | **3864** | 319 |
| Kernel CN: proof of soundness | **1504** | 158 |
| Informing implementation discussions | **1278** | 142 |
| An alternative presentation | **2052** | 92 |
| Memory object models, explained | **6713** | 395 |
| CN-VIP | **3167** | 106 |
| Epilogue on CN-VIP | **2823** | 45 |
| Tree-carving: taming C repositories | **2570** | 116 |
| Proof maintenance for pKVM buddy allocator | **3299** | 78 |
| CN comparison and feedback | **4194** | 184 |
| Lessons learned | **5028** | 57 |
| Future directions | **3245** | 16 |
| Conclusion | **1278** | 494 |

| **Document total** | **60745** | |

## Introduction

**Chapter total: 5882** (own 16)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Context |  |  | 610 |
| Thesis statement |  |  | 84 |
| Background |  | 3588 | 1 |
|  | The C programming language |  | 847 |
|  | Verification with Separation Logic |  | 1596 |
|  | CN: C, No bugs! |  | 1144 |
| Contributions of this thesis |  | 1584 | 66 |
|  | Formalisation of CN |  | 225 |
|  | Memory object model: design, formalisation and implementation |  | 218 |
|  | Engineering: will the real-world C, please stand up? |  | 316 |
|  | Contributions in published papers |  | 759 |

## Example: queues in CN

**Chapter total: 2769** (own 49)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| CN syntax |  |  | 375 |
| Queue definitions |  |  | 782 |
| Queue implementation |  |  | 798 |
| Proofs of lemmas |  |  | 765 |

## Background: Cerberus and CN design

**Chapter total: 6899** (own 32)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| CN design goals and constraints |  |  | 963 |
| Cerberus and Core for a usable and accurate C semantics |  |  | 244 |
| Core grammar |  |  | 828 |
| Elaboration example: list append |  | 1228 | 970 |
|  | Discussion |  | 258 |
| Decidable refinements for retrofitting and counter-examples |  |  | 534 |
| Bidirectionality for taming subtyping |  |  | 493 |
| Linearity to manage (non-leaky) resources |  |  | 676 |
| Section |  | 1105 | 512 |
|  | Precise assertions |  | 593 |
| Monadic syntax for mode-correctness |  |  | 374 |
| Iterated separating conjunctions to handle arrays |  |  | 422 |

## Kernel CN: Grammar

**Chapter total: 4180** (own 161)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Kernel CN types |  |  | 587 |
| Desugaring CN types into kernel types |  |  | 722 |
| ResCore |  |  | 846 |
| Permissions resource terms |  |  | 987 |
| Core to ResCore example |  |  | 877 |

## Kernel CN: Static semantics

**Chapter total: 3864** (own 319)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Contexts |  |  | 65 |
| Pure values and expressions |  |  | 280 |
| Pure statements |  |  | 174 |
| Resource terms |  | 647 | 56 |
|  | Synthesis for resource terms |  | 200 |
|  | Synthesis for predicate operations |  | 118 |
|  | Checking for resource terms |  | 273 |
| Memory actions and operations |  |  | 426 |
| Spine judgement |  |  | 214 |
| Effectful values and expressions |  |  | 73 |
| Pattern-matching |  |  | 392 |
| Effectful statements |  |  | 120 |
| Elaboration |  | 1154 | 505 |
|  | Normalised resource contexts |  | 174 |
|  | Synthesising output arguments |  | 311 |
|  | Synthesising indices for iterated predicates |  | 164 |

## Kernel CN: proof of soundness

**Chapter total: 1504** (own 158)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Substitution and contexts |  |  | 359 |
| Heaps and their types |  |  | 505 |
| Soundness |  |  | 482 |

## Informing implementation discussions

**Chapter total: 1278** (own 142)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Supporting loads of partially initialised structs/unions |  |  | 306 |
| Automatic unfolding scheme for logical functions |  |  | 224 |
| Higher-order resources |  |  | 105 |
| Restrictions on branching |  |  | 213 |
| Removing the pointer first restriction on predicates |  |  | 137 |
| Unifying the syntax of functions, predicates and specifications |  |  | 151 |

## An alternative presentation

**Chapter total: 2052** (own 92)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| MiniC and MiniCN |  |  | 255 |
| Aliasing requires linear resources |  |  | 254 |
| Implicit resource terms intertwine elaboration and typing |  |  | 146 |
| Early-returns intertwine normalising, synthesising and checking |  |  | 246 |
| Lack of let-normalisation requires join-points |  |  | 86 |
| Discussion |  |  | 973 |

## Memory object models, explained

**Chapter total: 6713** (own 395)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| PNVI-ae-udi |  | 1182 | 47 |
|  | Provenance not tracked via integers |  | 623 |
|  | Subsection |  | 333 |
|  | Subsection |  | 179 |
| VIP: verified integer-pointer casts |  |  | 684 |
| Design space |  | 4452 | 22 |
|  | Symbolic provenances |  | 301 |
|  | Exposure tracking |  | 380 |
|  | Provenance in integers and bytes |  | 1063 |
|  | Non-deterministic pointer equality |  | 819 |
|  | Allocation history |  | 361 |
|  | SMT representations |  | 1267 |
|  | Summary |  | 239 |

## CN-VIP

**Chapter total: 3167** (own 106)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| malloc and free |  |  | 386 |
| Converting to and from bytes |  |  | 226 |
| Unions and padding |  |  | 525 |
| memcpy and memcmp |  |  | 221 |
| Checking pointer shifts |  |  | 478 |
| Pointer liveness and bounds checks |  |  | 127 |
| CN-VIP soundness |  | 1098 | 131 |
|  | Extending the dynamic semantics |  | 309 |
|  | State typing |  | 99 |
|  | Updating the soundness proof |  | 322 |
|  | Linking CN-VIP to VIP |  | 237 |

## Epilogue on CN-VIP

**Chapter total: 2823** (own 45)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Performance |  |  | 507 |
| Updating existing code |  | 447 | 220 |
|  | Non-deterministic pointer equality |  | 227 |
| Lemma proofs within C |  |  | 505 |
| Lemma proofs in a proof-assistant |  |  | 514 |
| Better foundations for CN |  |  | 805 |

## Tree-carving: taming C repositories

**Chapter total: 2570** (own 116)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Need for tree-carving |  |  | 591 |
| Challenging preprocessor and C features |  |  | 407 |
| Demonstration |  |  | 231 |
| Implementation |  |  | 1039 |
| Limitations and future work |  |  | 186 |

## Proof maintenance for pKVM buddy allocator

**Chapter total: 3299** (own 78)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Successful update to intrusive free lists |  | 1423 | 367 |
|  | Carving and integrated the upstream code |  | 106 |
|  | Deleting old fields |  | 121 |
|  | Adding new fields |  | 114 |
|  | Physical to virtual address |  | 174 |
|  | Helper functions |  | 172 |
|  | Indexing and signed bit-vector division |  | 254 |
|  | Stuck in complexity |  | 115 |
| Successful update to experimental VIP |  |  | 201 |
| Failed update to support bit-vectors |  |  | 83 |
| Key takeaways |  | 1514 | 2 |
|  | Features |  | 863 |
|  | Handling large changes |  | 193 |
|  | Error messages |  | 456 |

## CN comparison and feedback

**Chapter total: 4194** (own 184)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Early allocator |  | 1880 | 74 |
|  | Early allocator in CN |  | 329 |
|  | Early allocator in VeriFast |  | 1243 |
|  | Early allocator in Frama-C and RefinedC |  | 234 |
| Other symbolic execution verifiers |  | 1186 | 119 |
|  | Gillian-C |  | 477 |
|  | Viper-based: VerCors and Gradual C0 |  | 336 |
|  | Soteria-C |  | 254 |
| Industry feedback |  |  | 861 |
| Summary |  |  | 83 |

## Lessons learned

**Chapter total: 5028** (own 57)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Work backwards from examples |  |  | 172 |
| Design with a formalism |  | 1264 | 81 |
|  | Calling conventions affect syntax |  | 119 |
|  | Error reporting |  | 805 |
|  | Elaborate with care |  | 259 |
| Software engineering |  | 1646 | 45 |
|  | Test for any visible regressions |  | 245 |
|  | Profile early and often, at the right level |  | 209 |
|  | Error with pride, do not crash |  | 619 |
|  | Log, do not debug |  | 284 |
|  | Miscellaneous |  | 244 |
| Get source locations right |  | 1540 | 74 |
|  | Keep the lexer and parser simple |  | 104 |
|  | Investigate strange source locations |  | 107 |
|  | Use source locations once you have them |  | 388 |
|  | Write parser error messages if feasible |  | 373 |
|  | Consider a custom pre-processor |  | 494 |
| Process counter-examples smartly |  |  | 349 |

## Future directions

**Chapter total: 3245** (own 16)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| Inferring frames |  |  | 916 |
| Weak sequencing |  |  | 642 |
| Join-points |  |  | 494 |
| Integers and bit-vectors |  |  | 475 |
| Higher-order predicates |  |  | 298 |
| Predicate definition checks |  |  | 404 |

## Conclusion

**Chapter total: 1278** (own 494)

| Section | Subsection | Total | Own |
| :-- | :-- | --: | --: |
| More expressiveness |  |  | 213 |
| More performance |  |  | 245 |
| More user-friendliness |  |  | 326 |

