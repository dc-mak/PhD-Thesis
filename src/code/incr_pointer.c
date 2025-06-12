int incr_pointer(int *p)
/*@ requires take x = RW(p);
             x < MAXi32();
    ensures  take x2 = RW(p);
             return == x2;
             x2 == x + 1i32; @*/
{ return *p = *p + 1; }
// [1/1]: incr_pointer -- pass
