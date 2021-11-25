#ifndef EX1_NODE_H
#define EX1_NODE_H

template <typename Data, typename Key>
class Node {
private:
    Data value;
    Key key;
    Node<Data, Key>* left;
    Node<Data,Key>* right;
    Node<Data,Key>* father;

public:
    int height, balancingParameter;
    explicit Node<Data,Key>(Data const &val) : value(val), left(nullptr), right(nullptr), father(nullptr), height(0), balancingParameter(0) {};
    ~Node() = default;
    Data &getValue(){ return this->value; }
    Node *getLeft(){ return this->left; }
    Node *getRight(){ return this->right; }
    void setLeft(Node *leftNode){
        this->left = leftNode;
    }
    void setRight(Node *rightNode){
        this->right = rightNode;
    }
    bool operator>(Node<Data,Key> &node) const {
        return this->value > (node->getValue());
    }

    bool operator==(Node<Data,Key> &node) const{
        return this->value == node->value;
    }
    bool operator>=(Node<Data,Key> &node) const{
        return  this ==node || this > node;
    }

    void setFather(Node<Data,Key> *prev){ this->father = prev;}

    Node<Data,Key> *getFather(){ return this->father; }
};


#endif //EX1_NODE_H
