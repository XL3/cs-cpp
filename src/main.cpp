#pragma warning(disable : 4267)
#include <iostream>

#include "sorting/Bubble.hpp"
#include "sorting/Counting.hpp"
#include "sorting/Heap.hpp"
#include "sorting/Insertion.hpp"
#include "sorting/Merge.hpp"
#include "sorting/Quick.hpp"
#include "sorting/Selection.hpp"
#include "sorting/SortingAlgorithm.hpp"
#include "data-structures/BST.hpp"
#include "tests.hpp"

int main(int, char**) {
    try {
        test_stack();
        test_queue();
        test_heap();
        test_sort<Insertion>();
        test_sort<Selection>();
        test_sort<Bubble>();
        test_sort<Heap>();
        test_sort<Counting>();
        test_sort<Merge>();
        test_sort<Quick>();
        test_BST();
        test_binary_search();

    } catch (const char* errmsg) {
        std::cerr << errmsg << std::endl;
    }
    return 0;
}