#include "btree.h"

#include "node.h"

BPlusTree::BPlusTree() : root(nullptr) {
}

Node* BPlusTree::find(int val) const {
  return nullptr;
}

void BPlusTree::add(int val) {
  auto entry = this->root->add(val);
  if (entry) {
    auto* newRoot = new Node(false, {(*entry).value}, {root, (*entry).child});
    this->root = newRoot;
  }
}

bool BPlusTree::remove(int val) {
  return this->remove(val);
}
