#include "Node.h"
#include "SearchTree.h"
#include <iostream>

template<typename Key, typename Data>
void SearchTree<Key, Data>::insert(const Key &key, const Data &data) {
//TODO: check values
    auto *newNode = new Node<Key, Data>(key, data);
    auto *temp = root;
    bool leafAdded = false;

    if(temp == nullptr){
        temp = newNode;
        this->root = temp;
        return;
    }
    while (!leafAdded) {
        if(temp==newNode){
            //TODO:
        }
        if (newNode->getKey() > temp->getKey()) {
            if (temp->getRight() == nullptr) {
                temp->setRight(newNode);
                leafAdded = true;
            } else {
                temp = temp->getRight();
            }
        } else {
            if (temp->getLeft() == nullptr) {
                temp->setLeft(newNode);
                leafAdded = true;
            } else {
                temp = temp->getLeft();
            }
        }
    }
    newNode->setFather(temp);
    this->size++;
    findUnbalance(temp);
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::print_in_order(){
    print_in_order(this->root);
}
