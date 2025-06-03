struct int_list {
  int head;
  struct int_list* tail; };

struct int_list* IntList_append(
    struct int_list *xs, struct int_list *ys)
{
  if (xs == 0) {
    return ys;
  } else {
    struct int_list *new_tail = IntList_append(xs->tail, ys);
    xs->tail = new_tail;
    return xs;
  }
}
