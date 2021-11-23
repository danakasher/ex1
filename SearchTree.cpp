
template <typename T>
class Node{
private:
    T* value; //TODO: shared ptr?
    Node* left, right;

public:
    Node(T const *val) : value(val) {};
    ~Node() = default;
    T const *getValue(){ return this->value; }
    Node const *getLeft(){ return this->left; }
    Node const *getRight(){ return this->right; }
    Node const *setLeft(T const *value){
        this->left = Node(value);
    }
    Node const *setRight(T const *value){
        this->right = Node(value);
    }
    Node const *setLeft(Node const *leftNode){
        this->left = leftNode;
    }
    Node const *setRight(Node const *rightNode){
        this->right = rightNode;
    }
};

template <typename T>
class SearchTree{
private:
    Node* root;

public:
    SearchTree() = default;
    insert(T const *value);
    ~SearchTree(){
        //TODO
    }
};
