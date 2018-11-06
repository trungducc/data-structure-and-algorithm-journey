#pragma once

#include "binary_tree.h"
#include "bstree.h"
#include "utils/utils.h"

namespace td {

// Binary node template with additional |height| property.
template <typename DataType>
class AVLNode : public BinaryNode<DataType> {
 public:
  std::size_t height{0};
};

namespace avl_tree {

// Private
namespace detail {

// Return height of AVL tree whose root is given node.
template <typename DataType>
std::size_t height(AVLNode<DataType>* node) {
  return node ? node->height : 0;
}

// Return height difference between left child and right child of given node.
template <typename DataType>
int balance_factor(AVLNode<DataType>* node) {
  return node ? height(node->left) - height(node->right) : 0;
}

// Update height of given node
template <typename DataType>
void update_height(AVLNode<DataType>* node) {
  return std::max(height(node->left), height(node->right)) + 1;
}

// Left rotate at given node
template <typename DataType>
void left_rotate(AVLNode<DataType>** p_node) {
  AVLNode<DataType>* node = *p_node;

  if (!node || !node->right) {
    return;
  }

  AVLNode<DataType>* new_root = node->right;
  *p_node = new_root;
  node->right = new_root->left;
  new_root->left = node;
}

// Right rotate at given node
template <typename DataType>
void right_rotate(AVLNode<DataType>** p_node) {
  AVLNode<DataType>* node = *p_node;

  if (!node || !node->left) {
    return;
  }

  AVLNode<DataType>* new_root = node->left;
  *p_node = new_root;
  node->left = new_root->right;
  new_root->right = node;
}

// Use to balace tree after insert or remove a node
template <typename DataType>
void balance(AVLNode<DataType>** p_node,
             const DataType& data,
             utils::Action action) {
  AVLNode<DataType>* node = *p_node;

  if (!node) {
    return;
  }

  int balance_factor = detail::balance_factor(node);

  if (balance_factor > 1) {
    if (data < node->left->data == (action == utils::Action::kRemove)) {
      detail::left_rotate(&node->left);
    }
    detail::right_rotate(p_node);
  }

  if (balance_factor < -1) {
    if (data >= node->right->data == (action == utils::Action::kInsert)) {
      detail::right_rotate(&node->right);
    }
    detail::left_rotate(p_node);
  }
}

}  // namespace detail

// Insert the given data into tree whose root is given node.
template <typename DataType>
void insert(AVLNode<DataType>** p_node, const DataType& data) {
  AVLNode<DataType>* node = *p_node;

  if (!node) {
    *p_node = new AVLNode<DataType>(data);
    return;
  }

  insert(data < node->data ? &node->left : &node->right, data);

  detail::update_height(node);
  detail::balance(p_node, data, utils::Action::kInsert);
}

// Remove the given data from tree whose root is given node.
template <typename DataType>
void remove(AVLNode<DataType>** p_node, const DataType& data) {
  AVLNode<DataType>* node = *p_node;

  if (!node) {
    return;
  }

  if (node->data != data) {
    remove(data < node->data ? &node->left : &node->right, data);
  } else {
    if (node->left && node->right) {
      AVLNode<DataType>* right_child_min_node =
          bstree::detail::min_node(node->right);
      node->data = right_child_min_node->data;
      right_child_min_node->data = data;
      remove(&node->right, data);
    } else {
      *p_node = node->left ?: node->right;
      delete node;
      node = &p_node;
    }
  }

  detail::update_height(node);
  detail::balance(p_node, data, utils::Action::kRemove);
}

}  // namespace avl_tree
}  // namespace td

