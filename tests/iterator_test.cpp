#include "iterator.h"

#include <gtest/gtest.h>

#include "btree.h"
#include "node.h"
#include "serializer.h"

using std::vector;

void check(const BPlusTree& tree, const Serializer::Values& expected) {
  const auto actual = Serializer::bfs(tree);
  EXPECT_EQ(expected, actual);
}

TEST(BfsIteratorTests, Empty) {
  BPlusTree tree;
  vector<vector<int>> actual = {};
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual.push_back(it->values());
  }
  const vector<vector<int>> expected = {{}};
  EXPECT_EQ(expected, actual);
}

TEST(BfsIteratorTests, OverflownRoot) {
  BPlusTree tree;
  const vector<int> values = {1, 2, 3, 4, 5, 6};
  for (int v : values) {
    tree.add(v);
  }
  vector<vector<int>> actual = {};
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual.push_back(it->values());
  }
  const vector<vector<int>> expected = {{4}, {1, 2, 3}, {4, 5, 6}};
  EXPECT_EQ(expected, actual);
}
