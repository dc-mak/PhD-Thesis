#include<limits.h>
#include "increment.c"
// [1/3]: increment -- pass

int call_incr_100(int y)
/*@ requires y <= 100i32; @*/
{ return increment(y); }
// [2/3]: call_incr_100 -- pass

int call_incr_INT_MAX()
{ return increment(INT_MAX); }
// [3/3]: call_incr_INT_MAX -- fail
// code/call_increment.c:9:10: error: Unprovable constraint
// { return increment(INT_MAX); }
// Constraint from code/increment.c:2:14:
// /*@ requires x < MAXi32(); @*/
// State file: ...
