#include "SearchTree.cpp"
#include "Node.cpp"

int main(){
    SearchTree<int> tree = SearchTree<int>();

    tree.insert(5);
    tree.insert(6);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(10);
    tree.insert(7);
    tree.insert(8);
    tree.insert(1);
    tree.print_in_order();
}