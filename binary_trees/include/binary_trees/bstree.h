


  #pragma once

#include "binary_tree.h"
#include "utils/macros.h"

namespace td {

// Binary search tree template
template <typename DataType>
class BSTree {
 public:
  BSTree() = default;
  ~BSTree();

  // Return number of nodes in tree
  std::size_t count();

  // Return height of tree.
  std::size_t height();

  // Insert the given data into tree
  void insert(const DataType& data);

  // Remove the given data from tree if it exists.
  void remove(const DataType& data);

  // Return |true| if tree contains given data. Otherwise, return |false|.
  bool contain(const DataType& data);

  // Return the minimum value stored in the tree (leftmost value).
  DataType min();

  // Return the maximum value stored in the tree (rightmost value).
  DataType max();

  // Return array of data which are equal or greater than |lower_bound|
  // and equal or less than |upper_bound|
  std::vector<DataType> data_in_range(const DataType& lower_bound,
                                      const DataType& upper_bound);

  // Revert tree to initialization state
  void reset();

 private:
  // Binary search tree's root node
  BinaryNode<DataType>* root_{nullptr};

  // Insert the given data into tree whose root is given node.
  void insert(BinaryNode<DataType>* node, const DataType& data);

  // Return |true| if the tree whose root is given node contains given data.
  // Otherwise, return |false|.
  bool contain(BinaryNode<DataType>* node, const DataType& data);

  DISALLOW_COPY_AND_ASSIGN(BSTree);
};

}  // namespace td

/****************  BSTree implementation ****************/
namespace td {

// Public
template <typename DataType>
~BSTree<DataType>::BSTree() {
  if (root_)
    delete root_;
}

template <typename DataType>
std::size_t BSTree<DataType>::count() {
  return binary_tree::node_count(root_);
}

template <typename DataType>
std::size_t BSTree<DataType>::height() {
  return binary_tree::height(root_);
}

template <typename DataType>
void BSTree<DataType>::insert(const DataType& data) {
  if (!root_) {
    root_ = new BinaryNode<DataType>(data);
  } else {
    insert(root_, data);
  }
}

// void remove(const DataType& data);

template <typename DataType>
bool BSTree<DataType>::contain(const DataType& data) {
  return contain(root_, data);
}

// DataType min();

// DataType max();

// std::vector<DataType> data_in_range(const DataType& lower_bound,
//                                     const DataType& upper_bound);

template <typename DataType>
void BSTree<DataType>::reset() {
  binary_tree::release(&root_);
}

// Private
template <typename DataType>
void insert(BinaryNode<DataType>* node, const DataType& data) {
  // TODO: Check null

  if (data < node->data) {
    if (node->left) {
      insert(node->left, data);
    } else {
      node->left = new BinaryNode<DataType>(data);
    }
  } else {
    if (node->right) {
      insert(node->right, data);
    } else {
      node->right = new BinaryNode<DataType>(data);
    }
  }
}

template <typename DataType>
bool contain(BinaryNode<DataType>* node, const DataType& data) {
  if (!node) {
    return false;
  }
  return data < node->data ? contain(node->left, data)
                           : contain(node->right, data);
}

}  // namespace td

