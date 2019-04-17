#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "SegmentTree.h"
#include "BinaryIndexedTree.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;

inline int randRange (int start, int end) {
    return start + rand() % (end - start + 1);
}

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
    BIT<int> bit;
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

inline bool randTest (const vector<int> &cases, size_t &caseStart, Test *tests[], size_t numTests, size_t count) {
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

int main () {
    const size_t count = 1000000;
    const size_t times = 1000000;
    srand (clock ());
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

    cout << "Testing " << count << " numbers for " << times << " times" << endl;
    vector<int> cases;
    for (size_t i = 0; i < times; i++) {
        int t = randRange (1, 5);
        cases.push_back (t);
        switch (t) {
            case 1:
                {
                    cases.push_back (randRange(1, count));
                    cases.push_back (rand());
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
                    cases.push_back (rand());
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
                }
        }
    }

    cout << "Testing correctness ...";
    clock_t c1 = clock ();
    size_t casePos = 0;
    for (size_t i = 0; i < times; i++) {
        if (!randTest (cases, casePos, tests, numTests, count)) {
            cout << "failed" << endl;
            return 1;
        }
    }
    clock_t c2 = clock ();
    cout << "Ok: " << c2 - c1 << "ms" << endl;

    cout << "Testing performance ..." << endl;
    for (size_t i = 0; i < numTests; i++) {
        cout << "  " << testNames[i] << " ...";
        clock_t c1 = clock ();
        size_t casePos = 0;
        for (size_t j = 0; j < times; j++) {
            randTest (cases, casePos, tests+i, 1, count);
        }
        clock_t c2 = clock ();
        cout << c2 - c1 << "ms" << endl;
    }

    return 0;
}