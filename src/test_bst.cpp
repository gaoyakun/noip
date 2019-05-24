#include <iostream>
#include <cstdlib>
#include "test_common.h"
#include "binary_tree_funcs.h"
#include "binary_search_tree.h"

#define USE_SCAPEGOAT_TREE

#ifdef USE_AVL_TREE
#include "avl_tree.h"
typedef AVLTree<int> tree_type;
#elif defined(USE_SCAPEGOAT_TREE)
#include "scapegoat_tree.h"
typedef ScapeGoatTree<int> tree_type;
#elif defined(USE_TREAP)
#include "treap.h"
typedef Treap<int> tree_type;
#else
#error Must define either USE_AVL_TREE or USE_SCAPEGOAT_REE or USE_TREAP
#endif

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
    tree_type bt;
    for (size_t i = 0; i < count; i++) {
		int val = randRange(-100, 100);
        bst.add (val);
		bt.add(val);
    }
	{
		TraverseFunc func;
		bst.inorderIterate (bst.root, func);
		bool ret = func.ok && func.count_verify == count;
		if (!ret) {
			BinaryTreeDebugger debugger;
			debugger.print_ascii_tree(bst.root);
			return false;
		}
	}
	{
		TraverseFunc func;
		bt.inorderIterate(bt.root, func);
		bool ret = func.ok && func.count_verify == count;
		if (!ret) {
			BinaryTreeDebugger debugger;
			debugger.print_ascii_tree(bt.root);
			return false;
		}
	}
	return true;
}

int debugBST () {
	tree_type bst;
    for (;;) {
        char cmd;
        cin.clear ();
        cin.sync ();
        cin >> cmd;
        if (cmd == 'a') {
            int value;
            cin >> value;
            bst.add (value);
            BinaryTreeDebugger debugger;
            debugger.print_ascii_tree (bst.root);
        } else if (cmd == 'A') {
            int value1, value2;
            cin >> value1 >> value2;
            for (; value1 <= value2; value1++) {
                bst.add (value1);
            }
            BinaryTreeDebugger debugger;
            debugger.print_ascii_tree (bst.root);
        } else if (cmd == 'k') {
            int k;
            cin >> k;
            const tree_type::node_type *node = bst_find_kth (bst.root, k);
            if (node) {
                cout << node->value.value << endl;
            } else {
                cout << "not found" << endl;
            }
        } else if (cmd == 'r') {
            int val;
            cin >> val;
            cout << bst_get_rank (bst.root, val) << endl;
        } else if (cmd == 'm') {
            const tree_type::node_type *node = bst_find_min (bst.root);
            if (node) {
                cout << node->value.value << endl;
            } else {
                cout << "not found" << endl;
            }
        } else if (cmd == 'n') {
            int val;
            cin >> val;
            const tree_type::node_type *node = bst_get_next (bst.root, val);
            if (node) {
                cout << node->value.value << endl;
            } else {
                cout << "not found" << endl;
            }
        } else if (cmd == 'p') {
            int val;
            cin >> val;
            const tree_type::node_type *node = bst_get_prev (bst.root, val);
            if (node) {
                cout << node->value.value << endl;
            } else {
                cout << "not found" << endl;
            }
        } else if (cmd == 'd') {
            int val;
            cin >> val;
            bst.remove (val);
            tree_print (bst.root);
        } else if (cmd == 'D') {
            int value1, value2;
            cin >> value1 >> value2;
            for (; value1 <= value2; value1++) {
                bst.remove (value1);
            }
            tree_print (bst.root);
        } else if (cmd == 'M') {
            const tree_type::node_type *node = bst_find_max (bst.root);
            if (node) {
                cout << node->value.value << endl;
            } else {
                cout << "not found" << endl;
            }
        } else if (cmd == 'c') {
            bst.clear ();
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
	const clock_t seed = time(NULL) % 1000;
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

