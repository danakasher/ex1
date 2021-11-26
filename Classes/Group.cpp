#include "../Headers/Group.h"

void Group::replaceIfHighest(Node<PlayerKey, int> *node, PlayerKey const &key) {
    if((!(key == this->currentHighest))){
        return;
    }

    Node<PlayerKey, int> *leftSon = node->getRight();
    Node<PlayerKey, int> *father = node->getFather();

    if(leftSon != nullptr){
        this->currentHighest = this->currentHighest < leftSon->getKey()? leftSon->getKey():this->currentHighest;
    }

    if(father != nullptr){
        this->currentHighest = this->currentHighest < father->getKey()? father->getKey():this->currentHighest;
    }
}
