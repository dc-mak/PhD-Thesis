let pointer_eq ?(negate = false) pe1 pe2 =
  let@ () = WellTyped.ensure_base_type loc ~expect Bool in
  let k, case, res =
    if negate then ((fun x -> k (not_ x loc)), "in", "ptrNeq") else (k, "", "ptrEq")
  in
  check_pexpr pe1 (fun arg1 ->
    check_pexpr pe2 (fun arg2 ->
      let bind name term =
        let sym, it = IT.fresh_named BT.Bool name loc in
        let@ _ = add_a sym Bool (here, lazy (Sym.pp sym)) in
        let@ () = add_c loc (LC.T (term it)) in
        return it
      in
      let@ ambiguous =
        bind "ambiguous"
        @@ fun ambiguous ->
        eq_
          ( ambiguous,
            and_
              [ hasAllocId_ arg1 here;
                hasAllocId_ arg2 here;
                ne_ (allocId_ arg1 here, allocId_ arg2 here) here;
                eq_ (addr_ arg1 here, addr_ arg2 here) here
              ]
              here )
          here
      in
      let@ provable = provable loc in
      let@ () =
        match provable @@ LC.T (not_ ambiguous here) with
        | `True -> return ()
        | `False ->
          let msg =
            Printf.sprintf
              "Cannot rule out ambiguous pointer %sequality case (addresses \
               equal, but provenances differ)"
              case
          in
          warn loc !^msg;
          return ()
      in
      let@ both_eq =
        bind "both_eq" @@ fun both_eq -> eq_ (both_eq, eq_ (arg1, arg2) here) here
      in
      let@ neither =
        bind "neither"
        @@ fun neither ->
        eq_ (neither, and_ [ not_ both_eq here; not_ ambiguous here ] here) here
      in
      let@ res =
        bind res
        @@ fun res ->
        (* NOTE: ambiguous case is intentionally under-specified *)
        and_ [ impl_ (both_eq, res) here; impl_ (neither, not_ res here) here ] loc
      in
      k res
