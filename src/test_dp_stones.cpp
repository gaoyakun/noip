#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::vector;

int dp (const vector<int> &v) {
    int n = v.size() - 1;
    vector<vector<int> > solutions(n + 1);
    for (int i = 0; i < solutions.size(); i++) {
        solutions[i].resize (n + 1, INT_MAX);
        solutions[i][i] = 0;
    }
    for (int len = 2; len <= n; len++) {
        for (int start = 1; start <= n - len + 1; start++) {
            int end = start + len - 1;
            for (int k = start; k < end; k++) {
                solutions[start][end] = min (solutions[start][end], solutions[start][k] + solutions[k+1][end] + v[end] - v[start-1]);
            }
        }
    }
    return solutions[1][n];
}

int main () {
    int n;
    cin >> n;
    vector<int> v(n+1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        v[i] += v[i-1];
    }
    cout << dp(v) << endl;
}