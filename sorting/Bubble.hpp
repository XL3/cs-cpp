#pragma once
#include <array>
#include <functional>

using index_t = unsigned long;

template <class _Ty>
class Bubble {
  using predicate_t = std::function<bool(_Ty, _Ty)>;

public:
  // In-place
  static void sort(
    _Ty *data,
    size_t SIZE,
    predicate_t predicate = [](_Ty a, _Ty b) { return a < b; }) {
    for (index_t i = 0; i < SIZE - 1; i++) {
      for (index_t j = i + 1; j < SIZE; j++) {
        if (predicate(data[j], data[i])) {
          std::swap(data[j], data[i]);
        }
      }
    }
  }
};
