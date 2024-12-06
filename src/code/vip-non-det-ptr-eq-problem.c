#include <inttypes.h>
int main() {
  int y=2, x=1;
  int *p = (int *)((uintptr_t)&x + sizeof(int));
  int *q = (int *)((uintptr_t)&y + 0);
  return (p==q) ? 0 : 1;
}
