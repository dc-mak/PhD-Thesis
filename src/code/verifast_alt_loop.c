//@ requires 0 <= i && i <= 4096 &*& chars(to + i, 4096 - i, ?unzeroed);
//@ ensures 0 <= old_i && old_i <= 4096 &*& chars(to + old_i, 4096 - old_i, create(4096 - old_i , 0));

/*@
fixpoint_auto list<t> create<t>(int n, t x)
  decreases n;
{ return n <= 0 ? nil : cons(x, create(n-1, x)); }

// This is the key lemma (and also slows down verification A LOT
lemma_auto void if_zero_then_nil<t>(list<t> a)
  requires 0 == length(a);
  ensures a == nil;
{
  switch(a) {
   case nil: return;
   case cons(ha, tla): { assert false; }
  }
}

lemma void if_zero_then_eq(list<char> a, list<char> b)
  requires true;
  ensures !(0 == length(a) && length(a) == length(b)) || (nil == a && a == b);
{
  if (0 == length(a) && length(a) == length(b)) {
    if_zero_then_nil(a);
    if_zero_then_nil(b);
  }
}
@*/
