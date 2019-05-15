#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "segment_tree.h"
#include "binary_indexed_tree.h"

//#define VERBOSE
#include "test_common.h"

using std::cin;
using std::cout;
using std::flush;
using std::endl;
using std::string;
using std::vector;
using std::swap;

#define TEST_1D
#define TEST_2D

//////////////////////////////////////////////////////////////////////////
// start 1d array test
//////////////////////////////////////////////////////////////////////////

class Test {
public:
    virtual void init (size_t size) = 0;
    virtual size_t count () const = 0;
    virtual void singleAdd (size_t pos, int d) = 0;
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) = 0;
    virtual int sum (size_t n) const = 0;
    virtual int singleQuery (size_t pos) const = 0;
    virtual int rangeQuery (size_t posStart, size_t posEnd) const = 0;
};

class BruteForceTest: public Test {
    vector<int> A;
public:
    virtual void init (size_t size) {
        A.resize (size, 0);
    }
    virtual size_t count () const {
        return A.size();
    }
    virtual void singleAdd (size_t pos, int d) {
        A[pos-1] += d;
    }
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) {
        for (size_t i = posStart-1; i < posEnd; i++) {
            A[i] += d;
        }
    }
    virtual int sum (size_t n) const {
        return rangeQuery (1, n);
    }
    virtual int singleQuery (size_t pos) const {
        return A[pos-1];
    }
    virtual int rangeQuery (size_t posStart, size_t posEnd) const {
        int result = 0;
        for (size_t i = posStart-1; i < posEnd; i++) {
            result += A[i];
        }
        return result;
    }
};

class BITTest: public Test {
    BinaryIndexedTree<int> bit;
public:
    virtual void init (size_t size) {
        bit.init(size);
    }
    virtual size_t count () const {
        return bit.count();
    }
    virtual void singleAdd (size_t pos, int d) {
        bit.singleAdd (pos, d);
    }
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) {
        bit.rangeAdd (posStart, posEnd, d);
    }
    virtual int sum (size_t n) const {
        return bit.sum (n);
    }
    virtual int singleQuery (size_t pos) const {
        return bit.singleQuery (pos);
    }
    virtual int rangeQuery (size_t posStart, size_t posEnd) const {
        return bit.rangeQuery (posStart, posEnd);
    }
};

class SegmentTreeTest: public Test {
    SegmentTree<int> st;
public:
    virtual void init (size_t size) {
        st.init (size);
    }
    virtual size_t count () const {
        return st.count ();
    }
    virtual void singleAdd (size_t pos, int d) {
        return st.singleAdd (pos, d);
    }
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) {
        st.rangeAdd (posStart, posEnd, d);
    }
    virtual int sum (size_t n) const {
        return rangeQuery (1, n);
    }
    virtual int singleQuery (size_t pos) const {
        return st.singleQuery (pos);
    }
    virtual int rangeQuery (size_t posStart, size_t posEnd) const {
        return st.rangeQuery (posStart, posEnd);
    }
};

//////////////////////////////////////////////////////////////////////////
// start 2d array test
//////////////////////////////////////////////////////////////////////////

class Test2D {
public:
    virtual void init (size_t rows, size_t cols) = 0;
    virtual size_t countRows () const = 0;
    virtual size_t countCols () const = 0;
    virtual void singleAdd (size_t posRow, size_t posCol, int d) = 0;
    virtual void rangeAdd (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd, int d) = 0;
    virtual int sum (size_t rows, size_t cols) const = 0;
    virtual int singleQuery (size_t posRow, size_t posCol) const = 0;
    virtual int rangeQuery (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd) const = 0;
};

