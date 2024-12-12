let add_r_internal ?(derive_constraints = true) loc (r, Res.O oargs) =
  let@ s = get_typing_context () in
  let@ simp_ctxt = simp_ctxt () in
  let r = Simplify.Request.simp simp_ctxt r in
  let oargs = Simplify.IndexTerms.simp simp_ctxt oargs in
  let pointer_facts =
    if derive_constraints then
      Res.pointer_facts ~new_resource:(r, Res.O oargs) ~old_resources:(Context.get_rs s)
    else
      []
  in
  let@ () = set_typing_context (Context.add_r loc (r, O oargs) s) in
  iterM (fun x -> add_c_internal (LC.T x)) pointer_facts
