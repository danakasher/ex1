#ifndef EX1_GROUP_H

#define EX1_GROUP_H
#include "Player.h"
#include "SearchTree.h"


class Group{
private:
    int groupId;
    PlayerKey currentHighest;
    SearchTree<PlayerKey, Player*> playerTree;
    void replaceHighestInGroup(Node<PlayerKey, Player*> *removedNode, PlayerKey const &key){
        if((!(key == this->currentHighest))){
            return;
        }

        currentHighest = PlayerKey();
        Node<PlayerKey, Player*> *rightmostLeft = playerTree.findRightmost(removedNode->getLeft());
        Node<PlayerKey, Player*> *father = removedNode->getFather();

        if(rightmostLeft != nullptr){
            this->currentHighest = this->currentHighest < rightmostLeft->getKey()? rightmostLeft->getKey():this->currentHighest;
        }

        if(father != nullptr){
            this->currentHighest = this->currentHighest < father->getKey()? father->getKey():this->currentHighest;
        }
    }

public:
    Group(const Group &group) = delete;
    Group &operator=(const Group &group) = delete;
    explicit Group(int id): groupId(id){}
    ~Group(){
        playerTree.~SearchTree();
    }

    int getId(){ return this->groupId; }

    PlayerKey getCurrentHighest() const { return this->currentHighest; }

    void insertPlayer(Player *newPlayer){
        PlayerKey key = PlayerKey(newPlayer);
        Node<PlayerKey, Player*> *playerNode = new Node<PlayerKey, Player*>(key, newPlayer);
        playerTree.insert(playerNode);
        if(key > currentHighest || playerTree.getSize() == 1){
            currentHighest = key;
        }
    }

    void removePlayer(int playerId, int playerLevel){
        PlayerKey playerKey = PlayerKey(playerId, playerLevel);
        Node<PlayerKey, Player*> *playerNode = playerTree.find(playerKey);
        if(playerNode == nullptr){
            return;
        }
        replaceHighestInGroup(playerNode, playerKey);
        playerTree.remove(playerKey);
    }

    void toArray(Node<PlayerKey, Player*> ***array){
        playerTree.scanInOrder(array);
    }

    void merge(Group *group){
        auto **arr = new Node<PlayerKey, Player*>*[group->getSize()];
        group->toArray(&arr);
        playerTree.mergeWith(arr, group->getSize());
        for(int i=0; i<group->getSize(); i++){
            arr[i]->getData()->setGroupId(this->groupId);
        }
        if(currentHighest < group->getCurrentHighest()){
            currentHighest = group->getCurrentHighest();
        }
        delete[] arr;
    }

    int getSize(){
        return this->playerTree.getSize();
    }
};

#endif //EX1_GROUP_H
