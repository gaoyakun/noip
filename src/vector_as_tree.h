/** tree structure implementation by vector */
#ifndef __VECTOR_AS_TREE__
#define __VECTOR_AS_TREE__

#include <vector>

template <class T>
class VectorAsBinaryTree {
public:
    enum {
        ROOT_NODE = 0,
        INVALID_NODE = -1
    };
    typedef T value_type;
protected:
    struct Node {
        T value;
        int parent;
        int left;
        int right;
        Node (const T &val, int root)
        : value(val)
        , parent(root)
        , left(INVALID_NODE)
        , right(INVALID_NODE) {
        }
    };
    std::vector<Node> _tree;
    std::vector<int> _slots;
public:
    VectorAsBinaryTree () {
    }
    VectorAsBinaryTree (const T &value) {
        _tree.push_back (Node(value, INVALID_NODE));
    }
    void setRoot (const T &value) {
        clear ();
        _tree.push_back (Node(value, INVALID_NODE));
    }
    int addLeft (int root, const T &value) {
        if (_tree[root].left != INVALID_NODE) {
            return INVALID_NODE;
        }
        int result;
        if (!_slots.empty()) {
            result = _slots.back();
            _tree[result].value = value;
            _tree[result].parent = root;
            _tree[result].left = INVALID_NODE;
            _tree[result].right = INVALID_NODE;
            _slots.pop_back();
        } else {
            result = _tree.size();
            _tree.push_back (Node(value, root));
        }
        _tree[root].left = result;
        return result;
    }
    int addRight (int root, const T &value) {
        if (_tree[root].right != INVALID_NODE) {
            return INVALID_NODE;
        }
        int result;
        if (!_slots.empty()) {
            result = _slots.back();
            _tree[result].value = value;
            _tree[result].parent = root;
            _tree[result].left = INVALID_NODE;
            _tree[result].right = INVALID_NODE;
            _slots.pop_back();
        } else {
            result = _tree.size();
            _tree.push_back (Node(value, root));
        }
        _tree[root].right = result;
        return result;
    }
    void removeLeft (int root) {
        int left = _tree[root].left;
        if (left != INVALID_NODE) {
            removeLeft (left);
            removeRight (left);
            _tree[root].left = INVALID_NODE;
            _slots.push_back (left);
        }
    }
    void removeRight (int root) {
        int right = _tree[root].right;
        if (right != INVALID_NODE) {
            removeLeft (right);
            removeRight (right);
            _tree[root].right = INVALID_NODE;
            _slots.push_back (right);
        }
    }
    int getParent (int node) const {
        return _tree[node].parent;
    }
    int getLeft (int root) const {
        return _tree[root].left;
    }
    int getRight (int root) const {
        return _tree[root].right;
    }
    const T &value (int node) const {
        return _tree[node].value;
    }
    T &value (int node) {
        return _tree[node].value;
    }
    int size () const {
        return _tree.size() - _slots.size();
    }
    void clear () {
        _tree.clear ();
        _slots.clear ();
    }
    template <class Pred>
    void preorderIterate (int node, const Pred &pred) {
        pred (value(node));
        int left = getLeft (node);
        if (left != INVALID_NODE) {
            preorderIterate (left, pred);
        }
        int right = getRight (node);
        if (right != INVALID_NODE) {
            preorderIterate (right, pred);
        }
    }
    template <class Pred>
    void inorderIterate (int node, const Pred &pred) {
        int left = getLeft (node);
        if (left != INVALID_NODE) {
            inorderIterate (left, pred);
        }
        pred (value(node));
        int right = getRight (node);
        if (right != INVALID_NODE) {
            inorderIterate (right, pred);
        }
    }
    template <class Pred>
    void postorderIterate (int node, const Pred &pred) {
        int left = getLeft (node);
        if (left != INVALID_NODE) {
            postorderIterate (left, pred);
        }
        int right = getRight (node);
        if (right != INVALID_NODE) {
            postorderIterate (right, pred);
        }
        pred (value(node));
    }
};

#endif // #define __VECTOR_AS_TREE__
