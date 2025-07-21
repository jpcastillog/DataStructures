#include <iostream>
#include <cassert>
#include <vector>
#include "../BinaryTree/BinarySearchTree.hpp"

using namespace std;

template<typename TypeKey, typename TypeValue>
void printTraverse(vector<tuple<TypeKey, TypeValue>> traverse) {
    for (const auto& t : traverse) {
        cout << "(" << get<0>(t) << ", " << get<1>(t) << ") ";
    }
    cout << endl;   
}

int main(int argc, char* argv[]) {
    // Test the binary search tree implementation
    BinarySearchTree<int, int> bst;
    
    // Insert some values
    bst.insert(5, 10);
    bst.insert(3, 6);
    bst.insert(7, 14);
    bst.insert(2, 4);
    bst.insert(4, 8);
    bst.insert (6, 12);

    vector<tuple<int, int>> traverse;
    // Test traversals
    cout << "-------------Testing traversals-------------" << endl;
    traverse = bst.breadthFirst();
    cout << "Breadth-first traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    traverse = bst.inOrder();
    cout << "In-order traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();
    
    traverse = bst.preOrder();
    cout << "Pre-order traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    traverse = bst.postOrder();
    cout << "Post-order traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    // Test find
    cout << "-------------Testing find method-------------" << endl;
    Node<int, int>* target = bst.find(5);
    cout <<"Find node with key 5: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }
    target = bst.find(3);
    cout <<"Find node with key 3: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }
    target = bst.find(6);
    cout <<"Find node with key 6: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }
    target = bst.find(13);
    cout <<"Find node with key 13: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }

    // Test remove
    cout << "-------------Testing remove method-------------" << endl;
    cout << "Removing node with key 5: " << (bst.remove(5) ? "Removed" : "Not Found") << endl;
    traverse = bst.breadthFirst();
    cout << "Breadth-first traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();
    
    cout << "Removing node with key 2: " << (bst.remove(2) ? "Removed" : "Not Found") << endl;
    traverse = bst.breadthFirst();
    cout << "Breadth-first traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();
    
    cout << "Removing node with key 3: " << (bst.remove(3) ? "Removed" : "Not Found") << endl;
    traverse = bst.breadthFirst();
    cout << "Breadth-first traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    cout << "-------------Testing [] operator  -------------\n";
    cout <<" Value of key [1000]: " << bst[1000] << endl;
    
    
    return 0;
}