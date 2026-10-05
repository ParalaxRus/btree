#include "node.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

using std::vector;

Node::Node(bool leaf) : Node(leaf, {}, {}) {
}

Node::Node(bool leaf, vector<int> vals, vector<Node*> children)
    : _leaf(std::move(leaf)),
      _keys(std::move(vals)),
      _children(std::move(children)) {
}

std::optional<Entry> Node::add(int val, Node* child) {
  if (this->leaf()) {
    this->insert({val, child});
    if (!this->overflow()) {
      return {};
    }
    return split();
  }

  const auto idx = this->childIndex(val);
  auto* nextChild = this->_children[idx];
  if (nextChild == nullptr) {
    throw std::runtime_error("next child is null");
  }
  auto entry = nextChild->add(val);
  if (!entry) {
    return {};
  }

  this->insert(*entry);
  return split();
}

bool Node::contains(int val) const {
  const auto* n = this->find(val);
  return std::binary_search(n->_keys.begin(), n->_keys.end(), val);
}

bool Node::remove(int value) {
  if (this->leaf()) {
    const int i = this->childIndex(value);
    if (i == 0) {
      // No greater element found, specified value does not exist
      return false;
    }
    this->_keys.erase(this->_keys.begin() + i - 1);
    return true;
  }

  const int idx = this->childIndex(value);
  auto* child = this->_children[idx];
  if (child == nullptr) {
    throw std::runtime_error("child is null");
  }

  if (!child->remove(value)) {
    return false;
  }

  // Node implementation does not support underflow yet. Thus deletion does not
  // have borrow just compaction in case if child is empty
  this->compact(idx);

  return true;
}

void Node::inorder(vector<int>& values) const {
  if (this->leaf()) {
    for (int value : this->_keys) {
      values.push_back(value);
    }
    return;
  }

  for (auto* child : this->_children) {
    child->inorder(values);
  }
}

const Node* Node::find(int val) const {
  if (this->leaf()) {
    return this;
  }

  const auto idx = this->childIndex(val);
  return this->_children[idx]->find(val);
}

Node* Node::find(int val) {
  return const_cast<Node*>(std::as_const(*this).find(val));
}

void Node::insert(const Entry& entry) {
  const int idx = this->childIndex(entry.value);
  this->_keys.insert(this->_keys.begin() + idx, entry.value);
  if (entry.child != nullptr) {
    this->_children.insert(this->_children.begin() + idx, entry.child);
  }
}

Entry Node::split() {
  const int idx = this->_keys.size() / 2;

  // Right node
  vector<int> vals;
  vector<Node*> children;
  for (int i = idx; i < this->_keys.size(); ++i) {
    vals.push_back(this->_keys[i]);
    if (!this->leaf()) {
      children.push_back(this->_children[i]);
    }
  }
  auto* node = new Node(this->leaf(), std::move(vals), std::move(children));

  // Center is a split value
  const int split = this->_keys[idx];

  // Left (current) node
  this->_keys.erase(this->_keys.begin() + idx, this->_keys.end());
  if (!this->leaf()) {
    this->_children.erase(this->_children.begin() + idx, this->_children.end());
  }

  return {split, node};
}

void Node::compact(int childIndex) {
  auto* child = this->_children[childIndex];
  if (!child->empty()) {
    // Child still have keys, no compaction needed
    return;
  }

  if (this->keysCount() > 1) {
    this->erase(childIndex);
    delete child;
  } else {
    // Last key is responsible for two children so we can delete it only when
    // both children are empty
    for (auto child : this->_children) {
      if (!child->empty()) {
        return;
      }
    }

    for (auto child : this->_children) {
      delete child;
    }

    this->_keys.clear();
    this->_children.clear();

    // Current node is empty
  }
}

void Node::erase(int childIndex) {
  if (this->keysCount() <= 1) {
    throw std::runtime_error(
        "can't simple delete last key because it tracks two children");
  }

  this->_keys.erase(this->_keys.begin() + childIndex);
  this->_children.erase(this->_children.begin() + childIndex);
}

int Node::childIndex(int val) const {
  const auto greater =
      std::upper_bound(this->_keys.begin(), this->_keys.end(), val);
  return (greater - this->_keys.begin());
}
