#include "increment.c"
// [1/2]: increment -- pass

int decr_broken(int y)
/*@ requires y <= 100i32; @*/
{ return increment(y)-1; }
// [2/2]: decr_broken -- fail
// code/decrement_broken.c:6:10: error: Undefined behaviour
// { return increment(y)-1; }
//          ~~~~~~~~~~~~^~
// an exceptional condition occurs during  ... (§6.5#5)
// State file: ...
