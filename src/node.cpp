#include "node.h"

#include <algorithm>
#include <stdexcept>

Node::Node(bool leaf) : _leaf(leaf) {
}

bool Node::contains(int val) {
    auto* n = this->find(val);
    return std::binary_search(n->_vals.begin(), n->_vals.end(), val);
    
}

void Node::add(int val) {
    auto* leaf = this->find(val);

    if (leaf->insert(val)) {
        return;
    }

    if (leaf->valueCount() < Node::kMaxChildren) {
        
        return;
    }
}

bool Node::remove(int val) {
    return false;
}

Node* Node::find(int val) {
    if (this->leaf()) {
        return this;
    }

    const auto idx = this->index(val);
    return this->_children[idx]->find(val);
}

bool Node::insert(int val) {
    if (!this->leaf()) {
        throw std::runtime_error("insert failed because its not a leaf node");
    }

    const int idx = this->index(val);
    this->_vals.insert(this->_vals.begin() + idx, val);

    return true;
}

int Node::index(int val) const {
    const auto greater = std::upper_bound(this->_vals.begin(), this->_vals.end(), val);
    return (greater - this->_vals.begin());
}
