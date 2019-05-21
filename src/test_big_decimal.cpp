#include <iostream>
#include "big_decimal.h"

using std::cin;
using std::cout;
using std::endl;

int main () {
    Decimal a, b;
    cin >> a >> b;
    cout << "gt:" << (a > b) << endl;
    cout << "lt:" << (a < b) << endl;
    cout << "eq:" << (a == b) << endl;
    cout << "not:" << !a << endl;

    return 0;
}