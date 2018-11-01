#include "binary_trees/bstree.h"
#include "gtest/gtest.h"

namespace {
using namespace td;
using namespace td::binary_tree;
using namespace td::bstree;

TEST(BSTreeTest, Min) {
  BinaryNode<int>* root = nullptr;
  EXPECT_THROW(min(root), std::invalid_argument);

  insert(&root, 18);
  insert(&root, 20);
  EXPECT_EQ(18, min(root));

  insert(&root, 15);
  insert(&root, 30);
  insert(&root, 25);
  EXPECT_EQ(15, min(root));

  insert(&root, 40);
  EXPECT_EQ(15, min(root));

  release(&root);
}

TEST(BSTreeTest, Max) {
  BinaryNode<int>* root = nullptr;
  EXPECT_THROW(max(root), std::invalid_argument);

  insert(&root, 18);
  insert(&root, 20);
  EXPECT_EQ(20, max(root));

  insert(&root, 15);
  insert(&root, 30);
  insert(&root, 25);
  EXPECT_EQ(30, max(root));

  insert(&root, 40);
  EXPECT_EQ(40, max(root));

  release(&root);
}

TEST(BSTreeTest, InorderSuccessor) {
  BinaryNode<int>* root = nullptr;

  int successor = 0;
  inorder_successor(root, 10, successor);
  EXPECT_EQ(0, successor);

  //              12
  //             /  \
  //            8    20
  //           /    /  \
  //          6    16   30
  //         /    /    /  \
  //        2    15   25   40
  //                 /  \
  //                23  27
  insert(&root, 12);
  insert(&root, 20);
  insert(&root, 8);
  insert(&root, 30);
  insert(&root, 25);
  insert(&root, 40);
  insert(&root, 16);
  insert(&root, 15);
  insert(&root, 6);
  insert(&root, 2);
  insert(&root, 23);
  insert(&root, 27);

  inorder_successor(root, 8, successor);
  EXPECT_EQ(12, successor);

  inorder_successor(root, 30, successor);
  EXPECT_EQ(40, successor);

  inorder_successor(root, 16, successor);
  EXPECT_EQ(20, successor);

  inorder_successor(root, 27, successor);
  EXPECT_EQ(30, successor);

  release(&root);
}

TEST(BSTreeTest, Contain) {
  BinaryNode<int>* root = nullptr;
  EXPECT_FALSE(contain(root, 0));

  insert(&root, 18);
  insert(&root, 20);
  EXPECT_FALSE(contain(root, 2));
  EXPECT_TRUE(contain(root, 18));
  EXPECT_TRUE(contain(root, 20));

  insert(&root, 15);
  insert(&root, 30);
  insert(&root, 25);
  EXPECT_FALSE(contain(root, 10));
  EXPECT_TRUE(contain(root, 15));
  EXPECT_TRUE(contain(root, 30));
  EXPECT_TRUE(contain(root, 25));

  insert(&root, 40);
  EXPECT_TRUE(contain(root, 40));

  release(&root);
}

TEST(BSTreeTest, Insert) {
  BinaryNode<int>* root = nullptr;

  //              18
  //             /  \
  //            15   20
  insert(&root, 18);
  insert(&root, 20);
  insert(&root, 15);
  EXPECT_EQ(std::vector<int>({18, 15, 20}), levelorder_traversal(root));

  //              18
  //             /  \
  //            15   20
  //                   \
  //                    30
  //                    / \
  //                   25 40
  insert(&root, 30);
  insert(&root, 25);
  insert(&root, 40);
  EXPECT_EQ(std::vector<int>({18, 15, 20, 30, 25, 40}),
            levelorder_traversal(root));

  release(&root);
}

TEST(BSTreeTest, Remove) {
  BinaryNode<int>* root = nullptr;

  //              12
  //             /  \
  //            8    20
  //           /    /  \
  //          6    16   30
  //         /    /    /  \
  //        2    15   25   40
  //                 /
  //                23
  insert(&root, 12);
  insert(&root, 20);
  insert(&root, 8);
  insert(&root, 30);
  insert(&root, 25);
  insert(&root, 40);
  insert(&root, 16);
  insert(&root, 15);
  insert(&root, 6);
  insert(&root, 2);
  insert(&root, 23);

  //              12
  //             /  \
  //            8    20
  //           /    /  \
  //          6    16   30
  //              /    /  \
  //             15   25   40
  //                 /
  //                23
  remove(&root, 2);
  EXPECT_EQ(std::vector<int>({12, 8, 20, 6, 16, 30, 15, 25, 40, 23}),
            levelorder_traversal(root));

  //              12
  //             /  \
  //            8    20
  //           /    /  \
  //          6    15   30
  //                   /  \
  //                  25   40
  //                 /
  //                23
  remove(&root, 16);
  EXPECT_EQ(std::vector<int>({12, 8, 20, 6, 15, 30, 25, 40, 23}),
            levelorder_traversal(root));

  //              12
  //             /  \
  //            8    23
  //           /    /  \
  //          6    15   30
  //                   /  \
  //                  25   40
  remove(&root, 20);
  EXPECT_EQ(std::vector<int>({12, 8, 23, 6, 15, 30, 25, 40}),
            levelorder_traversal(root));

  //              15
  //             /  \
  //            8    23
  //           /       \
  //          6         30
  //                   /  \
  //                  25   40
  remove(&root, 12);
  EXPECT_EQ(std::vector<int>({15, 8, 23, 6, 30, 25, 40}),
            levelorder_traversal(root));

  release(&root);
}

TEST(BSTreeTest, DataInRange) {
  BinaryNode<int>* root = nullptr;

  //              12
  //             /  \
  //            8    20
  //           /    /  \
  //          6    16   30
  //         /    /    /  \
  //        2    15   25   40
  //                 /
  //                23
  insert(&root, 12);
  insert(&root, 20);
  insert(&root, 8);
  insert(&root, 30);
  insert(&root, 25);
  insert(&root, 40);
  insert(&root, 16);
  insert(&root, 15);
  insert(&root, 6);
  insert(&root, 2);
  insert(&root, 23);

  EXPECT_EQ(std::vector<int>({8, 12, 15, 16, 20}), data_in_range(root, 8, 20));
  EXPECT_EQ(std::vector<int>({6, 8, 12, 15, 16, 20, 23}),
            data_in_range(root, 5, 24));
  EXPECT_EQ(std::vector<int>({15, 16}), data_in_range(root, 14, 17));
  EXPECT_EQ(std::vector<int>({23, 25, 30}), data_in_range(root, 22, 30));

  release(&root);
}

}  // namespace td
