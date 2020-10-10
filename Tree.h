#ifndef LAB2_3_TREE_H
#define LAB2_3_TREE_H

#include "Console.h"
#include <stack>
#include <cmath>

template<class Key = int, class Data = int>
class Tree {
private:
    class Node {
    private:
        Key key;
        Data data;
        Node *left;
        Node *right;

    public:
        explicit Node(Key key, Data data = Data(), Node *left = nullptr, Node *right = nullptr)
                : key(key), data(data), left(left), right(right) {};

        Key getKey() const;

        void setKey(Key key);

        Data getData() const;

        void setData(Data data);

        Node *getLeft() const;

        void setLeft(Node *left);

        Node *getRight() const;

        void setRight(Node *right);
    };

    Node *root;
    int size;

    void print(Node *node, int lvl);

public:
    explicit Tree() : root(nullptr), size(0) {};

    ~Tree();

    Node *getNodeByKey(Key key);

    Node *max(Node *node);

    Node *min(Node *node);

    Node *biggerParent(Node *current, Node *target);

    Node *lessParent(Node *current, Node *target);

    Node *getNodeWithMinimalKey();

    Node *getNodeWithMaximalKey();

    Node *getPrev(Node *target);

    Node *getNext(Node *target);

    bool insert(Key key, Data data = Data());

    Node *getParrent(Node *node);

    Data find(Key key);

    bool remove(Key key);

    bool setData(Key key, Data data);

    void traverse();

    void print();

    bool isEmpty();

    int getSize();

    void clear();

    Node *getRoot() const;

    class Iterator {
    private:
        Tree *tree;
        Node *node;

    public:
        explicit Iterator(Tree<Key, Data> *tree = nullptr, Node *node = nullptr);

        void setTree(Tree *tree);

        bool hasNode();

        bool hasTree();

        void print();

        Data getData();

        Node *getParrent();

        void toMinimalKey();

        bool toMaximalKey();

        bool setData(Data data);

        bool operator++(int);

        bool operator--(int);

        bool operator==(Iterator it);

        bool operator!=(Iterator it);

        Node *operator*();

    };

    Iterator begin();

    Iterator rbegin();

    Iterator rootIterator();

};



// ################################################
//                      Iterator
// ################################################

