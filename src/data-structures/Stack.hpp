#pragma once
#include <array>

template <class T = int, int _Cap = 1 << 10>
class Stack {
  std::array<T, _Cap> data;
  int top;

public:
  Stack() {
    top = -1;
  }

  T& peek() const {
    if (top < 0) throw "Tried to peek an empty stack";
    return data[top];
  }

  void push(T item) {
    if (top + 1 == _Cap) throw "Tried to push into a full stack";
    data[++top] = item;
  }

  T pop() {
    if (top < 0) throw "Tried to pop from an empty stack";
    return data[top--];
  }

  bool empty() {
    return top < 0;
  }
};