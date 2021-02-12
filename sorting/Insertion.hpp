#pragma once
#include <array>
#include <functional>

using index_t = unsigned long;

template <class _Ty>
class Insertion {
  using predicate_t = std::function<bool(_Ty, _Ty)>;

public:
  // In-place
  static void sort(
    _Ty *data,
    size_t SIZE,
    predicate_t predicate = [](_Ty a, _Ty b) { return a < b; }) {
    for (index_t i = 1; i < SIZE; i++) {
      _Ty item = data[i];
      index_t j = i;

      for (; j > 0; j--) {
        if (predicate(item, data[j - 1])) {
          data[j] = data[j - 1];
        }
        else {
          break;
        }
      }
      data[j] = item;
    }
  }
};
