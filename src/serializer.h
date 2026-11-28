#pragma once

#include <vector>

class BPlusTree;

class Serializer {
 public:
  using Values = std::vector<std::vector<std::vector<int>>>;
  static Values bfs(const BPlusTree& tree);
};