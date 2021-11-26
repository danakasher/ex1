#ifndef EX1_GROUP_H

#define EX1_GROUP_H
#include "Player.h"
#include "Level.h"
#include "SearchTree.h"

class Group{
private:
    const int groupId;
    int currentHighestLevel, highestPlayerId;
    SearchTree<PlayerKey, int> playerTree;


public:
    explicit Group(int id): groupId(id), currentHighestLevel(-1), highestPlayerId(-1), playerTree(){};
    ~Group(){
        //TODO
    }
    int getId(){ return this->groupId; }
    int getCurrentHighestLevel(){ return this->currentHighestLevel; }
    int getHighestPlayerId(){ return this->highestPlayerId; }
    void increaseLevel(int id, int oldLevel, int increaseBy){
        PlayerKey oldKey = PlayerKey(id, oldLevel);
        PlayerKey newKey = PlayerKey(id, oldLevel + increaseBy);
        playerTree.remove(oldKey);
        playerTree.insert(new Node<PlayerKey, int>(newKey, 0));
    }
    void insertPlayer(Node<PlayerKey, int> *playerNode){
        playerTree.insert(playerNode);
        PlayerKey key = playerNode->getKey();
        if(key.getLevel() > currentHighestLevel){
            currentHighestLevel = key.getLevel();
            highestPlayerId = key.getId();
        }
    }
    void removePlayer(PlayerKey key){
     playerTree.remove(key);
    }
};

#endif //EX1_GROUP_H
