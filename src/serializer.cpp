#include "serializer.h"

#include <queue>

#include "node.h"

using std::queue;
using std::vector;

vector<vector<int>> Serializer::bfs(const Node* root) {
  if (root == nullptr) {
    return {};
  }

  vector<vector<int>> levels;

  queue<const Node*> q;
  q.push(root);
  while (!q.empty()) {
    levels.push_back({});
    const int len = q.size();
    for (int i = 0; i < len; ++i) {
      const auto* node = q.front();
      q.pop();

      const auto& vals = node->values();
      auto& last = levels.back();
      last.insert(last.end(), vals.begin(), vals.end());

      const auto& children = node->children();
      for (const auto& child : children) {
        q.push(child);
      }
    }
  }

  return levels;
}