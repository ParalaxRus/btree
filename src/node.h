#pragma once

#include <optional>
#include <vector>

class Node;

struct Entry {
  int value;
  Node* child;
};

class Node final {
 public:
  explicit Node(bool leaf);
  Node(bool leaf, std::vector<int> values, std::vector<Node*> children);

  // Adds a value to the subtree
  // Returns entry if overlow happened and node had been split
  std::optional<Entry> add(int val, Node* child = nullptr);

  // Checks whether subtree contains specified value or not
  bool contains(int val) const;

  // Removes value from the subtree
  // Returns true if value had been removed of false if value was not found
  bool remove(int value);

  // Inorder traversal of the tree
  void inorder(std::vector<int>& values) const;

  bool leaf() const;

  int keysCount() const;

  int childrenCount() const;

  const std::vector<int>& values() const;

  const std::vector<Node*>& children() const;

  bool empty() const;

 private:
  static constexpr int kMaxChildren = 5;
  bool _leaf;
  std::vector<int> _keys;
  std::vector<Node*> _children;

  // Searches for the leaf node which might contain target value
  const Node* find(int val) const;
  Node* find(int val);

  void insert(const Entry& entry);

  Entry split();

  // Compacts current node if needed
  void compact(int childIndex);

  // Erases corresponding key and child
  void erase(int childIndex);

  // Gets index of the first key which is
  // strictly greater than the specified value
  // (i.e. index of the child we need to perform operation on)
  int childIndex(int value) const;

  bool overflow() const;
};

inline bool Node::leaf() const {
  return this->_leaf;
}

inline int Node::keysCount() const {
  return this->_keys.size();
}

inline int Node::childrenCount() const {
  return this->_children.size();
}

inline const std::vector<int>& Node::values() const {
  return this->_keys;
}

inline const std::vector<Node*>& Node::children() const {
  return this->_children;
}

inline bool Node::overflow() const {
  return (this->_keys.size() > Node::kMaxChildren);
}

inline bool Node::empty() const {
  return this->_keys.empty();
}
