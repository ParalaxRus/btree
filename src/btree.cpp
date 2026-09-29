#include "btree.h"

BPlusTree::BPlusTree() {
}

Node* BPlusTree::find(int val) const {
    return nullptr;
}

void BPlusTree::add(int val) {
    auto entry = this->root->add(val);
    if (entry) {
        auto* newRoot = new Node(false, this->root->values(), this->root->children());
        newRoot->insert(*entry);
        this->root = newRoot;
    }
}

bool BPlusTree::remove(int val) {
    return this->remove(val);   
}
