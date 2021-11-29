#pragma once
#include <functional>

namespace Binary_Search {
/**
 * Finds the last element satisfying the predicate in a sorted sequence
 * @return Where the element should be placed to keep the sequence sorted
 */
template <class T = int>
int find_last(T* data, std::function<bool(T)> predicate, int START, int END) {
    int left, right, mid;
    left = START;
    right = END - 1;

    while (left < right) {
        // Ceil (x / y) = (x + y - 1) / y
        mid = left + (right - left + 1) / 2;

        if (predicate(data[mid])) {
            left = mid;
        }
        else {
            right = mid - 1;
        }
    }

    return left;
}

/**
 * Finds the first element satisfying the predicate in a sorted sequence
 * @return Where the element should be placed to keep the sequence sorted
 */
template <class T = int>
int find_first(T* data, std::function<bool(T)> predicate, int START, int END) {
    int left, right, mid;
    left = START;
    right = END - 1;

    while (left < right) {
        // Floor (x / y) = x / y
        mid = left + (right - left) / 2;

        if (predicate(data[mid])) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    return left;
}
}  // namespace Binary_Search