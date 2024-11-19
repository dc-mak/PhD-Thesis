int incr_ensures(int x)
/*@ requires x < MAXi32();
    ensures  return == x + 1i32; @*/
{ return x + 1; }
// [1/2]: incr_ensures -- pass

int call_incr_100(int y)
/*@ requires y <= 100i32; @*/
{ return incr_ensures(y)-1; }
// [2/2]: call_incr_100 -- pass
