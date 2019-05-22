#include <iostream>
#include "big_decimal.h"

using std::cin;
using std::cout;
using std::endl;

int main () {
    Decimal a, b;
    long long x, y;
    cin >> x >> y;
    a.set(x);
    b.set(y);
    cout << "add:" << a + b << endl;
    cout << "add:" << a + y << endl;
    cout << "add:" << x + b << endl;
    cout << "add:" << x + y << endl;
    cout << "gt:" << (a > b) << endl;
    cout << "lt:" << (a < b) << endl;
    cout << "eq:" << (a == b) << endl;
    cout << "not:" << !a << endl;

    return 0;
}