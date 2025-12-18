#include "refinedc.h"
#include <stdio.h>
#include <stdint.h>
#include "address_guesses.h"
void f(uintptr_t j) {
  // VIP: $j = \mathit{Int} \,(x)$
  int i=5;
  uintptr_t k = (uintptr_t)&i;
  // VIP: $k = \mathit{Loc} \,(@i,x)$
  int *p = (int*)j;
  // p = copy_alloc_id(j, &i);
  // VIP: $p = (@i, x)$
  if (p == &i) *p=7;
  printf("i=%d\n",i);
}
int main() {
  uintptr_t j = ADDRESS_PFI_1I;
  f(j);
}
