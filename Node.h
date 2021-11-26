#ifndef EX1_NODE_H
#define EX1_NODE_H

#include <cmath>

template <typename Key, typename Data>
class Node {
private:
    Key key;
    Data data;
    Node<Key, Data>* left;
    Node<Key, Data>* right;
    Node<Key, Data>* father;

public:
    int height, balancingParameter;
    explicit Node<Key, Data>(Key const &k, Data const &val) : key(k), data(val), left(nullptr),
                                        right(nullptr), father(nullptr), height(0), balancingParameter(0) {};
    ~Node() = default;
    const Data &getData() const { return this->data; }
    const Key &getKey() const { return this->key; }
    Node *getLeft() const { return this->left; }
    Node *getRight() const { return this->right; }
    void setLeft(Node* const leftNode){
        this->left = leftNode;
    }
    void setRight(Node* const rightNode){
        this->right = rightNode;
    }
    void setFather(Node<Key, Data>* const prev){ this->father = prev;}
    void calculateHeightAndBalance(){
        int heightLeft = this->getLeft() == nullptr? 0:this->getLeft()->height;
        int heightRight = this->getRight() == nullptr? 0:this->getRight()->height;
        this->height = fmax((double) heightRight, (double) heightLeft)+1;
        this->balancingParameter = heightLeft - heightRight;
    }
    Node<Key, Data> *getFather() const { return this->father; }
};


#endif //EX1_NODE_H