template<class Key, class Data>
Tree<Key, Data>::Iterator::Iterator(Tree<Key, Data> *tree, Node *node) {
    this->tree = tree;
    this->node = node;
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::setTree(Tree *tree) {
    Iterator::tree = tree;
}

template<class Key, class Data>
Data Tree<Key, Data>::Iterator::getData() {
    if (this->hasNode()) {
        return node->getData();
    }
    throw runtime_error("Iterator has no node");
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::hasNode() {
    return this->node != nullptr;
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::operator++(int) {
    if (!this->hasNode()) {
        return false;
    }
    this->node = tree->getNext(this->node);
    if (this->node == nullptr)
        return false;
    return true;
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::operator--(int) {
    if (!this->hasNode()) {
        return false;
    }
    this->node = tree->getPrev(this->node);
    if (this->node == nullptr)
        return false;
    return true;
}


template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::Iterator::operator*() {
    return node;
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::setData(Data data) {
    if (!this->hasNode()) {
        return false;
    }
    this->node->setData(data);
    return false;
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::operator==(Tree::Iterator it) {
    if (this->node == it.node)
        return true;
    return false;
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::operator!=(Tree::Iterator it) {
    if (this->node == it.node)
        return false;
    return true;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::Iterator::getParrent() {
    if (this->node == this->tree->getRoot()) {
        return nullptr;
    }
    if (this->node == nullptr) {
        throw runtime_error("Iterator has no node!");
    }
    Node *next = nullptr;
    Node *current = this->tree->getRoot();
    if (this->node->getKey() > current->getKey()) {
        next = current->getRight();
    }
    if (this->node->getKey() < current->getKey()) {
        next = current->getLeft();
    }
    while (next != this->node) {
        current = next;
        if (this->node->getKey() > current->getKey()) {
            next = current->getRight();
            continue;
        }
        if (this->node->getKey() < current->getKey()) {
            next = current->getLeft();
            continue;
        }
    }
    return current;
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::print() {
    Console::print(this->node->getKey());
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::hasTree() {
    if (this->tree != nullptr)
        return true;
    else
        return false;
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::toMinimalKey() {
    this->node = tree->getNodeWithMinimalKey();
}



// ################################################
//                      Node
// ################################################

template<class Key, class Data>
Key Tree<Key, Data>::Node::getKey() const {
    return key;
}

template<class Key, class Data>
void Tree<Key, Data>::Node::setKey(Key key) {
    this->key = key;
}

template<class Key, class Data>
Data Tree<Key, Data>::Node::getData() const {
    return data;
}

template<class Key, class Data>
void Tree<Key, Data>::Node::setData(Data data) {
    this->data = data;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::Node::getLeft() const {
    return left;
}

template<class Key, class Data>
void Tree<Key, Data>::Node::setLeft(Tree::Node *left) {
    this->left = left;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::Node::getRight() const {
    return right;
}

template<class Key, class Data>
void Tree<Key, Data>::Node::setRight(Tree::Node *right) {
    Node::right = right;
}

// ################################################
//                      Tree
// ################################################

template<class Key, class Data>
Tree<Key, Data>::~Tree() {
    this->clear();
}

template<class Key, class Data>
void Tree<Key, Data>::clear() {
    // TODO: may be rewritten by recursive algo
    if (this->isEmpty()) {
        throw runtime_error("Tree is empty");
    }
    stack < Node * > nodes;
    nodes.push(this->root);
    while (!nodes.empty()) {
        Node *node = nodes.top();
        nodes.pop();
        Console::debug("REMOVED");
        if (node->getRight()) {
            nodes.push(node->getRight());
        }
        Node *left = node->getLeft();
        delete node;
        node = nullptr;
        this->size--;
        if (left) {
            nodes.push(left);
        }
    }
    this->root = nullptr;
}

template<class Key, class Data>
bool Tree<Key, Data>::insert(Key key, Data data) {
    if (!this->root) {
        this->root = new Node(key, data);
    } else {
        Node *node = this->root;
        Node *nodeBefore = nullptr;
        while (node) {
            nodeBefore = node;
            if (key < node->getKey()) {
                node = node->getLeft();
            } else if (key > node->getKey()) {
                node = node->getRight();
            } else {
                return false;
            }
        }
        node = new Node(key, data);
        if (key < nodeBefore->getKey()) {
            nodeBefore->setLeft(node);
        } else {
            nodeBefore->setRight(node);
        }
    }
    this->size++;
    return true;
}

template<class Key, class Data>
void Tree<Key, Data>::traverse() {
    if (this->isEmpty()) {
        throw runtime_error("EMPTY LIST");
    }
    stack < Node * > nodes;
    nodes.push(this->root);
    while (!nodes.empty()) {
        Node *node = nodes.top();
        nodes.pop();
        if (node->getRight()) {
            nodes.push(node->getRight());
        }
        Console::print(node->getKey());
        Console::print(" ");
        if (node->getLeft()) {
            nodes.push(node->getLeft());
        }
    }
    Console::println();
}

template<class Key, class Data>
void Tree<Key, Data>::print() {
    this->print(this->root, 0);
}

template<class Key, class Data>
void Tree<Key, Data>::print(Tree<Key, Data>::Node *node, int lvl) {
    if (node) {
        this->print(node->getRight(), lvl + 1);
        for (int i = 0; i < lvl; ++i) {
            Console::print("    ");
        }
        Console::print(node->getKey(), static_cast<COLORS>(lvl % 8)); // TODO: auto countering of COLORS length
        Console::print("(", static_cast<COLORS>(lvl % 8));
        Console::print(node->getData(), static_cast<COLORS>(lvl % 8));
        Console::println(")", static_cast<COLORS>(lvl % 8));
        this->print(node->getLeft(), lvl + 1);
    } else {
        for (int i = 0; i < lvl; ++i) {
            Console::print("    ");
        }
        Console::println("*", static_cast<COLORS>(lvl % 8));
    }
}

template<class Key, class Data>
bool Tree<Key, Data>::isEmpty() {
    return this->size == 0;
}

template<class Key, class Data>
int Tree<Key, Data>::getSize() {
    return this->size;
}


template<class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>:: getNodeByKey(Key key) {
    Node *node = this->root;
    while (node && key != node->getKey()) {
        if (key < node->getKey()) {
            node = node->getLeft();
        } else {
            node = node->getRight();
        }
    }
    if (!node) {
        throw invalid_argument("KEY ERROR");
    }
    return node;
}

template<class Key, class Data>
Data Tree<Key, Data>::find(Key key) {
    Node *node = getNodeByKey(key);
    return node->getData();
}


template<class Key, class Data>
bool Tree<Key, Data>::remove(Key key) {
    return false;
}

template<class Key, class Data>
typename Tree<Key, Data>::Iterator Tree<Key, Data>::begin() {
    if (this->isEmpty()) {
        return Tree<Key, Data>::Iterator(this);
    }
    Node *node = root;
    while (node->getLeft() != nullptr) {
        node = node->getLeft();
    }
    return Tree<Key, Data>::Iterator(this, node);
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getRoot() const {
    return root;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getParrent(Tree::Node *node) {
    if (node == this->getRoot()) {
        return nullptr;
    }
    if (node == nullptr) {
        throw runtime_error("Iterator has no node!");
    }
    Node *next = nullptr;
    Node *current = this->getRoot();
    if (node->getKey() > current->getKey()) {
        next = current->getRight();
    }
    if (node->getKey() < current->getKey()) {
        next = current->getLeft();
    }
    while (next != node) {
        current = next;
        if (node->getKey() > current->getKey()) {
            next = current->getRight();
            continue;
        }
        if (node->getKey() < current->getKey()) {
            next = current->getLeft();
            continue;
        }
    }
    return current;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::max(Tree::Node *node) {
    if (node == nullptr)
        return nullptr;
    while (node->getRight() != nullptr) {
        node = node->getRight();
    }
    return node;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::biggerParent(Node *current, Node *target) {
    if (current == target) return nullptr;
    if (target->getKey() > current->getKey()) {
        Node *returnNode = biggerParent(current->getRight(), target);
        if (returnNode == nullptr)
            return current;
        else return returnNode;
    } else {
        return biggerParent(current->getLeft(), target);
    }
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::lessParent(Node *current, Node *target) {
    if (current == target) return nullptr;
    if (target->getKey() < current->getKey()) {
        Node *returnNode = lessParent(current->getLeft(), target);
        if (returnNode == nullptr)
            return current;
        else return returnNode;
    } else {
        return lessParent(current->getRight(), target);
    }
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getPrev(Tree::Node *target) {
    if (this->isEmpty() || target == nullptr) {
        throw runtime_error("EXCEPTION");
    }
    if (target->getLeft() != nullptr) {
        return this->max(target->getLeft());
    } else {
        return biggerParent(root, target);
    }
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getNext(Tree::Node *target) {
    if (this->isEmpty() || target == nullptr) {
        throw runtime_error("EXCEPTION");
    }
    if (target->getRight() != nullptr) {
        return this->min(target->getRight());
    } else {
        return lessParent(root, target);
    }
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::min(Tree::Node *node) {
    if (node == nullptr)
        return nullptr;
    while (node->getLeft() != nullptr) {
        node = node->getLeft();
    }
    return node;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getNodeWithMinimalKey() {
    Node* node = this->root;
    while(node->getLeft()!= nullptr){
        node = node->getLeft();
    }
    return node;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getNodeWithMaximalKey() {
    Node* node = this->root;
    while(node->getRight()!= nullptr){
        node = node->getRight();
    }
    return node;
}

template<class Key, class Data>
bool Tree<Key, Data>::setData(Key key, Data data) {
    try {
        Node *node = this->getNodeByKey(key);
        node->setData(data);
    }
    catch (exception ex) {
        return false;
    }
    return true;
}

#endif //LAB2_3_TREE_H
