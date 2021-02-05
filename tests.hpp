#pragma once
#include <iostream>

#include "data-structures/Heap.hpp"
#include "data-structures/Queue.hpp"
#include "data-structures/Stack.hpp"

template <int __magic_number = 0>
void test_stack() {
  puts("Stack:");
  Stack<int> stack;
  for (auto x: {0, 1, 2, 3, 4})
    stack.push(x);

  int x;
  while (!stack.empty()) {
    x = stack.pop();
    std::printf("%d ", x);
  }
  puts("");
}

template <int __magic_number = 0>
void test_queue() {
  puts("Queue:");
  Queue<int, 4> queue;
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

template <int __magic_number = 0>
void test_heap() {
  puts("Heap:");

  puts("Merging..");
  BinaryHeap<int> bheap;
  for (int x = 0; x < 7; x++) {
    bheap.insert(1 << x);
  }
  BinaryHeap<int> maxheap([](int a, int b) { return a > b; });
  for (int x = 0; x < 7; x++) {
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
  for (int x = 1; x < 7; x++) {
    bheap.insert(x % 2 ? 1 << (x + 1) : 1 << (x - 1));
  }
  int print = 7;
  for (auto d: bheap.view_data()) {
    if (print-- == 0) break;
    std::printf("%d ", d);
  }
  puts("");
  for (int x = 0; x < 7; x++) {
    bheap.replace_item(1 << x, -(1 << x));
  }
  print = 7;
  for (auto d: bheap.view_data()) {
    if (print-- == 0) break;
    std::printf("%d ", d);
  }
  puts("");
}