#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <cstddef>
#include <cstdarg>
#include <climits>
#include "random.h"

#if defined(WIN32) || defined(_WIN32)
#include <intrin.h>
inline unsigned long long rdtsc() {
	return __rdtsc();
}
#else
inline unsigned long long rdtsc() {
	unsigned lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((unsigned long long)hi << 32) | lo;
}
#endif

#ifdef VERBOSE
#define DEBUG_LOG(format, ...) do { std::cout << strFormat(format, ##__VA_ARGS__) << std::flush; } while(0)
#else
#define DEBUG_LOG(format, ...)
#endif

struct Timing {
    long ts;
    void begin () {
        ts = clock ();
    }
    long end () {
		return (clock() - ts) * 1000 / CLOCKS_PER_SEC;
    }
};


inline std::string strFormat (const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer, 256, format, args);
    va_end (args);
    return buffer;
}

inline void randSeed (int seed) {
    return randomSeed (seed);
}

inline int randRange (int start, int end) {
    return randomInt (start, end);
}

struct RandIntGen {
    int operator () () const {
        return randomInt (INT_MIN, INT_MAX);
    }
    int operator () (int lower, int upper) const {
        return randomInt (lower, upper);
    }
};


#endif // __TEST_COMMON_H__
