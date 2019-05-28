#include <cstdio>
#include <iostream>
#include <string>

#ifdef WIN32
#include <windows>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Judge {
    string _inFile;
    string _outFile;
    unsigned _timestamp;
public:
    Judge (const char *inFile, const char *outFile)
    : _inFile(inFile)
    , _outFile(outFile) {
    }
    void beginJudge () {
    }
    void endJudge () {
    }
};