#pragma once

#include <vector>

class Node final {
public:
    Node(bool leaf);

    bool leaf() const;
    bool contains(int val);
    int valueCount() const;
    int childrenCount() const;
    
    void add(int val);
    bool remove(int val);

private:
    static constexpr int kMaxChildren = 5;
    bool _leaf;
    std::vector<int> _vals;
    std::vector<Node*> _children;

    // Searches for the leaf node which might contain target value
    Node* find(int val);

    // Inserts value into the current leaf if possible and returns true
    // Returns false if insert faieled because node contains max number of children
    bool insert(int val);

    // Gets index of the first value which is 
    // strictly greater than the specified
    int index(int val) const;
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
