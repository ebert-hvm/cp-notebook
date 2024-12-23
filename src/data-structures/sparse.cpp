#include "cp-notebook/data-structures/sparse.h"
namespace sparse {
int sparse[N][M], n, v[N];

void build() {
    for (int i = 0; i < n; i++) {
        sparse[i][0] = v[i];
    }
    for (int j = 1; j < M; j++) {
        for (int i = 0; i < n; i++) {
            sparse[i][j] = (i + (1 << j) - 1 < n ? min(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]) : sparse[i][j - 1]);
        }
    }
}

int query(int a, int b) {
    if (b - a <= 0) return sparse[a][0];
    int p = 31 - __builtin_clz(b - a);
    return min(sparse[a][p], sparse[b - (1 << p) + 1][p]);
}
}  // namespace sparse