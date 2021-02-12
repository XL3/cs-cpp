#pragma once
#include <array>
#include <functional>
#include <vector>

using index_t = unsigned long;
using _Ty = int;

class Counting {
  static std::vector<_Ty> build_cdf(_Ty *data, size_t SIZE) {
    _Ty max_item = data[0];
    for (index_t i = 1; i < SIZE; i++) {
      if (data[i] > max_item) max_item = data[i];
    }

    std::vector<_Ty> cdf(max_item + 1, 0);
    for (index_t i = 0; i < SIZE; i++) cdf[data[i]]++;
    for (index_t i = 1; i < cdf.size(); i++) {
      cdf[i] += cdf[i - 1];
    }

    return cdf;
  }

public:
  // Out-of-place
  static void sort(_Ty *data, size_t SIZE) {
    auto cdf = build_cdf(data, SIZE);
    std::vector<_Ty> sorted(SIZE, 0);

    for (index_t i = SIZE - 1; i + 1 > 0; i--) {
      sorted[--cdf[data[i]]] = data[i];
    }

    std::copy(sorted.begin(), sorted.end(), data);
  }
};