class BruteForceTest2D: public Test2D {
    vector<vector<int> > A;
public:
    BruteForceTest2D (size_t rows=0, size_t cols=0) {
        init (rows, cols);
    }
    virtual void init (size_t rows, size_t cols) {
        A.resize (rows);
        for (size_t i = 0; i < A.size(); i++) {
            A[i].resize (cols, 0);
        }
    }
    virtual size_t countRows () const {
        return A.size();
    }
    virtual size_t countCols () const {
        return A[0].size();
    }
    virtual void singleAdd (size_t posRow, size_t posCol, int d) {
        A[posRow-1][posCol-1] += d;
    }
    virtual void rangeAdd (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd, int d) {
        for (size_t i = posRowStart-1; i < posRowEnd; i++) {
            for (size_t j = posColStart-1; j < posColEnd; j++) {
                A[i][j] += d;
            }
        }
    }
    virtual int sum (size_t rows, size_t cols) const {
        return rangeQuery (1, 1, rows, cols);
    }
    virtual int singleQuery (size_t posRow, size_t posCol) const {
        return A[posRow-1][posCol-1];
    }
    virtual int rangeQuery (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd) const {
        int result = 0;
        for (size_t i = posRowStart-1; i < posRowEnd; i++) {
            for (size_t j = posColStart-1; j < posColEnd; j++) {
                result += A[i][j];
            }
        }
        return result;
    }
};

class BITTest2D: public Test2D {
    BinaryIndexedTree2D<int> bit;
public:
    BITTest2D (size_t rows=0, size_t cols=0): bit(rows, cols) {
    }
    virtual void init (size_t rows, size_t cols) {
        bit.init (rows, cols);
    }
    virtual size_t countRows () const {
        return bit.countRows();
    }
    virtual size_t countCols () const {
        return bit.countCols();
    }
    virtual void singleAdd (size_t posRow, size_t posCol, int d) {
        bit.singleAdd (posRow, posCol, d);
    }
    virtual void rangeAdd (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd, int d) {
        bit.rangeAdd (posRowStart, posColStart, posRowEnd, posColEnd, d);
    }
    virtual int sum (size_t rows, size_t cols) const {
        return bit.rangeQuery (1, 1, rows, cols);
    }
    virtual int singleQuery (size_t posRow, size_t posCol) const {
        return bit.singleQuery (posRow, posCol);
    }
    virtual int rangeQuery (size_t posRowStart, size_t posColStart, size_t posRowEnd, size_t posColEnd) const {
        return bit.rangeQuery (posRowStart, posColStart, posRowEnd, posColEnd);
    }
};

inline bool randTest (const vector<int> &cases, size_t &caseStart, Test *tests[], size_t numTests) {
    int t = cases[caseStart++];
    switch (t) {
    case 1:
        {
            size_t pos = cases[caseStart++];
            int d = cases[caseStart++];
            for (size_t i = 0; i < numTests; i++) {
                tests[i]->singleAdd (pos, d);
            }
            break;
        }
    case 2:
        {
            size_t posStart = cases[caseStart++];
            size_t posEnd = cases[caseStart++];     
            int d = cases[caseStart++];
            for (size_t i = 0; i < numTests; i++) {
                tests[i]->rangeAdd (posStart, posEnd, d);
            }
            break;
        }
    case 3:
        {
            size_t n = cases[caseStart++];
            int k = tests[0]->sum (n);
            for (size_t i = 1; i < numTests; i++) {
                if (k != tests[i]->sum (n)) {
                    return false;
                }
            }
            break;
        }
    case 4:
        {
            size_t pos = cases[caseStart++];
            int k = tests[0]->singleQuery (pos);
            for (size_t i = 1; i < numTests; i++) {
                if (k != tests[i]->singleQuery (pos)) {
                    return false;
                }
            }
            break;
        }
    case 5:
        {
            size_t posStart = cases[caseStart++];
            size_t posEnd = cases[caseStart++];
            int k = tests[0]->rangeQuery (posStart, posEnd);
            for (size_t i = 1; i < numTests; i++) {
                if (k != tests[i]->rangeQuery (posStart, posEnd)) {
                    return false;
                }
            }
            break;
        }
    }
    return true;
}

