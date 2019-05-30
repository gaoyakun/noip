#include <vector>
#include <iostream>
#include <stdexcept>
#include "judge.h"

using std::vector;
using std::istream;
using std::ostream;
using std::flush;

extern void solution (const vector<vector<int> > &numbers, vector<int> &result);

struct TestContextNWayMerge: public TestContext {
    vector<vector<int> > numbers;
    vector<int> result;
    TestContextNWayMerge () {
        Judge::registerTest(this);
    }
    virtual const char *name () const {
        return "nwaymerge";
    }
    virtual void read (istream &is) {
        int n;
        is >> n;
        numbers.resize (n);
        for (int i = 0; i < n; i++) {
        	int k;
        	is >> k;
        	numbers[i].resize(k);
        	for (int j = 0; j < k; j++) {
        		is >> numbers[i][j];
			}
        }
    }
    virtual void execute (ostream &os) {
		result.resize(0);
        solution (numbers, result);
        if (result.size()) {
        	os << result[0];
		}
		for (int i = 1; i < result.size(); i++) {
			os << ' ' << result[i];
		}
    }
};

static TestContextNWayMerge testNWayMerge;
