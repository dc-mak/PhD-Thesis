# $ \{ \} $
if x >= 5:
    # $ \{ \mathrm{x} \geq 5 \} $
    if x < 4:
        # $ \{ \mathrm{x} \geq 5 , \mathrm{x} < 4 \} \Rightarrow \mathsf{false} $
         # dead code
        raise Exception('UB')
    else:
        # $ \{ \mathrm{x} \geq 5 , \mathrm{x} \geq 4 \} $
        pass
else:
    # $ \{ \mathrm{x} < 5 \} $
    pass
