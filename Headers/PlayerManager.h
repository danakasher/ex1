#ifndef EX1_PLAYERMANAGER_H
#define EX1_PLAYERMANAGER_H
#include "Group.h"
#include "library.h"
#include <memory>

class PlayerManager {
    typedef std::shared_ptr<Player> PlayerOwner;
    typedef std::shared_ptr<Group> GroupOwner;

private:
    PlayerKey currentHighest;
    SearchTree<int, PlayerOwner> playerTree;
    SearchTree<int, GroupOwner> groupTree;
    SearchTree<int, Group*> nonEmptyGroupTree;
    void replaceHighestInSystem(Node<PlayerKey, int> *currentHighest, PlayerKey const &key);

public:
    explicit PlayerManager(): currentHighest(PlayerKey(-1, -1)){

    }

    ~PlayerManager(){
        //TODO
    }

    StatusType AddGroup(int groupID){

        if (groupID<=0){
            return INVALID_INPUT;
        }
        if(groupTree.find(groupID) != nullptr){
            return FAILURE;
        }
        Group *group;
        try{
            group = new Group(groupID);
        } catch (std::bad_alloc &e){
            return ALLOCATION_ERROR;
        }

        GroupOwner owner(group);

        groupTree.insert(groupID, owner);
        return SUCCESS;
    }

    StatusType AddPlayer(int playerId, int groupId, int level) {
        if (playerId<=0 || groupId<=0 || level<=0){
            return INVALID_INPUT;
        }

        Node<int, GroupOwner> *groupNode = groupTree.find(groupId);
        if(playerTree.find(playerId) != nullptr || groupNode == nullptr){
            return FAILURE;
        }

        Player *newPlayer;
        try {
            newPlayer = new Player(playerId, level, groupId);
        } catch (std::bad_alloc &exception){
            return ALLOCATION_ERROR;
        }

        PlayerOwner playerOwner(newPlayer);

        Node<int, PlayerOwner> *playerNode;
        try{
            playerNode = new Node<int, PlayerOwner>(playerOwner->getId(), playerOwner);
        } catch (std::bad_alloc &exception){
            return ALLOCATION_ERROR;
        }

        GroupOwner groupOwner = groupNode->getData();
        Group *group = groupOwner.get();
        groupOwner->insertPlayer(playerOwner.get());

        if(groupOwner->getSize() == 1){
            nonEmptyGroupTree.insert(groupId, group);
        }

        playerTree.insert(playerId, playerOwner);

        PlayerKey temp = PlayerKey(playerOwner->getId(), playerOwner->getLevel());
        if(temp > this->currentHighest || playerTree.getSize() == 1){
            this->currentHighest = temp;
        }

        return SUCCESS;
    }

    StatusType RemovePlayer(int playerID){
        if(playerID <= 0){
            return INVALID_INPUT;
        }

        Node<int, PlayerOwner> *node = playerTree.find(playerID);
        if(node == nullptr){
            return FAILURE;
        }

        PlayerOwner playerOwner = node->getData();

        //TODO
//       replaceIfHighest(playerNode, PlayerID);

        Node<int, GroupOwner> *groupNode = groupTree.find(playerOwner->getGroupId());
        GroupOwner groupOwner = groupNode->getData();

        playerTree.remove(playerID);
        groupOwner->removePlayer(playerID, playerOwner->getLevel());

        if(groupOwner->getSize() == 0) {
            nonEmptyGroupTree.remove(groupOwner->getId());
        }
        else {
            //לשים את השלב הכי גבוה החדש בדאטה של החוליה של הקבוצה בעץ הלא ריקות
            // מה???
        }
        return SUCCESS;
    }

//    StatusType ReplaceGroup(int groupId, int replacementId)
//    {
//        if ((GroupID<=0)||(ReplacementID<=0)||(GroupID==replacementId))
//        {
//            //return std::invalid_argument;
//            //ToDo
//        }
//        Group group = groupTree.find(groupId);
//        if (group == nullptr)
//        {
//            //return Failure
//            //Todo
//        }
//        Node<PlayerKey, int> **arr = group.toArray();
//        if (arr== nullptr)
//        {
//            //return Allocation Error
//            //Todo
//        }
//        Group newGroup = groupTree.find(ReplacementID);
//        if (newGroup== nullptr)
//        {
//                //return Failure
//                //Todo
//        }
//        if (group.getSize()>0){
//            this->UnEmptyGroupTree.remove(GroupID);
//        }
//        for (int i=0;i<group.getSize(); i++)
//        {
//            newGroup.insertPlayer(arr[i].getId(), arr[i].getLevel());
//        }
//        this->groupTree.remove(GroupID);
//        //לעדכן את הרמה הכי גבוהה של הקבוצה בעץ הלא ריקות
//        //return Success
//    }
//    StatusType IncreaseLevel (int PlayerID, int LevelIncrease)
//    {
//        if ((PlayerID<=0)||(LevelIncrease<=0))
//        {
//            //return InvalidInput
//            //Todo
//        }
//        Player player = this->playerTree.find(PlayerID);
//        if (player==nullptr)
//        {
//            //return allocation error
//            //todo
//        }
//        Group group = this->groupTree.find(player.getGroupId());
//        if (group==nullptr)
//        {
//            //return allocation error
//            //todo
//        }
//        group.increaseLevel(PlayerID,player.getLevel(), LevelIncrease);
//        player.increaseLevel(LevelIncrease);
//        //לעדכן גם בעץ הלא ריקות
//        //return success
//    }
//    void GetHighestLevel(int GroupID, int *PlayerID)
//    {
//        if ((playerID==nullptr)||(GroupId==0))
//        {
//            //return Invalid input
//            //todo
//        }
//        if (GroupID<0)
//        {
//            return currentHighest;
//        }
//        Group group = this->groupTree.find(GroupID);
//        if (group==nullptr)
//        {
//            //return failure;
//            //todo
//        }
//        *PlayerID = group.getCurrentHighest().getId();
//        //return success
//    }
//    void GetAllPlayersByLevel (int GroupID, int **Players, int *numOfPlayers)
//    {
//        if ((GroupID==0)||(Players==nullptr)||(numOfPlayers== nullptr))
//        {
//            //return invalid input
//            //todo
//        }
//        if (GroupID<0){
//            *numOfPlayers = this->playerTree.getSize();
//            if (this->playerTree.getSize()==0)
//            {
//                **Players = nullptr;
//            }
//            else {**Players = this->playerTree.scanInOrder();}
//        }
//        else{
//            Group group = this->groupTree.find(GroupID);
//            if (group== nullptr){
//                //return failure
//            }
//            *numOfPlayers=group.getSize();
//            if (group.getSize()==0)
//            {
//                **Players = nullptr;
//            }
//            else {**Players = group.toArray();}
//        }
//        //return success
//    }
//    void GetGroupsHighestLevel (int numOfGroups, int **Players){
//        auto *GroupArr = this->UnEmptyGroupTree.scanInOrder();
//        auto *PlayerArr = new Node<PlayerKey, int>*[numOfGroups]
//        for (int i=0; i<this->UnEmptyGroupTree.getSize();i++)
//        {
//           // PlayerArr[i] = GroupArr[i].getData();
//           //Todo
//        }
//    }
};


#endif //EX1_PLAYERMANAGER_H
