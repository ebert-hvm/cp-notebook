#include "cp-notebook/data-structures/dsu.h"
int sz[N], lk[N];

void build() {
    for (int i = 0; i < N; i++) {
        lk[i] = i;
        sz[i] = 1;
    }
}

int find(int x) {
    while (x != lk[x]) x = lk[x];
    return x;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (sz[a] < sz[b]) swap(a, b);
    lk[b] = a;
    sz[a] += sz[b];
}
