#include "Classes/SearchTree.cpp"
#include "Headers/Node.h"
#include "Headers/Group.h"
#include <iostream>
static bool testWithNumbers(){
    int size = 500;
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
    for (int j = 0; j < size - size/2 -1; j++) {
        if (prev > array[j]->getKey()) {
            std::cout << "Error: Not sorted\n";
            return false;
        }
        prev = array[j]->getKey();
    }
    return true;
}

int main() {
    if(testWithNumbers()){
        std::cout << "FINE\n";
    }
    return 0;
}

