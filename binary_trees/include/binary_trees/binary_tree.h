#pragma once

#include <vector>

namespace td {

// Binary node template, contains a |left| pointer, a |right| pointer, and a
// data element.
template <typename DataType>
struct BinaryNode {
  DataType data;
  BinaryNode<DataType>* left;
  BinaryNode<DataType>* right;

  BinaryNode(const DataType& d) : data(d), left(nullptr), right(nullptr) {}

  ~BinaryNode() {
    if (left)
      delete left;
    if (right)
      delete right;
  }
};

namespace binary_tree {

// Private
namespace detail {

// Use recursion to determine given node is root of binary tree or not.
// If |left_most| exists, |left_most|'s data is always equal or less than data
// of |node| and |node|'s child nodes.
// If |right_most| exists, |right_most|'s data is always equal or greater than
// data of |node| and |node|'s child nodes.
template <typename DataType>
bool is_bstree(BinaryNode<DataType>* node,
               BinaryNode<DataType>* left_most,
               BinaryNode<DataType>* right_most) {
  if (!node)
    return true;
  if (left_most && left_most->data > node->data)
    return false;
  if (right_most && right_most->data < node->data)
    return false;
  return is_bstree(node->left, left_most, node) &&
         is_bstree(node->right, node, right_most);
}

}  // namespace detail

// Return |true| if given node is root of binary tree. Otherwise, return
// |false|.
template <typename DataType>
bool is_bstree(BinaryNode<DataType>* node) {
  return detail::is_bstree(node, nullptr, nullptr);
}

// Return number of nodes in tree whose root node is given node.
template <typename DataType>
std::size_t node_count(BinaryNode<DataType>* node) {
  if (!node)
    return 0;
  return node_count(node->left) + node_count(node->right) + 1;
}

// Release nodes in tree whose root node is given node.
template <typename DataType>
void release(BinaryNode<DataType>* node) {
  delete node;
  node = nullptr;
}

// Return height of tree whose root node is given node.
template <typename DataType>
std::size_t height(BinaryNode<DataType>* node) {
  if (!node)
    return -1;
  return height(node->left) + height(node->right) + 1;
}

}  // namespace binary_tree
}  // namespace td

