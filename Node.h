#ifndef EX1_NODE_H
#define EX1_NODE_H

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
    explicit Node<Key, Data>(Key const *k, Data const &val) : key(k), data(val), left(nullptr), right(nullptr), father(nullptr), height(0), balancingParameter(0) {};
    ~Node() = default;
    Data &getValue(){ return this->data; }
    Key &getKey(){ return this->key; }
    Node *getLeft(){ return this->left; }
    Node *getRight(){ return this->right; }
    void setLeft(Node *leftNode){
        this->left = leftNode;
    }
    void setRight(Node *rightNode){
        this->right = rightNode;
    }
    bool operator>(Node<Key, Data> &node) const {
        return this->data > (node->getValue());
    }

    bool operator==(Node<Key, Data> &node) const{
        return this->data == node->data;
    }
    bool operator>=(Node<Key, Data> &node) const{
        return  this ==node || this > node;
    }

    void setFather(Node<Key, Data> *prev){ this->father = prev;}

    Node<Key, Data> *getFather(){ return this->father; }
};


#endif //EX1_NODE_H
