struct node { struct node *next; };

/*@
predicate void List_Seg(pointer front, pointer back) {
    take F = RW<struct node>(front);
    take L = List_Next_Seg(front, F.next, back);
    return;
}

predicate void List_Next_Seg(
    pointer front,
    pointer next,
    pointer back
) {
    if (ptr_eq(front, back)) {
        return;
    } else {
        take Rest = List_Seg(next, back);
        return;
    }
}
@*/

void push_front (struct node *front, struct node* back)
/*@
requires
    take Void = List_Seg(front, back);
    take B = RW(back);
ensures
    true;
@*/
{ /* diverges immediately */ }
