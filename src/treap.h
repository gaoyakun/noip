/** Implementation of Treap */
#ifndef __TREAP_H__
#define __TREAP_H__

#include <functional>
#include <utility>
#include <algorithm>
#include "binary_tree.h"
#include "binary_tree_funcs.h"

template <class T>
struct TreapNode {
    T value;
    int weight;
    int size;
    int count;
    TreapNode () 
    : value()
    , weight(randint())
    , size(1)
    , count(1) {
    }
    explicit TreapNode (const T &val)
    : value(val)
    , weight(randint())
    , size(1)
    , count(1) {
    }
    int randint () const {
        static int seed = 911;
        return seed = int(seed * 48271LL % ((1LL<<31)-1));
    }
};

template <class T>
struct TreapSerialize {
	void operator () (std::ostringstream& s, const TreapNode<T>& t) {
		s << t.value << "(" << t.weight << ")(" << t.size << ")";
	}
};

template <class T>
struct KeyType<TreapNode<T> > {
    typedef T key_type;
    typedef BSTHasSize has_size_tag;
};

template <class T, class Comp=std::less<T> > 
class Treap: public BinaryTree<TreapNode<T>, TreapSerialize<T> > {
public:
    typedef BinaryTree<TreapNode<T>, TreapSerialize<T> > base_type;
    typedef typename base_type::value_type value_type;
    typedef T key_type;
    typedef typename base_type::node_type node_type;
    typedef std::pair<node_type*, node_type*> couple_type;
public:
    Treap (): base_type() {
    }
    Treap (node_type *p): base_type(p) {
    }
    void add (const key_type &val) {
        int k = bst_get_rank (this->root, val);
        couple_type c = splitNode (this->root, k);
        node_type *newNode = new node_type(value_type(val));
        this->root = mergeNode (mergeNode(c.first, newNode), c.second);
    }
    void remove (const key_type &val) {
        int k = bst_get_rank (this->root, val);
        if (k) {
            couple_type x = splitNode (this->root, k-1);
            couple_type y = splitNode (x.second, 1);
            this->root = mergeNode (x.first, y.second);
        }
    }
    node_type *find (const key_type &val) {
        return this->root ? find_r (this->root, val) : NULL;
    }
private:
    couple_type splitNode (node_type *root, int k) {
        if (!root) {
            return couple_type(0, 0);
        } else if (getSize(root->left) >= k) {
            couple_type couple = splitNode (root->left, k);
            root->left = couple.second;
            updateSize (root);
            couple.second = root;
            return couple;
        } else {
            couple_type couple = splitNode (root->right, k-getSize(root->left)-1);
            root->right = couple.first;
            updateSize (root);
            couple.first = root;
            return couple;
        }
    }
    node_type *mergeNode (node_type *left, node_type *right) {
        if (!left) {
            return right;
        } else if (!right) {
            return left;
        } else if (left->value.weight < right->value.weight) {
            left->right = mergeNode (left->right, right);
            updateSize (left);
            return left;
        } else {
            right->left = mergeNode (left, right->left);
            updateSize (right);
            return right;
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
            return node;
        }
    }
};

#endif // __AVL_TREE_H__
