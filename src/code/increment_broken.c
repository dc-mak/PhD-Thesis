int increment(int x)
{ return x + 1; }
// [1/1]: increment -- fail
// code/increment.c:2:10: error: Undefined behaviour
// { return x + 1; }
//          ~~^~~ 
// an exceptional condition occurs during the evaluation of an
// expression (§6.5#5)
// State file: ...
