#pragma once
#include <array>
#include <functional>
#include <vector>
#include <stddef.h>

class Counting {
    using index_t = unsigned long;

    template <class T>
    static std::vector<T> build_cdf(T *data, size_t SIZE) {
        T max_item = data[0];
        for (index_t i = 1; i < SIZE; i++) {
            if (data[i] > max_item) max_item = data[i];
        }

        std::vector<T> cdf(max_item + 1, 0);
        for (index_t i = 0; i < SIZE; i++) cdf[data[i]]++;
        for (index_t i = 1; i < cdf.size(); i++) {
            cdf[i] += cdf[i - 1];
        }

        return cdf;
    }

public:
    // Out-of-place
    template <class T>
    static void sort(T *data, size_t SIZE) {
        auto cdf = build_cdf(data, SIZE);
        std::vector<T> sorted(SIZE, 0);

        for (index_t i = SIZE - 1; i + 1 > 0; i--) {
            sorted[--cdf[data[i]]] = data[i];
        }

        std::copy(sorted.begin(), sorted.end(), data);
    }
};
