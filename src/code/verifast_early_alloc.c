void clear_page(void *to)
//@ requires chars(to, 4096, _);
//@ ensures characters_zeroed(to, 4096);
{
  int i = 0;
  while(i < 4096)
  //@ requires chars(to + i, PAGE_SIZE - i, _);
  //@ ensures  characters_zeroed((char*) to + old_i, PAGE_SIZE - old_i);
  {
    ((char *) to)[i] = 0;
    i++;
  };
}

void * hyp_early_alloc_page(void *arg)
/*@ requires cur |-> ?cur_val &*& end |-> ?end_val &*&
             cur_val + 4096 <= end_val && end_val <= UINTPTR_MAX &*&
             earlyAlloc((char*) cur_val, end_val); @*/
/*@ ensures cur |-> ?cur_val' &*& end |-> end_val &*&
            earlyAlloc((char*) cur_val', end_val) &*&
            characters_zeroed((char*)result, PAGE_SIZE) &*&
            cur_val' == cur_val + PAGE_SIZE; @*/
{
        /*VERIFAST*/ //@ open earlyAlloc((char*) cur, end);
	unsigned long ret = cur;

	cur += PAGE_SIZE;
	if (cur > end) {
		cur = ret;
		return NULL;
	}
	clear_page((void*)ret);

        /*VERIFAST*/ //@ close earlyAlloc((char*) cur, end);
	return (void *)ret;
}
