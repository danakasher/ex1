#ifndef EX1_GROUP_H

#define EX1_GROUP_H
#include "Player.h"
#include "SearchTree.h"


class Group{
private:
    int groupId;
    int size;
    PlayerKey currentHighest;
    SearchTree<PlayerKey, int> playerTree;
    void replaceHighestInGroup(Node<PlayerKey, int> *currentHighest, PlayerKey const &key);

public:
    Group(const Group &group) = delete;
    Group &operator=(const Group &group) = delete;
    explicit Group(int id): groupId(id), size(0), currentHighest(PlayerKey(-1, -1)){}
    ~Group(){
        //TODO
    }

    int getId(){ return this->groupId; }

    PlayerKey getCurrentHighest() const { return this->currentHighest; }

    void increaseLevel(Player *player, int increaseBy){
        PlayerKey oldKey = PlayerKey(player->getId(), player->getLevel());
        playerTree.remove(oldKey);
        player->increaseLevel(increaseBy);
        insertPlayer(player);
    }

    void insertPlayer(Player *newPlayer){
        PlayerKey key = PlayerKey(newPlayer->getId(), newPlayer->getLevel());
        Node<PlayerKey, int> *playerNode = new Node<PlayerKey, int>(key, newPlayer->getId());
        playerTree.insert(playerNode);
        if(key > currentHighest || playerTree.getSize() == 1){
            currentHighest = key;
        }
        this->size = playerTree.getSize();
    }

    void removePlayer(int playerId, int playerLevel){
        PlayerKey playerKey = PlayerKey(playerId, playerLevel);
        Node<PlayerKey, int> *playerNode = playerTree.find(playerKey);
        if(playerNode == nullptr){
            return;
        }
        replaceHighestInGroup(playerNode, playerKey);
        playerTree.remove(playerKey);
    }

    Node<PlayerKey, int> **toArray(){
        return playerTree.scanInOrder();
    }

    int getSize(){
        return this->playerTree.getSize();
    }
};

#endif //EX1_GROUP_H
