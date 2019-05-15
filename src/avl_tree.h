/** Implementation of AVL-Tree */
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <functional>
#include <utility>
#include "vector_as_tree.h"

template <class T, class Comp=std::less<T> > 
class AVLTree: public VectorAsBinaryTree<T, std::pair<int,int> > {
public:
    typedef VectorAsBinaryTree<T, std::pair<int,int> > base_type;
    typedef typename base_type::value_type value_type;
public:
    void add (const T &val) {
        if (this->size() == 0) {
            this->setRoot (value_type(val, make_pair<int,int>(1,0)));
        } else {
            add_r (base_type::ROOT_NODE, val, this->value(base_type::ROOT_NODE).second.second != 0 ? base_type::ROOT_NODE : base_type::INVALID_NODE);
        }
    }
    int find (const T &val) {
        if (this->size() == 0) {
            return 0;
        }
        return find_r (0, val);
    }
private:
    int find_r (int node, const T &val) const {
        const T &curVal = this->value(node).first;
        if (Comp()(curVal, val)) {
            int right = this->getRight(node);
            if (right == base_type::INVALID_NODE) {
                return 0;
            } else {
                return find_r (right, val);
            }
        } else if (Comp()(val, curVal)) {
            int left = this->getLeft(node);
            if (left == base_type::INVALID_NODE) {
                return 0;
            } else {
                return find_r (left, val);
            }
        } else {
            return this->value(node).second;
        }
    }
    int add_r (int node, const T &val, int p) {
        const T &curVal = this->value(node).first;
        if (Comp()(curVal, val)) {
            int right = this->getRight(node);
            if (right == base_type::INVALID_NODE) {
                this->addRight (node, value_type(val, 1));

            } else {
                add_r (right, val, curVal.second.second != 0 ? node : p);
            }
        } else if (Comp()(val, curVal)) {
            int left = this->getLeft(node);
            if (left == base_type::INVALID_NODE) {
                this->addLeft (node, value_type(val, 1));
            } else {
                add_r (left, val, curVal.second.second != 0 ? node : p);
            }
        } else {
            this->value(node).second++;
        }
    }
};

#endif // __AVL_TREE_H__
