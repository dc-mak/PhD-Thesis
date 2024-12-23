void clear_page(void *to)
/*@ requires let to_i = (integer) to @*/
/*@ requires take B = each(integer j; to_i <= j && j < (to_i + 4096)){ Byte(((pointer) 0)+(j*1)) } @*/
/*@ ensures take B2 = each(integer j; to_i <= j && j < (to_i + 4096)){ ByteV(((pointer) 0)+(j*1), 0) } @*/
{
  int i = 0;
  while(i < 4096)
  /*@ inv 0 <= i; i <= 4096 @*/
  /*@ inv take Z = each(integer j; to_i <= j && j < (to_i + i)){ ByteV(((pointer) 0)+(j*1), 0) } @*/
  /*@ inv take BI = each(integer j; (to_i + i) <= j && j < (to_i + 4096)){ Byte(((pointer) 0)+(j*1)) } @*/
  /*@ inv {to}unchanged @*/
  {
    /*CN*/ /*@ unpack Byte ((pointer) ((integer) to+i)); @*/
    *((char *) to+i) = 0;
    /*CN*/ /*@ pack ByteV ((pointer) ((integer) to + i), 0); @*/
    i++;
  };
}

void * hyp_early_alloc_page(void *arg)
/*@ accesses cur; end @*/
/*@ requires cur + 4096 <= end @*/
/*@ requires take E = EarlyAlloc((pointer) cur, end) @*/
/*@ ensures take E2 = EarlyAlloc((pointer) cur, end) @*/
/*@ ensures take Z = each(integer j; ((integer) return) <= j && j < ((integer) return) + 4096){ Byte(((pointer) 0)+(j*1)) } @*/
/*@ ensures cur == {cur}@start + 4096; {end}unchanged @*/
{
        /*CN*/ /*@ unpack EarlyAlloc((pointer) cur, end); @*/
	unsigned long ret = cur;

	cur += PAGE_SIZE;
	if (cur > end) {
		cur = ret;
		return NULL;
	}
	/* clear_page((void*)ret); */

        /*CN*/ /*@ pack EarlyAlloc((pointer) cur, end); @*/
	return (void *)ret;
}
