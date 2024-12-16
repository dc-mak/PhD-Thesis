/*@
datatype List {
  Nil {},
  Cons {i32 head, datatype List tail} }

function (i32) hd(datatype List L) {
  match L {
    Nil {} => {
      0i32 }
    Cons {head : H, tail : _} => {
      H } } }

function (datatype List) tl(datatype List L) {
  match L {
    Nil {} => {
      Nil{} }
    Cons {head : _, tail : T} => {
      T } } }

function [rec] (datatype List) snoc(datatype List Xs, i32 Y) {
  match Xs {
    Nil {} => {
      Cons {head: Y, tail: Nil{}} }
    Cons {head: X, tail: Zs}  => {
      Cons{head: X, tail: snoc (Zs, Y)} } } }
@*/

struct queue {
  struct queue_cell* front;
  struct queue_cell* back;
};

struct queue_cell {
  int first;
  struct queue_cell* next;
};

/*@
predicate (datatype List) QueuePtr_At (pointer q) {
  take Q = Owned<struct queue>(q);
  assert (   (is_null(Q.front)  && is_null(Q.back))
          || (!is_null(Q.front) && !is_null(Q.back)));
  take L = QueueFB(Q.front, Q.back);
  return L;
}
@*/

/*@
predicate (datatype List) QueueFB (pointer front, pointer back) {
  if (is_null(front)) {
    return Nil{};
  } else {
    take B = Owned<struct queue_cell>(back);
    assert (is_null(B.next));
    assert (ptr_eq(front, back) || !addr_eq(front, back));
    take L = QueueAux (front, back);
    return snoc(L, B.first);
  }
}
@*/

/*@
predicate (datatype List) QueueAux (pointer f, pointer b) {
  if (ptr_eq(f,b)) {
    return Nil{};
  } else {
    take F = Owned<struct queue_cell>(f);
    assert (!is_null(F.next));
    assert (ptr_eq(F.next, b) || !addr_eq(F.next, b));
    take B = QueueAux(F.next, b);
    return Cons{head: F.first, tail: B};
  }
}
@*/

extern struct queue *malloc_queue();
/*@ spec malloc_queue();
    requires true;
    ensures take R = Block<struct queue>(return);
@*/

extern void free_queue (struct queue *p);
/*@ spec free_queue(pointer p);
    requires take P = Block<struct queue>(p);
    ensures true;
@*/

extern struct queue_cell *malloc_queue_cell();
/*@ spec malloc_queue_cell();
    requires true;
    ensures take R = Block<struct queue_cell>(return);
@*/

extern void free_queue_cell (struct queue_cell *p);
/*@ spec free_queue_cell(pointer p);
    requires take P = Block<struct queue_cell>(p);
    ensures true;
@*/
