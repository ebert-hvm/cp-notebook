#ifndef DSU_H
#define DSU_H
#include "../base.h"
const int N = 2e5 + 5;
extern int sz[N], lk[N];

void build();
int find(int x);
void unite(int a, int b);

#endif