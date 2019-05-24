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
        int k = this->root ? getRank (val) : 0;
        couple_type c = splitNode (this->root, k);
        node_type *newNode = new node_type(value_type(val));
        this->root = mergeNode (mergeNode(c.first, newNode), c.second);
    }
    void remove (const key_type &val) {
        int k = getRank (val);
        if (k) {
            couple_type x = splitNode (this->root, k-1);
            couple_type y = splitNode (x.second, 1);
            this->root = mergeNode (x.first, y.second);
        }
    }
    node_type *find (const key_type &val) {
        return this->root ? find_r (this->root, val) : NULL;
    }
    node_type *findKth (int k) const {
#if 1
        return bst_find_kth (this->root, k);
#else
        couple_type x = splitNode (this->root, k-1);
        couple_type y = splitNode (x.second, 1);
        node_type *result = y.first;
        this->root = mergeNode (mergeNode(x.first, result), y.second);
        return result;
#endif
    }
    int getRank (const key_type &val) {
        return bst_get_rank (this->root, val);
    }
    Treap *split (int k) {
        if (!this->root) {
            return 0;
        } else {
            couple_type couple = splitNode (this->root, k);
            if (couple) {
                this->root = couple.second;
                return new Treap (couple.first);
            } else {
                return 0;
            }
        }
    }
    void merge (Treap *other) {
        if (!this->root) {
            this->root = other->root;
        } else if (other) {
            this->root = mergeNode (this->root, other->root);
            other->root = 0;
            delete other;
        }
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
    node_type *fix_balance (node_type *node) {
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
        return fix_balance (node);
    }
    node_type *remove_maxnode_r (node_type *node) {
        if (!node->left) {
            return node;
        } else {
            node_type *t = remove_maxnode_r (node->left);
            node->left = t->right;
            updateSize (node);
            t->right = fix_balance (node);
            return t;
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
                node_type *p;
                if (!node->right) {
                    p = node->left;
                } else {
                    p = remove_maxnode_r (node->right);
                    p->left = node->left;
                }
                delete node;
                node = p;
            }
        }
        if (node) {
            updateSize (node);
            return fix_balance (node);
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
        updateSize(node);
		updateHeight(x);
        updateSize(x);
        return x;
    }
    node_type *rotateRight (node_type *node) {
        node_type *x = node->left;
        node_type *t = x->right;
        x->right = node;
        node->left = t;
		updateHeight(node);
        updateSize(node);
		updateHeight(x);
        updateSize(x);
        return x;
    }
};

#endif // __AVL_TREE_H__
