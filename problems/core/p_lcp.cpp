#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "judge.h"

using std::string;
using std::getline;
using std::vector;
using std::istream;
using std::ostream;
using std::flush;
using std::runtime_error;

extern string solution (const vector<string> &strList);

struct TestContextLCP: public TestContext {
    vector<string> strList;
    TestContextLCP () {
        Judge::registerTest(this);
    }
    virtual const char *name () const {
        return "lcp";
    }
    virtual void read (istream &is) {
        int n;
        is >> n;
        is.ignore ();
        strList.resize (n);
        for (int i = 0; i < n; i++) {
            getline (is, strList[i]);
        }
    }
    virtual void execute (ostream &os) {
        os << solution (strList);
    }
};

static TestContextLCP testLCP;
