#pragma once
#include <array>
#include <cstdlib>
#include <functional>
#include <vector>

using index_t = unsigned long;

template <class T>
class Quick {
    using predicate_t = std::function<bool(T, T)>;

    static int partition(T *data, index_t START, index_t END, predicate_t predicate) {
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

    static void divide(T *data, index_t START, index_t END, predicate_t predicate) {
        if (END - START <= 1) return;

        index_t pi = START + rand() % (END - START);
        std::swap(data[START], data[pi]);
        pi = partition(data, START, END, predicate);

        divide(data, START, pi, predicate);
        divide(data, pi, END, predicate);
    }

public:
    // In-place
    static void sort(
        T *data, size_t SIZE, predicate_t predicate = [](T a, T b) { return a < b; }) {
        divide(data, 0, SIZE, predicate);
    }
};
