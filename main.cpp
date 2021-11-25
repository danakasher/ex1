#include "SearchTree.cpp"
#include "Node.cpp"
#include <iostream>

int main(){
    SearchTree<int, int> tree = SearchTree<int, int>();
    int arr[20] = {0};
    int insert;
    bool canInsert;
    for(int i=0; i<20; i++){
        canInsert = false;
        while(!canInsert){
            insert = rand()%1000;
            canInsert = true;
            for(int j=0; j<6; j++){
                if(j == insert){
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insert;
        tree.insert(insert, insert);
    }
    Node<int, int> **ar = tree.scanInOrder();
    for(int i=0; i<20; i++){
        std::cout << ar[0]->getData() << ", ";
        ar++;
    }
//    for (int i=0; i<50; i++)
//    {
//        tree.remove(arr[i]);
//    }
//    tree.scanInOrder();
}