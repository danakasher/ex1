#include "Group.h"
#include "Player.cpp"
#include "SearchTree.cpp"

class Level{
private:
    int value;
    SearchTree<Player> playerById;

public:
    Level(int level): value(level){};
    ~Level(){
        //TODO
    }
    int getValue(){ return this->value; }

};

