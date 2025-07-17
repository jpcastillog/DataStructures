#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

template<typename TypeKey, typename TypeValue>
class Node {
    public:
        TypeKey key;
        TypeValue value;
        Node<TypeKey, TypeValue> *left;
        Node<TypeKey, TypeValue> *right;   
        // Constructor
        Node(TypeKey key, TypeValue value){
            left = nullptr;
            right = nullptr;
            Node::key = key;
            Node::value = value;
        }
};

template <typename TypeKey, typename TypeValue>
class binarySearchTree {
using BstNode = Node<TypeKey, TypeValue>;
protected:
    unsigned int n;
    BstNode* root;
public:    
    // Constructor
    binarySearchTree() {
        binarySearchTree::n = 0;
        binarySearchTree::root = nullptr;
    };
    // Destructor
    ~binarySearchTree() {
        // delete nodes using post-order traversal
        clear();
    };
    // Returns the number of node in the tree
    unsigned int size(){
        return binarySearchTree::n;
    };

    TypeValue operator[](TypeKey key){
        BstNode* node = find(key);
        if (node == nullptr){
            stringstream ss; 
            ss <<  "Key " << key << " not found";
            throw std::runtime_error(ss.str());
        }
        else
            return node->value;
    };

    /* BEGIN CLEAR TREE:
        * RESTART THE TREE TO EMPTY
    */
    void clearHelp(Node<TypeKey,TypeValue>* root){
        if (root == nullptr) return;
        clearHelp(root->left);
        clearHelp(root->right);
        delete(root);
    };

    void clear() {
        if (root == nullptr) return;
        clearHelp(root);
    };
    /* END CLEAR TREE */
    /* BEGIN INSERT NODE */
    bool insertHelp(BstNode* root, TypeKey key, TypeValue value){
        if (key == root->key) return false;
        else if (key <= root->key) {
            if (root->left == nullptr) {
                root->left = new BstNode(key, value);
                return true;
            }
            else return insertHelp(root->left, key, value);
        } else {
            if (root->right == nullptr){
                root->right = new BstNode(key, value);
                return true;    
            }
            else return insertHelp(root->right, key, value);
        }
    };
    bool insert(TypeKey key, TypeValue value){
        // Case when BST is empty
        if (root == nullptr){
            root = new BstNode(key, value);
            return true;
        }
        else {
            bool inserted = insertHelp(binarySearchTree::root, key, value);
            if (inserted) 
                binarySearchTree::n++;
            return inserted;
        }
    };
    /* END INSERT NODE */

    /* BEGIN FIND NODE
        * FIND THE NODE WITH THE KEY
        * RETURN A POINTER TO THE NODE, nullptr IF NOT FOUND
     */

    BstNode* findHelp(BstNode* root, TypeKey key){
        if (root == nullptr) return nullptr;
        else if (root->key == key) {
            return root;
        } 
        else if (key < root->key)
            return findHelp(root->left, key);
        else 
            return findHelp(root->right, key);
    };

