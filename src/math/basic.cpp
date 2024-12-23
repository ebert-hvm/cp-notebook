#include "cp-notebook/math/basic.h"
int comp[N];

void sieve() {
    comp[0] = comp[1] = 1;
    for (int i = 2; i < N; i++) {
        if (comp[i]) continue;
        for (int j = 2 * i; j < N; j += i) comp[j] = 1;
    }
}

long long fexp(long long a, long long b, long long m = M) {
    long long r = 1;
    for (a %= m; b; b >>= 1, a = (a * a) % m)
        if (b & 1) r = (r * a) % m;
    return r;
}