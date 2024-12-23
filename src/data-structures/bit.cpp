#include "cp-notebook/data-structures/bit.h"
long long bit[N];

long long sum(int p) {
    long long s = 0;
    p += 2;
    while (p) s += bit[p], p -= p & -p;
    return s;
}
void add(int p, long long v) {
    p += 2;
    while (p < N) bit[p] += v, p += p & -p;
}