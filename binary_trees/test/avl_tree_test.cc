#include "binary_trees/avl_tree.h"
#include "gtest/gtest.h"

namespace {
using namespace td;
using namespace td::avl_tree;
using namespace td::binary_tree;

TEST(AVLTreeTest, Insert) {
  AVLNode<int>* root = nullptr;

  //              12
  insert(&root, 12);
  EXPECT_EQ(std::vector<int>({12}), levelorder_traversal(root));

  //              12
  //                \
  //                 20
  insert(&root, 20);
  EXPECT_EQ(std::vector<int>({12, 20}), levelorder_traversal(root));

  //              12
  //             /  \
  //            8    20
  insert(&root, 8);
  EXPECT_EQ(std::vector<int>({12, 8, 20}), levelorder_traversal(root));

  //              12
  //             /  \
  //            8    20
  //                   \
  //                    30
  insert(&root, 30);
  EXPECT_EQ(std::vector<int>({12, 8, 20, 30}), levelorder_traversal(root));

  //              12
  //             /  \
  //            8    25
  //                /  \
  //               20   30
  insert(&root, 25);
  EXPECT_EQ(std::vector<int>({12, 8, 25, 20, 30}), levelorder_traversal(root));

  //              25
  //             /  \
  //            12   30
  //           /  \    \
  //          8    20   40
  insert(&root, 40);
  EXPECT_EQ(std::vector<int>({25, 12, 30, 8, 20, 40}),
            levelorder_traversal(root));

  //              25
  //             /  \
  //            12   30
  //           /  \    \
  //          8    20   40
  //         /
  //        4
  insert(&root, 4);
  EXPECT_EQ(std::vector<int>({25, 12, 30, 8, 20, 40, 4}),
            levelorder_traversal(root));

  //              25
  //             /  \
  //            12   30
  //           /  \    \
  //          6    20   40
  //         / \
  //        4   8
  insert(&root, 6);
  EXPECT_EQ(std::vector<int>({25, 12, 30, 6, 20, 40, 4, 8}),
            levelorder_traversal(root));

  //              25
  //             /  \
  //            6    30
  //           / \     \
  //          4   12    40
  //         /   /  \
  //        2   8   20
  insert(&root, 2);
  EXPECT_EQ(std::vector<int>({25, 6, 30, 4, 12, 40, 2, 8, 20}),
            levelorder_traversal(root));

  //               25
  //             /   \
  //            6     40
  //           / \    / \
  //          4   12 30 50
  //         /   /  \
  //        2   8   20
  insert(&root, 50);
  EXPECT_EQ(std::vector<int>({25, 6, 40, 4, 12, 30, 50, 2, 8, 20}),
            levelorder_traversal(root));

  release(&root);
}

TEST(AVLTreeTest, Remove) {
  AVLNode<int>* root = nullptr;

  //              25
  //             /  \
  //            6    30
  //           / \     \
  //          4   12    40
  //         /   /  \
  //        2   8   20
  insert(&root, 12);
  insert(&root, 20);
  insert(&root, 8);
  insert(&root, 30);
  insert(&root, 25);
  insert(&root, 40);
  insert(&root, 4);
  insert(&root, 6);
  insert(&root, 2);

  remove(&root, 7);

  //              6
  //             / \
  //            4   25
  //           /   /  \
  //          2   12   30
  //             /  \
  //            8   20
  remove(&root, 40);
  EXPECT_EQ(std::vector<int>({6, 4, 25, 2, 12, 30, 8, 20}),
            levelorder_traversal(root));

  //              12
  //             /  \
  //            6    25
  //           / \   / \
  //          2   8 20  30
  remove(&root, 4);
  EXPECT_EQ(std::vector<int>({12, 6, 25, 2, 8, 20, 30}),
            levelorder_traversal(root));

  //              12
  //             /  \
  //            6    25
  //           / \   / \
  //          2   8 20  30
  //                     \
  //                     40
  insert(&root, 40);

  //              12
  //             /  \
  //            6    30
  //           / \   / \
  //          2   8 25  40
  remove(&root, 20);
  EXPECT_EQ(std::vector<int>({12, 6, 30, 2, 8, 25, 40}),
            levelorder_traversal(root));

  //              12
  //             /  \
  //            6    30
  //           / \   / \
  //          2   8 25  40
  //           \
  //            4
  insert(&root, 4);

  //              12
  //             /  \
  //            4    30
  //           / \   / \
  //          2   6 25  40
  remove(&root, 8);
  EXPECT_EQ(std::vector<int>({12, 4, 30, 2, 6, 25, 40}),
            levelorder_traversal(root));
}

}  // namespace
