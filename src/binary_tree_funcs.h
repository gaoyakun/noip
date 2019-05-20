#ifndef __BINARY_TREE_FUNCS_H__
#define __BINARY_TREE_FUNCS_H__

#include "binary_tree.h"
#include "binary_search_tree.h"
#include "avl_tree.h"

namespace {
    template <class NodeType>
    struct kthFinder {
        typedef NodeType node_type;
        const node_type *operator () (const node_type *root, int k) const {
            int count = 0;
            return bst_find_kth_r (root, k, count);
        }
        const node_type *bst_find_kth_r (const node_type *root, int k, int &count) const {
            const node_type *p = NULL;
            if (root->left) {
                p = bst_find_kth_r (root->left, k, count);
                if (p) {
                    return p;
                }
            }
            count++;
            if (count == k) {
                return root;
            }
            return root->right ? bst_find_kth_r (root->right, k, count) : NULL;
        }
    };
    template <class NodeType>
    struct kthFinderAVL {
        typedef NodeType node_type;
        const node_type *operator () (const node_type *root, int k) const {
            return bst_find_kth_r (root, k);
        }
        const node_type *bst_find_kth_r (const node_type *root, int k) const {
            int leftSize = root->left ? root->left->value.size : 0;
            if (k <= leftSize) {
                return root->left ? bst_find_kth_r (root->left, k) : NULL;
            } else if (k == leftSize + 1) {
                return root;
            } else if (root->right) {
                return bst_find_kth_r (root->right, k - leftSize - 1);
            } else {
                return NULL;
            }
        }
    };
}

template <class NodeType>
const NodeType *bst_find_kth (const NodeType *root, int k) {
    return kthFinder<NodeType>()(root, k);
}

template <class NodeType>
const NodeType *avl_find_kth (const NodeType *root, int k) {
    return kthFinderAVL<NodeType>()(root, k);
}

template <class NodeType>
int avl_get_rank (const NodeType *node, const typename NodeType::key_type &value) {
    if (value < node->value.value) {
        return node->left ? avl_get_rank (node->left, value) : 0;
    } else if (value == node->value.value) {
        return node->left ? node->left->value.size + 1 : 1;
    } else if (node->right) {
        int k = avl_get_rank (node->right, value);
        return k ? k + (node->left ? node->left->value.size + node->value.count : node->value.count) : 0;
    } else {
        return 0;
    }
}

template <class NodeType>
const NodeType *bst_get_next (const NodeType *root, const typename NodeType::key_type &value) {
    if (root->value.value <= value) {
        return root->right ? bst_get_next (root->right, value) : NULL;
    } else {
        const NodeType *p = root->left ? bst_get_next (root->left, value) : NULL;
        return p ? p : root;
    }
}

template <class NodeType>
const NodeType *bst_get_prev (const NodeType *root, const typename NodeType::key_type &value) {
    if (root->value.value >= value) {
        return root->left ? bst_get_prev (root->left, value) : NULL;
    } else {
        const NodeType *p = root->right ? bst_get_prev (root->right, value) : NULL;
        return p ? p : root;
    }
}

template <class NodeType>
const NodeType *bst_find_min (const NodeType *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

template <class NodeType>
const NodeType *bst_find_max (const NodeType *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}


#endif // __BINARY_TREE_FUNCS_H__
