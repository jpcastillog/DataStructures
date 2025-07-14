#include <iostream>
#include "../BinaryTree/avl.hpp"

template<typename TypeKey, typename TypeValue>
void printTraverse(vector<tuple<TypeKey, TypeValue>> traverse) {
    for (const auto& t : traverse) {
        cout << "(" << get<0>(t) << ", " << get<1>(t) << ") ";
    }
    cout << endl;   
}

int main(int argc, char* argv[]){
    avlTree<int, int> avl;
    
    // Insert some values
    avl.insert(7, 10);
    avl.insert(5, 6);
    avl.insert(10, 14);
    avl.insert(3, 4);
    avl.insert(4, 8);
    avl.insert (0, 12);

    vector<tuple<int, int>> traverse;
    // Test traversals
    cout << "-------------Testing traversals-------------" << endl;
    traverse = avl.breadthFirst();
    cout << "Breadth-first traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    traverse = avl.inOrder();
    cout << "In-order traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();
    
    traverse = avl.preOrder();
    cout << "Pre-order traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    traverse = avl.postOrder();
    cout << "Post-order traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();
    return 0;
}