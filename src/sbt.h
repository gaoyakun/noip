/** Implementation of Size-Balanced-Tree */
#ifndef __SBT_H__
#define __SBT_H__

#include <functional>
#include <utility>
#include "vector_as_tree.h"

template <class T, class Comp = std::less<T> > 
class SBT: public VectorAsBinaryTree<std::pair<T, std::pair<int,int> > > {
public:
    typedef VectorAsBinaryTree<std::pair<T, std::pair<int, int> > > base_type;
    typedef typename base_type::value_type value_type;
public:
    void add (const T &val) {
        if (this->size() == 0) {
            this->setRoot (typename base_type::value_type(val, std::make_pair(1,1)));
        } else {
            add_r (base_type::ROOT_NODE, val);
        }
    }
    int find (const T &val) {
        if (this->size() == 0) {
            return 0;
        }
        return find_r (0, val);
    }
private:
    void rotateLeft (int node) {
        int right = _tree[node].right;
        _tree[node].right = _tree[right].left;
        _tree[right].left = node;
        _tree[right].second.second = _tree[node].second.second;
    }
    int find_r (int node, const T &val) const {
        if (Comp()(this->value(node).first, val)) {
            int right = this->getRight(node);
            if (right == base_type::INVALID_NODE) {
                return 0;
            } else {
                return find_r (right, val);
            }
        } else if (Comp()(val, this->value(node).first)) {
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
    void add_r (int node, const T &val) {
        if (Comp()(this->value(node).first, val)) {
            int right = this->getRight(node);
            if (right == base_type::INVALID_NODE) {
                this->addRight (node, value_type(val, 1));
            } else {
                add_r (right, val);
            }
        } else if (Comp()(val, this->value(node).first)) {
            int left = this->getLeft(node);
            if (left == base_type::INVALID_NODE) {
                this->addLeft (node, value_type(val, 1));
            } else {
                add_r (left, val);
            }
        } else {
            this->value(node).second++;
        }
    }
};

#endif // __SBT_H__
