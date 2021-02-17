#pragma once

#if defined(__GNUC__) || defined(__GNUG__)
#include <cxxabi.h>
#define TYPE_NAME(var) (abi::__cxa_demangle(typeid(_SortingAlgorithm).name(), NULL, NULL, NULL))
#else
#define TYPE_NAME(var) (typeid(_SortingAlgorithm).name())
#endif

#include <algorithm>
#include <iostream>
#include <string>

#include "data-structures/Heap.hpp"
#include "data-structures/Queue.hpp"
#include "data-structures/Stack.hpp"

template <class _Ty>
void print_array(_Ty *data, size_t SIZE, std::string label = "") {
  if (!label.empty()) {
    std::cout << label << std::endl;
  }
  for (index_t i = 0; i < SIZE; i++) {
    std::cout << "\r[ ";
    std::cout << std::string(i, '\t');
    std::cout << data[i] << " ";
  }
  std::cout << "]" << std::endl;
}

template <size_t _Size = 5>
void test_stack() {
  puts("Stack:");
  Stack<int, _Size> stack;
  for (auto x: {0, 1, 2, 3, 4})
    stack.push(x);

  int x;
  while (!stack.empty()) {
    x = stack.pop();
    std::printf("%d ", x);
  }
  puts("");
}

template <size_t _Size = 4>
void test_queue() {
  puts("Queue:");
  Queue<int, _Size> queue;
  for (auto x: {0, 1, 2, 3})
    queue.enqueue(1 << x);

  queue.dequeue();
  queue.dequeue();
  queue.enqueue(1 << 4);
  queue.enqueue(1 << 5);

  int x;
  while (!queue.empty()) {
    x = queue.dequeue();
    std::printf("%d ", x);
  }
  puts("");
}

template <size_t _Size = 7>
void test_heap() {
  puts("Heap:");

  puts("Merging..");
  BinaryHeap<int> bheap;
  for (int x = 0; x < _Size; x++) {
    bheap.insert(1 << x);
  }
  BinaryHeap<int> maxheap([](int a, int b) { return a > b; });
  for (int x = 0; x < _Size; x++) {
    maxheap.insert(-(1 << x));
  }

  bheap.merge(maxheap);
  while (!bheap.empty()) {
    int x = bheap.extract_top();
    std::printf("%d ", x);
  }
  puts("");

  puts("Replacing..");
  bheap.insert(1);
  for (int x = 1; x < _Size; x++) {
    bheap.insert(x % 2 ? 1 << (x + 1) : 1 << (x - 1));
  }
  print_array(bheap.view_data(), _Size);

  for (int x = 0; x < _Size; x++) {
    bheap.replace_item(1 << x, -(1 << x));
  }
  print_array(bheap.view_data(), _Size);
}

template <class _SortingAlgorithm, size_t _Size = 16>
void test_sort() {
  std::array<int, _Size> data;
  for (int i = 0; i < _Size; i++) {
    data[i] = 1 << i;
  }
  std::random_shuffle(data.begin(), data.end());

  print_array(&data[0], _Size, TYPE_NAME(_SortingAlgorithm));
  _SortingAlgorithm::sort(&data.front(), _Size);
  print_array(&data[0], _Size);
}