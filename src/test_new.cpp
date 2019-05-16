#include <iostream>
#include <vector>
#include <cstdlib>
#include "test_common.h"

using std::cout;
using std::cin;
using std::endl;
using std::flush;
using std::vector;

int main (int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: test_new ALLOC_SIZE TEST_COUNT" << endl;
        return 1;
    }
    const size_t allocSize = atoi(argv[1]);
    const size_t times = atoi(argv[2]);
    vector<char*> p(times);

    cout << "Testing new " << allocSize << " bytes " << times << " times ..." << endl;
    Timing timing;
    timing.begin ();
    for (size_t i = 0; i < times; i++) {
        p[i++] = new char[allocSize];
    }
    long allocTicks = timing.end ();
    timing.begin ();
    for (size_t i = 0; i < times; i++) {
        delete [] p[i++];
    }
    long freeTicks = timing.end ();
    cout << "  new :" << allocTicks << "ms" << endl;
    cout << "  delete :" << freeTicks << "ms" << endl;

    return 0;
}