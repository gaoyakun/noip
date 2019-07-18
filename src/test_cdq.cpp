#include <iostream>
#include <vector>
#include <algorithm>
#include "test_common.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::unique;
using std::lower_bound;

struct Point {
    int a;
    int b;
};

vector<Point> points;
vector<Point> temp;
vector<int> discret;
size_t ans = 0;

vector<int> bit;

#define LOWBIT(i) ((i) & (-(i)))

void bit_add (size_t pos, int val) {
    for (size_t i = pos; i < bit.size(); i += LOWBIT(i)) {
        bit[i] += val;
    }
}

int bit_sum (size_t end) {
    int sum = 0;
    while (end) {
        sum += bit[end];
        end -= LOWBIT(end);
    }
    return sum;
}

int bruteforce () {
    int result = 0;
    for (size_t i = 1; i < points.size(); i++) {
        for (size_t j = i+1; j < points.size(); j++) {
            if (points[i].a <= points[j].a && points[i].b <= points[j].b) {
                result++;
            }
        }
    }
    return result;
}

void cdq (size_t l, size_t r) {
    if (l == r) {
        return;
    }
    size_t mid = (l + r) >> 1;
    cdq (l, mid);
    cdq (mid+1, r);
    
    size_t left = l;
    size_t right = mid + 1;
    size_t pos = l;
    while (left <= mid || right <= r) {
        if (right > r || (left <= mid && points[left].a <= points[right].a)) {
            bit_add (points[left].b, 1);
            temp[pos++] = points[left++];
        } else {
            ans += bit_sum(points[right].b);
            temp[pos++] = points[right++];
        }
    }
    for (size_t i = l; i <= mid; i++) {
        bit_add (points[i].b, -1);
    }
    for (size_t i = l; i <= r; i++) {
        points[i] = temp[i];
    }
}

int main () {
    size_t count;
    cin >> count;
    points.resize (count + 1);
    temp.resize (count + 1);
    discret.resize (count);
    bit.resize (count + 1, 0);
    for (size_t i = 1; i <= count; i++) {
        cin >> points[i].a >> points[i].b;
        discret[i-1] = points[i].b;
    }
    sort (discret.begin(), discret.end());
    discret.erase (unique(discret.begin(), discret.end()), discret.end());
    for (size_t i = 1; i <= count; i++) {
        points[i].b = lower_bound(discret.begin(), discret.end(), points[i].b) - discret.begin() + 1;
    }
    cout << bruteforce () << endl;
    cdq (1, count);
    cout << ans << endl;
    return 0;
}
