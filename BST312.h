/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree

*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();      // default constructor
    BST_312(const BST_312 &src);       // copy constructor
    ~BST_312();     // deconstructor

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &newItem);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType &newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    bool isItemInTree(const ItemType &item);

private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode* root;


    void insertItem(TreeNode* &t, const ItemType &newItem);
    void inOrderTraversal(TreeNode* t, vector<ItemType> &result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode* &node);
    void makeEmpty(TreeNode* &t);
    void deleteItem(TreeNode* &t, const ItemType &newItem);
    void getPredecessor(TreeNode* t, ItemType &data);
    void preOrderTraversal(TreeNode* t, vector<ItemType> &result) const;
    void postOrderTraversal(TreeNode* t, vector<ItemType> &result) const;
    void copyTree(TreeNode* &copy, const TreeNode* originalTree);
};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312() {      // constructor
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 &src) {      // copy constructor
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312() {
    makeEmpty();
}

template<class ItemType>
void BST_312<ItemType>::copyTree(BST_312<ItemType>::TreeNode* &copy, const BST_312<ItemType>::TreeNode* originalTree) {
    if(originalTree == NULL) {
        copy = NULL;
    }
    else {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}

template<class ItemType>
void BST_312<ItemType>::deleteNode(TreeNode* &t) {
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if(t->left == NULL) {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL) {
        t = t->left;
        delete tempPtr;
    }
    else {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}

template<class ItemType>
void BST_312<ItemType>::getPredecessor(BST_312<ItemType>::TreeNode *t, ItemType &data) {
    while(t->right != NULL) {       // navigates to rightmost tree node
        t = t->right;
    }
    data = t->data;       // copies data from node into data from parameters
}

template<class ItemType>
void BST_312<ItemType>::deleteItem(BST_312<ItemType>::TreeNode *&t, const ItemType &newItem) {
    if(t == NULL) {
        return;
    }
    else if(newItem < t->data) {
        deleteItem(t->left, newItem);
    }
    else if(newItem > t->data) {
        deleteItem(t->right, newItem);
    }
    else {
        deleteNode(t);
    }
}

template<class ItemType>
void BST_312<ItemType>::deleteItem(const ItemType &newItem) {
    deleteItem(root, newItem);
}

template<class ItemType>
void BST_312<ItemType>::makeEmpty(TreeNode* &t) {
    if(root != NULL) {
        if (t->left != NULL) {
            makeEmpty(t->left);
        }
        if (t->right != NULL) {
            makeEmpty(t->right);
        }
        delete t;
    }
}

template<class ItemType>
void BST_312<ItemType>::makeEmpty() {
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312<ItemType>::isEmpty() const {
    return root == NULL;
}

template<class ItemType>
bool BST_312<ItemType>::isFull() const {
    try {        // exception and exception handling
        TreeNode* temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc) {
        return true;
    }
}

template<class ItemType>
void BST_312<ItemType>::insertItem(TreeNode* &t, const ItemType &newItem) {
    if(t->data == newItem) {
        return;
    }
    else if(t->data > newItem) {
        if(t->left != NULL) {
            insertItem(t->left, newItem);
        }
        else {
            t->left = new TreeNode;
            t->left->data = newItem;
            t->left->left = NULL;
            t->left->right = NULL;
        }
    }
    else if(t->data < newItem) {
        if(t->right != NULL) {
            insertItem(t->right, newItem);
        }
        else {
            t->right = new TreeNode;
            t->right->data = newItem;
            t->right->left = NULL;
            t->right->right = NULL;
        }
    }
}

template<class ItemType>
void BST_312<ItemType>::insertItem(const ItemType &newItem) {
    if(isFull() != true) {
        if (root == NULL) {
            root = new TreeNode;
            root->data = newItem;
            root->left = NULL;
            root->right = NULL;
        } else {
            insertItem(root, newItem);
        }
    }
    else {
        return;
    }
}

template<class ItemType>
int BST_312<ItemType>::countNodes(TreeNode* t) const {
    int count = 1;
    if(t->left != NULL) {
        count = count + countNodes(t->left);
    }
    if(t->right != NULL) {
        count = count + countNodes(t->right);
    }
    return count;
}

template<class ItemType>
int BST_312<ItemType>::countNodes() {
    int count = 0;
    if(root != NULL) {
        count = countNodes(root);
    }
    else {
        return 0;
    }
    return count;
}

template<class ItemType>
void BST_312<ItemType>::preOrderTraversal(BST_312<ItemType>::TreeNode *t, vector<ItemType> &result) const {
    result.push_back(t->data);
    if(t->left != NULL) {
        preOrderTraversal(t->left, result);
    }
    if(t->right != NULL) {
        preOrderTraversal(t->right, result);
    }
}

template<class ItemType>
vector<ItemType> BST_312<ItemType>::preOrderTraversal() {
    vector<ItemType> preVector;
    if(root != NULL) {
        preOrderTraversal(root, preVector);
        return preVector;
    }
    else {
        return preVector;
    }
}

template<class ItemType>
void BST_312<ItemType>::inOrderTraversal(BST_312<ItemType>::TreeNode *t, vector<ItemType> &result) const {
    if(t->left != NULL) {
        inOrderTraversal(t->left, result);
    }
    result.push_back(t->data);
    if(t->right != NULL) {
        inOrderTraversal(t->right, result);
    }
}

template<class ItemType>
vector<ItemType> BST_312<ItemType>::inOrderTraversal() {
    vector<ItemType> inVector;
    if(root != NULL) {
        inOrderTraversal(root, inVector);
        return inVector;
    }
    else {
        return inVector;
    }
}

template<class ItemType>
void BST_312<ItemType>::postOrderTraversal(BST_312<ItemType>::TreeNode *t, vector<ItemType> &result) const {
    if(t->left != NULL) {
        postOrderTraversal(t->left, result);
    }
    if(t->right != NULL) {
        postOrderTraversal(t->right, result);
    }
    result.push_back(t->data);
}

template<class ItemType>
vector<ItemType> BST_312<ItemType>::postOrderTraversal() {
    vector<ItemType> postVector;
    if(root != NULL) {
        postOrderTraversal(root, postVector);
        return postVector;
    }
    else {
        return postVector;
    }
}

template<class ItemType>
bool BST_312<ItemType>::isItemInTree(const ItemType &item) {
    if(root != NULL) {
        if (root->data == item) {
            return true;
        } else {
            TreeNode *ptr = root;

            while (ptr != NULL) {
                if (ptr->data == item) {
                    return true;
                } else if (ptr->data > item) {
                    ptr = ptr->left;
                } else if (ptr->data < item) {
                    ptr = ptr->right;
                }
            }
            return false;
        }
    }
    return false;
}

#endif