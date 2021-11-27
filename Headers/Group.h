#ifndef EX1_GROUP_H

#define EX1_GROUP_H
#include "Player.h"
#include "SearchTree.h"


class Group{
private:
    const int groupId;
    PlayerKey currentHighest;
    SearchTree<PlayerKey, int> playerTree;
    void replaceIfHighest(Node<PlayerKey, int> *currentHighest, PlayerKey const &key);

public:
    explicit Group(int id): groupId(id), currentHighest(PlayerKey(-1, -1)){
        playerTree = SearchTree<PlayerKey, int>();
    }
    ~Group(){
        //TODO
    }
    int getId(){ return this->groupId; }
    PlayerKey getCurrentHighest() const { return this->currentHighest; }
    void increaseLevel(int id, int oldLevel, int increaseBy){
        PlayerKey oldKey = PlayerKey(id, oldLevel);
        PlayerKey newKey = PlayerKey(id, oldLevel + increaseBy);
        playerTree.remove(oldKey);
        if(oldKey == currentHighest){
            currentHighest = newKey;
        }
        playerTree.insert(new Node<PlayerKey, int>(newKey, id));
    }
    void insertPlayer(int id, int level){
        PlayerKey key = PlayerKey(id, level);
        Node<PlayerKey, int> *playerNode = new Node<PlayerKey, int>(key, id);
        playerTree.insert(playerNode);
        if(key > currentHighest || playerTree.getSize() == 1){
            currentHighest = key;
        }
    }
    void removePlayer(PlayerKey key){
        Node<PlayerKey, int> *playerNode = playerTree.find(key);
        if(playerNode == nullptr){
            return;
        }
        replaceIfHighest(playerNode, key);
        playerTree.remove(key);
    }
    Node<PlayerKey, int> **toArray(){
        return playerTree.scanInOrder();
    }
    int getSize()
    {
        return this->playerTree.getSize();
    }
};

#endif //EX1_GROUP_H
