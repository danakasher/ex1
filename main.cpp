#include "SearchTree.cpp"
#include "Node.cpp"

int main(){
    SearchTree<int> tree = SearchTree<int>();

    tree.insert(5);
    tree.insert(6);
    tree.print_in_order();
    cout<<"\n";
    tree.insert(2);
    tree.print_in_order();
    cout<<"\n";
    tree.insert(3);
    tree.print_in_order();
    cout<<"\n";
    tree.insert(4);
    tree.print_in_order();
    cout<<"\n";
    tree.insert(10);
    tree.print_in_order();
    cout<<"\n";
    tree.insert(7);
    tree.print_in_order();
    cout<<"\n";
    tree.insert(8);
    tree.print_in_order();
    cout<<"\n";
    tree.insert(1);
    tree.print_in_order();
}