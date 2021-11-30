#ifndef EX1_GROUP_H

#define EX1_GROUP_H
#include "Player.h"
#include "SearchTree.h"


class Group{
private:
    int groupId;
    PlayerKey currentHighest;
    SearchTree<PlayerKey, Player*> playerTree;
    void replaceHighestInGroup(Node<PlayerKey, Player*> *currentHighest, PlayerKey const &key);

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

    Node<PlayerKey, Player*> **toArray(){
        return playerTree.scanInOrder();
    }

    void merge(Group *group){
        Node<PlayerKey, Player*> **arr = group->toArray();
        playerTree.mergeWith(arr, group->getSize());
        for(int i=0; i<group->getSize(); i++){
            arr[i]->getData()->setGroupId(this->groupId);
        }
        if(currentHighest < group->getCurrentHighest()){
            currentHighest = group->getCurrentHighest();
        }
    }

    int getSize(){
        return this->playerTree.getSize();
    }
};

#endif //EX1_GROUP_H
