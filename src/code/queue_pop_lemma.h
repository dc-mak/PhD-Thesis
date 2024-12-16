/*@
lemma snoc_facts (pointer front, pointer back, i32 x)
  requires
      take Q = QueueAux(front, back);
      take B = Owned<struct queue_cell>(back);
  ensures
      take Q_post = QueueAux(front, back);
      take B_post = Owned<struct queue_cell>(back);
      Q == Q_post; B == B_post;
      let L = snoc (Cons{Head: x, Tail: Q}, B.first);
      hd(L) == x;
      tl(L) == snoc(Q, B.first);
@*/