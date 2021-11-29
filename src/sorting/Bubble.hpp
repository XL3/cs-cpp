#pragma once
#include <array>
#include <functional>

using index_t = unsigned long;

template <class T>
class Bubble {
    using predicate_t = std::function<bool(T, T)>;

public:
    // In-place
    static void sort(
        T *data,
        size_t SIZE,
        predicate_t predicate = [](T a, T b) { return a < b; }) {
        for (index_t i = 0; i < SIZE - 1; i++) {
            for (index_t j = i + 1; j < SIZE; j++) {
                if (predicate(data[j], data[i])) {
                    std::swap(data[j], data[i]);
                }
            }
        }
    }
};
