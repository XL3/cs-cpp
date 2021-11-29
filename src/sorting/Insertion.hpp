#pragma once
#include <array>
#include <functional>

using index_t = unsigned long;

template <class T>
class Insertion {
    using predicate_t = std::function<bool(T, T)>;

public:
    // In-place
    static void sort(
        T *data,
        size_t SIZE,
        predicate_t predicate = [](T a, T b) { return a < b; }) {
        for (index_t i = 1; i < SIZE; i++) {
            T item = data[i];
            index_t j = i;

            for (; j > 0; j--) {
                if (predicate(item, data[j - 1])) {
                    data[j] = data[j - 1];
                }
                else {
                    break;
                }
            }
            data[j] = item;
        }
    }
};
