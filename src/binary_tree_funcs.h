#ifndef __BINARY_TREE_FUNCS_H__
#define __BINARY_TREE_FUNCS_H__

#include "binary_tree_debug.h"

namespace {
    template <class HasSizeTag>
    struct kthFinder {
        template <class NodeType>
        const NodeType *operator () (const NodeType *root, int k) const {
            int count = 0;
            return bst_find_kth_r (root, k, count);
        }
        template <class NodeType>
        const NodeType *bst_find_kth_r (const NodeType *root, int k, int &count) const {
            const NodeType *p = NULL;
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
    template <>
    struct kthFinder<BSTHasSize> {
        template <class NodeType>
        const NodeType *operator () (const NodeType *root, int k) const {
            return bst_find_kth_r (root, k);
        }
        template <class NodeType>
        const NodeType *bst_find_kth_r (const NodeType *root, int k) const {
            int leftSize = root->left ? root->left->value.size : 0;
            if (k <= leftSize) {
                return root->left ? bst_find_kth_r (root->left, k) : NULL;
            } else if (k <= leftSize + root->value.count) {
                return root;
            } else if (root->right) {
                return bst_find_kth_r (root->right, k - leftSize - root->value.count);
            } else {
                return NULL;
            }
        }
    };
}

template <class NodeType>
const NodeType *bst_find_kth (const NodeType *root, int k) {
    return kthFinder<typename NodeType::has_size_tag>()(root, k);
}

template <class NodeType>
int bst_get_rank (const NodeType *node, const typename NodeType::key_type &value) {
    if (!node) {
        return 0;
    } else if (value < node->value.value) {
        return node->left ? bst_get_rank (node->left, value) : 0;
    } else if (value == node->value.value && node->value.count) {
        return node->left ? node->left->value.size + 1 : 1;
    } else {
        return bst_get_rank (node->right, value) + (node->left ? node->left->value.size : 0) + node->value.count;
    }
}

template <class NodeType>
const NodeType *bst_get_next (const NodeType *root, const typename NodeType::key_type &value) {
    if (root->value.value <= value) {
        return root->right ? bst_get_next (root->right, value) : NULL;
    } else {
        const NodeType *p = root->left ? bst_get_next (root->left, value) : NULL;
        return p ? p : (root->value.count ? root : (root->right ? bst_get_next(root->right, value): NULL));
    }
}

template <class NodeType>
const NodeType *bst_get_prev (const NodeType *root, const typename NodeType::key_type &value) {
    if (root->value.value >= value) {
        return root->left ? bst_get_prev (root->left, value) : NULL;
    } else {
        const NodeType *p = root->right ? bst_get_prev (root->right, value) : NULL;
        return p ? p : (root->value.count ? root : (root->left ? bst_get_prev(root->left, value) : NULL));
    }
}

template <class NodeType>
const NodeType *bst_find_min (const NodeType *root) {
    return bst_find_kth (root, 1);
}

template <class NodeType>
const NodeType *bst_find_max (const NodeType *root) {
    return bst_find_kth (root, root->value.size);
}

template <class NodeType>
void tree_print (const NodeType *root) {
    BinaryTreeDebugger debugger;
    debugger.print_ascii_tree (root);    
}

#endif // __BINARY_TREE_FUNCS_H__
