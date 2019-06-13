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

typedef unsigned long long data_t;
vector<vector<data_t> > solutions;

void dp (const string &a, const string &b) {
    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            char x = a[i-1];
            char y = b[j-1];
            if (x == y) {
                solutions[i][j] = solutions[i-1][j-1] + 1;
            } else {
                solutions[i][j] = max (solutions[i-1][j], solutions[i][j-1]);
            }
        }
    }
}

int main () {
    string n, m;
    cin >> n >> m;
    solutions.resize (n.length() + 1);
    for (int i = 0; i <= n.length(); i++) {
        solutions[i].resize(m.length() + 1, 0);
    }
    dp (n, m);
    cout << solutions[n.length()][m.length()] << endl;
    return 0;
}