#pragma once
#include "SortingAlgorithm.hpp"

class Quick : public SortingAlgorithm {
    template <class T>
    static int partition(T *data, index_t START, index_t END, predicate_t<T> predicate) {
        index_t pi = START;

        // Grow a region of elements strictly smaller than the pivot element,
        // placing the last element where the pivot should be.
        for (index_t li = pi + 1; li < END; li++) {
            if (data[li] < data[START]) {
                std::swap(data[li], data[++pi]);
            }
        }

        // Swap the last element with the pivot
        std::swap(data[START], data[pi]);
        return pi;
    }

    template <class T>
    static void divide(T *data, index_t START, index_t END, predicate_t<T> predicate) {
        if (END - START <= 1) return;

        index_t pi = START + rand() % (END - START);
        std::swap(data[START], data[pi]);
        pi = partition(data, START, END, predicate);

        divide(data, START, pi, predicate);
        divide(data, pi, END, predicate);
    }

public:
    // In-place
    template <class T>
    static void sort(T *data, size_t SIZE, predicate_t<T> predicate = predicate_lt<T>) {
        divide(data, 0, SIZE, predicate);
    }
};
