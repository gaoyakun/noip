#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "bitop.h"
#include "test_common.h"

using std::cin;
using std::cout;
using std::flush;
using std::endl;

bool haveOppsiteSigns_bruteforce (int x, int y) {
    return (x >= 0 && y < 0) || (x < 0 && y >= 0);
}

bool isPowerOf2_bruteforce (unsigned x) {
    if (x == 0) {
        return false;
    }
    while (x > 1) {
        if (x % 2) {
            return false;
        }
        x /= 2;
    }
    return true;
}

unsigned bitsSet_bruteforce (unsigned x) {
    unsigned c = 0;
    for (; x; x >>= 1) {
        c += (x & 1);
    }
    return c;
}

unsigned bitsReverse_bruteforce (unsigned x) {
    unsigned r = 0;
    int s = sizeof(x) * CHAR_BIT;
    for (int i = 0; i < s; i++) {
        r |= (x & (1<<i)) >> i << (s-i-1);
    }
    return r;
}

unsigned nextPowerOf2_bruteforce (unsigned x) {
    unsigned val = 1;
    while (val < x) {
        val *= 2;
    }
    return val;
}

bool hasZeroByte_bruteForce (unsigned x) {
    return !((x & 0xff) && (x & 0xff00) && (x & 0xff0000) && (x & 0xff000000));
}

bool hasByte_bruteForce (unsigned x, unsigned char n) {
    return (x & 0xff) == n || (x & 0xff00) == (n << 8) || (x & 0xff0000) == (n << 16) || (x & 0xff000000) == (n << 24);
}

bool testHaveOppositeSigns () {
    int x = randRange (-50000, 50000);
    int y = randRange (-50000, 50000);
    return haveOppsiteSigns (x, y) == haveOppsiteSigns_bruteforce (x, y);
}

bool testIsPowerOf2 () {
    int n = randRange (0, 2<<29);
    return isPowerOf2 (n) == isPowerOf2_bruteforce (n);
}

bool testBitsSet () {
    unsigned n = randRange (0, 2<<29);
    return bitsSet (n) == bitsSet_bruteforce (n);
}

bool testBitsReverse () {
    unsigned n = randRange (0, 2<<29);
    return bitsReverse (n) == bitsReverse_bruteforce (n);
}

bool testNextPowerOf2 () {
    unsigned val = randRange (0, 2<<28);
    return nextPowerOf2(val) == nextPowerOf2_bruteforce(val);
}

bool testHasZeroByte () {
    unsigned val = randRange (0, 0xFFFFFFFF);
    return hasZeroByte(val) == hasZeroByte_bruteForce(val);
}

bool testHasByte () {
    unsigned val = randRange (0, 0xFFFFFFFF);
    unsigned char n = randRange (0, 0xFF);
    return hasByte (val, n) == hasByte_bruteForce (val, n);
}

bool (*testOptions[])() = {
    testHaveOppositeSigns,
    testIsPowerOf2,
    testBitsSet,
    testBitsReverse,
    testNextPowerOf2,
    testHasZeroByte,
    testHasByte,
};

const char *testNames[] = {
    "Have opposite signs",
    "Is power of 2",
    "Bits set",
    "Bits reverse",
    "Next power of 2",
    "Has zero byte",
    "Has specific byte value"
};

int main (int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: test_bitop TEST_COUNT" << endl;
        return 1;
    }
    const size_t times = atoi(argv[1]);
    const clock_t seed = clock() % 1000;
    cout << "Random seed: " << seed << endl;
    randomSeed (seed);

    for (int i = 0; i < sizeof(testOptions)/sizeof(testOptions[0]); i++) {
        cout << "Testing " << testNames[i] << "..." << flush;
        bool failed =false;
        for (int j = 0; j < times; j++) {
            if (!testOptions[i]()) {
                failed = true;
                break;
            }
        }
        cout << (failed ? "failed" : "ok") << endl;
    }

    return 0;
}

