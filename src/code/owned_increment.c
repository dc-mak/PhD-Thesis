int owned_incr(int *p)
/*@ requires take x  = RW(p); x < MAXi32();
    ensures  take x2 = RW(p); x2 == x + 1i32; @*/
{ return *p += 1; }
// [1/1]: owned_incr -- pass
