#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

#define MAX_N 100

void add (int C[], int total, int n, int d) {
    while (n <= total) {
        C[n] += d;
        n += n & -n;
    }
}

int sum (int C[], int n) {
    int result = 0;
    while (n) {
        result += C[n];
        n -= n & -n;
    }
    return result;
}

int main () {
    int C[MAX_N+1];
    int total;
    cin >> total;
    memset (C, 0, sizeof(C));
    for (int i = 0; i < total; i++) {
        int k;
        cin >> k;
        add (C, total, i+1, k);
    }
    for (;;) {
        int n;
        cout << "Sum what?";
        cin >> n;
        if (n == 0) {
            break;
        } else if (n > total) {
            cout << "Number too big" << endl;
        } else {
            cout << sum (C, n) << endl;
        }
    }
    return 0;
}