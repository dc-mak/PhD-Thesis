module Predicate = struct
  type t =
    { loc : Locations.t;
      pointer : Sym.t;
      iargs : (Sym.t * BaseTypes.t) list;
      oarg_bt : BaseTypes.t;
      clauses : Clause.t list option
    }
  (* ... *)
end
