#pragma once
#include <array>
#include <functional>

#include "Binary_Tree.hpp"

template <class _Ty = int, int _Cap = 1 << 10>
class BST {
  using predicate_t = std::function<bool(_Ty, _Ty)>;
  using Node = BT_Node<_Ty>*;

  // Total number of elements currently in the binary search tree
  int size;

  // Predicate according to which the binary search tree will be ordered
  const predicate_t predicate;

  Node find_successor(Node node) {
    // Minimum of right subtree
    Node successor = node->right;
    Node minimum = node->right;
    while (minimum) {
      successor = minimum;
      minimum = minimum->left;
    }

    if (successor != nullptr) return successor;

    // First parent of a left child
    Node child = node;
    successor = node;
    while (successor) {
      if (successor->left == child) return successor;
      successor = child->parent;
      child = successor;
    }

    return nullptr;
  }

protected:
  virtual int fixup_insert() { return -1; };
  virtual int fixup_delete() { return -1; };

public:
  Node root;
  BST(predicate_t _predicate = [](_Ty a, _Ty b) { return a < b; }) : predicate(_predicate) {
    size = 0;
    root = nullptr;
  }

  void insert_item(_Ty item) {
    if (size == _Cap) throw "Tried to insert into a full heap";
    if (!root) {
      root = new BT_Node<_Ty>{item};
      return;
    }

    Node parent;
    Node child = root;
    while (child) {
      parent = child;
      child = predicate(item, parent->item) ? parent->left : parent->right;
    }

    parent->insert_child(item, predicate(item, parent->item));
    size++;
  }

  Node find_item(_Ty item) {
    Node parent;
    Node child = root;
    while (child) {
      if (child->item == item) return child;
      parent = child;
      child = predicate(item, parent->item) ? parent->left : parent->right;
    }

    return nullptr;
  }

  void delete_item(_Ty item) {
    Node node = find_item(item);
    if (node == nullptr) return;

    Node successor = find_successor(node);
    while (successor) {
      node->item = successor->item;
      node = successor;
      successor = find_successor(node);
    }

    Node& parent_handle = node->parent->left == node ? node->parent->left : node->parent->right;
    parent_handle = node->left;
  }

  bool empty() {
    return root == nullptr;
  }
};