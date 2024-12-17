// arch/arm64/kvm/hyp/pgtable.c
#define KVM_PTE_ADDR_MASK             GENMASK(47, PAGE_SHIFT)

// include/linux/bits.h
#define GENMASK_INPUT_CHECK(h, l) \
     (BUILD_BUG_ON_ZERO(__builtin_choose_expr( \
             __is_constexpr((l) > (h)), (l) > (h), 0)))

#define __GENMASK(h, l) \
        (((~UL(0)) - (UL(1) << (l)) + 1) & \
         (~UL(0) >> (BITS_PER_LONG - 1 - (h))))

#define GENMASK(h, l) \
     (GENMASK_INPUT_CHECK(h, l) + __GENMASK(h, l))

// include/linux/const.h
/*
 * This returns a constant expression while determining if an argument is
 * a constant expression, most importantly without evaluating the argument.
 * Glory to Martin Uecker <Martin.Uecker@med.uni-goettingen.de>
 */
#define __is_constexpr(x) \
        (sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))

// include/linux/build_bug.h
#define BUILD_BUG_ON_ZERO(e) ((int)(sizeof(struct { int:(-!!(e)); })))
