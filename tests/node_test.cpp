#include "node.h"

#include <gtest/gtest.h>

#include <vector>

#include "serializer.h"

using std::vector;

namespace {

constexpr int kMaxChildren = 5;

void check(const Node& node,
           bool expectLeaf,
           const vector<vector<int>>& expectedValues) {
  EXPECT_EQ(node.leaf(), expectLeaf);
  const auto actual = Serializer::bfs(&node);
  EXPECT_EQ(expectedValues, actual);
}

}  // namespace

TEST(NodeTest, EmptyLeaf) {
  Node node(true);
  check(node, true, {{}});
}

TEST(NodeTest, Leaf) {
  Node node(true);
  EXPECT_EQ(node.add(1), std::nullopt);
  check(node, true, {{1}});
}

TEST(NodeTest, LeafWithDuplicate) {
  Node node(true);
  EXPECT_EQ(node.add(1), std::nullopt);
  EXPECT_EQ(node.add(1), std::nullopt);
  check(node, true, {{1, 1}});
}

TEST(NodeTest, UnderflownLeaf) {
  Node node(true);
  vector<int> values = {1, 2, 3, 4, 5};
  for (int v : values) {
    EXPECT_EQ(node.add(v), std::nullopt);
  }
  check(node, true, {values});
}

TEST(NodeTest, OverflownLeaf) {
  Node node(true);
  vector<int> values = {1, 2, 3, 4, 5};
  for (int v : values) {
    EXPECT_EQ(node.add(v), std::nullopt);
  }
  check(node, true, {values});

  auto res = node.add(6);
  EXPECT_NE(res, std::nullopt);

  auto newRoot = *res;
  EXPECT_EQ(newRoot.value, 4);

  check(*newRoot.child, false, {{4}, {1, 2, 3, 4, 5, 6}});

  const Node* left = &node;
  check(*left, true, {{1, 2, 3}});

  const Node* right = newRoot.child;
  EXPECT_NE(right, nullptr);
  check(*right, true, {{4, 5, 6}});
}
