#include <iostream>

#include "tests.hpp"

int main(int, char**) {
  try {
    test_stack();
    test_queue();
    test_heap();
  } catch (const char* errmsg) {
    std::cerr << errmsg << std::endl;
  }
  return 0;
}