#include <iostream>
#include "binary_tree_funcs.h"

#define USE_TREAP

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
#error Must define USE_AVL_TREE or USE_SCAPEGOAT_TREE
#endif

using std::cin;
using std::cout;
using std::endl;

int main () {
    int n;
    cin >> n;
    tree_type t;
    for (int i = 0; i < n; i++) {
        int opt, x;
        cin >> opt >> x;
        switch (opt) {
            case 1: // insert
                t.add (x);
                break;
            case 2: // remove
                t.remove (x);
                break;
            case 3: // rank
                cout << bst_get_rank (t.root, x) << endl;
                break;
            case 4: // kth
                cout << bst_find_kth (t.root, x)->value.value << endl;
                break;
            case 5: // prev
                cout << bst_get_prev (t.root, x)->value.value << endl;
                break;
            case 6: // next
                cout << bst_get_next (t.root, x)->value.value << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}
