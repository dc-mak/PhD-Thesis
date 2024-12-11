let empty =
  let logical =
    let loc_str = __FILE__ ^ ":" ^ string_of_int __LINE__ in
    let l_info = (Locations.other loc_str, lazy Pp.string loc_str) in
    SymMap.(empty |> add Alloc.History.sym (BaseType Alloc.History.bt, l_info))
  in
  { computational = SymMap.empty;
    logical;
    resources = ([], 0);
    resource_history = IntMap.empty;
    constraints = LCSet.empty;
    global = Global.empty;
    where = Where.empty
  }
