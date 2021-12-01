#pragma once
#include "SortingAlgorithm.hpp"

class Insertion : public SortingAlgorithm {
public:
    // In-place
    template <class T>
    static void sort(T *data, size_t SIZE, predicate_t<T> predicate = predicate_lt<T>) {
        for (index_t i = 1; i < SIZE; i++) {
            T item = data[i];
            index_t j = i;

            for (; j > 0; j--) {
                if (predicate(item, data[j - 1])) {
                    data[j] = data[j - 1];
                }
                else
                    break;
            }
            data[j] = item;
        }
    }
};
