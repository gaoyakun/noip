#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::max;

#include "big_decimal.h"

vector<vector<int> > matrix;
vector<int> sum;
vector<vector<Decimal> > cache;

const Decimal &dp (const vector<int> &number, int i, int j, vector<vector<Decimal> > &cache) {
    if (!cache[i][j].isValid()) {
        if (i == j) {
            cache[i][j] = number[i];
        } else {
            const Decimal &a = dp (number, i+1, j, cache);
            const Decimal &b = dp (number, i, j-1, cache);
            cache[i][j] = max (number[i] + a + a, number[j] + b + b);
        }
    }
    return cache[i][j];
}

Decimal solveRow (const vector<int> &numbers) {
    for (unsigned i = 0; i < cache.size(); i++) {
        for (unsigned j = 0; j < cache[i].size(); j++) {
            cache[i][j].invalidate();
        }
    }
    return dp (numbers, 0, numbers.size()-1, cache);
}

int main () {
    unsigned n, m;
    cin >> n >> m;
    sum.resize (m, 0);
    matrix.resize (n);
    cache.resize (m);
    for (unsigned i = 0; i < m; i++) {
        cache[i].resize (m, 0);
    }
    for (unsigned i = 0; i < n; i++) {
        matrix[i].resize(m);
        for (unsigned j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    Decimal result = 0;
    for (unsigned j = 0; j < n; j++) {
        result += solveRow (matrix[j]);
    }
    cout << result + result << endl;

    return 0;
}