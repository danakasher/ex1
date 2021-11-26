#ifndef EX1_SEARCHTREE_H
#define EX1_SEARCHTREE_H
#include <iostream>
#include "Node.h"

template <typename Key, typename Data>
class SearchTree{
private:
    Node<Key, Data> *root;
    int size;
    void findUnbalance(Node<Key, Data> *currentNode) {
        bool balancingPnt = false;
        while (!balancingPnt) {
            currentNode->calculateHeightAndBalance();
            if (abs(currentNode->balancingParameter) == 2) {
                balancingPnt = true;
            } else {
                if (currentNode != this->root) {
                    currentNode = currentNode->getFather();
                } else {
                    break;
                }
            }
        }
        balanceTree(currentNode);
    }
    void balanceTree(Node<Key, Data> *balancingPnt) {
        if(balancingPnt == nullptr) return;
        switch (balancingPnt->balancingParameter) {
            case 2: {
                if(balancingPnt->getLeft()->balancingParameter >= 0){
                    roll_LL(balancingPnt);
                } else {
                    roll_LR(balancingPnt);
                }
            } break;

            case -2: {
                if(balancingPnt->getRight()->balancingParameter <= 0){
                    roll_RR(balancingPnt);
                } else {
                    roll_RL(balancingPnt);
                }
            }
        }
    }
    int scanInOrder(Node<Key, Data> *node, Node<Key, Data> **sortedArr, int index){
        if(index == this->size || node == nullptr){
            return index;
        }
        index = scanInOrder(node->getLeft(), sortedArr, index);
        sortedArr[index] = node;
        index++;
        index = scanInOrder(node->getRight(), sortedArr, index);
        return index;
    }
    void roll_LL(Node<Key, Data> *balancingPnt){
        rightRotate(balancingPnt);
    }
    void roll_RR(Node<Key, Data> *balancingPnt){
        leftRotate(balancingPnt);
    }
    void roll_LR(Node<Key, Data> *balancingPnt){
        leftRotate(balancingPnt->getLeft());
        rightRotate(balancingPnt);
    }
    void roll_RL(Node<Key, Data> *balancingPnt){
        rightRotate(balancingPnt->getRight());
        leftRotate(balancingPnt);
    }
    void leftRotate(Node<Key, Data> *node){
        Node<Key, Data>* father = node->getFather();
        Node<Key, Data>* rightSon = node->getRight();
        Node<Key, Data>* leftOfRight = rightSon->getLeft();

        if(father == nullptr){
            this->root = rightSon;
            rightSon->setFather(nullptr);
        } else {
            if(father->getRight() == node){
                father->setRight(rightSon);
            } else {
                father->setLeft(rightSon);
            }
            rightSon->setFather(father);
        }

        rightSon->setLeft(node);
        node->setFather(rightSon);
        node->setRight(leftOfRight);
        if(leftOfRight != nullptr){
            leftOfRight->setFather(node);
        }

        node->calculateHeightAndBalance();
        rightSon->calculateHeightAndBalance();
    }
    void rightRotate(Node<Key, Data> *node){
        Node<Key, Data>* father = node->getFather();
        Node<Key, Data>* leftSon = node->getLeft();
        Node<Key, Data>* rightOfLeft = leftSon->getRight();

        if(father == nullptr){
            this->root = leftSon;
            leftSon->setFather(nullptr);
        } else {
            if(father->getRight() == node){
                father->setRight(leftSon);
            } else {
                father->setLeft(leftSon);
            }
            leftSon->setFather(father);
        }

        leftSon->setRight(node);
        node->setFather(leftSon);
        node->setLeft(rightOfLeft);
        if(rightOfLeft != nullptr){
            rightOfLeft->setFather(node);
        }

        node->calculateHeightAndBalance();
        leftSon->calculateHeightAndBalance();
    }
    Node<Key, Data>* findMin(Node<Key, Data> *node)
    {
        auto *temp = node->getLeft();
        while (temp!= nullptr)
        {
            node=node->getLeft();
            temp=temp->getLeft();
        }
        return node;
    }
    void removeNoChildren(Node<Key, Data> *node, Node<Key, Data> *father);
    Node<Key, Data>* removeTwoChildren(Node<Key, Data> *node, Node<Key, Data> *father);
    void removeOneChildRight(Node<Key, Data> *node, Node<Key, Data> *father);
    void deleteTree(Node<Key, Data> *node, Node<Key, Data> *father);
    bool isBalanced(Node<Key, Data> *node, bool carry);

public:
    SearchTree() : root(nullptr), size(0) {};
    ~SearchTree() {
        deleteTree(this->root, nullptr);
    }
    Node<Key, Data>* find (Key const &key);
    void remove(Key const &key);
    void insert(Node<Key, Data> *newNode);
    void insert(Key &key, Data &data); //For Testing
    Node<Key, Data> **scanInOrder();
    int getSize() const { return this->size; }
    void removeOneChildLeft(Node<Key, Data> *node, Node<Key, Data> *father);
    bool isBalanced();
};


