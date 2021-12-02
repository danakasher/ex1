#ifndef EX1_NODE_H
#define EX1_NODE_H

#include <cmath>
#include <memory>

template <typename Key, typename Data>
class Node {
    typedef std::shared_ptr<Node<Key, Data>> NodeOwner;
private:
    const Key key;
    Data data;
    NodeOwner left = nullptr;
    NodeOwner right = nullptr;
    NodeOwner father = nullptr;

public:
    int height, balancingParameter;
    explicit Node<Key, Data>(Key const &k, Data const &val) : key(k), data(val), left(nullptr),
                                        right(nullptr), father(nullptr), height(0), balancingParameter(0) {};
    ~Node() = default;
    Data &getData() { return this->data; }
    const Key &getKey() const { return this->key; }
    Node *getLeft() const { return this->left; }
    Node *getRight() const { return this->right; }
    void setData(Data data){
        this->data=data;
    }
    void setLeft(Node* const leftNode){
        this->left = leftNode;
        if(leftNode != nullptr){
            leftNode->setFather(this);
        }
        this->calculateHeightAndBalance();
    }
    void setRight(Node* const rightNode){
        this->right = rightNode;
        if(rightNode != nullptr){
            rightNode->setFather(this);
        }
        this->calculateHeightAndBalance();
    }
    void setFather(Node<Key, Data>* const prev){ this->father = prev;}
    void calculateHeightAndBalance(){
        if(this->getLeft() == nullptr && this->getRight() == nullptr) {
            this->balancingParameter = 0;
            this->height = 0;
            return;
        }
        int heightLeft = this->getLeft() == nullptr? 0:this->getLeft()->height;
        int heightRight = this->getRight() == nullptr? 0:this->getRight()->height;
        this->height = fmax((double) heightRight, (double) heightLeft)+1;
        this->balancingParameter = heightLeft - heightRight;
    }
    Node<Key, Data> *getFather() const { return this->father; }
};


#endif //EX1_NODE_H
