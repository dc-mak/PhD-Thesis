match memop with
| CopyAllocId (pe1, pe2) ->
  let@ () =
    WellTyped.ensure_base_type loc ~expect:Memory.uintptr_bt (Mu.bt_of_pexpr pe1)
  in
  let@ () =
    WellTyped.ensure_base_type loc ~expect:BT.(Loc ()) (Mu.bt_of_pexpr pe2)
  in
  check_pexpr pe1 (fun vt1 ->
    check_pexpr pe2 (fun vt2 ->
      let result = copyAllocId_ ~addr:vt1 ~loc:vt2 loc in
      let unspec = CF.Undefined.UB_unspec_copy_alloc_id in
      let@ () = check_has_alloc_id loc vt2 unspec in
      let ub = CF.Undefined.(UB_CERB004_unspecified unspec) in
      let@ () = check_live_alloc_bounds `Copy_alloc_id loc ub [ result ] in
      k result))
