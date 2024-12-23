#ifndef SEGTREE_H
#define SEGTREE_H
#include "../base.h"

namespace segtree {

const int N = 2e5 + 5, INF = 0x3f3f3f3f;
extern int st[4 * N], n, v[N];

void build(int p = 1, int l = 1, int r = n) {
    if (l == r) {
        st[p] = v[l];
        return;
    }
    build(2 * p, l, (l + r) / 2);
    build(2 * p + 1, (l + r) / 2 + 1, r);
    st[p] = min(st[2 * p], st[2 * p + 1]);
}

void update(int k, int u, int p = 1, int l = 1, int r = n) {
    if (r < k || l > k) return;
    if (l == r) {
        st[p] = u;
        return;
    }
    update(k, u, 2 * p, l, (l + r) / 2);
    update(k, u, 2 * p + 1, (l + r) / 2 + 1, r);
    st[p] = min(st[2 * p], st[2 * p + 1]);
}
int query(int i, int j, int p = 1, int l = 1, int r = n) {
    if (r < i || l > j) return INF;
    if (l >= i && r <= j) {
        return st[p];
    }
    return min(query(i, j, 2 * p, l, (l + r) / 2),
               query(i, j, 2 * p + 1, (l + r) / 2 + 1, r));
}

}  // namespace segtree
#endif