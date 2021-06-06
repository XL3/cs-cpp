#pragma once
#include <array>
#include <functional>

using index_t = unsigned long;

template <class T>
class Selection {
  using predicate_t = std::function<bool(T, T)>;

public:
  // In-place
  static void sort(
    T *data,
    size_t SIZE,
    predicate_t predicate = [](T a, T b) { return a < b; }) {
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
