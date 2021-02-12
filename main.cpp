#include <iostream>

#include "sorting/Bubble.hpp"
#include "sorting/Counting.hpp"
#include "sorting/Heap.hpp"
#include "sorting/Insertion.hpp"
#include "sorting/Merge.hpp"
#include "sorting/Selection.hpp"
#include "tests.hpp"

int main(int, char**) {
  try {
    test_stack();
    test_queue();
    test_heap();
    test_sort<Selection<int>>();
    test_sort<Insertion<int>>();
    test_sort<Bubble<int>>();
    test_sort<Heap<int>>();
    test_sort<Merge<int>>();
    test_sort<Counting>();

  } catch (const char* errmsg) {
    std::cerr << errmsg << std::endl;
  }
  return 0;
}