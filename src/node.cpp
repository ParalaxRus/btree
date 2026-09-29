#include "node.h"

#include <algorithm>
#include <stdexcept>

Node::Node(bool leaf) : Node(leaf, {}, {}) {
}

Node::Node(bool leaf, std::vector<int> vals, std::vector<Node*> children) 
    : _leaf(std::move(leaf)), _vals(std::move(vals)), _children(std::move(children)) {
}

bool Node::contains(int val) {
    const auto* n = this->find(val);
    return std::binary_search(n->_vals.begin(), n->_vals.end(), val);
    
}

std::optional<InsertEntry> Node::add(int val) {
    if (this->leaf()) {
        this->insert({val, nullptr});
        if (this->overflow()) {
            return {};
        }
        return split(true);
    }

    const auto idx = this->index(val);
    auto* child = this->_children[idx];
    if (child == nullptr) {
        throw std::runtime_error("child node is null");
    }
    auto entry = child->add(val);
    if (!entry) {
        return {};
    }

    this->insert(*entry);
    return split(false);
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

void Node::insert(const InsertEntry& entry) {
    const int idx = this->index(entry.val);
    this->_vals.insert(this->_vals.begin() + idx, entry.val);
    if (entry.child != nullptr) {
        this->_children.insert(this->_children.begin() + idx, entry.child);
    }
}

InsertEntry Node::split(bool leaf) {
    const int idx = this->_vals.size() / 2;

    // Split value and a child of a split value
    std::vector<int> vals;
    std::vector<Node*> children;
    for (int i = idx; i < this->_vals.size(); ++i) {
        vals.push_back(this->_vals[i]);
        children.push_back(this->_children[i]);
    }
    auto* node = new Node(leaf, std::move(vals), std::move(children));

    // Center is a split value
    const int split = this->_vals[idx];

    // Trimming current node
    this->_vals.erase(this->_vals.begin() + idx, this->_vals.end());
    this->_children.erase(this->_children.begin() + idx, this->_children.end());

    return {split, node};
}

int Node::index(int val) const {
    const auto greater = std::upper_bound(this->_vals.begin(), this->_vals.end(), val);
    return (greater - this->_vals.begin());
}
