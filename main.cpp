#include "SearchTree.cpp"
#include "Node.cpp"

int main(){
    SearchTree<int, int> tree = SearchTree<int, int>();
    int arr[100] = {0};
    int insert;
    bool canInsert;
    for(int i=0; i<100; i++){
        canInsert = false;
        while(!canInsert){
            insert = rand()%1000;
            canInsert = true;
            for(int j=0; j<100; j++){
                if(arr[j] == insert){
                    canInsert = false;
                    break;
                }
            }
        }
        arr[i] = insert;
        tree.insert(insert, insert);
    }
    tree.print_in_order();
}