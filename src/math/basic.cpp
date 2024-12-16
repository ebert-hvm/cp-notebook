#include "cp-notebook/math/basic.h"
int comp[N];
void sieve() {
    comp[0] = comp[1] = 1;
    for (int i = 2; i < N; i++) {
        if (comp[i]) continue;
        for (int j = 2 * i; j < N; j += i) comp[j] = 1;
    }
}