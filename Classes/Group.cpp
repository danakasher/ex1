#include "../Headers/Group.h"

void Group::replaceHighestInGroup(Node<PlayerKey, Player*> *removedNode, PlayerKey const &key) {
    if((!(key == this->currentHighest))){
        return;
    }

    currentHighest = PlayerKey();
    Node<PlayerKey, Player*> *leftSon = removedNode->getLeft();
    Node<PlayerKey, Player*> *father = removedNode->getFather();

    if(leftSon != nullptr){
        this->currentHighest = this->currentHighest < leftSon->getKey()? leftSon->getKey():this->currentHighest;
    }

    if(father != nullptr){
        this->currentHighest = this->currentHighest < father->getKey()? father->getKey():this->currentHighest;
    }
}
