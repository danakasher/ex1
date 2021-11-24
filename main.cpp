#include "SearchTree.cpp"
#include "Node.cpp"

int main(){
    SearchTree<int> tree = SearchTree<int>();
    int arr[50] = {0};
    int insert;
    bool canInsert;
    for(int i=0; i<50; i++){
        canInsert = false;
        while(!canInsert){
            insert = rand()%1000;
            canInsert = true;
            for(int j=0; j<50; j++){
                if(arr[j] == insert){
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insert;
        tree.insert(insert);
    }
    tree.print_in_order();
}