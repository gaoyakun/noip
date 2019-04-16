#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
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

class PartialSumTest: public Test {
    vector<int> A;
public:
    virtual void init (size_t size) {
        A.resize (size + 1, 0);
    }
    virtual size_t count () const {
        return A.size() - 1;
    }
    virtual void singleAdd (size_t pos, int d) {
        for (size_t i = pos; i < A.size(); i++) {
            A[i] += d;
        }
    }
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) {
        for (size_t i = posStart; i <= posEnd; i++) {
            A[i] += (i - posStart + 1) * d;
        }
        int k = (posEnd - posStart + 1) * d;
        for (size_t i = posEnd + 1; i < A.size(); i++) {
            A[i] += k;
        }
    }
    virtual int sum (size_t n) const {
        return A[n];
    }
    virtual int singleQuery (size_t pos) const {
        return A[pos] - A[pos-1];
    }
    virtual int rangeQuery (size_t posStart, size_t posEnd) const {
        return A[posEnd] - A[posStart-1];
    }
};

class BaseBITTest: public Test {
    vector<int> C;
public:
    virtual void init (size_t size) {
        C.resize (size + 1, 0);
    }
    virtual size_t count () const {
        return C.size() - 1;
    }
    virtual void singleAdd (size_t pos, int d) {
        size_t count = C.size();
        while (pos <= count) {
            C[pos] += d;
            pos += pos & -pos;
        }
    }
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) {
        for (size_t i = posStart; i <= posEnd; i++) {
            singleAdd (i, d);
        }
    }
    virtual int sum (size_t n) const {
        int result = 0;
        while (n) {
            result += C[n];
            n -= n & -n;
        }
        return result;
    }
    virtual int singleQuery (size_t pos) const {
        return sum(pos) - sum(pos-1);
    }
    virtual int rangeQuery (size_t posStart, size_t posEnd) const {
        return sum(posEnd) - sum(posStart-1);
    }
};

class DiffBITTest: public Test {
    BaseBITTest baseBIT;
public:
    virtual void init (size_t size) {
        baseBIT.init(size);
    }
    virtual size_t count () const {
        return baseBIT.count();
    }
    virtual void singleAdd (size_t pos, int d) {
        rangeAdd (pos, pos, d);
    }
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) {
        baseBIT.singleAdd (posStart, d);
        baseBIT.singleAdd (posEnd+1, -d);
    }
    virtual int sum (size_t n) const {
        return rangeQuery (1, n);
    }
    virtual int singleQuery (size_t pos) const {
        return baseBIT.sum (pos);
    }
    virtual int rangeQuery (size_t posStart, size_t posEnd) const {
        int result = 0;
        for (size_t i = posStart; i <= posEnd; i++) {
            result += singleQuery (i);
        }
        return result;
    }
};

class Diff2BITTest: public Test {
    BaseBITTest baseBIT1;
    BaseBITTest baseBIT2;
public:
    virtual void init (size_t size) {
        baseBIT1.init(size);
        baseBIT2.init(size);
    }
    virtual size_t count () const {
        return baseBIT1.count();
    }
    virtual void singleAdd (size_t pos, int d) {
        rangeAdd (pos, pos, d);
    }
    virtual void rangeAdd (size_t posStart, size_t posEnd, int d) {
        baseBIT1.singleAdd (posStart, d);
        baseBIT1.singleAdd (posEnd+1, -d);
        baseBIT2.singleAdd (posStart, d * posStart);
        baseBIT2.singleAdd (posEnd+1, -d * (posEnd+1));
    }
    virtual int sum (size_t n) const {
        return (n + 1) * baseBIT1.sum(n) - baseBIT2.sum(n);
    }
    virtual int singleQuery (size_t pos) const {
        return rangeQuery (pos, pos);
    }
    virtual int rangeQuery (size_t posStart, size_t posEnd) const {
        return sum (posEnd) - sum (posStart-1);
    }
};

inline bool randTest (Test *tests[], size_t numTests) {
    size_t count = tests[0]->count();
    int t = randRange (1, 5);
    switch (t) {
    case 1:
        {
            size_t pos = randRange (1, count);
            int d = rand ();
            for (size_t i = 0; i < numTests; i++) {
                tests[i]->singleAdd (pos, d);
            }
            break;
        }
    case 2:
        {
            size_t posStart = randRange (1, count);
            size_t posEnd = randRange (1, count);     
            if (posStart > posEnd) {
                swap (posStart, posEnd);
            }       
            int d = rand ();
            for (size_t i = 0; i < numTests; i++) {
                tests[i]->rangeAdd (posStart, posEnd, d);
            }
            break;
        }
    case 3:
        {
            size_t n = randRange (1, count);
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
            size_t pos = randRange (1, count);
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
            size_t posStart = randRange (1, count);
            size_t posEnd = randRange (1, count);
            if (posStart > posEnd) {
                swap (posStart, posEnd);
            }
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
    const size_t count = 100000;
    const size_t times = 500000;
    srand (clock ());
    Test *tests[] = {
        new BruteForceTest,
        new PartialSumTest,
        new BaseBITTest,
        new DiffBITTest,
        new Diff2BITTest,
    };
    const char *testNames[] = {
        "BruteForce",
        "PartialSum",
        "BaseBIT",
        "DiffBIT",
        "Diff2BIT"
    };
    const size_t numTests = sizeof(tests)/sizeof(tests[0]);
    for (size_t i = 0; i < numTests; i++) {
        tests[i]->init (count);
    }

    cout << "Testing " << count << " numbers for " << times << " times" << endl;
    for (size_t i = 0; i < count; i++) {
        int k = randRange (1, 1000000);
        for (size_t j = 0; j < numTests; j++) {
            tests[j]->singleAdd (i+1, k);
        }
    }
    cout << "Testing correctness ...";
    clock_t c1 = clock ();
    for (size_t i = 0; i < times; i++) {
        if (!randTest (tests, numTests)) {
            cout << "failed" << endl;
            return 0;
        }
    }
    clock_t c2 = clock ();
    cout << "Ok: " << c2 - c1 << "ms" << endl;

    cout << "Testing performance ..." << endl;
    for (size_t i = 0; i < numTests; i++) {
        cout << "  " << testNames[i] << " ...";
        clock_t c1 = clock ();
        for (size_t j = 0; j < times; j++) {
            randTest (tests+i, 1);
        }
        clock_t c2 = clock ();
        cout << c2 - c1 << "ms" << endl;
    }

    return 0;
}