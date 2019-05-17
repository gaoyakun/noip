/** Implementation of AVL-Tree */
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <functional>
#include <utility>
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
        if (!this->getRoot()) {
            this->setRoot (value_type(val));
        } else {
            add_r (this->getRoot(), val);
        }
    }
    int find (const T &val) {
        return this->getRoot() ? find_r (this->getRoot(), val) : 0;
    }
private:
	int getHeight(node_type* node) const {
		return node ? node->value.height : 0;
	}
	void updateHeight(node_type *node) const {
		if (node) {
			node->value.height = max2(getHeight(node->left), getHeight(node->right)) + 1;
		}
	}
	int max2(int a, int b) const {
		return a > b ? a : b;
	}
    int find_r (node_type *node, const T &val) const {
        const T &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            return node->right ? find_r (node->right, val) : 0;
        } else if (Comp()(val, curVal)) {
            return node->left ? find_r (node->left, val) : 0;
        } else {
            return node->value.count;
        }
    }
    void add_r (node_type *node, const T &val) {
        const T &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            if (node->right) {
                add_r (node->right, val);
				if (getHeight(node->right) - getHeight(node->left) == 2) {
					maintainRight(node);
				}
            } else {
                node->right = new node_type (value_type(val), node);
				if (node->value.height < 2) {
					node->value.height = 2;
				}
            }
        } else if (Comp()(val, curVal)) {
            if (node->left) {
                add_r (node->left, val);
				if (getHeight(node->left) - getHeight(node->right) == 2) {
					maintainLeft(node);
				}
            } else {
                node->left = new node_type (value_type(val), node);
				if (node->value.height < 2) {
					node->value.height = 2;
				}
			}
        } else {
            node->value.count++;
        }
    }
    void maintainLeft (node_type *node) {
        if (getHeight(node->left->left) < getHeight(node->left->right)) {
            rotateLeft (node->left);
        }
        rotateRight (node);
    }
    void maintainRight (node_type *node) {
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
            rotateRight (node->right);
        }
        rotateLeft (node);
    }
    void rotateLeft (node_type *node) {
        if (node->parent) {
            if (node->parent->left == node) {
				this->setLeft(node->parent, node->right);
            } else {
				this->setRight(node->parent, node->right);
            }
		} else {
			this->_root = node->right;
			node->right->parent = NULL;
		}
        node_type *tmp = node->right->left;
		this->setLeft(node->right, node);
		this->setRight(node, tmp);
		updateHeight(node);
		updateHeight(node->parent);
		updateHeight(node->parent->parent);
    }
    void rotateRight (node_type *node) {
        if (node->parent) {
            if (node->parent->left == node) {
				this->setLeft(node->parent, node->left);
            } else {
				this->setRight(node->parent, node->left);
            }
		} else {
			this->_root = node->left;
			node->left->parent = NULL;
		}
        node_type *tmp = node->left->right;
		this->setRight(node->left, node);
		this->setLeft(node, tmp);
		updateHeight(node);
		updateHeight(node->parent);
		updateHeight(node->parent->parent);
    }
};

#endif // __AVL_TREE_H__
