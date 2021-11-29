#include "Headers/PlayerManager.h"

bool isSorted(SearchTree<int, int> &tree){
    Node<int, int> **array = tree.scanInOrder();

    int prev = -1;
    for(int k=0; k<tree.getSize(); k++){
        if(k == tree.getSize()-1){
            std::cout << array[k]->getKey() << "\n";
        } else {
            std::cout << array[k]->getKey() << " ";
        }
        if (prev > (array[k]->getKey())) {
            return false;
        }
        prev = array[k]->getKey();
    }
    return true;
}

bool testWithNumbers(){
    int size = 5;
    SearchTree<int, int> tree;
    SearchTree<int, int> tree2;
    int *arr = new int[size];
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

    isSorted(tree);
    std::cout <<"\n";
    isSorted(tree2);
    std::cout <<"\n";
    tree.mergeWith(tree2.scanInOrder(), tree2.getSize());
    std::cout<<"\nMerged Tree: ";
    isSorted(tree);
    std::cout <<"\n";

//    for (int i = 0; i < size/2; i++) {
//        tree.remove(arr[i]);
//        if(!isSorted(tree)){
//            std::cout << "Not sorted";
//            return false;
//        }
//        if(tree.find(arr[i]) != nullptr){
//            std::cout << "WELL";
//        }
//        if(!tree.isBalanced()){
//            std::cout << "WELL WELLLLLLLL";
//            return false;
//        }
//    }
    return true;
}

bool testWithPlayersAndGroups(){
    PlayerManager manager;
    manager.AddGroup(1);

    int *playerId = new int();

    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.GetHighestLevel(-1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(11, 1, 1);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(2, 1, 3);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(3, 1, 1);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(4, 1, 1);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(4, 1, 2);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(5, 1, 3);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(6, 1, 4);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(7, 1, 2);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.RemovePlayer(6);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";
    manager.AddPlayer(8, 1, 4);
    manager.GetHighestLevel(1, playerId);
    std::cout << *playerId << "\n";

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

