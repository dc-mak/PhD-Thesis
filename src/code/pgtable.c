static u64 kvm_pte_to_phys(kvm_pte_t pte)
{
    u64 pa = pte & KVM_PTE_ADDR_MASK;
    if (PAGE_SHIFT == 16)
        pa |= FIELD_GET(KVM_PTE_ADDR_51_48, pte) << 48;
    return pa;
}

int kvm_pgtable_hyp_map(struct kvm_pgtable *pgt, u64 addr, u64 size,
            u64 phys, enum kvm_pgtable_prot prot)
{
    int ret;
    struct hyp_map_data map_data = {
        .phys   = ALIGN_DOWN(phys, PAGE_SIZE),
        .mm_ops = pgt->mm_ops,
    };
    struct kvm_pgtable_walker walker = {
        .cb     = hyp_map_walker,
        .flags  = KVM_PGTABLE_WALK_LEAF,
        .arg    = &map_data,
    };

    ret = hyp_set_prot_attr(prot, &map_data.attr);
    if (ret)
        return ret;

    ret = kvm_pgtable_walk(pgt, addr, size, &walker);
    dsb(ishst);
    isb();
    return ret;
}

