//-
//-/*@
//-datatype List {
//-    Nil {},
//-    Cons {i32 head, datatype List tl}
//-}
//-@*/
int kvm_pgtable_walk(struct kvm_pgtable *pgt, u64 addr, u64 size,
                     struct kvm_pgtable_walker *walker)
{
        // omitted
        return _kvm_pgtable_walk(&walk_data);
}
//-
struct hyp_map_data {
        u64                             phys;
        kvm_pte_t                       attr;
        struct kvm_pgtable_mm_ops       *mm_ops;
};
//-
