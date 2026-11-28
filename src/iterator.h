#pragma once

#include <iterator>
#include <queue>

class Node;

class BfsIterator {
 public:
  using pointer = Node*;
  using reference = Node&;
  using iterator_category = std::forward_iterator_tag;
  using value_type = Node;
  using difference_type = std::ptrdiff_t;

  BfsIterator() = default;
  explicit BfsIterator(Node* root);

  reference operator*() const;
  pointer operator->() const;

  BfsIterator& operator++();
  BfsIterator operator++(int);

  friend bool operator==(const BfsIterator& first, const BfsIterator& second) {
    if (first._queue.empty() && second._queue.empty()) {
      return true;
    }
    if (first._queue.empty() || second._queue.empty()) {
      return false;
    }
    return (first._queue.front() == second._queue.front());
  }

  friend bool operator!=(const BfsIterator& first, const BfsIterator& second) {
    return !(operator==(first, second));
  }

 private:
  std::queue<Node*> _queue;
};

inline BfsIterator::reference BfsIterator::operator*() const {
  return *this->_queue.front();
}

inline BfsIterator::pointer BfsIterator::operator->() const {
  return this->_queue.front();
}
