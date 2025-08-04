let bytes_constraints
      loc
      (to_from : CF.Cn.to_from)
      ~(value : IT.t)
      ~(byte_arr : IT.t)
      (ct : Sctypes.t)
  : IT.t t
  =
  (* FIXME this hard codes big endianness but this should be switchable *)
  let here = Locations.other __LOC__ in
  match ct with
  | Sctypes.Void | Array (_, _) | Struct _ | Function (_, _, _) | Byte ->
    fail (fun _ -> { loc; msg = Unsupported_byte_conv_ct ct })
  | Integer it ->
    let bt = IT.get_bt value in
    let lhs = value in
    let bytes =
      List.init (Memory.size_of_integer_type it) (fun i ->
        let index = int_lit_ i WellTyped.default_quantifier_bt here in
        map_get_ byte_arr index here)
    in
    let all_some = and_ (List.map (fun byte -> isSome_ byte here) bytes) here in
    let rhs =
      let shifted =
        List.mapi
          (fun i byte ->
             let casted = cast_ bt (getOpt_ byte here) here in
             let shift_amt = int_lit_ (i * 8) bt here in
             IT.IT (Binop (ShiftLeft, casted, shift_amt), bt, here))
          bytes
      in
      List.fold_left (fun x y -> IT.add_ (x, y) here) (List.hd shifted) (List.tl shifted)
    in
    (match to_from with
     | To -> return (and2_ (all_some, eq_ (lhs, rhs) here) here)
     | From ->
       let lc = LC.T all_some in
       let@ provable = provable loc in
       (match provable lc with
        | `True -> return (eq_ (lhs, rhs) here)
        | `False ->
          let@ model = model () in
          fail (fun ctxt ->
            { loc;
              msg =
                Unproven_constraint
                  { constr = lc; info = (loc, None); requests = []; ctxt; model }
            })))
  | Pointer _ ->
    let bt = Memory.uintptr_bt in
    let value_prov = cast_ BT.Alloc_id value here in
    let value_addr = cast_ bt value here in
    let bytes =
      List.init Memory.size_of_pointer (fun i ->
        let index = int_lit_ i WellTyped.default_quantifier_bt here in
        map_get_ byte_arr index here)
    in
    let bytes_addr =
      let shifted =
        List.mapi
          (fun i byte ->
             let casted = cast_ bt (getOpt_ byte here) here in
             let shift_amt = int_lit_ (i * 8) bt here in
             IT.IT (Binop (ShiftLeft, casted, shift_amt), bt, here))
          bytes
      in
      List.fold_left (fun x y -> IT.add_ (x, y) here) (List.hd shifted) (List.tl shifted)
    in
    let bytes_prov =
      List.map (fun byte -> cast_ (BT.Option Alloc_id) (getOpt_ byte here) here) bytes
    in
    let all_some = and_ (List.map (fun byte -> isSome_ byte here) bytes) here in
    (match to_from with
     | From ->
       let lc = LC.T all_some in
       let@ provable = provable loc in
       (match provable lc with
        | `False ->
          let@ model = model () in
          fail (fun ctxt ->
            { loc;
              msg =
                Unproven_constraint
                  { constr = lc; info = (loc, None); requests = []; ctxt; model }
            })
        | `True ->
          (* if two byte provenances are not CN_None, they should be equal *)
          let bytes_prov_eq =
            let pairwise prov1 prov2 =
              or_
                [ isNone_ prov1 here;
                  isNone_ prov2 here;
                  eq_ (getOpt_ prov1 here, getOpt_ prov2 here) here
                ]
                here
            in
            let _, _, pairwise_opt_eq =
              List.fold_right
                (fun prov1 (prov2, rest, constr) ->
                   ( prov1,
                     prov2 :: rest,
                     List.map (pairwise prov1) (prov2 :: rest) @ constr ))
                bytes_prov
                (none_ Alloc_id here, [], [])
            in
            and_ pairwise_opt_eq here
          in
          let combined_prov_sym, combined_prov =
            IT.fresh_named (BT.Option Alloc_id) "combined_prov" here
          in
          (* evaluate to the first non-CN_None provenance... *)
          let first_some_prov =
            List.fold_right
              (fun rest prov -> ite_ (isSome_ prov here, prov, rest) here)
              bytes_prov
              (none_ Alloc_id here)
          in
          (* ...and name it for easy reference *)
          let@ () =
            add_a
              combined_prov_sym
              (BT.Option Alloc_id)
              (here, lazy (Pp.string "combined provenance"))
          in
          let@ () = add_c here (LC.T (IT.eq_ (combined_prov, first_some_prov) here)) in
          (* this constraint implements the combine_provenance function *)
          let prov_constr =
            impl_
              ( and2_ (bytes_prov_eq, isSome_ combined_prov here) here,
                eq_ (value_prov, getOpt_ combined_prov here) here )
              here
          in
          return (and_ [ prov_constr; eq_ (value_addr, bytes_addr) here ] here))
     | To ->
       let bytes_prov_eq =
         and_
           (List.map
              (fun byte_prov -> eq_ (byte_prov, some_ value_prov here) here)
              bytes_prov)
           here
       in
       return (and_ [ all_some; bytes_prov_eq; eq_ (value_addr, bytes_addr) here ] here))

