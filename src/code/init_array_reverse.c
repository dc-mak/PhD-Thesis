void init_array_rev (char *p, int n)
/*@ requires take A_pre  = each(i32 i; 0i32 <= i && i < n) { Block(array_shift(p,i)) };
                  n > 0i32;
    ensures  take A_post = each(i32 i; 0i32 <= i && i < n) { Owned(array_shift(p,i)) }; @*/
{ int j = 0;
  while (j < n)
  /*@ inv {p} unchanged; {n} unchanged;
          0i32 <= j && j <= n;
          take Uninit = each (i32 i; 0i32 <= i && i < n-j) { Block(array_shift(p,i)) };
          take Init   = each (i32 i; n-j <=  i && i < n  ) { Owned(array_shift(p,i)) }; @*/
  { /*@ extract Block<char>, n-j-1i32; @*/
    p[n-j-1] = 0;
    /*@ extract Owned<char>, n-j-1i32); @*/
    j++; } }
// [1/1]: init_array_rev -- pass
