#pragma once
#include <iostream>

template <class T>
void print_array(T *data, size_t SIZE, std::string label = "") {
    using index_t = unsigned long;

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