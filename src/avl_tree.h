/** Implementation of AVL-Tree */
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <functional>
#include <utility>
#include "binary_tree.h"

template <class T>
struct AVLNode {
    T value;
    int balanceFactor;
    unsigned count;
    AVLNode () 
    : value()
    , balanceFactor(0)
    , count(1) {
    }
    explicit AVLNode (const T &val)
    : value(val)
    , balanceFactor(0)
    , count(1) {
    }
    AVLNode (const T &val, unsigned c)
    : value(val)
    , balanceFactor(0)
    , count(c) {
    }
};


template <class T, class Comp=std::less<T> > 
class AVLTree: public BinaryTree<AVLNode<T> > {
public:
    typedef BinaryTree<AVLNode<T> > base_type;
    typedef typename base_type::value_type value_type;
    typedef typename base_type::node_type node_type;
public:
    void add (const T &val) {
        if (!this->getRoot()) {
            this->setRoot (value_type(val));
        } else {
            node_type *rotateNode = NULL;
            add_r (this->getRoot(), val, rotateNode);
            if (rotateNode) {
                int bf = rotateNode->value.balanceFactor;
                if (bf == 2) {
                    maintainLeft(rotateNode);
                } else {
                    maintainRight(rotateNode);
                }
            }
        }
    }
    int find (const T &val) {
        return this->getRoot() ? find_r (this->getRoot(), val) : 0;
    }
private:
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
    int add_r (node_type *node, const T &val, node_type *&rotateNode) {
        const T &curVal = node->value.value;
        if (node->balanceFactor) {
            rotateNode = bf;
        }
        int d = 0;
        if (Comp()(curVal, val)) {
            if (node->right) {
                d = -add_r (node->right, val, rotateNode);
            } else {
                node->right = new node_type (value_type(val), node);
                d = -1;
            }
        } else if (Comp()(val, curVal)) {
            if (node->left) {
                d = add_r (node->left, val, rotateNode);
            } else {
                node->left = new node_type (value_type(val), node);
                d = 1;
            }
        } else {
            node->value.count++;
        }
        node->balanceFactor += d;
        return node->balanceFactor && node != rotateNode ? 1 : 0;
    }
    void maintainLeft (node_type *node) {
        if (node->left->value.balanceFactor < 0) {
            rotateLeft (node->right);
        }
        rotateRight (node);
    }
    void maintainRight (node_type *node) {
        if (node->right->value.balanceFactor > 0) {
            rotateRight (node->left);
        }
        rotateLeft (node);
    }
    void rotateLeft (node_type *node) {

    }
    void rotateRight (node_type *node) {
        int parent = this->getParent(node);
        if (parent != INVALID_NODE) {
            if (this->getLeft(parent) == node) {
                this->setLeft (parent, this->getLeft(node));
            } else {
                this->setRight (parent, this->getLeft(node));
            }
        }
        int right = this->getRight(this->getLeft(node));
        this->setRight(this->getLeft(node), node);
        this->setLeft(node, right);
    }
};

#endif // __AVL_TREE_H__
