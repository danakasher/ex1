#include "Headers/PlayerManager.h"

bool isSorted(SearchTree<int, int> &tree){
    Node<int, int> **array = tree.scanInOrder();

    int prev = -1;
    for(int k=0; k<tree.getSize(); k++){
//        if(k == tree.getSize()-1){
//            std::cout << array[k]->getKey() << "\n";
//        } else {
//            std::cout << array[k]->getKey() << " ";
//        }
        if (prev > (array[k]->getKey())) {
            return false;
        }
        prev = array[k]->getKey();
    }
    return true;
}

bool testWithNumbers(){
    int size = 50;
    SearchTree<int, int> tree;
    SearchTree<int, int> tree2;
    int *arr = new int[size*2];
    int insertRand;
    bool canInsert;
    for (int i = 0; i < size; i++) {
        canInsert = false;
        while (!canInsert) {
            insertRand = rand() % (size*100);
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

    for (int i = 0; i < size; i++) {
        canInsert = false;
        while (!canInsert) {
            insertRand = rand() % ((size)*100);
            canInsert = true;
            for (int j = 0; j < size; j++) {
                if (arr[j] == insertRand) {
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insertRand;
        if(!tree2.isBalanced()){
            std::cout << "WELL WELLLLLLLL";
            return false;
        }
        tree2.insert(insertRand, insertRand);
    }

    tree.mergeWith(tree2.scanInOrder(), tree2.getSize());

    for (int i = 0; i < size/2; i++) {
        tree.remove(arr[i]);
        if(!isSorted(tree)){
            std::cout << "Not sorted";
            return false;
        }
        if(tree.find(arr[i]) != nullptr){
            std::cout << "WELL";
        }
        if(!tree.isBalanced()){
            std::cout << "WELL WELLLLLLLL";
            return false;
        }
    }
    return true;
}

bool testWithPlayersAndGroups(){
    PlayerManager manager;
    int *playerId = new int();
    manager.AddGroup(1);
    manager.AddGroup(2);

    manager.AddPlayer(123, 1, 2);
    manager.AddPlayer(122, 1, 1);
    manager.GetHighestLevel(-1, playerId);
    if(*playerId != 123){
        return false;
    }
    manager.AddPlayer(121, 1, 2);
    manager.GetHighestLevel(-1, playerId);
    if(*playerId != 121){
        return false;
    }
    manager.GetHighestLevel(2, playerId);
    if(*playerId != 1){
        return false;
    }
    if(manager.RemovePlayer(3) != FAILURE){
        return false;
    }
    manager.AddPlayer(1, 1, 1);
    manager.AddPlayer(2, 1, 1);
    manager.AddPlayer(2, 1, 1);
    manager.AddPlayer(2, 1, 1);
    manager.AddPlayer(2, 1, 1);
    manager.AddPlayer(2, 1, 1);
    manager.AddPlayer(2, 1, 1);



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

