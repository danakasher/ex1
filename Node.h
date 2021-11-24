#ifndef EX1_NODE_H
#define EX1_NODE_H

template <typename T> class Node {
private:
    T value; //TODO: shared ptr?
    Node<T>* left;
    Node<T>* right;
    Node<T>* father;

public:
    int height, balancingParameter;
    explicit Node<T>(T const &val) : value(val), left(nullptr), right(nullptr), father(nullptr) {};
    ~Node() = default;
    T &getValue(){ return this->value; }
    Node *getLeft(){ return this->left; }
    Node *getRight(){ return this->right; }
    void setLeft(Node *leftNode){
        this->left = leftNode;
    }
    void setRight(Node *rightNode){
        this->right = rightNode;
    }
    bool operator>(Node<T> &node) const {
        return this->value > (node->getValue());
    }

    bool operator==(Node<T> &node) const{
        return this->value == node->value;
    }
    bool operator>=(Node<T> &node) const{
        return  this ==node || this > node;
    }

    void setFather(Node<T> *father){ this->father = father;}

    Node<T> *getFather(){ return this->father; }
};


#endif //EX1_NODE_H
