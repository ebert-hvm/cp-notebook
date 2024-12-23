#ifndef LAZYSEGTREE_H
#define LAZYSEGTREE_H
#include "../base.h"

namespace lazysegtree {

const int N = 2e5 + 5;
extern int st[4 * N], lz[4 * N], n, v[N];

void build(int p = 1, int l = 1, int r = n) {
    if (l == r) {
        st[p] = v[l];
        return;
    }
    build(2 * p, l, (l + r) / 2);
    build(2 * p + 1, (l + r) / 2 + 1, r);
    st[p] = st[2 * p] + st[2 * p + 1];
}

void push(int p, int l, int r) {
    if (lz[p]) {
        st[p] += (r - l + 1) * lz[p];
        if (l != r) lz[2 * p] += lz[p], lz[2 * p + 1] += lz[p];
        lz[p] = 0;
    }
}

void update(int i, int j, int k, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (r < i || l > j) return;
    if (l >= i && r <= j) {
        lz[p] = k;
        push(p, l, r);
        return;
    }
    update(i, j, k, 2 * p, l, (l + r) / 2);
    update(i, j, k, 2 * p + 1, (l + r) / 2 + 1, r);
    st[p] = st[2 * p] + st[2 * p + 1];
}

int query(int i, int j, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (r < i || l > j) return 0;
    if (l >= i && r <= j) {
        return st[p];
    }
    return query(i, j, 2 * p, l, (l + r) / 2) +
           query(i, j, 2 * p + 1, (l + r) / 2 + 1, r);
}

}  // namespace lazysegtree
#endif