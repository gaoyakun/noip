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

template <class T, class P=DefaultSerialize<T> >
class BinaryTree {
public:
    typedef T value_type;
    typedef struct Node {
        value_type value;
        Node *parent;
        Node *left;
        Node *right;
        Node (const value_type &val, Node *p = NULL)
        : value(val)
        , parent(p)
        , left(NULL)
        , right(NULL) {
        }
        std::string toString () const {
            std::ostringstream s;
            P() (s, value);
            return s.str();
        }
    } node_type;
protected:
    node_type *_root;
private:
    BinaryTree (const BinaryTree&);
    void operator = (const BinaryTree&);
public:
    BinaryTree () {
        _root = NULL;
    }
    BinaryTree (const value_type &value) {
        _root = new Node (value);
    }
    virtual ~BinaryTree () {
        clear ();
    }
    node_type *getRoot () const {
        return this->_root;
    }
    void setRoot (const value_type &value) {
        clear ();
        _root = new Node (value);
    }
	void setLeft(node_type* node, node_type* child) const {
		node->left = child;
		if (child) {
			child->parent = node;
		}
	}
	void setRight(node_type* node, node_type* child) const {
		node->right = child;
		if (child) {
			child->parent = node;
		}
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
        if (_root) {
            deleteLeft (_root);
            deleteRight (_root);
            delete _root;
            _root = NULL;
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
