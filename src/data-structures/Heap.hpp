#pragma once
#include <array>
#include <functional>

#include "Binary_Tree.hpp"

template <class T = int, int _Cap = 1 << 10>
class Binary_Heap : public BT_Array<> {
    using predicate_t = std::function<bool(T, T)>;
    static const inline predicate_t default_predicate = [](T a, T b) { return a < b; };

    std::array<T, _Cap> data;

    // Position of the next item to be inserted
    int size;

    // Predicate according to which the heap will be ordered
    const predicate_t predicate;

    void reheap_up(int node) {
        int p_node;
        while (node > 0) {
            p_node = parent(node);
            if (!predicate(data[node], data[p_node])) return;

            std::swap(data[node], data[p_node]);
            node = p_node;
        }
    }

    void reheap_down(int node) {
        while (lchild(node) < size) {
            int l_node = lchild(node);
            int r_node = rchild(node) < size ? rchild(node) : l_node;

            // Swap with the child which satisfies the predicate
            l_node = predicate(data[r_node], data[l_node]) ? r_node : l_node;
            if (predicate(data[node], data[l_node])) return;

            std::swap(data[node], data[l_node]);
            node = l_node;
        }
    }

    int find_item(T item) {
        int node = 0;
        while (lchild(node) < size) {
            // The item cannot exist in this level
            if (predicate(item, data[node])) break;

            int l_node = lchild(node);
            int r_node = rchild(node) < size ? rchild(node) : l_node;

            l_node = predicate(data[r_node], data[l_node]) ? r_node : l_node;
            node = l_node;
        }

        int start = fsibling(parent(node));
        if (lchild(node) >= size) node = size;

        // Find the item in the level
        for (int i = start; i < node; i++) {
            if (data[i] == item) return i;
        }

        return -1;
    }

public:
    Binary_Heap(predicate_t _predicate = default_predicate) : predicate(_predicate) {
        size = 0;
    }

    T& peek() const {
        if (size == 0) throw "Tried to peek an empty heap";
        return data[0];
    }

    void insert_item(T item) {
        if (size == _Cap) throw "Tried to insert into a full heap";
        int node = size++;
        data[node] = item;

        reheap_up(node);
    }

    T extract_top() {
        if (size == 0) throw "Tried to extract from an empty heap";
        std::swap(data[--size], data[0]);
        T item = data[size];

        reheap_down(0);

        return item;
    }

    /**
     * Merges another heap into the current heap if there's enough space
     */
    template <int _h_Cap>
    void merge(Binary_Heap<T, _h_Cap> bheap) {
        if (this->size + bheap.size > _Cap)
            throw "Tried to merge a heap with not enough available space";

        // Insert the heap into the array
        int mi = size;
        for (int i = 0; i < bheap.size; i++, mi++) {
            data[mi] = bheap.data[i];
        }
        size += bheap.size;

        // Reheap the array
        for (int i = size / 2 - 1; i >= 0; i--)
            reheap_down(i);
    }

    // increase/decrease_key
    void replace_item(T item, T replace) {
        if (size == 0) throw "Tried to replace an item inside an empty heap";
        int node = find_item(item);
        if (node < 0) return;

        data[node] = replace;

        reheap_down(node);
        reheap_up(node);
    }

    void delete_item(T item) {
        if (size == 0) throw "Tried to delete an item inside an empty heap";
        int node = find_item(item);
        if (node < 0) return;

        std::swap(data[--size], data[node]);

        reheap_down(node);
        reheap_up(node);
    }

    bool empty() {
        return size == 0;
    }

    T* view_data() {
        return &data[0];
    }
};