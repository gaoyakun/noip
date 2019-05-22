#ifndef __NUM_LIMITS_H__
#define __NUM_LIMITS_H__

#include <climits>
#include <cfloat>

template <class T>
struct NumberLimits;

template <class T>
struct NumberTraits {
    static const bool is_signed = NumberLimits<T>::min_value < 0;
};

template <>
struct NumberLimits<signed char> {
    enum {
        max_value = SCHAR_MAX,
        min_value = SCHAR_MIN
    };
};

template <>
struct NumberLimits<unsigned char> {
    enum {
        max_value = UCHAR_MAX,
        min_value = static_cast<unsigned char>(0)
    };
};

template <>
struct NumberLimits<short> {
    enum {
        max_value = SHRT_MAX,
        min_value = SHRT_MIN
    };
};

template <>
struct NumberLimits<unsigned short> {
    enum {
        max_value = USHRT_MAX,
        min_value = static_cast<unsigned short>(0)
    };
};

template <>
struct NumberLimits<int> {
    enum {
        max_value = INT_MAX,
        min_value = INT_MIN
    };
};

template <>
struct NumberLimits<unsigned int> {
    enum {
        max_value = UINT_MAX,
        min_value = static_cast<unsigned int>(0)
    };
};

template <>
struct NumberLimits<long> {
    enum {
        max_value = LONG_MAX,
        min_value = LONG_MIN
    };
};

template <>
struct NumberLimits<unsigned long> {
    enum {
        max_value = ULONG_MAX,
        min_value = static_cast<unsigned long>(0)
    };
};

template <>
struct NumberLimits<long long> {
    enum {
        max_value = LLONG_MAX,
        min_value = LLONG_MIN
    };
};

template <>
struct NumberLimits<unsigned long long> {
    enum {
        max_value = ULLONG_MAX,
        min_value = static_cast<unsigned long long>(0)
    };
};

#endif // __NUM_LIMITS_H__
