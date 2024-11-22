def gt_zero()
    # $ \vdash \{ \} \; \mathrm{gt\_zero()}  \; \{ \mathsf{ret} \mid \mathsf{ret} > 0 \} $
    x = randint()
    if x >= 5:
        # $ \{ \mathrm{x} \geq 5 \} $
        if x < 4:
            # $ \{ \mathrm{x} \geq 5 , \mathrm{x} < 4 \} \Rightarrow \mathsf{false} $
            # dead code
            raise Exception('UB')
        else:
            # $ \{ \mathrm{x} \geq 5 , \mathrm{x} \geq 4 \} $
            return x
    else:
        # $ \{ \mathrm{x} < 5 \} $
        return 1
