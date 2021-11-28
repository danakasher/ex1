#include "../Headers/Group.h"

void Group::replaceHighestInGroup(Node<PlayerKey, int> *removedNode, PlayerKey const &key) {
    if((!(key == this->currentHighest))){
        return;
    }

    currentHighest = PlayerKey();
    Node<PlayerKey, int> *leftSon = removedNode->getLeft();
    Node<PlayerKey, int> *father = removedNode->getFather();

    if(leftSon != nullptr){
        this->currentHighest = this->currentHighest < leftSon->getKey()? leftSon->getKey():this->currentHighest;
    }

    if(father != nullptr){
        this->currentHighest = this->currentHighest < father->getKey()? father->getKey():this->currentHighest;
    }
}
