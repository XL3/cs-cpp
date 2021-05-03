#pragma once
#include <functional>

namespace Binary_Search {
/**
 * Finds the last element satisifying the predicate in a sorted sequence
 * @return Where the element should be placed to keep the sequence sorted
 */
template <class _Ty = int>
int find_last(_Ty* data, std::function<bool(_Ty)> predicate, int START, int END) {
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
 * Finds the first element satisifying the predicate in a sorted sequence
 * @return Where the element should be placed to keep the sequence sorted
 */
template <class _Ty = int>
int find_first(_Ty* data, std::function<bool(_Ty)> predicate, int START, int END) {
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