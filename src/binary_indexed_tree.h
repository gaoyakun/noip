#ifndef __BINARYINDEXEDTREE__
#define __BINARYINDEXEDTREE__

#include <vector>
using std::vector;

template <class T>
class BaseBIT {
    vector<T> C;
public:
    BaseBIT (size_t size = 0) {
        init (size);
    }
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
    BIT (size_t size = 0)
    : baseBIT1(size)
    , baseBIT2(size) {
    } 
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

template <class T>
class BIT2D {
    vector<vector<T> > t1;
    vector<vector<T> > t2;
    vector<vector<T> > t3;
    vector<vector<T> > t4;
public:
    BIT2D (size_t rows = 0, size_t cols = 0) {
        init (rows, cols);
    }
    void init (size_t rows, size_t cols) {
        t1.resize (rows + 1);
        t2.resize (rows + 1);
        t3.resize (rows + 1);
        t4.resize (rows + 1);
        for (size_t i = 0; i < rows + 1; i++) {
            t1[i].resize (cols + 1, 0);
            t2[i].resize (cols + 1, 0);
            t3[i].resize (cols + 1, 0);
            t4[i].resize (cols + 1, 0);
        }
    }
    size_t countRows () const {
        return t1.size() - 1;
    }
    size_t countCols () const {
        return t1[0].size() - 1;
    }
    void singleAdd (size_t posRow, size_t posCol, T d) {
        rangeAdd (posRow, posCol, posRow, posCol, d);
    }
    void rangeAdd (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd, T d) {
        _add (posRowStart, posColStart, d);
        _add (posRowStart, posColEnd+1, -d);
        _add (posRowEnd+1, posColStart, -d);
        _add (posRowEnd+1, posColEnd+1, d);
    }
    T sum (size_t posRow, size_t posCol) const {
        T result = 0;
        for (size_t i = posRow; i > 0; i -= i & -i) {
            for (size_t j = posCol; j > 0; j -= j & -j) {
                result += (posRow + 1) * (posCol + 1) * t1[i][j] - (posCol + 1) * t2[i][j] - (posRow + 1) * t3[i][j] + t4[i][j];
            }
        }
        return result;
    }
    T singleQuery (size_t posRow, size_t posCol) const {
        return rangeQuery (posRow, posCol, posRow, posCol);
    }
    T rangeQuery (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd) const {
        return sum (posRowEnd, posColEnd) - sum (posRowStart-1, posColEnd) - sum (posRowEnd, posColStart-1) + sum (posRowStart-1, posColStart-1);
        //return sum (posRowEnd, posColEnd) - sum (posRowEnd, posColStart) - sum (posRowStart, posColEnd) + sum (posRowStart, posColStart);
    }
private:
    void _add (size_t posRow, size_t posCol, T d) {
        size_t rows = countRows();
        size_t cols = countCols();
        for (size_t i = posRow; i <= rows; i += i & -i) {
            for (size_t j = posCol; j <= cols; j+= j & -j) {
                t1[i][j] += d;
                t2[i][j] += posRow * d;
                t3[i][j] += posCol * d;
                t4[i][j] += posRow * posCol * d;
            }
        }
    }
};

#endif // __BINARYINDEXEDTREE__