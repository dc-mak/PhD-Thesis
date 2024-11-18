int owned_increment(int *p)
/*@ requires take x  = Owned(p); x < MAXi32();
    ensures  take x2 = Owned(p); x2 == x + 1i32; @*/
{ return *p += 1; }
// [1/1]: owned_increment -- pass
