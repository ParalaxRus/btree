#include "serializer.h"

#include <queue>

#include "btree.h"
#include "node.h"

using std::queue;
using std::vector;

Serializer::Values Serializer::bfs(const BPlusTree& tree) {
  if (tree.empty()) {
    return {};
  }

  Serializer::Values levels;

  queue<const Node*> q;
  q.push(tree._root);

  while (!q.empty()) {
    levels.push_back({});
    const int len = q.size();
    for (int i = 0; i < len; ++i) {
      const auto* node = q.front();
      q.pop();

      const auto& vals = node->values();
      auto& last = levels.back();
      last.push_back(vals);

      const auto& children = node->children();
      for (const auto& child : children) {
        q.push(child);
      }
    }
  }

  return levels;
}
