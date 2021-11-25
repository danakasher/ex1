#include "SearchTree.cpp"
#include "Node.cpp"
#include "Group.cpp"

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
        i = insert;
        tree.insert(insert, insert);
    }
}