#ifndef __BITOP__
#define __BITOP__

// Detect if two integers have opposite signs
static inline bool haveOppsiteSigns (int x, int y) {
    return (x ^ y) < 0;
}

// Determin if an integer is a power of 2
static inline bool isPowerOf2 (unsigned x) {
    return x && (x & (x - 1)) == 0;
}

// Counting bits set
static inline unsigned bitsSet (unsigned x) {
    unsigned c = 0;
    for (; x; c++) {
        x &= x - 1;
    }
    return c;
}

// Reverse bits
static inline unsigned bitsReverse (unsigned x) {
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    x = ((x >> 4) & 0x0f0f0f0f) | ((x & 0x0f0f0f0f) << 4);
    x = ((x >> 8) & 0x00ff00ff) | ((x & 0x00ff00ff) << 8);
    x = (x >> 16) | (x << 16);
    return x;
}

// Round up to the next highest power of 2
static inline unsigned nextPowerOf2 (unsigned x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1 + (x == 0);
}

// Determine if a word has a zero byte
static inline bool hasZeroByte (unsigned x) {
    return ~((((x & 0x7f7f7f7f) + 0x7f7f7f7f) | x) | 0x7f7f7f7f);
}

// Determine if a word has a byte equal to n
static inline bool hasByte (unsigned x, unsigned char n) {
    return hasZeroByte (x ^ (~0u / 255 * n));
}

#endif // __BITOP__