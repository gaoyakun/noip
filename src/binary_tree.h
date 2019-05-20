#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <cstddef>
#include <functional>
#include <utility>
#include <sstream>

template <class T>
struct DefaultSerialize {
    void operator () (std::ostringstream &s, const T &t) {
        s << t;
    }
};

template <class T>
struct KeyType {
    typedef T key_type;
};

template <class T, class P=DefaultSerialize<T> >
class BinaryTree {
public:
    typedef T value_type;
    typedef T key_type;
    typedef struct Node {
        typedef typename KeyType<value_type>::key_type key_type;
        value_type value;
        Node *left;
        Node *right;
        Node (const value_type &val, Node *p = NULL)
        : value(val)
        , left(NULL)
        , right(NULL) {
        }
        std::string toString () const {
            std::ostringstream s;
            P() (s, value);
            return s.str();
        }
    } node_type;
    node_type *root;
private:
    BinaryTree (const BinaryTree&);
    void operator = (const BinaryTree&);
public:
    BinaryTree () {
        root = NULL;
    }
    virtual ~BinaryTree () {
        clear ();
    }
    void deleteLeft (node_type *node) const {
        if (node && node->left) {
            deleteLeft (node->left);
            deleteRight (node->left);
            delete node->left;
            node->left = NULL;
        }
    }
    void deleteRight (node_type *node) const {
        if (node && node->right) {
            deleteLeft (node->right);
            deleteRight (node->right);
            delete node->right;
            node->right = NULL;
        }
    }
    void clear () {
        if (root) {
            deleteLeft (root);
            deleteRight (root);
            delete root;
            root = NULL;
        }
    }
    template <class Pred>
    void preorderIterate (node_type *node, const Pred &pred) const {
        pred (node->value);
        if (node->left) {
            preorderIterate (node->left, pred);
        }
        if (node->right) {
            preorderIterate (node->right, pred);
        }
    }
    template <class Pred>
    void inorderIterate (node_type *node, const Pred &pred) const {
        if (node->left) {
            inorderIterate (node->left, pred);
        }
        pred (node->value);
        if (node->right) {
            inorderIterate (node->right, pred);
        }
    }
    template <class Pred>
    void postorderIterate (node_type *node, const Pred &pred) const {
        if (node->left) {
            postorderIterate (node->left, pred);
        }
        if (node->right) {
            postorderIterate (node->right, pred);
        }
        pred (node->value);
    }
};

#endif // __BINARY_TREE_H__
