#ifndef EX1_SEARCHTREE_H
#define EX1_SEARCHTREE_H
#include <iostream>

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


public:
    SearchTree() : root(nullptr), size(0) {};
    ~SearchTree() {
        //TODO
    }
    Node<Key, Data>* find (Key const &key);
    void remove(Key const &key);
    void insert(Key const &key, Data const &data);
    Node<Key, Data> **scanInOrder();
    void removeNoChildren(Node<Key, Data> *node, Node<Key, Data> *father);
    void removeTwoChildren(Node<Key, Data> *node, Node<Key, Data> *father);
    void removeOneChildRight(Node<Key, Data> *node, Node<Key, Data> *father);
    void removeOneChildLeft(Node<Key, Data> *node, Node<Key, Data> *father);
    void deleteTree();

};


template<typename Key, typename Data>
void SearchTree<Key, Data>::insert(const Key &key, const Data &data) {
//TODO: check values
    auto *newNode = new Node<Key, Data>(key, data);
    auto *temp = root;
    bool leafAdded = false;

    if(temp == nullptr){
        temp = newNode;
        this->root = temp;
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
        }
        else{
            node=node->getRight();
        }
    }
    return nullptr;
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::remove(Key const &key)
{
    auto *node = find(key);
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
        removeTwoChildren(node,father);
    }

    //remain balancing
    while (father!= nullptr) {
        father->calculateHeightAndBalance();
        if (abs(father->balancingParameter) == 2)
        {
            balanceTree(father);
        }
        father = father->getFather();
    }
}


template<typename Key, typename Data>
void SearchTree<Key, Data>::removeNoChildren(Node<Key, Data> *node, Node<Key, Data> *father)
{
        if (father== nullptr)
        {
            this->root= nullptr;
            this->size-=1;
        }
        if (father->getLeft()==node) {
            father->setLeft(nullptr);
            this->size-=1;
        }
        else if (father->getRight()==node){
            father->setRight(nullptr);
            this->size-=1;
        }
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::removeOneChildLeft(Node<Key, Data> *node, Node<Key, Data> *father)
{
    if (father== nullptr)
    {
        this->root= node->getLeft();
        this->size-=1;
    }
    else if (father->getLeft()==node) {
        father->setLeft(node->getLeft());
        this->size-=1;
    }
    else if (father->getRight()==node){
        father->setRight(node->getLeft());
        this->size-=1;
    }
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::removeOneChildRight(Node<Key, Data> *node, Node<Key, Data> *father)
{
    if (father== nullptr)
    {
        this->root= node->getRight();
        this->size-=1;
    }
    else if (father->getLeft()==node) {
        father->setLeft(node->getRight());
        this->size-=1;
    }
    else if (father->getRight()==node){
        father->setRight(node->getRight());
        this->size-=1;
    }
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::removeTwoChildren(Node<Key, Data> *node, Node<Key, Data> *father)
{
    auto *nextInOrder = findMin(node->getRight());
    if (father== nullptr)
    {
        this->root= nextInOrder;
        this->size-=1;
    }
    else if (father->getLeft()==node) {
        father->setLeft(nextInOrder);
        this->size-=1;
    }
    else if (father->getRight()==node){
        father->setRight(nextInOrder);
        this->size-=1;
    }
    auto *temp=node;
    temp->setLeft(nextInOrder->getLeft());
    temp->setLeft(nextInOrder->getRight());
    nextInOrder->setLeft(node->getLeft());
    nextInOrder->setRight(node->getRight());
    node->setLeft(temp->getLeft());
    node->setRight(temp->getRight());
    remove(node->getKey());
}

template<typename Key, typename Data>
void SearchTree<Key, Data>::deleteTree(Node<Key, Data> *node)
{
    if (node== nullptr){
        return;
    }
    auto *father = min->getFather();
    auto *minRight = findMin(father->getRight());
    delete node;
    deleteTree(minRight);
    deleteTree(father);
}
#endif //EX1_SEARCHTREE_H
