#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <tuple>
#include <vector>
#include <queue>

using namespace std;

template<typename TypeKey, typename TypeValue>
struct Node {
    TypeKey key;
    TypeValue value;
    Node<TypeKey, TypeValue> *left;
    Node<TypeKey, TypeValue> *right;
    // Constructor
    Node(TypeKey key, TypeValue value){
        left = NULL;
        right = NULL;
        Node::key = key;
        Node::value = value;
    }
};

template <typename TypeKey, typename TypeValue>
class binarySearchTree {
    private:
        unsigned int n;
        Node<TypeKey, TypeValue>* root;
    public:
        binarySearchTree();
        ~binarySearchTree();
        bool find(TypeKey key, TypeValue &value);
        void clear();
        bool insert(TypeKey key, TypeValue value);
        bool remove(TypeKey key);
        unsigned int size();
        vector<tuple<TypeKey, TypeValue>> inOrder();
        vector<tuple<TypeKey, TypeValue>> preOrder();
        vector<tuple<TypeKey, TypeValue>> postOrder();
        vector<tuple<TypeKey, TypeValue>> levelOrder();
};

template<typename TypeKey, typename TypeValue>
binarySearchTree<TypeKey, TypeValue>::binarySearchTree() {
    binarySearchTree::n = 0;
    binarySearchTree::root = NULL;
}

template<typename TypeKey, typename TypeValue>
binarySearchTree<TypeKey, TypeValue>::~binarySearchTree() {
    // delete nodes using post-order traversal
    clear();
}

template<typename TypeKey, typename TypeValue>
void clearHelp(Node<TypeKey,TypeValue>* root){
    if (root == NULL) return;
    clearHelp(root->left);
    clearHelp(root->right);
    delete(root);
};

template<typename TypeKey, typename TypeValue>
void binarySearchTree<TypeKey, TypeValue>::clear() {
    if (root == NULL) return;
    clearHelp<TypeKey, TypeValue>(root);
};

template<typename TypeKey, typename TypeValue>
bool insertHelp(Node<TypeKey, TypeValue>* root, TypeKey key, TypeValue value){
    if (value == root->key) return false;
    else if (value < root->key) {
        if (root->left == NULL) {
            root->left = new Node<TypeKey, TypeValue>(key, value);
            return true;
        }
        else return insertHelp(root->left, key, value);
    } else {
        if (root->right == NULL){
            root->right = new Node<TypeKey, TypeValue>(key, value);
            return true;    
        }
        else return insertHelp(root->right, key, value);
    }
};

template<typename TypeKey, typename TypeValue>
bool binarySearchTree<TypeKey, TypeValue>::insert(TypeKey key, TypeValue value){
    // Case when BST is empty
    if (root == NULL){
        root = new Node<TypeKey, TypeValue>(key, value);
        return true;
    }
    else
        return insertHelp(root, key, value);
};

template<typename TypeKey, typename TypeValue>
unsigned int binarySearchTree<TypeKey, TypeValue>::size(){
    return binarySearchTree::n;
};


template<typename TypeKey, typename TypeValue>
bool findHelp(Node<TypeKey, TypeValue>* root, TypeKey key, TypeValue &value){
    if (root == NULL) return false;
    else if (root->key == key) {
        value = root->value;
        return true;
    } 
    else if (key < root->key)
        return findHelp(root->left, key, value);
    else 
        return findHelp(root->right, key, value);
};

template<typename TypeKey, typename TypeValue>
bool binarySearchTree<TypeKey, TypeValue>::find(TypeKey key, TypeValue &value){
    return findHelp<TypeKey, TypeValue>(root, key, value);
};

template<typename TypeKey, typename TypeValue>
void inOrderHelp(Node<TypeKey, TypeValue>* root, vector<tuple<TypeKey, TypeValue>> &traverse){
    if (root == NULL) return;
    inOrderHelp(root->left, traverse);
    tuple<TypeKey, TypeValue> data(root->key, root->value);
    traverse.push_back(data);
    inOrderHelp(root->right, traverse);
};

template<typename TypeKey, typename TypeValue>
vector<tuple<TypeKey, TypeValue>> binarySearchTree<TypeKey, TypeValue>::inOrder(){
    vector<tuple<TypeKey, TypeValue>> traverse;
    traverse.reserve(n);
    inOrderHelp(root, traverse);
    return traverse;
};

template<typename TypeKey, typename TypeValue>
void postOrderHelp(Node<TypeKey, TypeValue>* root, vector<tuple<TypeKey, TypeValue>> &traverse){
    if (root == NULL) return;
    postOrderHelp(root->left, traverse);
    postOrderHelp(root->right, traverse);
    tuple<TypeKey, TypeValue> data(root->key, root->value);  traverse.push_back(data);  
};

template<typename TypeKey, typename TypeValue>
vector<tuple<TypeKey, TypeValue>> binarySearchTree<TypeKey, TypeValue>::postOrder(){
    vector<tuple<TypeKey, TypeValue>> traverse;
    traverse.reserve(n);
    postOrderHelp(root, traverse);
    return traverse;
};

template<typename TypeKey, typename TypeValue>
void preOrderHelp(Node<TypeKey, TypeValue>* root, vector<tuple<TypeKey, TypeValue>> &traverse){
    if (root == NULL) return;
    tuple<TypeKey, TypeValue> data(root->key, root->value);
    traverse.push_back(data);
    preOrderHelp(root->left, traverse);
    preOrderHelp(root->right, traverse);
};

template<typename TypeKey, typename TypeValue>
vector<tuple<TypeKey, TypeValue>> binarySearchTree<TypeKey, TypeValue>::preOrder(){
    vector<tuple<TypeKey, TypeValue>> traverse;
    traverse.reserve(n);
    preOrderHelp(root, traverse);
    return traverse;
};

template<typename TypeKey, typename TypeValue>
vector<tuple<TypeKey, TypeValue>> binarySearchTree<TypeKey, TypeValue>::levelOrder(){
    // Queue to perfor level-wise traverse
    queue<Node<TypeKey,TypeValue>*> Q;
    vector<tuple<TypeKey, TypeValue>> traverse; // vector to return the traverse
    // reserve space to n pairs key and value
    traverse.reserve(n);
    Q.push(root);
    Node<TypeKey, TypeValue> *aux;
    while(!Q.empty()){
        aux = Q.front();
        traverse.push_back(tuple<TypeKey, TypeValue>(aux->key, aux->value));
        if (aux->left != NULL)
            Q.push(aux->left);
        if (aux->right != NULL)
            Q.push(aux->right);
        Q.pop();
    }
    return traverse;
};

#endif