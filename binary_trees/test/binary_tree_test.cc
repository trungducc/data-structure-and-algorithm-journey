#include "binary_trees/binary_tree.h"
#include "gtest/gtest.h"

namespace {
using namespace td;
using namespace td::binary_tree;

TEST(BinaryTreeTest, IsBSTree) {
  BinaryNode<int>* root = nullptr;
  EXPECT_TRUE(is_bstree(root));

  //              50          true
  root = new BinaryNode<int>(50);
  EXPECT_TRUE(is_bstree(root));

  //              50
  //             /            true
  //            20
  root->left = new BinaryNode<int>(20);
  EXPECT_TRUE(is_bstree(root));

  //              50
  //             /
  //            20            true
  //           /
  //          10
  root->left->left = new BinaryNode<int>(10);
  EXPECT_TRUE(is_bstree(root));

  //              50
  //             /  \
  //            20  40        false
  //           /
  //          10
  root->right = new BinaryNode<int>(40);
  EXPECT_FALSE(is_bstree(root));

  //              50
  //             /  \
  //            20  60        true
  //           /
  //          10
  release(&root->right);
  root->right = new BinaryNode<int>(60);
  EXPECT_TRUE(is_bstree(root));

  //              50
  //             /  \
  //            20  60        false
  //           /  \
  //          10  55
  root->left->right = new BinaryNode<int>(55);
  EXPECT_FALSE(is_bstree(root));

  release(&root);
}

TEST(BinaryTreeTest, NodeCount) {
  BinaryNode<int>* root = nullptr;
  EXPECT_EQ(0, node_count(root));

  //              50          1
  root = new BinaryNode<int>(50);
  EXPECT_EQ(1, node_count(root));

  //              50
  //             /            2
  //            5
  root->left = new BinaryNode<int>(5);
  EXPECT_EQ(2, node_count(root));

  //              50
  //             /  \         3
  //            5    3
  root->right = new BinaryNode<int>(6);
  EXPECT_EQ(3, node_count(root));

  //              50
  //             /  \
  //            5    3        4
  //                /
  //               2
  root->right->left = new BinaryNode<int>(2);
  EXPECT_EQ(4, node_count(root));

  //              50
  //             /  \
  //            5    3        5
  //                / \
  //               2   2
  root->right->right = new BinaryNode<int>(2);
  EXPECT_EQ(5, node_count(root));

  //              50
  //             /  \
  //            5    3
  //           /    / \
  //          8    2   2      8
  //         /
  //        9
  //       /
  //      0
  root->left->left = new BinaryNode<int>(8);
  root->left->left->left = new BinaryNode<int>(9);
  root->left->left->left->left = new BinaryNode<int>(0);
  EXPECT_EQ(8, node_count(root));

  release(&root);
}

TEST(BinaryTreeTest, Release) {
  BinaryNode<int>* root = nullptr;
  release(&root);

  root = new BinaryNode<int>(10);
  release(&root);
  EXPECT_EQ(nullptr, root);

  root = new BinaryNode<int>(10);
  root->left = new BinaryNode<int>(8);
  root->right = new BinaryNode<int>(7);
  root->left->left = new BinaryNode<int>(4);
  root->left->right = new BinaryNode<int>(5);
  release(&root);
  EXPECT_EQ(nullptr, root);
}

TEST(BinaryTreeTest, Height) {
  BinaryNode<int>* root = nullptr;
  EXPECT_EQ(-1, height(root));

  //              50          0
  root = new BinaryNode<int>(50);
  EXPECT_EQ(0, height(root));

  //              50
  //             /            1
  //            5
  root->left = new BinaryNode<int>(5);
  EXPECT_EQ(1, height(root));

  //              50
  //             /  \         1
  //            5    3
  root->right = new BinaryNode<int>(6);
  EXPECT_EQ(1, height(root));

  //              50
  //             /  \
  //            5    3        2
  //                /
  //               2
  root->right->left = new BinaryNode<int>(2);
  EXPECT_EQ(2, height(root));

  //              50
  //             /  \
  //            5    3        2
  //                / \
  //               2   2
  root->right->right = new BinaryNode<int>(2);
  EXPECT_EQ(2, height(root));

  //              50
  //             /  \
  //            5    3
  //           /    / \
  //          8    2   2      4
  //         /
  //        9
  //       /
  //      0
  root->left->left = new BinaryNode<int>(8);
  root->left->left->left = new BinaryNode<int>(9);
  root->left->left->left->left = new BinaryNode<int>(0);
  EXPECT_EQ(4, height(root));

  release(&root);
}

}  // namespace
