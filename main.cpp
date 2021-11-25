#include "SearchTree.cpp"
#include "Node.cpp"

int main(){
    SearchTree<int, int> tree = SearchTree<int, int>();
    int arr[100] = {0};
    int insert;
    bool canInsert;
    for(int & i : arr){
        canInsert = false;
        while(!canInsert){
            insert = rand()%1000;
            canInsert = true;
            for(int j : arr){
                if(j == insert){
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insert;
        tree.insert(insert, insert);
    }
    tree.scanInOrder();
    for (int i=0; i<50; i++)
    {
        tree.remove(arr[i]);
    }
    tree.scanInOrder();
}