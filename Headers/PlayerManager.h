#ifndef EX1_PLAYERMANAGER_H
#define EX1_PLAYERMANAGER_H
#include "Group.h"
#include "library1.h"
#include <memory>

class PlayerManager {
    typedef std::shared_ptr<Player> PlayerOwner;
    typedef std::shared_ptr<Group> GroupOwner;

private:
    //TODO: Make everything a pointer
    PlayerKey currentHighest;
    SearchTree<int, PlayerOwner> playerTree;
    SearchTree<int, GroupOwner> groupTree;
    SearchTree<int, Group*> nonEmptyGroupTree;
    void replaceIfHighestRemoved(Node<int, PlayerOwner> *removedNode){
        Player *player = removedNode->getData().get();
        PlayerKey nodeKey = PlayerKey(player);
        if((!(nodeKey == this->currentHighest))){
            return;
        }

        currentHighest = PlayerKey();
        Node<int, PlayerOwner> *leftSon = removedNode->getLeft();
        Node<int, PlayerOwner> *father = removedNode->getFather();

        if(leftSon != nullptr){
            PlayerKey leftKey = PlayerKey(leftSon->getData().get());
            this->currentHighest = this->currentHighest < leftKey? leftKey:this->currentHighest;
        }

        if(father != nullptr){
            PlayerKey fatherKey = PlayerKey(father->getData().get());
            this->currentHighest = this->currentHighest < fatherKey? fatherKey:this->currentHighest;
        }
    }

public:
    PlayerManager(const PlayerManager &manager) = delete;
    PlayerManager &operator=(const PlayerManager &manager) = delete;
    explicit PlayerManager(): currentHighest(){}

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

    StatusType RemovePlayer(const int playerID){
        if(playerID <= 0){
            return INVALID_INPUT;
        }

        Node<int, PlayerOwner> *node = playerTree.find(playerID);
        if(node == nullptr){
            return FAILURE;
        }

        PlayerOwner playerOwner = node->getData();

        replaceIfHighestRemoved(node);

        Node<int, GroupOwner> *groupNode = groupTree.find(playerOwner->getGroupId());
        GroupOwner groupOwner = groupNode->getData();

        playerTree.remove(playerID);
        groupOwner->removePlayer(playerID, playerOwner->getLevel());

        if(groupOwner->getSize() == 0) {
            nonEmptyGroupTree.remove(groupOwner->getId());
        }
        return SUCCESS;
    }

    void Quit(){
        groupTree.~SearchTree();
        playerTree.~SearchTree();
    }

    StatusType ReplaceGroup(int groupId, int replacementId)
    {
        if ( groupId <=0  || replacementId <= 0 || groupId == replacementId){
            return INVALID_INPUT;
        }

        Node<int, GroupOwner> *group = groupTree.find(groupId);
        Node<int, GroupOwner> *replacementGroup = groupTree.find(replacementId);
        if(group == nullptr || replacementGroup == nullptr){
            return FAILURE;
        }

        GroupOwner toRemoveOwner = group->getData();
        GroupOwner toMergeOwner = replacementGroup->getData();

        toMergeOwner->merge(toRemoveOwner.get());

        groupTree.remove(toRemoveOwner->getId());
        nonEmptyGroupTree.remove(toRemoveOwner->getId());

        return SUCCESS;
    }

    StatusType IncreaseLevel(int PlayerID, int increaseBy){
        if (PlayerID <= 0 || increaseBy <= 0){
            return INVALID_INPUT;
        }

        Node<int, PlayerOwner> *playerNode = this->playerTree.find(PlayerID);
        if (playerNode == nullptr){
            return FAILURE;
        }

        PlayerOwner playerOwner = playerNode->getData();

        Group *group = this->nonEmptyGroupTree.find(playerOwner->getGroupId())->getData();

        group->increaseLevel(playerOwner.get(), increaseBy);
        playerOwner->increaseLevel(increaseBy);

        return SUCCESS;
    }

    StatusType GetHighestLevel(int groupId, int *playerId){
        if (playerId == nullptr || groupId == 0){
            return INVALID_INPUT;
        }
        if (groupId < 0){
            *playerId = currentHighest.getId();
            return SUCCESS;
        }

        Node<int, GroupOwner> *groupNode = groupTree.find(groupId);
        if (groupNode == nullptr) {
            return FAILURE;
        }

        GroupOwner groupOwner = groupNode->getData();
        *playerId = groupOwner->getCurrentHighest().getId();
        return SUCCESS;
    }

    StatusType GetAllPlayersByLevel (int groupID, int **players, int *numOfPlayers){
        if (groupID == 0 || players == nullptr || numOfPlayers == nullptr){
            return INVALID_INPUT;
        }
        Node<int, PlayerOwner> **playerNodes;
        Node<PlayerKey, Player*> **groupPlayerNodes;
        if (groupID < 0){
            *numOfPlayers = this->playerTree.getSize();
            if (this->playerTree.getSize()==0){
                return SUCCESS;
            }
            else {
                try{
                    playerNodes = playerTree.scanInOrder();
                    (*players) = new int[playerTree.getSize()];
                } catch (std::bad_alloc &e){
                    return ALLOCATION_ERROR;
                }
                for(int i=0; i<playerTree.getSize(); i++){
                    (*players)[i] = playerNodes[i]->getKey();
                }
            }
        }
        else{
            Node<int, GroupOwner> *groupNode = this->groupTree.find(groupID);
            if (groupNode == nullptr){
                return FAILURE;
            }
            GroupOwner groupOwner = groupNode->getData();
            *numOfPlayers= groupOwner->getSize();
            if (*numOfPlayers == 0){
                return SUCCESS;
            }
            else {
                try{
                    groupPlayerNodes = groupOwner->toArray();
                    (*players) = new int[groupOwner->getSize()];
                } catch (std::bad_alloc &e){
                    return ALLOCATION_ERROR;
                }
                for(int i=0; i<playerTree.getSize(); i++){
                    (*players)[i] = groupPlayerNodes[i]->getKey().getId();
                }
            }
        }
        return SUCCESS;
    }

    StatusType GetGroupsHighestLevel(int numOfGroups, int **players){
        if(players == nullptr || numOfGroups < 1){
            return INVALID_INPUT;
        }
        Node<int, Group*> **groupArr;
        try{
            groupArr = this->nonEmptyGroupTree.scanInOrder();
            (*players) = (int*)(malloc(sizeof(int) * playerTree.getSize()));
        } catch(std::bad_alloc &e){
            return ALLOCATION_ERROR;
        }
        for (int i=0; i<numOfGroups; i++){
            (*players)[i] = groupArr[i]->getData()->getCurrentHighest().getId();
        }
        return SUCCESS;
    }
};


#endif //EX1_PLAYERMANAGER_H
