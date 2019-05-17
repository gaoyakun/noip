/** Implementation of AVL-Tree */
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <functional>
#include <utility>
#include <algorithm>
#include "binary_tree.h"

template <class T>
struct AVLNode {
    T value;
    int height;
    unsigned count;
    AVLNode () 
    : value()
    , height(1)
    , count(1) {
    }
    explicit AVLNode (const T &val)
    : value(val)
    , height(1)
    , count(1) {
    }
    AVLNode (const T &val, unsigned c)
    : value(val)
    , height(1)
    , count(c) {
    }
};

template <class T>
struct AVLSerialize {
	void operator () (std::ostringstream& s, const AVLNode<T>& t) {
		s << t.value << "(" << t.count << ")(" << t.height << ")";
	}
};



template <class T, class Comp=std::less<T> > 
class AVLTree: public BinaryTree<AVLNode<T>, AVLSerialize<T> > {
public:
    typedef BinaryTree<AVLNode<T>, AVLSerialize<T> > base_type;
    typedef typename base_type::value_type value_type;
    typedef typename base_type::node_type node_type;
public:
    void add (const T &val) {
        if (!this->root) {
            this->root = new node_type (value_type(val), NULL);
        } else {
            this->root = add_r (this->root, val);
        }
    }
    node_type *find (const T &val) {
        return this->root ? find_r (this->root, val) : NULL;
    }
private:
	int getHeight(node_type* node) const {
		return node ? node->value.height : 0;
	}
	void updateHeight(node_type *node) const {
		if (node) {
			node->value.height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
		}
	}
    node_type *find_r (node_type *node, const T &val) const {
        const T &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            return node->right ? find_r (node->right, val) : NULL;
        } else if (Comp()(val, curVal)) {
            return node->left ? find_r (node->left, val) : NULL;
        } else {
            return node;
        }
    }
    node_type *add_r (node_type *node, const T &val) {
        const T &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            node->right = node->right ? add_r (node->right, val) : new node_type (value_type(val), node);
        } else if (Comp()(val, curVal)) {
            node->left = node->left ? add_r (node->left, val) : new node_type (value_type(val), node);
        } else {
            node->value.count++;
            return node;
        }
        updateHeight (node);
        int hl = getHeight (node->left);
        int hr = getHeight (node->right);
        if (hr - hl == 2) {
            return maintainRight(node);
        } else if (hl - hr == 2) {
            return maintainLeft(node);
        } else {
            return node;
        }
    }
    node_type *maintainLeft (node_type *node) {
        if (getHeight(node->left->left) < getHeight(node->left->right)) {
            node->left = rotateLeft (node->left);
        }
        return rotateRight (node);
    }
    node_type *maintainRight (node_type *node) {
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
            node->right = rotateRight (node->right);
        }
        return rotateLeft (node);
    }
    node_type *rotateLeft (node_type *node) {
        node_type *x = node->right;
        node_type *t = x->left;
        x->left = node;
        node->right = t;
		updateHeight(node);
		updateHeight(x);
        return x;
    }
    node_type *rotateRight (node_type *node) {
        node_type *x = node->left;
        node_type *t = x->right;
        x->right = node;
        node->left = t;
		updateHeight(node);
		updateHeight(x);
        return x;
    }
};

#endif // __AVL_TREE_H__
