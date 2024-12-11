let alloc =
  Predicate.
    { loc = Locations.other (__FILE__ ^ ":" ^ string_of_int __LINE__);
      pointer = Sym.fresh_named "ptr";
      iargs = [];
      oarg_bt = Alloc.History.value_bt;
      clauses = None
    }
