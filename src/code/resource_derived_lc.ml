let derived_lc1 ((resource : Req.t), O output) =
  let here = Locations.other (__FUNCTION__ ^ ":" ^ string_of_int __LINE__) in
  match resource with
  | P { name = Owned (ct, _); pointer; iargs = _ } ->
    let addr = IT.addr_ pointer here in
    let upper = IT.upper_bound addr ct here in
    let alloc_bounds =
      if !IT.use_vip then
        let module H = Alloc.History in
        let H.{ base; size } = H.(split (lookup_ptr pointer here) here) in
        [ IT.(le_ (base, addr) here); IT.(le_ (upper, add_ (base, size) here) here) ]
      else
        []
    in
    [ IT.hasAllocId_ pointer here; IT.(le_ (addr, upper) here) ] @ alloc_bounds
  | P { name; pointer; iargs = [] }
    when !IT.use_vip && Req.(equal_name name Predicate.alloc) ->
    let module H = Alloc.History in
    let lookup = H.lookup_ptr pointer here in
    let H.{ base; size } = H.split lookup here in
    [ IT.(eq_ (lookup, output) here); IT.(le_ (base, add_ (base, size) here) here) ]
  | Q { name = Owned _; pointer; _ } -> [ IT.hasAllocId_ pointer here ]
  | P { name = PName _; pointer = _; iargs = _ } | Q { name = PName _; _ } -> []

let derived_lc2 ((resource : Req.t), _) ((resource' : Req.t), _) =
  match (resource, resource') with
  | ( P { name = Owned (ct1, _); pointer = p1; iargs = _ },
      P { name = Owned (ct2, _); pointer = p2; iargs = _ } ) ->
    let here = Locations.other (__FUNCTION__ ^ ":" ^ string_of_int __LINE__) in
    let addr1 = IT.addr_ p1 here in
    let addr2 = IT.addr_ p2 here in
    let up1 = IT.upper_bound addr1 ct1 here in
    let up2 = IT.upper_bound addr2 ct2 here in
    [ IT.(or2_ (le_ (up2, addr1) here, le_ (up1, addr2) here) here) ]
  | _ -> []

let disable_resource_derived_constraints = ref false

let pointer_facts ~new_resource ~old_resources =
  if !disable_resource_derived_constraints then
    []
  else
    derived_lc1 new_resource @ List.concat_map (derived_lc2 new_resource) old_resources
