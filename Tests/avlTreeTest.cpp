#include <iostream>
#include "../BinaryTree/AVLTree.hpp"

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

    // Test find
    cout << "-------------Testing find method-------------" << endl;
    Node<int, int>* target = avl.find(5);
    cout <<"Find node with key 5: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }
    target = avl.find(3);
    cout <<"Find node with key 3: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }
    target = avl.find(6);
    cout <<"Find node with key 6: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }
    target = avl.find(13);
    cout <<"Find node with key 13: " << (target != NULL ? "Found" : "Not Found") << endl;
    if (target != NULL) {
        cout << "   * Node value: " << target->value << endl;
    }

      cout << "-------------Testing remove method-------------" << endl;
    cout << "Removing node with key 5: " << (avl.remove(5) ? "Removed" : "Not Found") << endl;
    traverse = avl.breadthFirst();
    cout << "Breadth-first traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    cout << "Removing node with key 12: " << (avl.remove(12) ? "Removed" : "Not Found") << endl;
    traverse = avl.breadthFirst();
    cout << "Breadth-first traversal:" << endl;
    printTraverse(traverse);
    traverse.clear();

    cout << "-------------Testing [] operator  -------------\n";
    cout <<" Value of key [10]: " << avl[10] << endl;
    avl[10] = 20;
    cout <<" Value of key [10] after update: " << avl[10] << endl;
    return 0;
}