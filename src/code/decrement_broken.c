#include "increment.c"
// [1/2]: increment -- pass

int call_incr_100_broken(int y)
/*@ requires y <= 100i32; @*/
{ return increment(y)-1; }
// [2/2]: call_incr_100_broken -- fail
// code/call_increment2.c:6:10: error: Undefined behaviour
// { return increment(y)-1; }
//          ~~~~~~~~~~~~^~ 
// an exceptional condition occurs during  ... (§6.5#5)
// State file: ...