inline bool randTest2D (const vector<int> &cases, size_t &caseStart, Test2D *tests[], size_t numTests) {
    int t = cases[caseStart++];
    switch (t) {
    case 1:
        {
            size_t posRow = cases[caseStart++];
            size_t posCol = cases[caseStart++];
            int d = cases[caseStart++];
            DEBUG_LOG ("\tsingleAdd (%ul, %ul, %d)\n", posRow, posCol, d);
            for (size_t i = 0; i < numTests; i++) {
                tests[i]->singleAdd (posRow, posCol, d);
            }
            break;
        }
    case 2:
        {
            size_t posRowStart = cases[caseStart++];
            size_t posColStart = cases[caseStart++];
            size_t posRowEnd = cases[caseStart++];
            size_t posColEnd = cases[caseStart++];
            int d = cases[caseStart++];
            DEBUG_LOG ("\trangeAdd (%ul, %ul, %ul, %ul, %d)\n", posRowStart, posColStart, posRowEnd, posColEnd, d);
            for (size_t i = 0; i < numTests; i++) {
                tests[i]->rangeAdd (posRowStart, posColStart, posRowEnd, posColEnd, d);
            }
            break;
        }
    case 3:
        {
            size_t posRow = cases[caseStart++];
            size_t posCol = cases[caseStart++];
            DEBUG_LOG ("\tsingleQuery (%ul, %ul)\n", posRow, posCol);
            int k = tests[0]->singleQuery (posRow, posCol);
            for (size_t i = 1; i < numTests; i++) {
                if (k != tests[i]->singleQuery (posRow, posCol)) {
                    return false;
                }
            }
            break;
        }
    case 4:
        {
            size_t posRowStart = cases[caseStart++];
            size_t posColStart = cases[caseStart++];
            size_t posRowEnd = cases[caseStart++];
            size_t posColEnd = cases[caseStart++];
            DEBUG_LOG ("\trangeQuery (%ul, %ul, %ul, %ul)\n", posRowStart, posColStart, posRowEnd, posColEnd);
            int k = tests[0]->rangeQuery (posRowStart, posColStart, posRowEnd, posColEnd);
            for (size_t i = 1; i < numTests; i++) {
                if (k != tests[i]->rangeQuery (posRowStart, posColStart, posRowEnd, posColEnd)) {
                    return false;
                }
            }
            break;
        }
    }
    return true;
}


void test1D (size_t count, size_t times) {
    Timing timing;
    Test *tests[] = {
        new BruteForceTest,
        new BITTest,
        new SegmentTreeTest
    };
    const char *testNames[] = {
        "BruteForce",
        "BIT",
        "SegmentTree"
    };
    const size_t numTests = sizeof(tests)/sizeof(tests[0]);
    for (size_t i = 0; i < numTests; i++) {
        tests[i]->init (count);
    }

    cout << "1D Testing " << count << " numbers for " << times << " times" << endl;
    vector<int> cases;
    for (size_t i = 0; i < times; i++) {
        int t = randRange (1, 5);
        cases.push_back (t);
        switch (t) {
            case 1:
                {
                    cases.push_back (randRange(1, count));
                    cases.push_back (randRange(-10000, 10000));
                    break;
                }
            case 2:
                {
                    int start = randRange(1, count);
                    int end = randRange(1, count);
                    if (start > end) {
                        swap (start, end);
                    }
                    cases.push_back (start);
                    cases.push_back (end);
                    cases.push_back (randRange(-10000, 10000));
                    break;
                }
            case 3:
            case 4:
                {
                    cases.push_back (randRange(1, count));
                    break;
                }
            case 5:
                {
                    int start = randRange(1, count);
                    int end = randRange(1, count);
                    if (start > end) {
                        swap (start, end);
                    }
                    cases.push_back (start);
                    cases.push_back (end);
                    break;
                }
        }
    }

    cout << "Testing correctness ..." << flush;
    size_t casePos = 0;
    for (size_t i = 0; i < times; i++) {
        if (!randTest (cases, casePos, tests, numTests)) {
            cout << "failed" << endl;
            return;
        }
    }
    cout << "ok" << endl;

    cout << "Testing performance ..." << endl;
    double base = 0;
    for (size_t i = 0; i < numTests; i++) {
        cout << "  " << testNames[i] << " ..." << flush;
        timing.begin();
        size_t casePos = 0;
        for (size_t j = 0; j < times; j++) {
            randTest (cases, casePos, tests+i, 1);
        }
        if (i == 0) {
            base = timing.end();
            cout << "100%" << endl;
        } else {
            cout << int((timing.end() / base) * 1000)/10.f << "%" << endl;
        }
    }
}

