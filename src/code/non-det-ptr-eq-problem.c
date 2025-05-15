#include <stdint.h>

void* empty_prov(int* p) {
    // needs permissive_pointer_arith
    return (int*)((uintptr_t)p+8)-2;
}

int x;
int main() {
    int *p = empty_prov(&x);
    int *q = p;
    // p = &x; // uncomment for UB
    if (p == q) *q;
    return 0;
}
