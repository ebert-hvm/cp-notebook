#ifndef SPARSE_H
#define SPARSE_H
#include "../base.h"
namespace sparse {
const int N = 2e5 + 5, M = 20;
extern int sparse[N][M], n, v[N];

void build();
int query(int a, int b);

}  // namespace sparse
#endif