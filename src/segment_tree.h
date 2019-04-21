#ifndef __SEGMENTTREE__
#define __SEGMENTTREE__

#include <vector>
using std::vector;
using std::plus;

template <class T>
struct SegmentTreeTraits_Sum {
    T combine (const T &a, const T &b) const {
        return a + b;
    }
    T combineLeft (const T &a) const {
        return a;
    }
    T combineRight (const T &a) const {
        return a;
    }
    T update (const T &a, const T &delta, size_t num) const {
        return a + delta * num;
    }
};

template <class T>
struct SegmentTreeTraits_Max {
    T combine (const T &a, const T &b) const {
        return a > b ? a : b;
    }
    T combineLeft (const T &a) const {
        return a;
    }
    T combineRight (const T &a) const {
        return a;
    }
    T update (const T &a, const T &delta, size_t num) const {
        return a + delta;
    }
};

template <class T>
struct SegmentTreeTraits_Min {
    T combine (const T &a, const T &b) const {
        return a < b ? a : b;
    }
    T combineLeft (const T &a) const {
        return a;
    }
    T combineRight (const T &a) const {
        return a;
    }
    T update (const T &a, const T &delta, size_t num) const {
        return a + delta;
    }
};

template <class T, class Traits = SegmentTreeTraits_Sum<T> >
class SegmentTree {
    mutable vector<T> C;
    mutable vector<T> f;
    Traits traits;
public:
    void init (size_t size) {
        C.resize (size * 4, 0);
        f.resize (size * 4, 0);
    }
    size_t count () const {
        return C.size() / 4;
    }
    void singleAdd (size_t pos, T d) {
        rangeAdd (pos, pos, d);
    }
    void rangeAdd (size_t posStart, size_t posEnd, T d) {
        rangeAdd_r (1, 1, C.size()/4, posStart, posEnd, d);
    }
    T singleQuery (size_t pos) const {
        return rangeQuery (pos, pos);
    }
    T rangeQuery (size_t posStart, size_t posEnd) const {
        return rangeQuery_r (1, 1, C.size()/4, posStart, posEnd);
    }
private:
    void rangeAdd_r (size_t node, size_t l, size_t r, size_t L, size_t R, T d) {
        if (L <= l && R >= r) {
            C[node] = traits.update(C[node], d, r - l + 1);
            f[node] += d;
        } else {
            size_t mid = (l + r) / 2;
            if (f[node]) {
                C[node*2] = traits.update(C[node*2], f[node], mid - l + 1);
                f[node*2] += f[node];
                C[node*2+1] = traits.update(C[node*2+1], f[node], r - mid);
                f[node*2+1] += f[node];
                f[node] = 0;
            }
            if (L <= mid) {
                rangeAdd_r (node*2, l, mid, L, R, d);
            }
            if (R > mid) {
                rangeAdd_r (node*2+1, mid+1, r, L, R, d);
            }
            C[node] = traits.combine(C[node*2], C[node*2+1]);
        }
    }
    T rangeQuery_r (size_t node, size_t l, size_t r, size_t L, size_t R) const {
        if (L <= l && R >= r) {
            return C[node];
        } else {
            size_t mid = (l + r)/2;
            if (f[node]) {
                C[node*2] = traits.update(C[node*2], f[node], mid - l + 1);
                f[node*2] += f[node];
                C[node*2+1] = traits.update(C[node*2+1], f[node], r - mid);
                f[node*2+1] += f[node];
                f[node] = 0;
            }
            T left = 0, right = 0;
            bool hasLeft = false, hasRight = false;
            if (L <= mid) {
                left = rangeQuery_r (node*2, l, mid, L, R);
                hasLeft = true;
            }
            if (R > mid) {
                right = rangeQuery_r (node*2+1, mid+1, r, L, R);
                hasRight = true;
            }
            if (hasLeft && hasRight) {
                return traits.combine(left, right);
            } else if (hasLeft) {
                return traits.combineLeft (left);
            } else {
                return traits.combineRight (right);
            }
        }
    }
};

#endif //__SEGMENTTREE__
