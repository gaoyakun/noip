#include <iostream>
#include "avl_tree.h"
#include "binary_tree_funcs.h"

using std::cin;
using std::cout;
using std::endl;

int main () {
    int n;
    cin >> n;
    AVLTree<int> t;
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
                cout << avl_get_rank (t.root, x) << endl;
                break;
            case 4: // kth
                cout << avl_find_kth (t.root, x)->value.value << endl;
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
