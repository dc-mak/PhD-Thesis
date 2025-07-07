/*@
lemma snoc_facts (pointer front, pointer back, i32 x)
  requires
      take Q = QueueAux(front, back);
      take B = RW<struct queue_cell>(back);
  ensures
      take Q_post = QueueAux(front, back);
      take B_post = RW<struct queue_cell>(back);
      Q == Q_post; B == B_post;
      let L = snoc (Cons{Head: x, Tail: Q}, B.first);
      hd(L) == x;
      tl(L) == snoc (Q, B.first);
@*/

int pop_queue (struct queue *q)
/*@ requires take Q = QueuePtr_At(q);
             Q != Nil{};
    ensures take Q_post = QueuePtr_At(q);
            Q_post == tl(Q);
            return == hd(Q);
@*/
{
  /*@ split_case is_null(q->front); @*/
  struct queue_cell* h = q->front;
  if (h == q->back) {
    int x = h->first;
    free_queue_cell(h);
    q->front = NULL;
    q->back = NULL;
    /*@ unfold snoc(Nil{}, x); @*/
    return x;
  } else {
    int x = h->first;
    /*@ apply snoc_facts(h->next, q->back, x); @*/
    q->front = h->next;
    free_queue_cell(h);
    return x;
  }
}
