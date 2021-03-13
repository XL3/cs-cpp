#pragma once
#include <array>
#include <functional>
#include <vector>
#include <cstdlib>

using index_t = unsigned long;

template <class _Ty>
class Quick {
  using predicate_t = std::function<bool(_Ty, _Ty)>;

  static int partition(_Ty *data, index_t START, index_t END, predicate_t predicate) {
    index_t pi = START;

    // Grow a region of elements strictly smaller than the pivot element,
    // placing the last element where the pivot should be.
    for (index_t li = pi+1; li < END; li++) {
      if (data[li] < data[START]) {
        std::swap(data[li], data[++pi]);
      }
    }

    // Swap the last element with the pivot
    std::swap(data[START], data[pi]);
    return pi;
  }

  static void divide(_Ty *data, index_t START, index_t END, predicate_t predicate) {
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
    _Ty *data, size_t SIZE, predicate_t predicate = [](_Ty a, _Ty b) { return a < b; }) {
    divide(data, 0, SIZE, predicate);
  }
};
