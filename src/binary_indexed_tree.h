#ifndef __BINARY_INDEXED_TREE_H__
#define __BINARY_INDEXED_TREE_H__

#include <vector>

template <class T>
class BinaryIndexedTree {
    std::vector<T> t1;
    std::vector<T> t2;
public:
    BinaryIndexedTree (size_t size = 0) {
        init (size);
    } 
    void init (size_t size) {
        t1.resize (size + 1, 0);
        t2.resize (size + 1, 0);
    }
    size_t count () const {
        return t1.size() - 1;
    }
    void singleAdd (size_t pos, T d) {
        rangeAdd (pos, pos, d);
    }
    void rangeAdd (size_t posStart, size_t posEnd, T d) {
        size_t n = count();
        for (size_t i = posStart; i <= n; i += i & -i) {
            t1[i] += d;
            t2[i] += posStart * d;
        }
        for (size_t i = posEnd+1; i <= n; i += i & -i) {
            t1[i] -= d;
            t2[i] -= (posEnd + 1) * d;
        }
    }
    T sum (size_t n) const {
        T r1 = 0;
        T r2 = 0;
        for (size_t i = n; i > 0; i -= i & -i) {
            r1 += t1[i];
            r2 += t2[i];
        }
        return (n + 1) * r1 - r2;
    }
    T singleQuery (size_t pos) const {
        return rangeQuery (pos, pos);
    }
    T rangeQuery (size_t posStart, size_t posEnd) const {
        return sum (posEnd) - sum (posStart-1);
    }
};

template <class T>
class BinaryIndexedTree2D {
    std::vector<std::vector<T> > t1;
    std::vector<std::vector<T> > t2;
    std::vector<std::vector<T> > t3;
    std::vector<std::vector<T> > t4;
public:
    BinaryIndexedTree2D (size_t rows = 0, size_t cols = 0) {
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

#endif // __BINARY_INDEXED_TREE_H__