    BstNode* find(TypeKey key, bool recursive=false){
        if (recursive)
            return findHelp(root, key);
        else {
            BstNode* curr = root;
            while (curr != nullptr && curr->key != key) {
                if (key < curr->key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            return curr;
        }
    };
    /* END FIND NODE */

    /* BEGIN TRAVERSALS */
    // DFS Traversals
    // In-order traversal
    void inOrderHelp(BstNode* root, vector<tuple<TypeKey, TypeValue>> &traverse){
        if (root == nullptr) return;
        inOrderHelp(root->left, traverse);
        tuple<TypeKey, TypeValue> data(root->key, root->value);
        traverse.push_back(data);
        inOrderHelp(root->right, traverse);
    };
    vector<tuple<TypeKey, TypeValue>> inOrder(){
        vector<tuple<TypeKey, TypeValue>> traverse;
        traverse.reserve(n);
        inOrderHelp(root, traverse);
        return traverse;
    };

    //Post-order traversal 
    void postOrderHelp(BstNode* root, vector<tuple<TypeKey, TypeValue>> &traverse){
        if (root == nullptr) return;
        postOrderHelp(root->left, traverse);
        postOrderHelp(root->right, traverse);
        tuple<TypeKey, TypeValue> data(root->key, root->value);  
        traverse.push_back(data);  
    };
    vector<tuple<TypeKey, TypeValue>> postOrder(){
        vector<tuple<TypeKey, TypeValue>> traverse;
        traverse.reserve(n);
        postOrderHelp(root, traverse);
        return traverse;
    };
    // Pre-order traversal
    void preOrderHelp(BstNode* root, vector<tuple<TypeKey, TypeValue>> &traverse){
        if (root == nullptr) return;
        tuple<TypeKey, TypeValue> data(root->key, root->value);
        traverse.push_back(data);
        preOrderHelp(root->left, traverse);
        preOrderHelp(root->right, traverse);
    };
    vector<tuple<TypeKey, TypeValue>> preOrder(){
        vector<tuple<TypeKey, TypeValue>> traverse;
        traverse.reserve(n);
        preOrderHelp(root, traverse);
        return traverse;
    };

    // Breadthfirst traversal (BFS)
    vector<tuple<TypeKey, TypeValue>> breadthFirst(){
        // Queue to perfor level-wise traverse
        queue<Node<TypeKey,TypeValue>*> Q;
        vector<tuple<TypeKey, TypeValue>> traverse; // vector to return the traverse
        // reserve space to n pairs key and value
        traverse.reserve(n);
        Q.push(root);
        BstNode *aux;
        while(!Q.empty()){
            aux = Q.front();
            traverse.push_back(tuple<TypeKey, TypeValue>(aux->key, aux->value));
            if (aux->left != nullptr)
                Q.push(aux->left);
            if (aux->right != nullptr)
                Q.push(aux->right);
            Q.pop();
        }
        return traverse;
    };
    /* END TRAVERSALS */

    /* BEGIN REMOVE NODE */
    BstNode* findSuccessor(BstNode* node) {
        if (node -> right == nullptr) return nullptr;
        else {
            Node<TypeKey,TypeValue>* curr = node->right;
            while (curr -> left != nullptr)
                curr = curr -> left;
            return curr;
        }   
    };
    
    BstNode* findPredecessor(BstNode* node) {
        if (node -> left == nullptr) return nullptr;
        else {
            Node<TypeKey,TypeValue>* curr = node->left;
            while (curr -> right != nullptr)
                curr = curr -> right;
            return curr;
        }   
    };

    BstNode* findParent(BstNode* node, TypeKey key){
        if (node == nullptr) return nullptr;
        else if (node->left != nullptr and node->left->key == key) 
            return node;
        else if (node->right != nullptr and node->right->key == key) 
            return node;
        else if (key < node->key)
            return findParent(node->left, key);
        else
            return findParent(node->right, key);
    };

    bool remove(TypeKey key){
        if (root == nullptr) return false;
        BstNode* parent = findParent(root, key);
        BstNode* node;
        if (parent == nullptr) 
            node = root;
        else    
            node = parent->left->key == key ? parent->left : parent->right;
        // case 1: node has no children
        if (node -> left == nullptr and node->right == nullptr){
            if (parent != nullptr and parent->left == node) 
                parent->left = nullptr;
            else if (parent != nullptr and parent->right == node) 
                parent->right = nullptr;
            else 
                root = nullptr;
            delete node;
            n--;
            return true;
        }
        // case 2: node has one child
        else if (node->left == nullptr xor node->right == nullptr){
            BstNode* child = node->left != nullptr ? node->left : node->right;
            if (parent != nullptr and parent->left == node) 
                parent->left = child;
            else if (parent != nullptr and parent->right == node)
                parent->right = child;
            else
                root = child;
            delete node;
            n--;
            return true;
        }
        // case 3: node has two children
        else {
            BstNode* successor = findSuccessor(node);
            BstNode* successorParent = findParent(binarySearchTree::root, successor->key);
            BstNode temp = *node;
            // exchange the values of the node and the successor
            node->key = successor->key;
            node->value = successor->value;
            successor->key = temp.key;
            successor->value = temp.value;
            // remove the successor
            // note: the child of successor is at most one and always on the right
            if (successorParent->left == successor)
                successorParent->left = successor->right;
            else
                successorParent->right = successor->right;
            delete successor;
            n--;
            return true;
        }
    };
    /* END REMOVE NODE */
};

#endif