/*@
lemma byte_arrays_equal(pointer x, pointer y, u64 n)

requires
    take X = each (u64 i; 0u64 <= i && i < n)
             { RW(array_shift<unsigned char>(x, i)) };
    take Y = each (u64 i; 0u64 <= i && i < n)
             { RW(array_shift<unsigned char>(y, i)) };
    each (u64 i; 0u64 <= i && i < n) { X[i] == Y[i] };

ensures
    take XR = each (u64 i; 0u64 <= i && i < n )
              { RW(array_shift<unsigned char>(x, i)) };
    take YR = each (u64 i; 0u64 <= i && i < n )
              { RW(array_shift<unsigned char>(y, i)) };
    X == XR; Y == YR;
    XR == YR;
@*/
