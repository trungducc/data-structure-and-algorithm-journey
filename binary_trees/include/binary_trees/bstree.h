#pragma once

#include "binary_tree.h"

namespace td {
namespace bstree {

// Private
namespace detail {

// Return pointer points to node with minimum value in tree.
template <typename DataType>
BinaryNode<DataType>** min_node(BinaryNode<DataType>** node) {
  if (!*node) {
    throw std::invalid_argument("Cannot find minimum from nullptr");
  }

  if ((*node)->left) {
    return min_node(&(*node)->left);
  } else {
    return node;
  }
}

// Return pointer points to node with maximum value in tree.
template <typename DataType>
BinaryNode<DataType>** max_node(BinaryNode<DataType>** node) {
  if (!*node) {
    throw std::invalid_argument("Cannot find maximum from nullptr");
  }

  if ((*node)->right) {
    return max_node(&(*node)->right);
  } else {
    return node;
  }
}

// Return node which has same data as given data. Return nullptr if node can't
// be found.
template <typename DataType>
BinaryNode<DataType>* node_with_data(BinaryNode<DataType>* node,
                                     const DataType& data) {
  if (!node || data == node->data) {
    return node;
  }

  return data < node->data ? node_with_data(node->left, data)
                           : node_with_data(node->right, data);
}

// Used to get array of data which are equal or greater than |lower_bound| and
// equal or less than |upper_bound|
template <typename DataType>
void data_in_range(BinaryNode<DataType>* node,
                   std::vector<DataType>& v,
                   const DataType& lower_bound,
                   const DataType& upper_bound) {
  if (!node) {
    return;
  }

  if (node->data > lower_bound) {
    data_in_range(node->left, v, lower_bound, upper_bound);
  }

  if (lower_bound <= node->data && node->data <= upper_bound) {
    v.push_back(node->data);
  }

  if (node->data < upper_bound) {
    data_in_range(node->right, v, lower_bound, upper_bound);
  }
}

}  // namespace detail

// Return the minimum value stored in the tree whose root is given node.
template <typename DataType>
DataType min(BinaryNode<DataType>* node) {
  return (*detail::min_node(&node))->data;
}

// Return the maximum value stored in the tree whose root is given node.
template <typename DataType>
DataType max(BinaryNode<DataType>* node) {
  return (*detail::max_node(&node))->data;
}

// Used to get next value in inorder traversal of the tree.
template <typename DataType>
void inorder_successor(BinaryNode<DataType>* node,
                       const DataType& data,
                       DataType& successor) {
  if (!node) {
    return;
  }

  BinaryNode<DataType>* curr_node = detail::node_with_data(node, data);
  if (!curr_node) {
    return;
  }

  if (curr_node->right) {
    successor = (*detail::min_node(&curr_node->right))->data;
    return;
  }

  BinaryNode<DataType>* ancestor_node = node;

  while (ancestor_node->data != curr_node->data) {
    if (ancestor_node->data > data) {
      successor = ancestor_node->data;
      ancestor_node = ancestor_node->left;
    } else {
      ancestor_node = ancestor_node->right;
    }
  }
}

// Return |true| if the tree whose root is given node contains given data.
// Otherwise, return |false|.
template <typename DataType>
bool contain(BinaryNode<DataType>* node, const DataType& data) {
  return detail::node_with_data(node, data) != nullptr;
}

// Insert the given data into tree whose root is given node.
template <typename DataType>
void insert(BinaryNode<DataType>** node, const DataType& data) {
  BinaryNode<DataType>* new_node = new BinaryNode<DataType>(data);

  if (!*node) {
    *node = new_node;
    return;
  }

  if (data < (*node)->data) {
    insert(&(*node)->left, data);
  } else {
    insert(&(*node)->right, data);
  }
}

// Remove the given data from tree whose root is given node.
template <typename DataType>
void remove(BinaryNode<DataType>** node, const DataType& data) {
  if (!*node) {
    return;
  }

  if ((*node)->data != data) {
    remove(data < (*node)->data ? &(*node)->left : &(*node)->right, data);
    return;
  }

  BinaryNode<DataType>* removed_node = *node;

  if (removed_node->left && removed_node->right) {
    BinaryNode<DataType>** right_child_min_node =
        detail::min_node(&removed_node->right);
    removed_node->data = (*right_child_min_node)->data;
    (*right_child_min_node)->data = data;

    removed_node = *right_child_min_node;
    *right_child_min_node = nullptr;
  } else if (!removed_node->left) {
    *node = removed_node->right;
  } else {
    *node = removed_node->left;
  }

  delete removed_node;
}

// Return array of data which are equal or greater than |lower_bound|
// and equal or less than |upper_bound|
template <typename DataType>
std::vector<DataType> data_in_range(BinaryNode<DataType>* node,
                                    const DataType& lower_bound,
                                    const DataType& upper_bound) {
  std::vector<DataType> result;
  detail::data_in_range(node, result, lower_bound, upper_bound);
  return result;
}

}  // namespace bstree
}  // namespace td
