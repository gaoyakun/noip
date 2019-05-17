#include <iostream>
#include <cstdlib>
#include "test_common.h"
#include "binary_tree.h"
#include "binary_tree_debug.h"
#include "binary_search_tree.h"
#include "avl_tree.h"

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
	template <class T>
    void operator () (const T &val) const {
        if (val.value <= lastValue) {
            ok = false;
        }
        count_verify += val.count;
    }
};

bool testCase (size_t count) {
	BinarySearchTree<int> bst;
    AVLTree<int> avl;
    for (size_t i = 0; i < count; i++) {
		int val = randRange(-100, 100);
        bst.add (val);
		avl.add(val);
    }
	{
		TraverseFunc func;
		bst.inorderIterate (bst.getRoot(), func);
		bool ret = func.ok && func.count_verify == count;
		if (!ret) {
			BinaryTreeDebugger debugger;
			debugger.print_ascii_tree(bst.getRoot());
			return false;
		}
	}
	{
		TraverseFunc func;
		avl.inorderIterate(avl.getRoot(), func);
		bool ret = func.ok && func.count_verify == count;
		if (!ret) {
			BinaryTreeDebugger debugger;
			debugger.print_ascii_tree(bst.getRoot());
			return false;
		}
	}
	return true;
}

int debugBST () {
	AVLTree<int> bst;
    for (;;) {
        char cmd;
        cin >> cmd;
        if (cmd == 'a') {
            int value;
            cin >> value;
            bst.add (value);
            BinaryTreeDebugger debugger;
            debugger.print_ascii_tree (bst.getRoot());
        } else if (cmd == 'q') {
            return 0;
        }
    }
}

int main (int argc, char *argv[]) {
    if (argc == 1) {
        return debugBST ();
    } else if (argc != 3) {
        cout << "Usage: test_bitop ARRAY_SIZE TEST_COUNT" << endl;
        return 1;
    }
    const size_t count = atoi(argv[1]);
    const size_t times = atoi(argv[2]);
	const clock_t seed = 162;// rdtsc() % 1000;
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

