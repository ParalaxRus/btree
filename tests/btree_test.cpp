#include "btree.h"

#include <gtest/gtest.h>

#include <vector>

#include "btree.h"
#include "serializer.h"

using std::vector;

namespace {

void check(const BPlusTree& tree, const Serializer::Values& expected) {
  const auto actual = Serializer::bfs(tree);
  EXPECT_EQ(expected, actual);
}

template <typename T>
struct ScopedOverride {
  ScopedOverride(T& t, T val) : _trg(t), _orig(t) {
    _trg = val;
  }
  ~ScopedOverride() {
    _trg = _orig;
  }
  T& _trg;
  T _orig;
};

}  // namespace

TEST(BTreeTests, Empty) {
  BPlusTree tree;
  check(tree, {});
}

TEST(BTreeTests, SingleValue) {
  BPlusTree tree;
  tree.add(1);
  check(tree, {{{1}}});
}

TEST(BTreeTests, TwoDuplicates) {
  BPlusTree tree;
  tree.add(1);
  tree.add(1);
  check(tree, {{{1, 1}}});
}

TEST(BTreeTests, MaxCapacity) {
  BPlusTree tree;
  const vector<int> vals = {1, 2, 3, 4, 5};
  for (int v : vals) {
    tree.add(v);
  }
  check(tree, {{vals}});
}

TEST(BTreeTests, OverflownLeaf) {
  BPlusTree tree;
  const vector<int> vals = {1, 2, 3, 4, 5, 6};
  for (int v : vals) {
    tree.add(v);
  }
  check(tree, {{{4}}, {{1, 2, 3}, {4, 5, 6}}});
}

TEST(BTreeTests, OverflownInternalNode) {
  ScopedOverride guard(Node::kMaxChildren, 2);

  BPlusTree tree;
  const vector<int> vals = {1, 2, 3, 0, 4, 2, -1};
  for (int v : vals) {
    tree.add(v);
  }
  check(tree, {{{2}}, {{0}, {3}}, {{-1}, {0, 1}, {2, 2}, {3, 4}}});
}
