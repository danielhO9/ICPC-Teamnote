/**
 * Author: -
 * Date: -
 * License: -
 * Source: https://cp-algorithms.com/data_structures/fenwick.html
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 * Time: $O(\log^2 N)$.
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FenwickTree2D {
    vector<vector<int>> bit;
    int n, m;
	FenwickTree2D(int n, int m) : n(_n), m(_m) {
		bit.assign(n, vector<int>(m, 0));
	}
    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }
    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};