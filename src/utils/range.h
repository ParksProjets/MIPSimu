/*

A class representing a range.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include <stdint.h>

namespace utils {


// A class representing a range.
template<typename T = uint32_t>
class range {
public:

    range(T lower, T upper): lower_(lower), upper_(upper) {};


    // Does the range contains the given value?
    template<typename V> bool contains(V value) {
        return value <= upper_ && value >= lower_; }

    // Translate a value.
    template<typename V> V translate(V value) {
        return value - lower_; }


    // Comparaison with another range.
    template<typename U, typename V> friend bool operator<(const range<U> &lhs, const range<V> &rhs);
    template<typename U, typename V> friend bool operator>(const range<U> &lhs, const range<V> &rhs);
    template<typename U, typename V> friend bool operator>=(const range<U> &lhs, const range<V> &rhs);
    template<typename U, typename V> friend bool operator<=(const range<U> &lhs, const range<V> &rhs);
    template<typename U, typename V> friend bool operator==(const range<U> &lhs, const range<V> &rhs);
    template<typename U, typename V> friend bool operator!=(const range<U> &lhs, const range<V> &rhs);

    // Comparaison with a T value.
    template<typename U, typename V> friend bool operator<(const range<U> &rhs, const V lhs);
    template<typename U, typename V> friend bool operator>(const range<U> &rhs, const V lhs);
    template<typename U, typename V> friend bool operator<=(const range<U> &rhs, const V lhs);
    template<typename U, typename V> friend bool operator>=(const range<U> &rhs, const V lhs);


private:
    
    T upper_, lower_;
};




// Create a range.
template<typename T>
inline range<T> make_range(T lower, T upper) {
    return range<T>(lower, upper);
}



// Comparaison with two ranges.

template<typename T, typename V>
inline bool operator<(const range<T> &lhs, const range<V> &rhs) {
    return lhs.upper_ < rhs.lower_; 
}

template<typename T, typename V>
inline bool operator>(const range<T> &lhs, const range<V> &rhs) {
    return rhs < lhs;
}

template<typename T, typename V>
inline bool operator<=(const range<T> &lhs, const range<V> &rhs) {
    return !(lhs > rhs);
}

template<typename T, typename V>
inline bool operator>=(const range<T> &lhs, const range<V> &rhs) {
    return !(lhs < rhs);
}

template<typename T, typename V>
inline bool operator==(const range<T> &lhs, const range<V> &rhs) {
    return lhs.lower_ == rhs.lower_ && lhs.upper_ == rhs.upper_;
}

template<typename T, typename V>
inline bool operator!=(const range<T> &lhs, const range<V> &rhs) {
    return !(lhs == rhs);
}



// Comparaison with a T value.

template<typename T, typename V>
inline bool operator<(const range<T> &lhs, const V rhs) {
    return lhs.upper_ < rhs;
}

template<typename T, typename V>
inline bool operator>(const range<T> &lhs, const V rhs) {
    return lhs.lower_ > rhs;
}

template<typename T, typename V>
inline bool operator<=(const range<T> &lhs, const V rhs) {
    return lhs.upper_ <= rhs;
}

template<typename T, typename V>
inline bool operator>=(const range<T> &lhs, const V rhs) {
    return lhs.lower_ >= rhs;
}


} // namespace utils
