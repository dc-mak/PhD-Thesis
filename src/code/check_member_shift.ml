let in_bounds ptr =
  let here = Locations.other __FUNCTION__ in
  let module H = Alloc.History in
  let H.{ base; size } = H.(split (lookup_ptr ptr here) here) in
  let addr = addr_ ptr here in
  let lower = le_ (base, addr) here in
  let upper = le_ (addr, add_ (base, size) here) here in
  [ lower; upper ]

let check_live_alloc_bounds reason loc ub ptrs =
  if !use_vip then
    let@ () = RI.Special.check_live_alloc reason loc (List.hd ptrs) in
    let here = Locations.other __FUNCTION__ in
    let constr = and_ (List.concat_map in_bounds ptrs) here in
    let@ provable = provable loc in
    match provable @@ LC.T constr with
    | `True -> return ()
    | `False ->
      let@ model = model () in
      fail (fun ctxt ->
        let term = IT.tuple_ ptrs here in
        { loc; msg = Alloc_out_of_bounds { constr; term; ub; ctxt; model } })
  else
    return ()

match pe_ with
| PEmember_shift (pe, tag, member) ->
  let@ () = WellTyped.ensure_base_type loc ~expect (Loc ()) in
  let@ () = ensure_base_type loc ~expect:(Loc ()) (Mu.bt_of_pexpr pe) in
  check_pexpr pe (fun vt ->
    let@ _ = get_struct_member_type loc tag member in
    let result = memberShift_ (vt, tag, member) loc in
    (* This should only be called after a PtrValidForDeref, so if we were
       willing to optimise, we could skip the has_alloc_id, bounds and
       liveness checks. *)
    let unspec = CF.Undefined.UB_unspec_pointer_add in
    let@ () = check_has_alloc_id loc vt unspec in
    let ub = CF.Undefined.(UB_CERB004_unspecified unspec) in
    let@ () = check_live_alloc_bounds `ISO_member_shift loc ub [ result ] in
    k result)