void test2D (size_t rows, size_t cols, size_t times) {
    Timing timing;
    Test2D *tests[] = {
        new BruteForceTest2D,
        new BITTest2D
    };
    const char *testNames[] = {
        "BruteForce",
        "BIT"
    };
    const size_t numTests = sizeof(tests)/sizeof(tests[0]);
    for (size_t i = 0; i < numTests; i++) {
        tests[i]->init (rows, cols);
    }

    cout << "2D Testing " << rows << "x" << cols << " numbers for " << times << " times" << endl;
    vector<int> cases;
    for (size_t i = 0; i < times; i++) {
        int t = randRange (1, 3);
        cases.push_back (t);
        switch (t) {
            case 1:
                {
                    cases.push_back (randRange(1, rows));
                    cases.push_back (randRange(1, cols));
                    cases.push_back (randRange(-10000, 10000));
                    break;
                }
            case 2:
                {
                    int rowStart = randRange(1, rows);
                    int colStart = randRange(1, cols);
                    int rowEnd = randRange(1, rows);
                    int colEnd = randRange(1, cols);
                    if (rowStart > rowEnd) {
                        swap (rowStart, rowEnd);
                    }
                    if (colStart > colEnd) {
                        swap (colStart, colEnd);
                    }
                    cases.push_back (rowStart);
                    cases.push_back (colStart);
                    cases.push_back (rowEnd);
                    cases.push_back (colEnd);
                    cases.push_back (randRange(-10000, 10000));
                    break;
                }
            case 3:
                {
                    cases.push_back (randRange(1, rows));
                    cases.push_back (randRange(1, cols));
                    break;
                }
            case 4:
                {
                    int rowStart = randRange(1, rows);
                    int colStart = randRange(1, cols);
                    int rowEnd = randRange(1, rows);
                    int colEnd = randRange(1, cols);
                    if (rowStart > rowEnd) {
                        swap (rowStart, rowEnd);
                    }
                    if (colStart > colEnd) {
                        swap (colStart, colEnd);
                    }
                    cases.push_back (rowStart);
                    cases.push_back (colStart);
                    cases.push_back (rowEnd);
                    cases.push_back (colEnd);
                    break;
                }
        }
    }

    cout << "Testing correctness ..." << flush;
    size_t casePos = 0;
    for (size_t i = 0; i < times; i++) {
        if (!randTest2D (cases, casePos, tests, numTests)) {
            cout << "failed" << endl;
            return;
        }
    }
    cout << "ok" << endl;

    cout << "Testing performance ..." << endl;
    double base = 0;
    for (size_t i = 0; i < numTests; i++) {
        cout << "  " << testNames[i] << " ..." << flush;
        timing.begin ();
        size_t casePos = 0;
        for (size_t j = 0; j < times; j++) {
            randTest2D (cases, casePos, tests+i, 1);
        }
        if (i == 0) {
            base = timing.end();
            cout << "100%" << endl;
        } else {
            cout << int((timing.end() / base) * 1000)/10.f << "%" << endl;
        }
    }
}

int main (int argc, char *argv[]) {
    if (argc != 5) {
        cout << "Usage: test_bit_segtree 1D_ARRAY_SIZE 2D_ARRAY_ROWS 2D_ARRAY_COLS TEST_COUNT" << endl;
        return 1;
    }
    const size_t times = atoi(argv[4]);
    const clock_t seed = clock() % 1000;
    cout << "Random seed: " << seed << endl;
    randomSeed (seed);

#ifdef TEST_1D
    const size_t count = atoi(argv[1]);
    test1D (count, times);
#endif

#ifdef TEST_2D
    const size_t rows = atoi(argv[2]);
    const size_t cols = atoi(argv[3]);
    test2D (rows, cols, times);
#endif

    return 0;
}