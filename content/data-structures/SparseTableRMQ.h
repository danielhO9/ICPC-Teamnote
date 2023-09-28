/**
 * Author: -
 * Date: -
 * License: -
 * Source: https://cp-algorithms.com/data_structures/sparse-table.html
 * Description: Computes minimum of a range in $O(1)$ time.
 * Time: $O(1)$.
 * Status: stress-tested
 */

// update
int st[K + 1][MAXN];

std::copy(array.begin(), array.end(), st[0]);

for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);

// query with [L, R]
int log2_floor(unsigned long long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

int minimum(int L, int R) {
    int i = log2_floor(R - L + 1);
    return min(st[i][L], st[i][R - (1 << i) + 1]);
}