#pragma once

class Node;

class BPlusTree {
 public:
  BPlusTree();
  virtual ~BPlusTree() = default;

  Node* find(int val) const;

  void add(int val);
  bool remove(int val);
  bool empty() const;

 private:
  Node* root;
  friend class Serializer;
};

inline bool BPlusTree::empty() const {
  return (root == nullptr);
}
