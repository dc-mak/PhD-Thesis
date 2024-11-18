unsigned int sum_array(unsigned int *p)
/*@ requires take arr  = each (u64 i; i < 2u64) { Owned(array_shift(p,i)) };
             arr[0u64] + arr[1u64] < MAXu32();
    ensures  take arr2 = each (u64 i; i < 2u64) { Owned(array_shift(p,i)) };
             each (u64 i; i < 2u64) { arr[i] == arr2[i] };
             return == arr[0u64] + arr[1u64]; @*/
{  /*@ extract Owned<unsigned int>, 0u64; @*/
   /*@ extract Owned<unsigned int>, 1u64; @*/
   return p[0] + p[1]; }
// [1/1]: sum_array -- pass
