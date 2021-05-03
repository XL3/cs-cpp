#pragma once

// Binary tree implementation using pointers
template <class _Ty>
struct BT_Node {
  _Ty item;
  BT_Node* left;
  BT_Node* right;
  BT_Node* parent;

  void insert_child(_Ty item, bool _left) {
    BT_Node* new_node = new BT_Node{item};
    if (_left)
      left = new_node;
    else
      right = new_node;

    new_node->parent = this;
  }

  template <typename _F>
  void inorder(_F func) {
    if (left != nullptr)
      left->inorder(func);

    func(item);

    if (right != nullptr)
      right->inorder(func);
  }

  template <typename _F>
  void preorder(_F func) {
    func(item);

    if (left != nullptr)
      left->inorder(func);

    if (right != nullptr)
      right->inorder(func);
  }

  template <typename _F>
  void postorder(_F func) {
    if (left != nullptr)
      left->inorder(func);

    if (right != nullptr)
      right->inorder(func);

    func(item);
  }
};

// Contains utility functions for array-based Binary Tree implementations
template <class _Ty>
class BT_Array {
protected:
  static int parent(int i) {
    return i > 0 ? (i - 1) / 2 : 0;
  }

  static int lchild(int i) {
    return (2 * i) + 1;
  }

  static int rchild(int i) {
    return (2 * i) + 2;
  }

  /**
   * Every sibling in a level = (fs+1) + c [-1, 0, 1, 2, ...]
   * First sibling = 2^(level) - 1
   */
  static int fsibling(int i) {
    i += 1;

    // Zero-based highest exponent
    int exp = 0;
    while (i >>= 1) exp++;

    return (1 << exp) - 1;
  }
};