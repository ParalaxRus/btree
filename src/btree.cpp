#include "btree.h"

#include <stack>

BPlusTree::BPlusTree() : _root(new Node(true)) {
}

BPlusTree::~BPlusTree() {
  if (this->_root != nullptr) {
    std::stack<Node*> s;
    s.push(this->_root);

    while (!s.empty()) {
      auto* n = s.top();
      s.pop();

      for (auto* child : n->children()) {
        s.push(child);
      }

      delete n;
    }
  }
}

Node* BPlusTree::find(int val) const {
  return nullptr;
}

void BPlusTree::add(int val) {
  auto entry = this->_root->add(val);
  if (entry) {
    auto* newRoot = new Node(false, {(*entry).value}, {_root, (*entry).child});
    this->_root = newRoot;
  }
}

bool BPlusTree::remove(int val) {
  return this->remove(val);
}
