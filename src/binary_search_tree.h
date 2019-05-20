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

template <class T>
struct KeyType<BSTNode<T> > {
    typedef T key_type;
};

template <class T, class Comp=std::less<T> > 
class BinarySearchTree: public BinaryTree<BSTNode<T>, BSTSerialize<T> > {
public:
    typedef BinaryTree<BSTNode<T>, BSTSerialize<T> > base_type;
    typedef typename base_type::value_type value_type;
    typedef T key_type;
    typedef typename base_type::node_type node_type;
public:
    void add (const key_type &val) {
        if (!this->root) {
            this->root = new node_type(value_type(val));
        } else {
            add_r (this->root, val);
        }
    }
    void remove (const key_type &val) {
        if (this->root) {
            this->root = remove_r (this->root, val);
        }
    }
    node_type *find (const key_type &val) const {
        if (!this->root) {
            return NULL;
        }
        return find_r (this->root, val);
    }
private:
    node_type *find_r (node_type *node, const key_type &val) const {
        const key_type &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            return node->right ? find_r (node->right, val) : NULL;
        } else if (Comp()(val, curVal)) {
            return node->left ? find_r (node->left, val) : NULL;
        } else {
            return node;
        }
    }
    void add_r (node_type *node, const key_type &val) {
        const key_type &curVal = node->value.value;
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
    node_type *remove_r (node_type *node, const key_type &val) {
        const key_type &curVal = node->value.value;
        if (Comp()(curVal, val)) {
            if (node->right) {
                node->right = remove_r (node->right, val);
            }
        } else if (Comp()(val, curVal)) {
            if (node->left) {
                node->left = remove_r (node->left, val);
            }
        } else {
            node->value.count--;
            if (node->value.count == 0) {
                if (node->left) {
                    node_type *p = node->left;
                    node_type *t = p->right;
                    while (t && t->right) {
                        p = t;
                        t = t->right;
                    }
                    if (t) {
                        p->right = t->left;
                        t->left = node->left;
                        delete node;
                        return t;
                    } else {
                        delete node;
                        return p;
                    }
                } else if (node->right) {
                    delete node;
                    return node->right;
                } else {
                    delete node;
                    return NULL;
                }
            }
        }
    }
};

#endif // __BINARY_SEARCH_TREE_H__
