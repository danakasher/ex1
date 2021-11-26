#include "Classes/SearchTree.cpp"
#include "Headers/Node.h"
#include "Headers/Group.h"
#include <iostream>
bool testWithNumbers(){
    int size = 1000;
    SearchTree<int, int> tree = SearchTree<int, int>();
    int *arr = new int[size];
    int insertRand;
    bool canInsert;
    Node<int, int> **array;
    int prev;
    for (int i = 0; i < size; i++) {
        canInsert = false;
        while (!canInsert) {
            insertRand = rand() % (size*10);
            canInsert = true;
            for (int j = 0; j < size; j++) {
                if (arr[j] == insertRand) {
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insertRand;
        if(!tree.isBalanced()){
            std::cout << "WELL WELLLLLLLL";
            return false;
        }
        tree.insert(insertRand, insertRand);
    }

    for (int i = 0; i < size/2; i++) {
        tree.remove(arr[i]);
        if(!tree.isBalanced()){
            std::cout << "WELL WELLLLLLLL";
            return false;
        }
    }

    array = tree.scanInOrder();
    prev = -1;
    for (int j = 0; j < tree.getSize(); j++) {
        if (prev > array[j]->getKey()) {
            std::cout << "Error: Not sorted\n";
            return false;
        }
        prev = array[j]->getKey();
    }
    return true;
}

bool testWithPlayersAndGroups(){
    SearchTree<int, Group> groupsTree = SearchTree<int, Group>();
    int groups = 2, players = 200;
    int *groupIds = new int[groups];
    int insertRand;
    Group **dummy = new Group*[groups];
    bool canInsert;
    int prev;
    Node<int, Group> *node;
    for (int i = 0; i < groups; i++) {
        canInsert = false;
        while (!canInsert) {
            insertRand = rand() % (groups*10);
            canInsert = true;
            for (int j = 0; j < groups; j++) {
                if (groupIds[j] == insertRand) {
                    canInsert = false;
                    break;
                }
            }
        }
        groupIds[i] = insertRand;
        dummy[i] = new Group(insertRand);
        if(!groupsTree.isBalanced()){
            std::cout << "WELL WELLLLLLLL";
            return false;
        }
        node = new Node<int, Group>(insertRand, *dummy[i]);
        groupsTree.insert(node);
    }
    int randGroup;
    int randLevel, randId;
    int *ids = new int[players];
    for(int i=0; i<players; i++){
        ids[i] = i;
    }
    bool pickedId;
    for(int i=0; i<players; i++){
        pickedId = false;
        randGroup = rand()%groups;
        randLevel = rand()%10;
        while(!pickedId){
            randId = rand()%players;
            if(ids[randId] != -1){
                ids[randId] = -1;
                pickedId = true;
            }
        }
        groupsTree.find(groupIds[randGroup])->getData().insertPlayer(randId, randLevel);
    }
    return true;
}
int main() {
    if(testWithNumbers()){
        std::cout << "FINE\n";
    }
    if(testWithPlayersAndGroups()){
        std::cout << "FINE\n";
    }
    return 0;
}

