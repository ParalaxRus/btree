#include "btree.h"

#include <gtest/gtest.h>

#include <vector>

#include "btree.h"
#include "serializer.h"

using std::vector;

namespace {

constexpr int kMaxChildren = 5;

void check(const BPlusTree& tree, const vector<vector<int>>& expectedValues) {
  const auto actual = Serializer::bfs(tree);
  EXPECT_EQ(expectedValues, actual);
}

}  // namespace

TEST(BTreeTests, Empty) {
  BPlusTree tree;
  check(tree, {});
}

TEST(BTreeTests, SingleValue) {
  BPlusTree tree;
  tree.add(1);
  check(tree, {{1}});
}

TEST(BTreeTests, TwoDuplicates) {
  BPlusTree tree;
  tree.add(1);
  tree.add(1);
  check(tree, {{1, 1}});
}

TEST(BTreeTests, UnderflownRoot) {
  BPlusTree tree;
  vector<int> values = {1, 2, 3, 4, 5};
  for (int v : values) {
    tree.add(v);
  }
  check(tree, {values});
}

TEST(BTreeTests, OverflownRoot) {
  BPlusTree tree;
  vector<int> values = {1, 2, 3, 4, 5, 6};
  for (int v : values) {
    tree.add(v);
  }
  check(tree, {{4}, {1, 2, 3, 4, 5, 6}});
}
