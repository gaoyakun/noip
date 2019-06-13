#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef unsigned long long data_t;
vector<vector<data_t> > solutions;

void dp (int n, int m) {
    for (int i = 1; i <= n; i++) {
        solutions[i][0] = 1;
        solutions[i][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            solutions[i][j] = solutions[i-1][j-1] + solutions[i-1][j];
        }
    }
}

int main () {
    int n, m;
    cin >> n >> m;
    solutions.resize (n + 1);
    for (int i = 0; i <= n; i++) {
        solutions[i].resize(n + 1, 0);
    }
    dp (n, m);
    cout << solutions[n][m] << endl;
    return 0;
}