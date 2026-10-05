#include "node.h"

#include <gtest/gtest.h>

#include <vector>

using std::vector;

namespace {

constexpr int kMaxChildren = 5;

void check(const Node& node,
           bool expectLeaf,
           int expectValueCount,
           int expectChildCount,
           const vector<int>& expectExistingValues,
           const vector<int>& expectNonExistingValues) {
  EXPECT_EQ(node.leaf(), expectLeaf);
  EXPECT_EQ(node.keysCount(), expectValueCount);
  EXPECT_EQ(node.childrenCount(), expectChildCount);

  for (int val : expectExistingValues) {
    EXPECT_TRUE(node.contains(val));
  }

  for (int val : expectNonExistingValues) {
    EXPECT_FALSE(node.contains(val));
  }
}

}  // namespace

TEST(NodeTest, EmptyLeaf) {
  Node node(true);
  check(node, true, 0, 0, {}, {});
}

TEST(NodeTest, Leaf) {
  Node node(true);
  EXPECT_EQ(node.add(1), std::nullopt);
  check(node, true, 1, 0, {1}, {2});
}

TEST(NodeTest, LeafWithDuplicate) {
  Node node(true);
  EXPECT_EQ(node.add(1), std::nullopt);
  EXPECT_EQ(node.add(1), std::nullopt);
  check(node, true, 2, 0, {1, 1}, {2});
}

TEST(NodeTest, UnderflownLeaf) {
  Node node(true);
  vector<int> values = {1, 2, 3, 4, 5};
  for (int v : values) {
    EXPECT_EQ(node.add(v), std::nullopt);
  }
  check(node, true, values.size(), 0, values, {6});
}

TEST(NodeTest, OverflownLeaf) {
  Node node(true);
  vector<int> values = {1, 2, 3, 4, 5};
  for (int v : values) {
    EXPECT_EQ(node.add(v), std::nullopt);
  }
  check(node, true, values.size(), 0, values, {6});

  auto res = node.add(6);
  EXPECT_NE(res, std::nullopt);
  auto entry = *res;

  EXPECT_EQ(entry.value, 4);

  const Node* left = &node;
  check(*left, true, 3, 0, {1, 2, 3}, {4});

  const Node* right = entry.child;
  EXPECT_NE(right, nullptr);
  check(*right, true, 3, 0, {4, 5, 6}, {3});
}
