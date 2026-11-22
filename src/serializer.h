#pragma once

#include <vector>

class Node;

class Serializer {
 public:
  static std::vector<std::vector<int>> bfs(const Node* root);
};