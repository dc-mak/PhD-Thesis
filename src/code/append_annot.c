struct int_list {
  int head;
  struct int_list* tail; };

/*@
datatype seq {
  Seq_Nil {},
  Seq_Cons {i32 head, datatype seq tail} }

function [rec] (datatype seq) append(
    datatype seq xs, datatype seq ys) {
  match xs {
    Seq_Nil {} => { ys }
    Seq_Cons {head : h, tail : zs}  => {
      Seq_Cons {head: h, tail: append(zs, ys)} } } }

predicate (datatype seq) IntList(pointer p) {
  if (is_null(p)) {
    return Seq_Nil{};
  } else {
    take H = Owned<struct int_list>(p);
    take tl = IntList(H.tail);
    return (Seq_Cons { head: H.head, tail: tl }); } }
@*/

struct int_list* IntList_append(
    struct int_list* xs, struct int_list* ys)
/*@ requires take L1 = IntList(xs);
             take L2 = IntList(ys);
    ensures  take L3 = IntList(return);
             L3 == append(L1, L2); @*/
{ if (xs == 0) {
    /*@ unfold append(L1, L2); @*/
    return ys;
  } else {
    /*@ unfold append(L1, L2); @*/
    struct int_list *new_tail =
        IntList_append(xs->tail, ys);
    xs->tail = new_tail;
    return xs; } }
// [1/1]: IntList_append -- pass
