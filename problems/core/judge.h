#ifndef __JUDGE_H__
#define __JUDGE_H__

#include <iostream>
#include <string>
#include <vector>

struct TestContext {
    std::string _name;
    TestContext (const char *name): _name(name) {}
    virtual const char *name () const { return _name.c_str(); }
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

template <class T>
void readData (std::istream &s, T &val) {
    s >> val;
}

template <class T>
void readData (std::istream &s, std::vector<T> &val) {
    unsigned sz;
    s >> sz;
    val.resize (sz);
    for (unsigned i = 0; i < sz; i++) {
        readData (s, val[i]);
    }
}

template <class T> 
struct RemoveReference {
    typedef T type;
};

template <class T>
struct RemoveReference<T&> {
    typedef T type;
};

template <class T>
struct RemoveReference<const T&> {
    typedef T type;
};

template <class T> struct TestContextT;

template <class T1>
struct TestContextT <void (*)(std::ostream&, T1)>: public TestContext {
    typedef typename RemoveReference<T1>::type type;
    typedef void (*func_type)(std::ostream&, T1);
    func_type function;
    type param1;
    TestContextT (const char *name, func_type func): TestContext(name), function(func) {
    }
    virtual void read (std::istream &s) {
        readData (s, param1);
    }
    virtual void execute (std::ostream &out) {
        function (out, param1);
    }
};

template <class T1, class T2>
struct TestContextT <void (*)(std::ostream&, T1, T2)>: public TestContext {
    typedef typename RemoveReference<T1>::type type1;
    typedef typename RemoveReference<T2>::type type2;
    typedef void (*func_type)(std::ostream&, T1, T2);
    func_type function;
    type1 param1;
    type2 param2;
    TestContextT (const char *name, func_type func): TestContext(name), function(func) {
    }
    virtual void read (std::istream &s) {
        readData (s, param1);
        readData (s, param2);
    }
    virtual void execute (std::ostream &out) {
        function (out, param1, param2);
    }
};

template <class T1, class T2, class T3>
struct TestContextT <void (*)(std::ostream&, T1, T2, T3)>: public TestContext {
    typedef typename RemoveReference<T1>::type type1;
    typedef typename RemoveReference<T2>::type type2;
    typedef typename RemoveReference<T3>::type type3;
    typedef void (*func_type)(std::ostream&, T1, T2, T3);
    func_type function;
    type1 param1;
    type2 param2;
    type3 param3;
    TestContextT (const char *name, func_type func): TestContext(name), function(func) {
    }
    virtual void read (std::istream &s) {
        readData (s, param1);
        readData (s, param2);
        readData (s, param3);
    }
    virtual void execute (std::ostream &out) {
        function (out, param1, param2, param3);
    }
};

template <class T1, class T2, class T3, class T4>
struct TestContextT <void (*)(std::ostream&, T1, T2, T3, T4)>: public TestContext {
    typedef typename RemoveReference<T1>::type type1;
    typedef typename RemoveReference<T2>::type type2;
    typedef typename RemoveReference<T3>::type type3;
    typedef typename RemoveReference<T4>::type type4;
    typedef void (*func_type)(std::ostream&, T1, T2, T3, T4);
    func_type function;
    type1 param1;
    type2 param2;
    type3 param3;
    type4 param4;
    TestContextT (const char *name, func_type func): TestContext(name), function(func) {
    }
    virtual void read (std::istream &s) {
        readData (s, param1);
        readData (s, param2);
        readData (s, param3);
        readData (s, param4);
    }
    virtual void execute (std::ostream &out) {
        function (out, param1, param2, param3, param4);
    }
};

template <class T1, class T2, class T3, class T4, class T5>
struct TestContextT <void (*)(std::ostream&, T1, T2, T3, T4, T5)>: public TestContext {
    typedef typename RemoveReference<T1>::type type1;
    typedef typename RemoveReference<T2>::type type2;
    typedef typename RemoveReference<T3>::type type3;
    typedef typename RemoveReference<T4>::type type4;
    typedef typename RemoveReference<T5>::type type5;
    typedef void (*func_type)(std::ostream&, T1, T2, T3, T4, T5);
    func_type function;
    type1 param1;
    type2 param2;
    type3 param3;
    type4 param4;
    type5 param5;
    TestContextT (const char *name, func_type func): TestContext(name), function(func) {
    }
    virtual void read (std::istream &s) {
        readData (s, param1);
        readData (s, param2);
        readData (s, param3);
        readData (s, param4);
        readData (s, param5);
    }
    virtual void execute (std::ostream &out) {
        function (out, param1, param2, param3, param4, param5);
    }
};

template <class T>
TestContextT<T> *createTestContext (const char *name, T func) {
    return new TestContextT<T> (name, func);
}

#define DECLARE_PROBLEM(name, func) \
static struct AutoRegister_##name { \
    AutoRegister_##name () { \
        Judge::registerTest(createTestContext(#name, func)); \
    } \
} __autoregister_##name; \


#endif // __JUDGE_H__
