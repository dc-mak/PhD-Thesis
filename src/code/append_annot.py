def append(xs, ys):
# $\forall l_1, l_2.\ \vdash{} \{ \mathrm{list}(\mathsf{xs}, l_1) \ast{} \mathrm{list}(\mathsf{ys}, l_2) \} \; \mathsf{append}(\mathsf{xs}, \mathsf{ys}) \; \{ \mathsf{ret} \mid \ \mathrm{list}(\mathsf{ret}, l_1 @ l_2) \}$
if (xs == NULL) then
  # $\{ \mathrm{list}(\mathsf{NULL}, []) \ast{} \mathrm{list}(\mathsf{ys}, l_2) \}$
  return ys
  # $\{ \mathrm{list}(\mathsf{ys}, l_2) \}$
else
  # $\{ l_1 = v::l_1' \wedge{} xs \mapsto v \ast{} (\mathsf{xs} + 1) \mapsto{} \mathsf{xs'} \ast{} \mathrm{list}(\mathsf{xs'}, l_1')  \ast{} \mathrm{list}(\mathsf{ys}, l_2) \}$
  new_tail = append(xs->tail, ys)
  # $\{ l_1 = v::l_1' \wedge{} xs \mapsto{} v \ast{} (xs + 1) \mapsto{} \mathsf{xs'} \ast{}  \mathrm{list}(\mathsf{new\_tail}, l_1' @ l_2) \}$
  return xs
  # $\{ \mathrm{list}(\mathsf{xs}, l_1 @ l_2) \}$
