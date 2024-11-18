int increment_ensures(int x)
/*@ requires x < MAXi32();
    ensures  return == x + 1i32; @*/
{ return x + 1; }
// [1/2]: increment_ensures -- pass

int call_incr_100_broken(int y)
/*@ requires y <= 100i32; @*/
{ return increment_ensures(y)-1; }
// [2/2]: call_incr_100_broken -- pass
