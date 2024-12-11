| Create (pe, act, prefix) ->
  (* base types *)
  let@ () = WellTyped.WCT.is_ct act.loc act.ct in
  let@ () = WellTyped.ensure_base_type loc ~expect (Loc ()) in
  let@ () = WellTyped.ensure_bits_type loc (Mu.bt_of_pexpr pe) in
  check_pexpr pe (fun arg ->
    (* alignment *)
    let ret_s, ret = (* uses prefix *) in
    let@ () = add_a ret_s (IT.bt ret) (loc, lazy (Pp.string "allocation")) in
    let align_v = cast_ Memory.uintptr_bt arg loc in
    let@ () = add_c loc (LC.T (alignedI_ ~align:align_v ~t:ret loc)) in
    (* ownership *)
    let@ () =
      add_r
        loc
        ( P { name = Owned (act.ct, Uninit); pointer = ret; iargs = [] },
          O (default_ (Memory.bt_of_sct act.ct) loc) )
    in
    (* VIP *)
    let lookup = Alloc.History.lookup_ptr ret here in
    let value =
      let size = Memory.size_of_ctype act.ct in
      Alloc.History.make_value ~base:(addr_ ret here) ~size here
    in
    let@ () =
      if !use_vip then
        (* This is not backwards compatible because in the solver
         * Alloc_id maps to unit if not (!use_vip) *)
        add_c loc (LC.T (eq_ (lookup, value) here))
      else
        return ()
    in
    let@ () = add_r loc (P (Req.make_alloc ret), O lookup) in
    let@ () = record_action (Create ret, loc) in
    k ret)
