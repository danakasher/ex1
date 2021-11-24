#ifndef EX1_GROUP_H
#define EX1_GROUP_H

#include "Level.cpp"
#include "SearchTree.cpp"
#include "Player.cpp"

class Group{
private:
    int groupId;
    int currentHighestLevelPlayer;
    int numberOfPlayers;
    SearchTree<Level> levelTree;

public:
    Group(int id): groupId(id), currentHighestLevelPlayer(-1), numberOfPlayers(0), levelTree(){};
    int getId(){ return this->groupId; }
    int getCurrentHighestLevelPlayer(){ return this->currentHighestLevelPlayer; }
    int getNumberOfPlayers(){ return this->numberOfPlayers; }
    void setCurrentHighestLevelPlayer(Player player){}
};

#endif //EX1_GROUP_H
