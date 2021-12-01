#pragma once
#include "SortingAlgorithm.hpp"

class Selection : public SortingAlgorithm {
public:
    // In-place
    template <class T>
    static void sort(T *data, size_t SIZE, predicate_t<T> predicate = predicate_lt<T>) {
        for (index_t i = 0; i < SIZE - 1; i++) {
            index_t minimum_index = i;

            for (index_t j = i + 1; j < SIZE; j++) {
                if (predicate(data[j], data[minimum_index])) {
                    minimum_index = j;
                }
            }

            if (i != minimum_index) {
                std::swap(data[i], data[minimum_index]);
            }
        }
    }
};
