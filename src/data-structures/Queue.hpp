#pragma once
#include <array>

template <class T = int, int _Cap = 1 << 10>
class Queue {
    std::array<T, _Cap> data;

    // Position of the next item to be dequeued
    int front;

    // Position of the next item to be enqueued
    int back;

public:
    Queue() {
        front = -1;
        back = 0;
    }

    T& peek_front() const {
        if (front < 0) throw "Tried to peek an empty queue";
        return data[front];
    }

    void enqueue(T item) {
        if (back == front) throw "Tried to enqueue into a full queue";
        if (front < 0) front = back;
        data[back++] = item;
        back %= _Cap;
    }

    T dequeue() {
        if (front < 0) throw "Tried to dequeue from an empty queue";
        T item = data[front++];
        front %= _Cap;

        // If the queue has been emptied
        // Reset it to its initial state
        if (front == back) {
            front = -1;
            back = 0;
        }

        return item;
    }

    bool empty() {
        return front < 0;
    }
};