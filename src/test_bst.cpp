#include <iostream>
#include <cstdlib>
#include "test_common.h"
#include "binary_tree.h"
#include "binary_search_tree.h"

using std::cin;
using std::cout;
using std::endl;
using std::flush;

struct TraverseFunc {
    int lastValue;
    mutable size_t count_verify;
    mutable bool ok;
    TraverseFunc () {
        lastValue = INT_MIN;
        count_verify = 0;
        ok = true;
    }
    void operator () (const BinarySearchTree<int>::value_type &val) const {
        if (val.value <= lastValue) {
            ok = false;
        }
        count_verify += val.count;
    }
};

bool testCase (size_t count) {
    BinarySearchTree<int> bst;
    for (size_t i = 0; i < count; i++) {
        bst.add (randRange (-10000, 10000));
    }
    TraverseFunc func;
    bst.inorderIterate (bst.getRoot(), func);
    return func.ok && func.count_verify == count;
}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: test_bitop ARRAY_SIZE TEST_COUNT" << endl;
        return 1;
    }
    const size_t count = atoi(argv[1]);
    const size_t times = atoi(argv[2]);
    const clock_t seed = rdtsc() % 1000;
    cout << "Random seed: " << seed << endl;
    randomSeed (seed);

    cout << "Testing binary search tree ..." << flush;
    bool failed = false;
    for (size_t j = 0; j < times; j++) {
        if (!testCase (count)) {
            failed = true;
            break;
        }
    }
    cout << (failed ? "failed" : "ok") << endl;

    return 0;
}

