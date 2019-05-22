#ifndef __BIG_DECIMAL_H__
#define __BIG_DECIMAL_H__

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "num_limits.h"

namespace detail {
    template <class T>
    struct UnitSize {
        template <T N, int dummy = 0>
        struct Calc {
            static const int decimal_size = Calc<N/10>::decimal_size + 1;
        };
        template <int dummy>
        struct Calc<0, dummy> {
            static const int decimal_size = 0;
        };
        static const int value = Calc<NumberLimits<T>::max_value>::decimal_size;
    };

    template <class T, int N>
    struct UnitBase {
        static const T value = UnitBase<T, N-1>::value * 10;
    };
    template <class T>
    struct UnitBase<T, 0> {
        static const T value = 1;
    };
}

template <class T = unsigned long long>
class DecimalT;

typedef DecimalT<> Decimal;

template <class T>
class DecimalT {
    typedef std::vector<T> data_type;
    data_type _data;
public:
    static const int decimal_size = detail::UnitSize<T>::value/2;
    static const T base = detail::UnitBase<T, decimal_size>::value;
    typedef T native_type;
    typedef DecimalT<T> self_type;
    DecimalT () {
    }
    DecimalT (const DecimalT &other)
    : _data(other._data) {
    }
    DecimalT (native_type value) {
        set (value);
    }
    DecimalT (const std::string &s) {
        set (s);
    }
public:
    friend std::ostream & operator << (std::ostream &s, const self_type &x) {
        for (typename data_type::const_reverse_iterator it = x._data.rbegin(); it != x._data.rend(); it++) {
            if (it == x._data.rbegin()) {
                s << *it;
            } else {
                s << std::setw(decimal_size) << std::setfill('0') << *it;
            }
        }
        return s;
    }
    friend std::istream & operator >> (std::istream &s, self_type &x) {
        std::string str;
        s >> str;
        x.fromString (str);
        return s;
    }
    friend self_type operator + (const self_type &a, const self_type &b) {
        return a.add (b);
    }
    friend self_type operator * (const self_type &a, native_type b) {
        return a.mul (b);
    }
    friend self_type operator * (native_type a, const self_type &b) {
        return b.mul (a);
    }
    friend bool operator > (const self_type &a, const self_type &b) {
        return a.gt (b);
    }
    friend bool operator < (const self_type &a, const self_type &b) {
        return a.lt (b);
    }
    friend bool operator == (const self_type &a, const self_type &b) {
        return a.eq (b);
    }
    friend bool operator != (const self_type &a, const self_type &b) {
        return !a.eq (b);
    }
    friend bool operator >= (const self_type &a, const self_type &b) {
        return !a.lt (b);
    }
    friend bool operator <= (const self_type &a, const self_type &b) {
        return !a.gt (b);
    }
    bool operator !() const {
        return eq (0);
    }
    self_type & operator += (const self_type &other) {
        return inplaceAdd (other);
    }
    self_type & operator *= (native_type x) {
        return inplaceMul (x);
    }
public:
    self_type &set (native_type value) {
        invalidate();
        do {
            _data.push_back (value % base);
            value /= base;
        } while (value);
        return *this;
    }
    self_type &set (const std::string &value) {
        fromString (value);
        return *this;
    }
    bool isValid () const {
        return !_data.empty();
    }
    void invalidate () {
        _data.resize(0);
    }
    void fromString (const std::string &str) {
        std::string s = str;
        // remove leading zeroes
        unsigned i = 0;
        while (i < s.length() && s[i] == '0') {
            i++;
        }
        s.erase (0, i);

        invalidate();
        while (s.length()) {
            unsigned len = s.length();
            if (len > decimal_size) {
                len = decimal_size;
            }
            native_type value = 0;
            unsigned pos = s.length() - len;
            for (unsigned i = s.length() - len; i < s.length(); i++) {
                value = value * 10 + (s[i] - '0');
            }
            _data.push_back (value);
            s.erase (pos, len);
        }
        if (_data.empty()) {
            set (0);
        }
    }
    std::string toString () const {
        std::ostringstream s;
        for (typename data_type::const_reverse_iterator it = _data.rbegin(); it != _data.rend(); it++) {
            s << *it;
        }
        return s.str();
    }
    bool gt (const self_type &other) const {
        if (this->_data.size() > other._data.size()) {
            return true;
        } else if (this->_data.size() < other._data.size()) {
            return false;
        } else {
            for (typename data_type::const_reverse_iterator it1 = this->_data.rbegin(), it2 = other._data.rbegin(); it1 != this->_data.rend(); it1++, it2++) {
                if (*it1 > *it2) {
                    return true;
                } else if (*it1 < *it2) {
                    return false;
                }
            }
            return false;
        }
    }
    bool lt (const self_type &other) const {
        if (_data.size() < other._data.size()) {
            return true;
        } else if (this->_data.size() > other._data.size()) {
            return false;
        } else {
            for (typename data_type::const_reverse_iterator it1 = this->_data.rbegin(), it2 = other._data.rbegin(); it1 != this->_data.rend(); it1++, it2++) {
                if (*it1 < *it2) {
                    return true;
                } else if (*it1 > *it2) {
                    return false;
                }
            }
            return false;
        }
    }
    bool eq (const self_type &other) const {
        if (this->_data.size() != other._data.size()) {
            return false;
        } else {
            for (typename data_type::const_reverse_iterator it1 = this->_data.rbegin(), it2 = other._data.rbegin(); it1 != this->_data.rend(); it1++, it2++) {
                if (*it1 != *it2) {
                    return false;
                }
            }
            return true;
        }
    }
    self_type &inplaceMul (native_type x) {
        native_type carry = 0;
        for (unsigned i = 0; i < _data.size(); i++) {
            native_type val = _data[i] * x + carry;
            carry = val / base;
            _data[i] = val % base;
        } 
        if (carry) {
            _data.push_back (carry);
        }
        return *this;
    }
    self_type mul (native_type x) const {
        return self_type(*this).inplaceMul (x);
    }
    self_type &inplaceAdd (const self_type &other) {
        native_type carry = 0;
        unsigned len = other._data.size();
        if (_data.size() < len) {
            _data.resize (len, 0);
        }
        for (unsigned i = 0; i < _data.size(); i++) {
            native_type val = _data[i] + (i < len ? other._data[i] : 0) + carry;
            carry = val / base;
            _data[i] = val % base;
        } 
        if (carry) {
            _data.push_back (carry);
        }
        return *this;
    }
    self_type add (const self_type &other) const {
        return self_type(*this).inplaceAdd (other);
    }
};

#endif // __BIG_DECIMAL_H__
