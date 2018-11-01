#pragma once

#include <vector>
#include <queue>

namespace td {

// Binary node template, contains a |left| pointer, a |right| pointer, and a
// data element.
template <typename DataType>
struct BinaryNode {
  DataType data;
  BinaryNode<DataType>* left;
  BinaryNode<DataType>* right;

  BinaryNode(const DataType& d) : data(d), left(nullptr), right(nullptr) {}
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
               BinaryNode<DataType>* left_most = nullptr,
               BinaryNode<DataType>* right_most = nullptr) {
  if (!node)
    return true;
  if (left_most && left_most->data > node->data)
    return false;
  if (right_most && right_most->data < node->data)
    return false;
  return is_bstree(node->left, left_most, node) &&
         is_bstree(node->right, node, right_most);
}

// Return |std::size_t| can cause trouble with null nodes. |int| is used to
// avoid these cases.
template <typename DataType>
int height(BinaryNode<DataType>* node) {
  if (!node)
    return -1;
  return std::max(height(node->left), height(node->right)) + 1;
}

// Preorder traversal implementation using recursion
template <typename DataType>
void preorder_traversal(BinaryNode<DataType>* node, std::vector<DataType>& v) {
  if (!node)
    return;
  v.push_back(node->data);
  preorder_traversal(node->left, v);
  preorder_traversal(node->right, v);
}

// Inorder traversal implementation using recursion
template <typename DataType>
void inorder_traversal(BinaryNode<DataType>* node, std::vector<DataType>& v) {
  if (!node)
    return;
  inorder_traversal(node->left, v);
  v.push_back(node->data);
  inorder_traversal(node->right, v);
}

// Postorder traversal implementation using recursion
template <typename DataType>
void postorder_traversal(BinaryNode<DataType>* node, std::vector<DataType>& v) {
  if (!node)
    return;
  postorder_traversal(node->left, v);
  postorder_traversal(node->right, v);
  v.push_back(node->data);
}

}  // namespace detail

// Return |true| if given node is root of binary tree. Otherwise, return
// |false|.
template <typename DataType>
bool is_bstree(BinaryNode<DataType>* node) {
  return detail::is_bstree(node);
}

// Return height of tree whose root node is given node.
template <typename DataType>
int height(BinaryNode<DataType>* node) {
  return detail::height(node);
}

// Return number of nodes in tree whose root node is given node.
// Return -1 if given node is null.
template <typename DataType>
std::size_t node_count(BinaryNode<DataType>* node) {
  if (!node)
    return 0;
  return node_count(node->left) + node_count(node->right) + 1;
}

// Release nodes in tree whose root node is given node.
template <typename DataType>
void release(BinaryNode<DataType>** node) {
  if (!*node)
    return;

  release(&(*node)->left);
  release(&(*node)->right);

  delete *node;
  *node = nullptr;
}

// Level-order traversal on binary tree whose root node is given node.
template <typename DataType>
std::vector<DataType> levelorder_traversal(BinaryNode<DataType>* node) {
  std::vector<DataType> result;
  std::queue<BinaryNode<DataType>*> node_queue;

  if (node)
    node_queue.push(node);

  while (!node_queue.empty()) {
    BinaryNode<DataType>* curr_node = node_queue.front();
    result.push_back(curr_node->data);
    node_queue.pop();

    if (curr_node->left)
      node_queue.push(curr_node->left);
    if (curr_node->right)
      node_queue.push(curr_node->right);
  }

  return result;
}

// Preorder traversal on binary tree whose root node is given node.
template <typename DataType>
std::vector<DataType> preorder_traversal(BinaryNode<DataType>* node) {
  std::vector<DataType> result;
  detail::preorder_traversal(node, result);
  return result;
}

// Inorder traversal on binary tree whose root node is given node.
template <typename DataType>
std::vector<DataType> inorder_traversal(BinaryNode<DataType>* node) {
  std::vector<DataType> result;
  detail::inorder_traversal(node, result);
  return result;
}

// Postorder traversal on binary tree whose root node is given node.
template <typename DataType>
std::vector<DataType> postorder_traversal(BinaryNode<DataType>* node) {
  std::vector<DataType> result;
  detail::postorder_traversal(node, result);
  return result;
}

}  // namespace binary_tree
}  // namespace td
