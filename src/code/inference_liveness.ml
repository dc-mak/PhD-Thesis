let check_live_alloc reason loc ptr =
  let module Ans = struct
    type t =
      | Found
      | No_res
      | Model of (Solver.model_with_q * IT.t)
  end
  in
  let here = Locations.other __FUNCTION__ in
  let alloc_id_matches found res_ptr =
    let@ found in
    match found with
    | Ans.Found -> return Ans.Found
    | No_res | Model _ ->
      let constr = IT.(eq_ (allocId_ ptr here, allocId_ res_ptr here) here) in
      let@ provable = provable loc in
      (match provable (LC.T constr) with
       | `True -> return Ans.Found
       | `False ->
         let@ model = model () in
         return (Ans.Model (model, constr)))
  in
  let f res found =
    let found =
      match res with
      | Req.Q _, _ -> found
      | Req.P { name = Owned _; pointer; iargs = _ }, _ ->
        alloc_id_matches found pointer
      | Req.P { name = PName name; pointer; iargs = _ }, _ ->
        if Sym.equal name Alloc.Predicate.sym then
          alloc_id_matches found pointer
        else
          found
    in
    (Unchanged, found)
  in
  let@ found, _ = map_and_fold_resources loc f (return Ans.No_res) in
  let@ found in
  match found with
  | Ans.Found -> return ()
  | No_res ->
    fail (fun ctxt ->
      let msg =
        TypeErrors.Allocation_not_live { reason; ptr; model_constr = None; ctxt }
      in
      { loc; msg })
  | Model (model, constr) ->
    fail (fun ctxt ->
      let msg =
        TypeErrors.Allocation_not_live
          { reason; ptr; model_constr = Some (model, constr); ctxt }
      in
      { loc; msg })

