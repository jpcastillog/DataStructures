#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <vector>
#include "binarySearchTree.hpp"

using namespace std;


template<typename TypeKey, typename TypeValue>
class avlNode: public Node<TypeKey, TypeValue> {
    using  BstNode = Node<TypeKey, TypeValue>;
    public:    
        int balanceFactor;
        avlNode(TypeKey key, TypeValue value): 
                BstNode(key, value),balanceFactor(0){}
};

template<typename TypeKey, typename TypeValue>
using AvlNode = avlNode<TypeKey, TypeValue>;

template<typename TypeKey, typename TypeValue>
class avlTree: public binarySearchTree<TypeKey, TypeValue> {
    
    using BstNode = Node<TypeKey, TypeValue>;
    using AvlNode = avlNode<TypeKey, TypeValue>;
    using bst = binarySearchTree<TypeKey, TypeValue>;
    
    private:
        BstNode* root;
    public:
    avlTree():bst() {
        avlTree::root = nullptr;
    };
    ~avlTree() {
        clear();
    };

    void clearHelp(BstNode* root){
        if (root == nullptr) return;
        clearHelp(root->left);
        clearHelp(root->right);
        cout << "Deleting node with key: " << root->key << endl;
        delete((AvlNode*)root);
    };

    void clear() {
        if (avlTree::root == nullptr) return;
        bst::n = 0;
        bst::root = nullptr;
        clearHelp(avlTree::root);
        cout << "Tree cleared." << endl;
    };

    /*  BEGIN ROTATIONS   */
    BstNode* leftRotation(BstNode* node) {
        BstNode* temp=node->right;
        node->right=temp->left;
        temp->left=node;
        // Update balance factors        
        ((AvlNode*)node)->balanceFactor -= 1 + max(0, ((AvlNode*)temp)->balanceFactor);
        ((AvlNode*)temp)->balanceFactor -= 1 - min(0, ((AvlNode*)node)->balanceFactor);
        // end Update balance factors
        return temp;
    };

    BstNode* rightRotation(BstNode* node) {
        BstNode* temp=node->left;
        node->left=temp->right;
        temp->right=node;
        // Update balance factors
        ((AvlNode*)node)->balanceFactor += 1 - min(0, ((AvlNode*)temp)->balanceFactor);
        ((AvlNode*)temp)->balanceFactor += 1 + max(0, ((AvlNode*)node)->balanceFactor);
        // end Update balance factors
        return temp;
    };

    BstNode* leftRightRotation(BstNode* node) {
        node->left=leftRotation(node->left);   
        return rightRotation(node);
    };

    BstNode* rightLeftRotation(BstNode* node) {
        node->right=rightRotation(node->right);
        return leftRightRotation(node);
    };
    /*  END ROTATIONS   */

    BstNode* insertHelp(BstNode* node, TypeKey key, TypeValue value){
        if (node == nullptr)
            return new AvlNode(key, value);
            
        else if (key < node->key) {
            node->left = avlTree::insertHelp(node->left, key, value);
            ((AvlNode*)node)->balanceFactor--;
            // Balance the tree if necessary
            if (((AvlNode*)node)->balanceFactor < -1) {
                if (((AvlNode*)node->left)->balanceFactor < 0)
                    node = rightRotation(node); // Right rotation
                else
                    node = leftRightRotation(node); // Left-Right rotation
            }
            else if (((AvlNode*)node)->balanceFactor > 1) {
                if (((AvlNode*)node->right)->balanceFactor > 0)
                    node = leftRotation(node); // Left rotation
                else
                    node = rightLeftRotation(node); // Right-Left rotation
            }
        }
        else if (key > node->key) {
            node->right = avlTree::insertHelp(node->right, key, value);
            ((AvlNode*)node)->balanceFactor++;
            // Balance the tree if necessary
            if (((AvlNode*)node)->balanceFactor > 1) {
                if (((AvlNode*)node->right)->balanceFactor > 0)
                    node = leftRotation(node); // Left rotation
                else
                    node = rightLeftRotation(node); // Right-Left rotation
            } 
            else if (((AvlNode*)node)->balanceFactor < -1) {
                if (((AvlNode*)node->left)->balanceFactor < 0)
                    node = rightRotation(node); // Right rotation
                else
                    node = leftRightRotation(node); // Left-Right rotation
            }
        }
        else {
            return node;
        }
        return node;
    };

    bool insert(TypeKey key, TypeValue value) {
        // Implement AVL tree insertion logic here
        // This will involve balancing the tree after insertion
        if (bst::root == nullptr) {
            BstNode* newNode = new AvlNode(key, value);
            avlTree::root = newNode;
            bst::root = newNode;
            bst::n++;
            return true;
        }
        else {
            avlTree::root = avlTree::insertHelp(avlTree::root, key, value);
            bst::root = avlTree::root;
            return true;
        }
    };
    void remove(TypeKey key) {
        // Implement AVL tree removal logic here
        // This will involve balancing the tree after removal
    };
};

#endif
