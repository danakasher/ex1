#ifndef EX1_PLAYERMANAGER_H
#define EX1_PLAYERMANAGER_H
#include "Group.h"
#include "library1.h"
#include <memory>

//Current working
class PlayerManager {
    typedef std::shared_ptr<Player> PlayerOwner;
    typedef std::shared_ptr<Group> GroupOwner;

private:
    //TODO: Make everything a pointer
    PlayerKey currentHighest;
    SearchTree<int, PlayerOwner> playerTree;
    SearchTree<PlayerKey, Player*> playerByLevel;
    SearchTree<int, GroupOwner> groupTree;
    SearchTree<int, Group*> nonEmptyGroupTree;

    void replaceIfHighestRemoved(Node<PlayerKey, Player*> *removedNode){
        Player *player = removedNode->getData();
        PlayerKey nodeKey = PlayerKey(player);
        if((!(nodeKey == this->currentHighest))){
            return;
        }

        currentHighest = PlayerKey();
        Node<PlayerKey, Player*> *leftSon = playerByLevel.findRightmost(removedNode->getLeft());
        Node<PlayerKey, Player*> *father = removedNode->getFather();

        if(leftSon != nullptr){
            PlayerKey leftKey = PlayerKey(leftSon->getData());
            this->currentHighest = this->currentHighest < leftKey? leftKey:this->currentHighest;
        }

        if(father != nullptr){
            PlayerKey fatherKey = PlayerKey(father->getData());
            this->currentHighest = this->currentHighest < fatherKey? fatherKey:this->currentHighest;
        }
    }

public:
    PlayerManager(const PlayerManager &manager) = delete;
    PlayerManager &operator=(const PlayerManager &manager) = delete;
    explicit PlayerManager(): currentHighest(){}

    ~PlayerManager(){
        playerTree.~SearchTree();
        nonEmptyGroupTree.~SearchTree();
        groupTree.~SearchTree();
        currentHighest.~PlayerKey();
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
        if (playerId<=0 || groupId<=0 || level<0){
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
        PlayerKey playerKey = PlayerKey(playerId, level);
        playerByLevel.insert(playerKey, newPlayer);

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

        PlayerKey key = PlayerKey(playerOwner->getId(), playerOwner->getLevel());
        Node<PlayerKey, Player*> *nodeByLevel = playerByLevel.find(key);
        replaceIfHighestRemoved(nodeByLevel);

        int groupId = playerOwner->getGroupId();
        Node<int, Group*> *groupNode = nonEmptyGroupTree.find(groupId);
        Group *group = groupNode->getData();

        playerByLevel.remove(PlayerKey(playerID, playerOwner->getLevel()));
        playerTree.remove(playerID);
        group->removePlayer(playerID, playerOwner->getLevel());

        if(group->getSize() == 0) {
            nonEmptyGroupTree.remove(group->getId());
        }
        return SUCCESS;
    }

    void Quit(){
        groupTree.~SearchTree();
        playerTree.~SearchTree();
    }

    StatusType ReplaceGroup(int groupId, int replacementId){
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
        Group *toMerge = toMergeOwner.get();
        toMergeOwner->merge(toRemoveOwner.get());

        if(toMergeOwner->getSize() - toRemoveOwner->getSize() == 0 && toMergeOwner->getSize() != 0){
            nonEmptyGroupTree.insert(replacementId, toMerge);
        }

        groupTree.remove(groupId);
        nonEmptyGroupTree.remove(groupId);

        return SUCCESS;
    }

    StatusType IncreaseLevel(int playerID, int increaseBy){
        if (playerID <= 0 || increaseBy <= 0){
            return INVALID_INPUT;
        }

        Node<int, PlayerOwner> *playerNode = this->playerTree.find(playerID);
        if (playerNode == nullptr){
            return FAILURE;
        }

        PlayerOwner playerOwner = playerNode->getData();

        Group *group = this->nonEmptyGroupTree.find(playerOwner->getGroupId())->getData();

        PlayerKey oldKey = PlayerKey(playerID, playerOwner->getLevel());
        group->removePlayer(oldKey.getId(), oldKey.getLevel());
        playerByLevel.remove(oldKey);

        Player *player = playerOwner.get();
        player->increaseLevel(increaseBy);
        PlayerKey newKey = PlayerKey(player->getId(), player->getLevel());
        playerByLevel.insert(newKey, player);
        group->insertPlayer(player);

        if(currentHighest < newKey){
            currentHighest = newKey;
        }

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
        if (groupID < 0){
            *numOfPlayers = this->playerTree.getSize();
            if (this->playerTree.getSize()==0){
                *players = nullptr;
                return SUCCESS;
            }
            else {
                try{
                    auto **playerNodes = new Node<PlayerKey, Player*>*[playerTree.getSize()];
                    playerByLevel.scanInOrder(&playerNodes);
                    (*players) = new int[playerTree.getSize()];
                    for(int i=playerTree.getSize()-1; i>=0; i--){
                        (*players)[playerTree.getSize()-1 - i] = playerNodes[i]->getKey().getId();
                    }
                    delete []playerNodes;
                } catch (std::bad_alloc &e){
                    return ALLOCATION_ERROR;
                }
            }
        }
        else{
            Node<int, GroupOwner> *groupNode = this->groupTree.find(groupID);
            if (groupNode == nullptr){
                return FAILURE;
            }
            GroupOwner groupOwner = groupNode->getData();
            Group *group = groupOwner.get();
            *numOfPlayers = groupOwner->getSize();
            if (*numOfPlayers == 0){
                (*players) = nullptr;
                return SUCCESS;
            }
            else {
                try{
                    Node<PlayerKey, Player*> **groupPlayerNodes = new Node<PlayerKey, Player*>*[groupOwner->getSize()];
                    groupOwner->toArray(&groupPlayerNodes);
                    (*players) = (int*)(malloc(sizeof(int) * groupOwner->getSize()));
                    for(int i=groupOwner->getSize()-1; i >=0; i--){
                        (*players)[groupOwner->getSize()-1 - i] = groupPlayerNodes[i]->getKey().getId();
                    }
                    delete[] groupPlayerNodes;
                } catch (std::bad_alloc &e){
                    return ALLOCATION_ERROR;
                }
            }
        }
        return SUCCESS;
    }

    StatusType GetGroupsHighestLevel(int numOfGroups, int **players){
        if(players == nullptr || numOfGroups < 1){
            return INVALID_INPUT;
        }

        if(numOfGroups > nonEmptyGroupTree.getSize()){
            return FAILURE;
        }

        try{
            auto **groupArr = new Node<int, Group*>*[numOfGroups];
            //auto **groupArr = new Node<int, Group*>*[nonEmptyGroupTree.getSize()];
            nonEmptyGroupTree.scanInOrderLimited(&groupArr, numOfGroups);
            (*players) = (int*)(malloc(sizeof(int) * numOfGroups));
            for (int i=0; i<numOfGroups; i++){
                (*players)[i] = groupArr[i]->getData()->getCurrentHighest().getId();
            }
            delete []groupArr;
        } catch(std::bad_alloc &e){
            return ALLOCATION_ERROR;
        }

        return SUCCESS;
    }
};


#endif //EX1_PLAYERMANAGER_H
