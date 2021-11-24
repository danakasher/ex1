#include "Node.h"
#include <cmath>
using namespace std;
#include <iostream>
using std::fmax;

template<typename T>
class SearchTree {
private:
    Node<T> *root;
    int size;

public:
    SearchTree() : root(nullptr), size(0) {};

    void insert(const T &value) {
        Node<T> *newNode = new Node<T>(value);
        Node<T> *temp = root;
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
            if (newNode->getValue() > temp->getValue()) {
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

    void roll_LL(Node<T> *balancingPnt){
        rightRotate(balancingPnt);
    }

    void roll_RR(Node<T> *balancingPnt){
        leftRotate(balancingPnt);
    }

    void roll_LR(Node<T> *balancingPnt){
        leftRotate(balancingPnt->getLeft());
        rightRotate(balancingPnt);
    }

    void roll_RL(Node<T> *balancingPnt){
        rightRotate(balancingPnt->getRight());
        leftRotate(balancingPnt);
    }

    void calculateHeight(Node<T> *node){
        int heightLeft = node->getLeft() == nullptr? 0:node->getLeft()->height;
        int heightRight = node->getRight() == nullptr? 0:node->getRight()->height;
        node->height = fmax((double) heightRight, (double) heightLeft)+1;
    }

    void leftRotate(Node<T> *node){
        Node<T>* father = node->getFather();
        Node<T>* rightSon = node->getRight();
        Node<T>* leftOfRight = rightSon->getLeft();

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

    void rightRotate(Node<T> *node){
        Node<T>* father = node->getFather();
        Node<T>* leftSon = node->getLeft();
        Node<T>* rightOfLeft = leftSon->getRight();

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


    void print_in_order(Node<T> *node){
        if(node == nullptr){
            return;
        }
        print_in_order(node->getLeft());
        cout << node->getValue()<< ", ";
        print_in_order(node->getRight());
    }

    ~SearchTree() {
        //TODO
    }
};
