#ifndef __BINARYINDEXEDTREE__
#define __BINARYINDEXEDTREE__

#include <vector>
using std::vector;

template <class T>
class BaseBIT {
    vector<T> C;
public:
    void init (size_t size) {
        C.resize (size + 1, 0);
    }
    size_t count () const {
        return C.size() - 1;
    }
    void singleAdd (size_t pos, T d) {
        size_t count = C.size();
        while (pos <= count) {
            C[pos] += d;
            pos += pos & -pos;
        }
    }
    void rangeAdd (size_t posStart, size_t posEnd, T d) {
        for (size_t i = posStart; i <= posEnd; i++) {
            singleAdd (i, d);
        }
    }
    T sum (size_t n) const {
        T result = 0;
        while (n) {
            result += C[n];
            n -= n & -n;
        }
        return result;
    }
    T singleQuery (size_t pos) const {
        return sum(pos) - sum(pos-1);
    }
    T rangeQuery (size_t posStart, size_t posEnd) const {
        return sum(posEnd) - sum(posStart-1);
    }
};

template <class T>
class BIT {
    BaseBIT<T> baseBIT1;
    BaseBIT<T> baseBIT2;
public:
    void init (size_t size) {
        baseBIT1.init(size);
        baseBIT2.init(size);
    }
    size_t count () const {
        return baseBIT1.count();
    }
    void singleAdd (size_t pos, T d) {
        rangeAdd (pos, pos, d);
    }
    void rangeAdd (size_t posStart, size_t posEnd, T d) {
        baseBIT1.singleAdd (posStart, d);
        baseBIT1.singleAdd (posEnd+1, -d);
        baseBIT2.singleAdd (posStart, d * posStart);
        baseBIT2.singleAdd (posEnd+1, -d * (posEnd+1));
    }
    T sum (size_t n) const {
        return (n + 1) * baseBIT1.sum(n) - baseBIT2.sum(n);
    }
    T singleQuery (size_t pos) const {
        return rangeQuery (pos, pos);
    }
    T rangeQuery (size_t posStart, size_t posEnd) const {
        return sum (posEnd) - sum (posStart-1);
    }
};

#endif // __BINARYINDEXEDTREE__