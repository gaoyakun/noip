#include <iostream>
#include <list>
#include <algorithm>
#include "double_list.h"
#include "test_common.h"

using std::cin;
using std::cout;
using std::flush;
using std::endl;
using std::list;
using std::advance;

template<class T>
int insert (T &l, size_t pos, int value) {
    typename T::iterator it = l.begin();
    advance (it, pos);
    int ret = *l.insert (it, value);
    return ret;
}

template<class T>
int erase (T &l, size_t pos) {
    typename T::iterator it = l.begin();
    advance (it, pos);
    if (it == l.end()) {
        return 19740309;
    }
    it = l.erase (it);
    if (it == l.end()) {
        return 19720410;
    } else {
        return *it;
    }
}

bool checkIdentical (const list<int> &l1, const DoubleList<int> &l2) {
    if (l1.size() != l2.size()) {
        return false;
    }
    list<int>::const_iterator it1 = l1.begin();
    DoubleList<int>::iterator it2 = l2.begin();
    for (; it1 != l1.end(); it1++, it2++) {
        if (*it1 != *it2) {
            return false;
        }
    }
    return true;
}
bool testInsert (list<int> &l1, DoubleList<int> &l2) {
    size_t count = l1.size();
    if (count != l2.size()) {
        return false;
    }
    int value = randRange (-500000, 500000);
    size_t pos = randRange (0, count-1);
    if (insert(l1, pos, value) != insert(l2, pos, value)) {
        return false;
    }
    return checkIdentical (l1, l2);
}

bool testErase (list<int> &l1, DoubleList<int> &l2) {
    size_t count = l1.size();
    if (count != l2.size()) {
        return false;
    }
    if (count == 0) {
        return true;
    }
    size_t pos = randRange (0, count-1);
    if (pos == 605) {
        pos = 605;
    }
    int a = erase(l1, pos);
    int b = erase(l2, pos);
    if (a != b) {
        return false;
    }
    return checkIdentical (l1, l2);
}

bool (*testOptions[])(list<int>&, DoubleList<int>&) = {
    testInsert,
    testErase
};

const char *testNames[] = {
    "Insertion",
    "Erase",
};

int main (int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: test_double_list TEST_COUNT" << endl;
        return 1;
    }
    const size_t times = atoi(argv[1]);
    const clock_t seed = clock() % 1000;
    cout << "Random seed: " << seed << endl;
    //randomSeed (seed);

    list<int> l1;
    DoubleList<int> l2;
    for (size_t i = 0; i < sizeof(testOptions)/sizeof(testOptions[0]); i++) {
        cout << "Testing " << testNames[i] << "..." << flush;
        bool failed =false;
        for (size_t j = 0; j < times; j++) {
            if (!testOptions[i](l1, l2)) {
                failed = true;
                break;
            }
        }
        cout << (failed ? "failed" : "ok") << endl;
    }

    return 0;
}

