#pragma once
#include "SortingAlgorithm.hpp"

class Bubble : public SortingAlgorithm {
public:
    // In-place
    template <class T>
    static void sort(T *data, size_t SIZE, predicate_t<T> predicate = predicate_lt<T>) {
        for (index_t i = 0; i < SIZE - 1; i++) {
            for (index_t j = i + 1; j < SIZE; j++) {
                if (predicate(data[j], data[i])) {
                    std::swap(data[j], data[i]);
                }
            }
        }
    }
};
