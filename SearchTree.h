#ifndef EX1_SEARCHTREE_H
#define EX1_SEARCHTREE_H
#include <iostream>

template <typename Key, typename Data>
class SearchTree{
private:
    Node<Key, Data> *root;
    int size;

    ~SearchTree() {
        //TODO
    }
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
    void print_in_order(Node<Key, Data> *node){
        if(node == nullptr){
            return;
        }
        print_in_order(node->getLeft());
        std::cout << node->getData()<< ", ";
        print_in_order(node->getRight());
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

public:
    SearchTree() : root(nullptr), size(0) {};
    void insert(Key const &key, Data const &data);
    void print_in_order();
};

#endif //EX1_SEARCHTREE_H
