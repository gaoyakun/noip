#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::max;

int dp (const string &s) {
    int n = s.length();
    vector<vector<int> > solutions(n+1);
    for (int i = 1; i < solutions.size(); i++) {
        solutions[i].resize (n+1, 0);
        solutions[i][i] = 1;
        if (i < n) {
            solutions[i][i+1] = s[i-1] == s[i] ? 2 : 1;
        }
    }
    for (int len = 3; len <= n; len++) {
        for (int start = 1; start <= n - len + 1; start++) {
            int end = start + len - 1;
            for (int k = start; k < end; k++) {
                if (s[start-1] == s[end-1]) {
                    solutions[start][end] = solutions[start+1][end-1] + 2;
                } else {
                    solutions[start][end] = max(solutions[start][k], solutions[k+1][end]);
                }
            }
        }
    }
    return solutions[1][n];
}

int main () {
    string s;
    cin >> s;
    cout << dp(s) << endl;
    return 0;
}