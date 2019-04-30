#ifndef __TEST_COMMON__
#define __TEST_COMMON__

#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <cstdarg>
#include <cstdint>
#include "random.h"

#if defined(WIN32) || defined(_WIN32)
#include <intrin.h>
inline uint64_t rdtsc() {
	return __rdtsc();
}
#else
inline uint64_t rdtsc() {
	unsigned lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}
#endif

#ifdef VERBOSE
#define DEBUG_LOG(format, ...) do { std::cout << strFormat(format, ##__VA_ARGS__) << std::flush; } while(0)
#else
#define DEBUG_LOG(format, ...)
#endif

struct Timing {
    uint64_t ts;
    void begin () {
        ts = rdtsc ();
    }
    uint64_t end () {
		return rdtsc() - ts;
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

#endif // __TEST_COMMON__
