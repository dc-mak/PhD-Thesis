#include <stdio.h>
#include <stdint.h>
#include "address_guesses.h"
void f(uintptr_t j) {
  int i=5;
  // uintptr_t k = (uintptr_t)&i;
  int *p = (int*)j;
  if (p == &i) *p=7;
  printf("i=%d\n",i);
}
int main() {
  uintptr_t j = ADDRESS_PFI_1I;
  f(j);
}
