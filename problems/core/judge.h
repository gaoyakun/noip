#ifndef __JUDGE_H__
#define __JUDGE_H__

#include <iostream>
#include <string>
#include <vector>

struct TestContext {
    virtual const char *name () const = 0;
    virtual void read (std::istream &) = 0;
    virtual void execute (std::ostream &) = 0;
};

class Judge {
public:
    static std::vector<TestContext*> &getTests ();
    static void registerTest (TestContext *ctx);
    static void start ();
private:
    static void executeContext (TestContext *ctx);
    static bool check (std::istream &refData, std::string outData);
};

#endif // __JUDGE_H__
