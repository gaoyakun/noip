#ifndef __RANDOM__
#define __RANDOM__

namespace {
    static double u[97], c, cd, cm;
    static int i97, j97;
    static bool test = false;

    static inline void _randomSeed (int seed) {
        int ij = ((seed & 0xffff0000) >> 16) % 31329;
        int kl = (seed & 0xffff) % 30082;
        int i = (ij / 177) % 177 + 2;
        int j = (ij / 177) + 2;
        int k = (kl / 169) % 178 + 1;
        int l = kl % 169;
        for (int ii = 0; ii < 97; ii++) {
            double s = 0.0;
            double t = 0.5;
            for (int jj = 0; jj < 24; jj++) {
                int m = (((i * j) % 179) * k) % 179;
                i = j;
                j = k;
                k = m;
                l = (53 * l + 1) % 169;
                if (((l * m % 64)) >= 32) {
                    s += t;
                }
                t *= 0.5;
            }
            u[ii] = s;
        }
        c = 362436.0 / 16777216.0;
        cd = 7654321.0 / 16777216.0;
        cm = 16777213.0 / 16777216.0;
        i97 = 97;
        j97 = 33;
        test = true;
    }

    static inline double _randomUniform () {
        if (!test) {
            _randomSeed ((1802 << 16) + 9373);
        }
        double uni = u[i97-1] - u[j97-1];
        if (uni < 0.0) {
            uni++;
        }
        u[--i97] = uni;
        if (i97 == 0) {
            i97 = 97;
        }
        j97--;
        if (j97 == 0) {
            j97 = 97;
        }
        c -= cd;
        if (c < 0.0) {
            c += cm;
        }
        uni -= c;
        if (uni < 0.0) {
            uni++;
        }
        return uni;
    }
}

inline void randomSeed (int seed) {
    _randomSeed (seed);
}

inline int randomInt (int lower, int upper) {
    return (int)(_randomUniform() * (upper - lower + 1)) + lower;
}

inline double randomDouble (double lower, double upper) {
    return (upper - lower) * _randomUniform() + lower;
}

#endif // __RANDOM__
