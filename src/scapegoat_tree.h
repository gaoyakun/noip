/** Implementation of ScapeGoat-Tree */
#ifndef __SCAPEGOAT_TREE_H__
#define __SCAPEGOAT_TREE_H__

#include <functional>
#include <utility>
#include <algorithm>
#include "binary_tree.h"

template <class T>
struct ScapeGoatNode {
    T value;
    int size;
    int weight;
    int count;
    ScapeGoatNode () 
    : value()
    , size(1)
    , weight(1)
    , count(1) {
    }
    explicit ScapeGoatNode (const T &val)
    : value(val)
    , size(1)
    , weight(1)
    , count(1) {
    }
    ScapeGoatNode (const T &val, unsigned c)
    : value(val)
    , size(1)
    , weight(1)
    , count(c) {
    }
};

template <class T>
struct ScapeGoatSerialize {
	void operator () (std::ostringstream& s, const ScapeGoatNode<T>& t) {
		s << t.value << "(" << t.count << ")(" << t.size << ")";
	}
};

template <class T>
struct KeyType<ScapeGoatNode<T> > {
    typedef T key_type;
    typedef BSTHasSize has_size_tag;
};

template <class T, class Comp=std::less<T>, int K=30> 
class ScapeGoatTree: public BinaryTree<ScapeGoatNode<T>, ScapeGoatSerialize<T> > {
public:
    typedef BinaryTree<ScapeGoatNode<T>, ScapeGoatSerialize<T> > base_type;
    typedef typename base_type::value_type value_type;
    typedef T key_type;
    typedef typename base_type::node_type node_type;
private:
    struct FlattenElement {
        key_type value;
        int count;
        bool operator < (const FlattenElement &other) const {
            return value < other.value;
        }
    };
    int deletedCount;
public:
    ScapeGoatTree () {
        deletedCount = 0;
    }
    void add (const key_type &val) {
        if (!this->root) {
            this->root = new node_type (value_type(val));
        } else {
            this->root = add_r (this->root, val);
        }
    }
    void remove (const key_type &val) {
        if (this->root) {
            int r = remove_r (this->root, val);
            if (r) {
                this->deletedCount++;
                if (check_reduce ()) {
                    this->deletedCount = 0;
                }
            }
        }
    }
    node_type *find (const key_type &val) {
        return this->root ? find_r (this->root, val) : NULL;
    }
private:
    int getWeight(node_type *node) const {
        return node ? node->value.weight : 0;
    }
    void updateWeight (node_type *node) const {
        if (node) {
            node->value.weight = getWeight(node->left) + getWeight(node->right) + 1;
        }
    }
    int getSize(node_type* node) const {
        return node ? node->value.size : 0;
    }
    void updateSize(node_type *node) const {
        if (node) {
            node->value.size = getSize(node->left) + getSize(node->right) + node->value.count;
        }
    }
    node_type *find_r (node_type *node, const key_type &val) const {
        const key_type &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            return node->right ? find_r (node->right, val) : NULL;
        } else if (Comp()(val, curVal)) {
            return node->left ? find_r (node->left, val) : NULL;
        } else {
            return node->value.count ? node : NULL;
        }
    }
    struct FlattenFunc {
        FlattenElement *arr;
        FlattenFunc (FlattenElement *p): arr(p) {
        }
        void operator () (const value_type &val) {
            if (val.count > 0) {
                arr->value = val.value;
                arr->count = val.count;
                arr++;
            }
        }
    };
    unsigned flatten (node_type *node, FlattenElement *array) const {
        FlattenFunc pred(array);
        this->inorderIterate (node, pred);
        return pred.arr - array;
    }
    node_type *build_r (const FlattenElement *inorder, unsigned start, unsigned end) const {
        unsigned mid = (start + end) / 2;
        node_type *root = new node_type (value_type(inorder[mid].value, inorder[mid].count));
        if (mid > start) {
            root->left = build_r (inorder, start, mid-1);
        }
        if (mid < end) {
            root->right = build_r (inorder, mid+1, end);
        }
        updateSize (root);
        updateWeight (root);
        return root;
    }
    bool check_reduce () {
        if (this->root) {
            int sz = getWeight(this->root);
            if (sz > K && this->deletedCount * 3 > sz) {
                this->root = rebuild (this->root, sz);
                return true;
            }
        }
        return false;
    }
    node_type *fix_balance (node_type *node) {
        int sz = getSize (node);
        if (sz >= K) {
            int lsz = getSize (node->left);
            int rsz = getSize (node->right);
            if (lsz * 3 > sz * 2 || rsz * 3 > sz * 2) {
                return rebuild (node, sz);
            }
        }
        return node;
    }
    node_type *rebuild (node_type *node, int sz) {
        FlattenElement *arr = new FlattenElement[sz];
        unsigned count = flatten (node, arr);
        node_type *newNode = count  ? build_r (arr, 0, count-1) : NULL;
        delete [] arr;
        delete node;
        return newNode;
    }
    node_type *add_r (node_type *node, const key_type &val) {
        const key_type &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            node->right = node->right ? add_r (node->right, val) : new node_type (value_type(val));
        } else if (Comp()(val, curVal)) {
            node->left = node->left ? add_r (node->left, val) : new node_type (value_type(val));
        } else {
            node->value.count++;
        }
        updateSize (node);
        updateWeight (node);
        return fix_balance (node);
    }
    int remove_r (node_type *node, const key_type &val) {
        const key_type &curVal = node->value.value;
        int result = 0;
        if (Comp()(curVal, val)) {
            if (node->right) {
                result = remove_r (node->right, val);
            }
        } else if (Comp()(val, curVal)) {
            if (node->left) {
                result = remove_r (node->left, val);
            }
        } else if (node->value.count > 0) {
            node->value.count--;
            result = 1;
        }
        if (result) {
            updateSize (node);
        }
        return result;
    }
};

#endif // __SCAPEGOAT_TREE_H__
