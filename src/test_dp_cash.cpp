#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::max;
using std::min;

typedef unsigned long long data_t;
vector<int> solutions;

int dp (const vector<int> &v, int m) {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j < v.size(); j++) {
            if (i >= v[j]) {
                solutions[i] = min(solutions[i], 1+solutions[i-v[j]]);
            }
        }
    }
    return solutions[m];
}

int main () { 
    int n, m;
    cin >> n >> m;
    solutions.resize (m + 1, 99999999);
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        if (v[i] <= m) {
            solutions[v[i]] = 1;
        }
    }
    cout << dp (v, m) << endl;
    return 0;
}