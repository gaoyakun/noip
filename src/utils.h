#ifndef __UTILS_H__
#define __UTILS_H__

#define M_JOIN(x, y) x##y
#define M_STATIC_ASSERT(expr) typedef static_assert_test<sizeof(CompileTimeError<(bool)(expr)>)> M_JOIN(static_assert_typedef_, __COUNTER__)

template <int x> struct static_assert_test {};
template <bool x> struct CompileTimeError;
template <> struct CompileTimeError<true> {
    enum { value = 1 };
};

#endif // __UTILS_H__
