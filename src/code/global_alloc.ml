module Global = struct
  type t = (* ... *)
  let empty =
    { struct_decls = Sym.Map.empty;
      datatypes = Sym.Map.empty;
      datatype_constrs = Sym.Map.empty;
      datatype_order = None;
      fun_decls = Sym.Map.empty;
      resource_predicates = Sym.Map.(empty |> add Alloc.Predicate.sym Definition.alloc);
      logical_functions = Sym.Map.empty;
      lemmata = Sym.Map.empty
    }
  (* ... *)
end
