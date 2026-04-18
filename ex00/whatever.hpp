#ifndef WHATEVER_HPP
#define WHATEVER_HPP

# include <iostream>
# include <string>

template <typename T>
void swap(T &v1, T &v2){
    T swap = v1;
    v1 = v2;
    v2 = swap;
}

template <typename T>
T const &min(T const &v1, T const &v2){
    return (v1 < v2) ? v1 : v2;
}

template <typename T>
T const &max(T const &v1, T const &v2){
    return (v1 > v2) ? v1 : v2;
}

#endif