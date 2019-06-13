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
vector<int> solutions;

int dp (const vector<data_t> &v) {
    solutions[1] = 1;
    int result = 1;
    for (int i = 2; i < v.size(); i++) {
        solutions[i] = 1;
        for (int j = 1; j < i; j++) {
            if (v[i] >= v[j]) {
                solutions[i] = max(solutions[i], solutions[j] + 1);
            }
        }
        if (solutions[i] > result) {
            result = solutions[i];
        }
    }
    return result;
}

int main () {
    int n;
    cin >> n;
    solutions.resize (n + 1);
    vector<data_t> v(n+1);
    for (int i = 1; i < v.size(); i++) {
        cin >> v[i];
    }
    cout << dp (v) << endl;
    return 0;
}