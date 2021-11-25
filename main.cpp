#include "SearchTree.cpp"
#include "Node.cpp"
#include <iostream>

int main(){
    int size = 20;
    SearchTree<int, int> tree = SearchTree<int, int>();
    int arr[20] = {0};
    int insert;
    bool canInsert;
    for(int i=0; i<size; i++){
        canInsert = false;
        while(!canInsert){
            insert = rand()%100;
            canInsert = true;
            for(int j=0; j<size; j++){
                if(arr[j] == insert){
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insert;
        tree.insert(insert, insert);
    }
    Node<int, int> **ar = tree.scanInOrder();
    for(int i=0; i<size; i++){
        std::cout << ar[0]->getData() << ", ";
        ar++;
    }
   for (int i=0; i<size; i++) {
       tree.remove(arr[i]);
       Node<int, int> **array = tree.scanInOrder();
       std::cout << "\n ";
       int prev = -1;
       for (int j = 0; j < size-i-1; j++) {
           if(prev > array[0]->getData()){
               std::cout << "Error: Not sorted\n";
           }
           prev = array[0]->getData();
           std::cout << array[0]->getData() << ", ";
           array++;
       }
   }
}