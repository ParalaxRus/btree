#include "iterator.h"

#include <stdexcept>

#include "node.h"

BfsIterator::BfsIterator(Node* root) : _queue() {
  if (root == nullptr) {
    throw std::runtime_error("invalid root");
  }
  this->_queue.push(root);
}

BfsIterator& BfsIterator::operator++() {
  auto* n = this->_queue.front();
  this->_queue.pop();
  for (auto* child : n->children()) {
    this->_queue.push(child);
  }

  return *this;
}

BfsIterator BfsIterator::operator++(int) {
  BfsIterator tmp = *this;
  ++(*this);
  return tmp;
}
