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
            if (&temp > &newNode) {
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

        bool balancingPnt = false;
        int heightLeft, heightRight;
        while(!balancingPnt && temp != root){
            heightLeft = temp->getLeft() == nullptr? 0:temp->getLeft()->height;
            heightRight = temp->getRight() == nullptr? 0:temp->getRight()->height;
            temp->height = fmax((double) heightRight, (double) heightLeft)+1;
            temp->balancingParameter = heightLeft-heightRight;
            if(abs(temp->balancingParameter) == 2){
                balancingPnt = true;
            } else {
                temp = temp->getFather();
            }
        }

        Node<T> *father = temp->getFather();
        bool isRightSon = false;
        if(father != nullptr){
            isRightSon = father->getRight() == temp;
        }

        switch (temp->balancingParameter) {
            case 2: {
                if(temp->getLeft()->balancingParameter >= 0){
                    roll_LL(temp, isRightSon);
                } else {
                    roll_LR(temp, isRightSon);
                }
            } break;

            case -2: {
                if(temp->getRight()->balancingParameter <= 0){
                    roll_RR(temp, isRightSon);
                } else {
                    roll_RL(temp, isRightSon);
                }
            }
        }
    }

    void roll_LL(Node<T> *balancingPnt, bool isRight){
        Node<T> *leftSon = balancingPnt->getLeft();
        Node<T> *rightOfLeft = leftSon != nullptr? leftSon->getRight(): nullptr;
        Node<T> *father = balancingPnt->getFather();

        if(father == nullptr){
            this->root = leftSon;
            this->root->setFather(nullptr);
            leftSon->setRight(balancingPnt);
            balancingPnt->setLeft(rightOfLeft);
        } else {
            if(isRight){
                father->setRight(leftSon);
            } else {
                father->setLeft(leftSon);
            }
            father->setLeft(leftSon);
            leftSon->setFather(father);
            leftSon->setRight(balancingPnt);
            balancingPnt->setLeft(rightOfLeft);
        }
    }


    void roll_RR(Node<T> *balancingPnt, bool isRight){
        Node<T> *rightSon = balancingPnt->getLeft();
        Node<T> *leftOfRight = rightSon != nullptr? rightSon->getLeft(): nullptr;
        Node<T> *father = balancingPnt->getFather();

        if(father == nullptr){
            this->root = rightSon;
            this->root->setFather(nullptr);
            rightSon->setLeft(balancingPnt);
            balancingPnt->setRight(leftOfRight);
        } else {
            if(isRight){
                father->setRight(rightSon);
            } else {
                father->setLeft(rightSon);
            }
            rightSon->setFather(father);
            rightSon->setLeft(balancingPnt);
            balancingPnt->setRight(leftOfRight);
        }
    }

    void roll_LR(Node<T> *balancingPnt, bool isRight) {
        Node<T> *leftSon = balancingPnt->getLeft();
        Node<T> *rightOfLeft = leftSon != nullptr ? leftSon->getLeft() : nullptr;
        Node<T> *leftOfRightOfLeft = rightOfLeft != nullptr ? rightOfLeft->getLeft() : nullptr;
        Node<T> *rightOfRightOfLeft = rightOfLeft != nullptr ? rightOfLeft->getRight() : nullptr;
        Node<T> *father = balancingPnt->getFather();

        if(father == nullptr){
            this->root = leftSon;
            leftSon->setFather(nullptr);
            rightOfLeft->setRight(balancingPnt);
            rightOfLeft->setLeft(leftSon);
            balancingPnt->setLeft(rightOfRightOfLeft);
            leftSon->setRight(leftOfRightOfLeft);
        } else {
            if(isRight){
                father->setRight(leftSon);
            } else {
                father->setLeft(leftSon);
            }
            rightOfLeft->setRight(balancingPnt);
            rightOfLeft->setLeft(leftSon);
            balancingPnt->setLeft(rightOfRightOfLeft);
            leftSon->setRight(leftOfRightOfLeft);
        }
    }


    void roll_RL(Node<T> *balancingPnt, bool isRight) {
        Node<T> *rightSon = balancingPnt->getRight();
        Node<T> *leftOfRight = rightSon != nullptr ? rightSon->getLeft() : nullptr;
        Node<T> *rightOfLeftOfRight = leftOfRight != nullptr ? leftOfRight->getRight() : nullptr;
        Node<T> *leftOfLeftOfRight = leftOfRight != nullptr ? leftOfRight->getRight() : nullptr;
        Node<T> *father = balancingPnt->getFather();

        if(father == nullptr){
            this->root = rightSon;
            rightSon->setFather(nullptr);
            leftOfRight->setRight(balancingPnt);
            leftOfRight->setLeft(rightSon);
            balancingPnt->setLeft(leftOfLeftOfRight);
            rightSon->setRight(rightOfLeftOfRight);
        } else {
            if(isRight){
                father->setRight(rightSon);
            } else {
                father->setLeft(rightSon);
            }
            leftOfRight->setRight(balancingPnt);
            leftOfRight->setLeft(rightSon);
            balancingPnt->setLeft(leftOfLeftOfRight);
            rightSon->setRight(rightOfLeftOfRight);
        }
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
