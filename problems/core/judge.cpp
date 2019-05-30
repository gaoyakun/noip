#include <cstdio>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string>
#include "judge.h"

struct Timing {
    long ts;
    void begin () {
        ts = clock ();
    }
    long end () {
		return (clock() - ts) * 1000 / CLOCKS_PER_SEC;
    }
};

std::vector<TestContext*> &Judge::getTests () {
    static std::vector<TestContext*> tests;
    return tests;
}
void Judge::registerTest (TestContext *ctx) {
    getTests().push_back (ctx);
}
void Judge::start () {
    for (unsigned i = 0; i < getTests().size(); i++) {
        executeContext (getTests()[i]);
    }
}
void Judge::executeContext (TestContext *ctx) {
    char inFile[260];
    char outFile[260];
    const char *results[100];
    int n = 0;
    std::cout << "Judging " << ctx->name() << "..." << std::flush;
    while (true) {
        sprintf (inFile, "data\\%s%d.in", ctx->name(), n+1);
        std::ifstream is(inFile);      
        if (!is.is_open ()) {
            break;
        }
        sprintf (outFile, "data\\%s%d.out", ctx->name(), n+1);
        std::ifstream is_out(outFile);
        if (!is_out.is_open()) {
            break;
        }
        results[n] = NULL;
        std::stringstream outData;
        try {
			ctx->read(is);
			{
				Timing t;
				ctx->execute(outData);
				if (t.end() > 1000) {
					results[n] = "TLE";
				}
			}
		} catch (...) {
            results[n] = "RE";
        }
        if (!results[n]) {
            results[n] = check (is_out, outData.str()) ? "AC" : "WA";
        }
        n++;
    }
    std::cout << "|";
    for (int i = 0; i < n; i++) {
        std::cout << results[i] << "|";
    }
    std::cout << std::endl;
}
bool Judge::check (std::istream &refData, std::string outData) {
    refData.seekg (0, refData.end);
    int len = refData.tellg ();
    refData.seekg (0, refData.beg);
    char *buffer = new char[len + 1];
    refData.read (buffer, len);
    buffer[len] = '\0';
    len = strlen (buffer);
    // Remove trailing carrage returns
    for (; len && buffer[len-1]=='\n'; len--) {
        buffer[len-1] = '\0';
    }
    while (outData.length() && isspace(outData[outData.length()-1])) {
        outData.erase (outData.length()-1, 1);
    }
    return outData == buffer;
}

