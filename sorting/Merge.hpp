#pragma once
#include <array>
#include <functional>
#include <vector>

using index_t = unsigned long;

template <class _Ty>
class Merge {
  using predicate_t = std::function<bool(_Ty, _Ty)>;

  static void merge(_Ty *data, index_t START, index_t MID, index_t END, predicate_t predicate, std::vector<_Ty> &merge_array) {
    std::copy(data + START, data + END, merge_array.begin() + START);
    index_t left_index = START;
    index_t right_index = MID;

    for (index_t i = START; i < END; i++) {
      if (predicate(merge_array[left_index], merge_array[right_index])) {
        data[i] = merge_array[left_index++];
        if (left_index == MID) {
          std::copy(merge_array.begin() + right_index, merge_array.begin() + END, data + i + 1);
          break;
        }
      }

      else {
        data[i] = merge_array[right_index++];
        if (right_index == END) {
          std::copy(merge_array.begin() + left_index, merge_array.begin() + MID, data + i + 1);
          break;
        }
      }
    }
  }

  static void split(_Ty *data, index_t START, index_t END, predicate_t predicate, std::vector<_Ty> &merge_array) {
    if (END - START <= 1) return;

    const index_t MID = START + (END - START) / 2;
    split(data, START, MID, predicate, merge_array);
    split(data, MID, END, predicate, merge_array);

    merge(data, START, MID, END, predicate, merge_array);
  }

public:
  // In-place
  static void sort(
    _Ty *data, size_t SIZE, predicate_t predicate = [](_Ty a, _Ty b) { return a < b; }) {
    std::vector<_Ty> merge_array(SIZE);
    split(data, 0, SIZE, predicate, merge_array);
  }
};
