module CN_AllocId = struct
  let t () = if !use_vip then SMT.t_int else CN_Tuple.t []
  (* ... *)
end

module CN_MemByte = struct
  let name = "mem_byte"
  let alloc_id_name = "alloc_id"
  let value_name = "value"
  let alloc_id_value_name = "AiV"
  (** Bit-width of memory bytes *)
  let width = Memory.bits_per_byte
  (** The name of the pointer type *)
  let t = SMT.atom name
  (** Make a allocation ID & address pair pointer value *)
  let con ~alloc_id ~value = SMT.app_ alloc_id_value_name [ alloc_id; value ]
  let declare s = (* ... *)
end

module CN_Pointer = struct
  let name = "pointer"
  let null_name = "NULL"
  let alloc_id_addr_name = "AiA"
  let alloc_id_name = "alloc_id"
  let addr_name = "addr"
  let width = (* ... *)
  let declare s =
    ack_command
      s
      (SMT.declare_datatype
         name
         []
         [ (null_name, []);
           ( alloc_id_addr_name,
             [ (alloc_id_name, CN_AllocId.t ()); (addr_name, SMT.t_bits width) ] )
         ]);
    (* ... *)
end
