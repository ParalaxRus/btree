#pragma once

#include "iterator.h"
#include "node.h"

class BPlusTree {
 public:
  using iterator = BfsIterator;
  BfsIterator begin() const {
    return iterator(this->_root);
  }
  BfsIterator end() const {
    return BfsIterator();
  }

  BPlusTree();
  virtual ~BPlusTree();

  Node* find(int val) const;

  void add(int val);
  bool remove(int val);
  bool empty() const;

 private:
  Node* _root;
  friend class Serializer;
};

inline bool BPlusTree::empty() const {
  return (_root->empty());
}
