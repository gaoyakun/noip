#include <iostream>
#include <vector>
#include <algorithm>
#include "test_common.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

struct Bundle {
    int a[3];
};

vector<Bundle> bundles;
vector<Bundle> bundles2;
size_t ans = 0;

struct CompGreater {
    size_t index;
    CompGreater (size_t i) {
        index = i;
    }
    bool operator () (const Bundle &a, const Bundle &b) const {
        return a.a[index] > b.a[index];
    }
};

struct CompLess {
    size_t index;
    CompLess (size_t i) {
        index = i;
    }
    bool operator () (const Bundle &a, const Bundle &b) const {
        return a.a[index] < b.a[index];
    }
};

void cdq (size_t l, size_t r) {
    if (l == r) {
        return;
    }
}

int main () {
    size_t count;
    cin >> count;
    bundles.resize (count);
    for (size_t i = 0; i < count; i++) {
        cin >> bundles[i].a[0] >> bundles[i].a[1] >> bundles[i].a[2];
    }
    sort (bundles.begin(), bundles.end(), CompLess(0));
}