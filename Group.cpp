#include "Level.cpp"
#include "SearchTree.cpp"

class Group{
private:
    int groupId;
    int currentHighestLevelPlayer;
    SearchTree<Level> levelTree;

public:
    Group(int id): groupId(id), currentHighestLevelPlayer(-1), levelTree(){};
    ~Group(){

    };
};