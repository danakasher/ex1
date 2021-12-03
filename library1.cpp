#include "library1.h"
#include "PlayerManager.h"

void *Init(){
    PlayerManager *manager;
    try{
        manager = new PlayerManager();
    } catch (std::bad_alloc &e){
        return nullptr;
    }
    return manager;
}

StatusType AddGroup(void *DS, int GroupID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->AddGroup(GroupID);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->AddPlayer(PlayerID, GroupID, Level);
}

StatusType RemovePlayer(void *DS, int PlayerID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->RemovePlayer(PlayerID);
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->ReplaceGroup(GroupID, ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->IncreaseLevel(PlayerID, LevelIncrease);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->GetHighestLevel(GroupID, PlayerID);
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->GetAllPlayersByLevel(GroupID, Players, numOfPlayers);
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((PlayerManager*)DS)->GetGroupsHighestLevel(numOfGroups, Players);
}

void Quit(void** DS){
    ((PlayerManager*)*DS)->Quit();
    ((PlayerManager*)*DS)->~PlayerManager();
    *DS = nullptr;
}
