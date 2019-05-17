/** Implementation of Binary-Search-Tree */
#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <functional>
#include <utility>
#include <sstream>
#include "vector_as_tree.h"

template <class T>
struct BSTNode {
    T value;
    unsigned count;
    BSTNode () 
    : value()
    , count(1) {
    }
    explicit BSTNode (const T &val)
    : value(val)
    , count(1) {
    }
    BSTNode (const T &val, unsigned c)
    : value(val)
    , count(c) {
    }
    std::string toString () const {
        std::ostringstream s;
        s << value << "(" << count << ")";
        return s.str();
    }
};

template <class T>
struct BSTSerialize {
    void operator () (std::ostringstream &s, const BSTNode<T> &t) {
        s << t.value << "(" << t.count << ")";
    }
};

template <class T, class Comp=std::less<T> > 
class BinarySearchTree: public BinaryTree<BSTNode<T>, BSTSerialize<T> > {
public:
    typedef BinaryTree<BSTNode<T>, BSTSerialize<T> > base_type;
    typedef typename base_type::value_type value_type;
    typedef typename base_type::node_type node_type;
public:
    void add (const T &val) {
        if (!this->root) {
            this->root = new node_type(value_type(val));
        } else {
            add_r (this->root, val);
        }
    }
    node_type *find (const T &val) const {
        if (!this->root) {
            return NULL;
        }
        return find_r (this->root, val);
    }
private:
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
    void add_r (node_type *node, const T &val) {
        const T &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            if (node->right) {
                add_r (node->right, val);
            } else {
                node->right = new node_type (value_type(val), node);
            }
        } else if (Comp()(val, curVal)) {
            if (node->left) {
                add_r (node->left, val);
            } else {
                node->left = new node_type (value_type(val), node);
            }
        } else {
            node->value.count++;
        }
    }
};

#endif // __BINARY_SEARCH_TREE_H__
