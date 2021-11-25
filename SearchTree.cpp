#include "Node.h"
#include <cmath>
using namespace std;
#include <iostream>
using std::fmax;

template<typename Data, typename Key>
class SearchTree {
private:
    Node<Key, Data> *root;
    int size;

public:
    SearchTree() : root(nullptr), size(0) {};

    void insert(Key const &key, Data const &data) {
        //TODO: check values
        auto *newNode = new Node<Key, Data>(key, data);
        auto *temp = root;
        bool leafAdded = false;

        if(temp == nullptr){
            temp = newNode;
            this->root = temp;
            leafAdded = true;
        }
        while (!leafAdded) {
            if(temp==newNode){
                //TODO:
            }
            if (newNode->getKey() > temp->getKey()) {
                if (temp->getRight() == nullptr) {
                    temp->setRight(newNode);
                    newNode->setFather(temp);
                    leafAdded = true;
                } else {
                    temp = temp->getRight();
                }
            } else {
                if (temp->getLeft() == nullptr) {
                    temp->setLeft(newNode);
                    newNode->setFather(temp);
                    leafAdded = true;
                } else {
                    temp = temp->getLeft();
                }
            }
        }

        this->size++;
        bool balancingPnt = false;
        int heightLeft, heightRight;
        while(!balancingPnt){
            heightLeft = temp->getLeft() == nullptr? 0:temp->getLeft()->height;
            heightRight = temp->getRight() == nullptr? 0:temp->getRight()->height;
            temp->height = fmax((double) heightRight, (double) heightLeft)+1;
            temp->balancingParameter = heightLeft-heightRight;
            if(abs(temp->balancingParameter) == 2){
                balancingPnt = true;
            } else {
                if(temp != this->root){
                    temp = temp->getFather();
                } else {
                    break;
                }
            }
        }

        switch (temp->balancingParameter) {
            case 2: {
                if(temp->getLeft()->balancingParameter >= 0){
                    roll_LL(temp);
                } else {
                    roll_LR(temp);
                }
            } break;

            case -2: {
                if(temp->getRight()->balancingParameter <= 0){
                    roll_RR(temp);
                } else {
                    roll_RL(temp);
                }
            }
        }
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

    void calculateHeight(Node<Key, Data> *node){
        int heightLeft = node->getLeft() == nullptr? 0:node->getLeft()->height;
        int heightRight = node->getRight() == nullptr? 0:node->getRight()->height;
        node->height = fmax((double) heightRight, (double) heightLeft)+1;
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

        calculateHeight(node);
        calculateHeight(rightSon);
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

        calculateHeight(node);
        calculateHeight(leftSon);
    }

    void print_in_order(){
        print_in_order(this->root);
    }


    void print_in_order(Node<Key, Data> *node){
        if(node == nullptr){
            return;
        }
        print_in_order(node->getLeft());
        cout << node->getData()<< ", ";
        print_in_order(node->getRight());
    }

    Node<Key, Data>* find (Node<Key, Data> *node, Key* key) {
        if(node== nullptr){
            return nullptr;
        }
        if(node->getKey() == key){
            return node;
        }
        if (find(node->getLeft(), key)!= nullptr) return find(node->getLeft(), key);
        else if (find(node->getRight(), key)!= nullptr) return find(node->getRight(), key);
        return nullptr;
    }

    ~SearchTree() {
        //TODO
    }
};
