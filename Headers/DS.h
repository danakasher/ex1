//
// Created by USER on 27/11/2021.
//

#ifndef EX1_DS_H
#define EX1_DS_H
#include "Player.h"
#include "SearchTree.h"
#include "Group.h"


class DS {
private:
    PlayerKey currentHighest;
    SearchTree<PlayerKey, int> playerTree;
    SearchTree<int, SearchTree<PlayerKey, int>> groupTree;
    SearchTree<int, PlayerKey> UnEmptyGroupTree;
    void replaceIfHighest(Node<PlayerKey, int> *currentHighest, PlayerKey const &key);

public:
    explicit DS(): currentHighest(PlayerKey(-1, -1)){
        playerTree = SearchTree<PlayerKey, int>();
        groupTree = SearchTree<int, SearchTree<PlayerKey, int>>();
        UnEmptyGroupTree = SearchTree<int, int>();

    }
    ~DS(){
        //TODO
    }

    void AddGroup(int GroupID){
        if (GroupID<=0){
            //return invalid input
            //todo
        }
        Node<PlayerKey, int> *GroupNode = new Node<int, SearchTree<PlayerKey, int>>(GroupID, nullptr);
        if (GroupNode== nullptr)
        {
            //return allocation error
        }
        groupTree.insert(GroupNode);
    }
    void AddPlayer(int PlayerID, int GroupID, int Level)
    {
        if ((PlayerID<=0)||(GroupID<=0)||(Level<=0)){
            //return invalid input
            //todo
        }
        Node<int, SearchTree<PlayerKey, int>> groupNode = groupTree.find(GroupID);
        if (groupNode== nullptr){
            //return failure
            //todo
        }
        Group group = groupNode.getData();
        group.insertPlayer(PlayerID,level);
        PlayerKey key = PlayerKey(id, level);
        Node<PlayerKey, int> *playerNode = new Node<PlayerKey, int>(key, id);
        if (playerNode== nullptr)
        {
            //return allocation error
        }
        this->playerTree.insert(playerNode);
        if(key > this->currentHighest || this->playerTree.getSize() == 1){
            this->currentHighest = key;
        }
        if (group.getSize()==1)
        {
            this->UnEmptyGroupTree.insert(GroupID, playerNode);
        }
        //צריך לעדכן את החוליה של הקבוצה בצומת הלא ריקה להצביע על השחקן ברמה הכי גבוהה
    }
    void RemovePlayer(int PlayerID)
    {
        //we need an option to find a player only by Id and not Level
        Node<PlayerKey, int> *playerNode = playerTree.find(PlayerID);
        if(playerNode == nullptr){
            return;
        }
        Player player =playerNode->getData();
        replaceIfHighest(playerNode, PlayerID);
        Node<int, SearchTree<PlayerKey, int>> *groupNode = groupTree.find(player.getGroupId());
        Group group = groupNode->getData();
        playerTree.remove(PlayerID);
        group.removePlayer(PlayerID);
        if (group.getSize()==0)
        {
            this->UnEmptyGroupTree.remove(group.getId());
        }
        else
        {
            //לשים את השלב הכי גבוה החדש בדאטה של החוליה של הקבוצה בעץ הלא ריקות
        }
        //return success
    }
    void ReplaceGroup(int GroupID, int ReplacementID)
    {
        if ((GroupID<=0)||(ReplacementID<=0)||(GroupID==ReplacementID))
        {
            //return std::invalid_argument;
            //ToDo
        }
        Group group = groupTree.find(groupId);
        if (group== nullptr)
        {
            //return Failure
            //Todo
        }
        Node<PlayerKey, int> **arr = group.toArray();
        if (arr== nullptr)
        {
            //return Allocation Error
            //Todo
        }
        Group newGroup = groupTree.find(ReplacementID);
        if (newGroup== nullptr)
        {
                //return Failure
                //Todo
        }
        if (group.getSize()>0){
            this->UnEmptyGroupTree.remove(GroupID);
        }
        for (int i=0;i<group.getSize(); i++)
        {
            newGroup.insertPlayer(arr[i].getId(), arr[i].getLevel());
        }
        this->groupTree.remove(GroupID);
        //לעדכן את הרמה הכי גבוהה של הקבוצה בעץ הלא ריקות
        //return Success
    }
    void IncreaseLevel (int PlayerID, int LevelIncrease)
    {
        if ((PlayerID<=0)||(LevelIncrease<=0))
        {
            //return InvalidInput
            //Todo
        }
        Player player = this->playerTree.find(PlayerID);
        if (player==nullptr)
        {
            //return allocation error
            //todo
        }
        Group group = this->groupTree.find(player.getGroupId());
        if (group==nullptr)
        {
            //return allocation error
            //todo
        }
        group.increaseLevel(PlayerID,player.getLevel(), LevelIncrease);
        player.increaseLevel(LevelIncrease);
        //לעדכן גם בעץ הלא ריקות
        //return success
    }
    void GetHighestLevel(int GroupID, int *PlayerID)
    {
        if ((playerID==nullptr)||(GroupId==0))
        {
            //return Invalid input
            //todo
        }
        if (GroupID<0)
        {
            return currentHighest;
        }
        Group group = this->groupTree.find(GroupID);
        if (group==nullptr)
        {
            //return failure;
            //todo
        }
        *PlayerID = group.getCurrentHighest().getId();
        //return success
    }
    void GetAllPlayersByLevel (int GroupID, int **Players, int *numOfPlayers)
    {
        if ((GroupID==0)||(Players==nullptr)||(numOfPlayers== nullptr))
        {
            //return invalid input
            //todo
        }
        if (GroupID<0){
            *numOfPlayers = this->playerTree.getSize();
            if (this->playerTree.getSize()==0)
            {
                **Players = nullptr;
            }
            else {**Players = this->playerTree.scanInOrder();}
        }
        else{
            Group group = this->groupTree.find(GroupID);
            if (group== nullptr){
                //return failure
            }
            *numOfPlayers=group.getSize();
            if (group.getSize()==0)
            {
                **Players = nullptr;
            }
            else {**Players = group.toArray();}
        }
        //return success
    }
    void GetGroupsHighestLevel (int numOfGroups, int **Players){
        auto *GroupArr = this->UnEmptyGroupTree.scanInOrder();
        auto *PlayerArr = new Node<PlayerKey, int>*[numOfGroups]
        for (int i=0; i<this->UnEmptyGroupTree.getSize();i++)
        {
           // PlayerArr[i] = GroupArr[i].getData();
           //Todo
        }



    }




}


#endif //EX1_DS_H
