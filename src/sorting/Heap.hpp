#pragma once
#include <array>
#include <functional>

using index_t = unsigned long;

template <class T>
class Heap {
  using predicate_t = std::function<bool(T, T)>;

private:
  static void reheap_down(T *data, int node, int size, predicate_t predicate) {
    auto parent = [](int i) {
      return i > 0 ? (i - 1) / 2 : 0;
    };

    auto lchild = [](int i) {
      return (2 * i) + 1;
    };

    auto rchild = [](int i) {
      return (2 * i) + 2;
    };

    while (lchild(node) < size) {
      int l_node = lchild(node);
      int r_node = rchild(node) < size ? rchild(node) : l_node;

      // Swap with the child which satisfies the predicate
      // Reverse predicate to reverse heap
      // and extract the last item from the top of the heap
      l_node = !predicate(data[r_node], data[l_node]) ? r_node : l_node;
      if (!predicate(data[node], data[l_node])) return;

      std::swap(data[node], data[l_node]);
      node = l_node;
    }
  }

public:
  // In-place
  static void sort(
    T *data, size_t SIZE, predicate_t predicate = [](T a, T b) { return a < b; }) {
    for (index_t i = SIZE / 2 - 1; i + 1 > 0; i--) {
      reheap_down(data, i, SIZE, predicate);
    }

    size_t size = SIZE;
    while (size--) {
      std::swap(data[0], data[size]);
      reheap_down(data, 0, size, predicate);
    }
  }
};
