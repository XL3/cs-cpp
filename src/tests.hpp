#pragma once

#if defined(__GNUC__) || defined(__GNUG__)
#include <cxxabi.h>
#define TYPE_NAME(var) (abi::__cxa_demangle(typeid(var).name(), NULL, NULL, NULL))
#else
#define TYPE_NAME(var) (typeid(var).name())
#endif

#include <algorithm>
#include <iostream>
#include <string>

#include "algorithms/Binary_Search.hpp"
#include "data-structures/BST.hpp"
#include "data-structures/Heap.hpp"
#include "data-structures/Queue.hpp"
#include "data-structures/Stack.hpp"

using index_t = unsigned long;

template <class T>
void print_array(T *data, size_t SIZE, std::string label = "") {
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

template <size_t _Size = 4>
void test_queue() {
    puts("Queue:");
    Queue<int> queue;
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
    Binary_Heap<int> bheap;
    for (int x = 0; x < _Size; x++) {
        bheap.insert_item(1 << x);
    }
    Binary_Heap<int> maxheap([](int a, int b) { return a > b; });
    for (int x = 0; x < _Size; x++) {
        maxheap.insert_item(-(1 << x));
    }

    bheap.merge(maxheap);
    while (!bheap.empty()) {
        int x = bheap.extract_top();
        std::printf("%d ", x);
    }
    puts("");

    puts("Replacing..");
    bheap.insert_item(1);
    for (int x = 1; x < _Size; x++) {
        bheap.insert_item(x % 2 ? 1 << (x + 1) : 1 << (x - 1));
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

template <size_t _Size = 15>
void test_BST() {
    BST<int> tree;
    for (auto x: {128, 8, 2048, 2, 32, 1, 4, 16, 64, 512, 8192, 256, 1024, 4096, 16384}) {
        tree.insert_item(x);
    }

    int sorted[_Size];

    auto itr = sorted;
    tree.root->inorder([&](int x) {
        *(itr++) = x;
    });
    print_array(sorted, _Size, "BST");

    tree.delete_item(8);

    itr = sorted;
    tree.root->inorder([&](int x) {
        *(itr++) = x;
    });
    print_array(sorted, _Size - 1, "delete(8)");
}

template <size_t _Size = 15>
void test_binary_search() {
    std::array<int, _Size> data;
    for (int i = 0; i < _Size; i++) {
        data[i] = 1 << i;
    }

    std::function<bool(int)> flast = [](int x) { return x <= 4; };
    std::function<bool(int)> ffirst = [](int x) { return x > 4; };

    int last = Binary_Search::find_last(&data[0], flast, 0, _Size);
    int first = Binary_Search::find_first(&data[0], ffirst, 0, _Size);

    std::printf("Binary_Search:\nlast <= 4 [%d] first > 4 [%d]\n", data[last], data[first]);
    print_array(&data[0], _Size);
}
