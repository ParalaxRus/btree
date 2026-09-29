#pragma once

#include <vector>
#include <optional>

class Node;

struct InsertEntry {
    int val;
    Node* child;
};

class Node final {
public:
    explicit Node(bool leaf);
    Node(bool leaf, std::vector<int> vals, std::vector<Node*> children);

    bool leaf() const;
    bool contains(int val);
    int valueCount() const;
    int childrenCount() const;
    const std::vector<int>& values() const;
    const std::vector<Node*>& children() const;
    
    // Add new value to the node recursively
    // Returns new entry if overlow happened and child had been split
    std::optional<InsertEntry> add(int val);
    bool remove(int val);
    
    void insert(const InsertEntry& entry);

private:
    static constexpr int kMaxChildren = 5;
    bool _leaf;
    std::vector<int> _vals;
    std::vector<Node*> _children;

    // Searches for the leaf node which might contain target value
    Node* find(int val);

    InsertEntry split(bool leaf);

    // Gets index of the first value which is 
    // strictly greater than the specified
    int index(int val) const;

    bool overflow() const;
};

inline bool Node::leaf() const {
    return this->_leaf;
}

inline int Node::valueCount() const {
    return this->_vals.size();
}

inline int Node::childrenCount() const {
    return this->_children.size();
}

inline const std::vector<int>& Node::values() const {
    return this->_vals;
}

inline const std::vector<Node*>& Node::children() const {
    return this->_children;
}

inline bool Node::overflow() const {
    return (this->_children.size() > Node::kMaxChildren);
}
