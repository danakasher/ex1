#include "SearchTree.cpp"
#include "Node.cpp"
#include <iostream>

int main() {
    int size = 20;
    SearchTree<int, int> tree = SearchTree<int, int>();
    int arr[20] = {0};
    int insert;
    bool canInsert;
    for (int i = 0; i < size; i++) {
        canInsert = false;
        while (!canInsert) {
            insert = rand() % 100;
            canInsert = true;
            for (int j = 0; j < size; j++) {
                if (arr[j] == insert) {
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insert;
        if(!tree.isBalanced()){
            std::cout << "WELL WELLLLLLLL";
            return -1;
        }
        tree.insert(insert, insert);
        Node<int, int> **ar = tree.scanInOrder();
        for (int j = 0; j < i; j++) {
            std::cout << ar[0]->getData() << ", ";
            ar++;
        }
        std::cout << "\n";
    }

    Node<int, int> **array;
    for (int i = 0; i < size/2; i++) {
        tree.remove(arr[i]);
    }

    int prev;
    array = tree.scanInOrder();
    for (int j = 0; j < size - size/2 -1; j++) {
        prev = -1;
        if (prev > array[j]->getKey()) {
            std::cout << "Error: Not sorted\n";
            return -1;
        }
        prev = array[j]->getKey();
        std::cout << prev << ", ";
    }
    return 0;
}