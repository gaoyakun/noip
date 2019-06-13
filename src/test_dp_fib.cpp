#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef unsigned long long data_t;
vector<data_t> solutions;

void dp (int n) {
    solutions[1] = 0;
    solutions[2] = 1;
    for (int i = 3; i <= n; i++) {
        solutions[i] = solutions[i-1] + solutions[i-2];
    }
}

int main () {
    int n;
    cin >> n;
    solutions.resize (n + 1);
    dp (n);
    for (int i = 1; i <= n; i++) {
        cout << solutions[i] << endl;
    }
    return 0;
}