template<typename Key, typename Data>
void SearchTree<Key, Data>::insert(Node<Key, Data> *newNode) {
    auto *temp = root;
    bool leafAdded = false;

    if(temp == nullptr){
        this->root = newNode;
        this->size++;
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
Node<Key, Data> **SearchTree<Key, Data>::scanInOrder(){
    auto **sortedArr = new Node<Key, Data>*[this->size];
    scanInOrder(this->root, sortedArr, 0);
    return sortedArr;
}

template<typename Key, typename Data>
Node<Key, Data>* SearchTree<Key, Data>::find(Key const &key) {
    auto *node = this->root;
    while (node!= nullptr)
    {
        if (node->getKey()==key){
            return node;
        }
        if (key<node->getKey()){
            node=node->getLeft();
        } else {
            node=node->getRight();
        }
    }
    return nullptr;
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::remove(Key const &key)
{
    Node<Key, Data> *node = find(key);
    if (node==nullptr){
        return;
    }
    auto *father = node->getFather();

    //no children
    if ((node->getLeft()== nullptr)&&(node->getRight()==nullptr)){
        removeNoChildren(node,father);
    }

    //one child in left
    if ((node->getLeft()!= nullptr)&&(node->getRight()==nullptr)){
        removeOneChildLeft(node,father);
    }

    //one child in Right
    if ((node->getLeft()== nullptr)&&(node->getRight()!=nullptr)){
        removeOneChildRight(node,father);
    }

    //two children
    if ((node->getLeft()!= nullptr)&&(node->getRight()!=nullptr))
    {
        father = removeTwoChildren(node, father);
    }

    // Re-balance
    if(father == nullptr){
        father = this->root;
        balanceTree(father->getRight());
        balanceTree(father->getLeft());
    }
    while (father != nullptr) {
        father->calculateHeightAndBalance();
        balanceTree(father);
        father = father->getFather();
    }

    this->size -= 1;
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::removeNoChildren(Node<Key, Data> *node, Node<Key, Data> *father) {
    if (father == nullptr){
        this->root= nullptr;
        return;
    }
    if(father->getLeft()==node) {
        father->setLeft(nullptr);
    } else {
        father->setRight(nullptr);
    }
    node->setFather(nullptr);
    node->setRight(nullptr);
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::removeOneChildLeft(Node<Key, Data> *node, Node<Key, Data> *father) {
    Node<Key, Data> *leftSon = node->getLeft();
    if (father== nullptr) {
        this->root= leftSon;
        return;
    }
    if (father->getLeft()==node) {
        father->setLeft(leftSon);
    } else {
        father->setRight(leftSon);
    }
    if(node->getLeft() != nullptr){
        leftSon->setFather(father);
    }
    node->setFather(nullptr);
    node->setRight(nullptr);
    father->calculateHeightAndBalance();
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::removeOneChildRight(Node<Key, Data> *node, Node<Key, Data> *father) {
    Node<Key, Data> *rightSon = node->getRight();
    if (father== nullptr) {
        this->root= rightSon;
        rightSon->setFather(nullptr);
    }
    else if (father->getLeft()==node) {
        father->setLeft(rightSon);
    }else{
        father->setRight(rightSon);
    }
    if(rightSon != nullptr){
        rightSon->setFather(father);
    }

    node->setFather(nullptr);
    node->setRight(nullptr);
    father->calculateHeightAndBalance();
}

template<typename Key, typename Data>
Node<Key, Data>* SearchTree<Key, Data>::removeTwoChildren(Node<Key, Data> *node, Node<Key, Data> *father) {
    Node<Key, Data> *nextInOrder = findMin(node->getRight());
    Node<Key, Data>  *fatherNextInOrder = nextInOrder->getFather();
    Node<Key, Data>  *tempLeft = node->getLeft();
    Node<Key, Data>  *tempRight = node->getRight();

    if (father == nullptr){
        this->root= nextInOrder;
    } else {
        if (father->getLeft()==node) {
            father->setLeft(nextInOrder);
        }else{
            father->setRight(nextInOrder);
        }
    }
    nextInOrder->setFather(father);
    if(fatherNextInOrder->getRight() == nextInOrder){
        nextInOrder->setLeft(node);
        node->setRight(nullptr);
        node->setFather(nextInOrder);
        removeOneChildLeft(node, nextInOrder);
        return nextInOrder;
    } else {
        fatherNextInOrder->setLeft(node);
    }
    node->setFather(fatherNextInOrder);

    node->setRight(nextInOrder->getRight());
    node->setLeft(nullptr);
    nextInOrder->setLeft(tempLeft);
    nextInOrder->setRight(tempRight);
    tempLeft->setFather(nextInOrder);
    tempRight->setFather(nextInOrder);
    node->calculateHeightAndBalance();
    nextInOrder->calculateHeightAndBalance();
    if(node->getRight() != nullptr){
        node->getRight()->setFather(node);
        removeOneChildRight(node, node->getFather());
    } else {
        removeNoChildren(node, node->getFather());
    }
    fatherNextInOrder->calculateHeightAndBalance();
    nextInOrder->calculateHeightAndBalance();
    return fatherNextInOrder;
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::deleteTree(Node<Key, Data> *node, Node<Key, Data> *father){
    if (node== nullptr){
        return;
    }
    deleteTree(node->getLeft(), node);
    deleteTree(node->getLeft(), node);
    deleteTree(node->getRight(), node);
    if(father != nullptr){
        if(father->getRight() == node){
            father->setRight(nullptr);
        } else {
            father->setLeft(nullptr);
        }
    }

    delete node;
}

template<typename Key, typename Data>
bool SearchTree<Key, Data>::isBalanced(Node<Key, Data> *node, bool carry){
    if(node == nullptr) return true;

    carry = isBalanced(node->getLeft(), carry) && carry;
    if(!carry){
        return false;
    }
    carry = isBalanced(node->getRight(), carry) && carry;
    if(!carry){
        return false;
    }
    node->calculateHeightAndBalance();

    return carry && abs(node->balancingParameter) < 2;
}

template<typename Key, typename Data>
bool SearchTree<Key, Data>::isBalanced(){
    return isBalanced(this->root, true);
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::insert(Key &key, Data &data) {
    Node<Key, Data> *newNode = new Node<Key, Data>(key, data);
    insert(newNode);
}

#endif //EX1_SEARCHTREE_H
