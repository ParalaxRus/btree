#pragma once

#include "node.h"

class BPlusTree {
private:
    Node* root;
public:
    BPlusTree();
    virtual ~BPlusTree() = default;

    Node* find(int val) const;

    void add(int val);
    bool remove(int val);
};
