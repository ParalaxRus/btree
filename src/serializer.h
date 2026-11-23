#pragma once

#include <vector>

class BPlusTree;

class Serializer {
 public:
  static std::vector<std::vector<int>> bfs(const BPlusTree& tree);
};