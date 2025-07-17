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

    /*  BEGIN INSERT    */
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
    /*  END INSERT  */
    
    /*  BEGIN REMOVE    */

    BstNode* minNode(BstNode* node) {
        if (node == nullptr) return nullptr;
        while(node -> left != nullptr)
            node = node -> left;
        return node;
    };

    BstNode* removeHelp(BstNode* node, TypeKey key, bool &found){
        if (node == nullptr) {
            found = false;
            return nullptr;
        }

        if (key < node->key) {
            node->left = avlTree::removeHelp(node->left, key, found);
            ((AvlNode*)node)->balanceFactor++;
        } 
        else if (key > node->key) {
            node->right = avlTree::removeHelp(node->right, key, found);
            ((AvlNode*)node)->balanceFactor--;
        } 
        else {
            // Node to be deleted found
            if (node->left == nullptr || node->right == nullptr) {
                BstNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    delete node;
                    return nullptr;
                } else {
                    *node = *temp; // Copy the contents of the child
                    delete temp;
                }
            } else {
                BstNode* temp = minNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = avlTree::removeHelp(node->right, temp->key, found);
            }
        }

        // Update balance factor and balance the tree
        if (((AvlNode*)node)->balanceFactor < -1) {
            if (((AvlNode*)node->left)->balanceFactor <= 0)
                return rightRotation(node); // Right rotation
            else
                return leftRightRotation(node); // Left-Right rotation
        } 
        else if (((AvlNode*)node)->balanceFactor > 1) {
            if (((AvlNode*)node->right)->balanceFactor >= 0)
                return leftRotation(node); // Left rotation
            else
                return rightLeftRotation(node); // Right-Left rotation
        }

        return node;
    }

    bool remove(TypeKey key){
        if (avlTree::root == nullptr) 
            return false;
        
        bool found = true;
        avlTree::root = avlTree::removeHelp(avlTree::root, key, found);
        
        if(!found) 
            return false;
        else {
            bst::root = avlTree::root;
            bst::n--;
            return true;
        }
    }
    /*  END REMOVE  */
};

#endif
