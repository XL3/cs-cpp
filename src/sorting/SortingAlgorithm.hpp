#pragma once
#include <algorithm>
#include <array>
#include <vector>
#include <functional>
#include <stddef.h>

#if defined(__GNUC__) || defined(__GNUG__)
#   include <cxxabi.h>
#   define TYPE_NAME(var) (abi::__cxa_demangle(typeid(var).name(), NULL, NULL, NULL))
#else
#   define TYPE_NAME(var) (typeid(var).name())
#endif
#include "../utility/print.hpp"

class SortingAlgorithm {
protected:
    using index_t = unsigned long;

    template <class T>
    using predicate_t = std::function<bool(T, T)>;

    template <class T>
    const static inline predicate_t<T> predicate_lt = [](T a, T b) { return a < b; };

    template <class T>
    static void sort(T *data, size_t SIZE, predicate_t<T> predicate);
};

template <class _SortingAlgorithm, size_t _Size = 16>
void test_sort() {
    std::array<char, _Size> data;
    for (int i = 0; i < _Size; i++) {
        // data[i] = 1 << i;
        data[i] = 'a' + i;
    }
    std::random_shuffle(data.begin(), data.end());

    print_array(&data[0], _Size, TYPE_NAME(_SortingAlgorithm));
    _SortingAlgorithm::sort(&data.front(), _Size);
    print_array(&data[0], _Size);
}