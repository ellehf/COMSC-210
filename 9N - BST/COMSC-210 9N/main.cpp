//
//  main.cpp
//  COMSC-210 9N
//
//  Created by Elle Hoarau on 11/17/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>
using namespace std;

struct BSTNode /// BinarySearchTreeNode
{
    int value;
    int count;
    BSTNode* left= NULL;
    BSTNode* right= NULL;
};

class BST // BinarySearchTree
{
private:
    BSTNode* root ;
public:
    BST (){ root = NULL;}
    
    void Insert(int value);
    BSTNode *Insert(BSTNode * node, int key);
    
    void Remove(int value);
    BSTNode *Remove(BSTNode *node, int value);
    
    BSTNode* findMin(BSTNode *node) ;
    BSTNode* findMax(BSTNode *node) ;
    
    void preOrderTraversal() const;
    void preOrderTraversal(BSTNode* node) const;
    void inOrderTraversal() const;
    void inOrderTraversal(BSTNode* node) const;
    void postOrderTraversal() const;
    void postOrderTraversal(BSTNode* node) const;
    
};

void BST:: preOrderTraversal() const
{
    cout << "Pre Order Traversal (with count): ";
    preOrderTraversal(root);
    cout << endl;
}
void BST:: preOrderTraversal(BSTNode* node) const
{
    if (node != NULL)
    {
        cout << node->value << " (" << node->count << ") ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

void BST:: inOrderTraversal() const
{
    cout << "In Order Traversal (with count): ";
    inOrderTraversal(root);
    cout << endl;
}
void BST:: inOrderTraversal(BSTNode* node) const
{
    if (node != NULL)
    {
        inOrderTraversal(node->left);
        cout << node->value << " (" << node->count << ") ";
        inOrderTraversal(node->right);
    }
}

void BST:: postOrderTraversal() const
{
    cout << "Post Order Traversal (with count): ";
    postOrderTraversal(root);
    cout << endl;
}
void BST:: postOrderTraversal(BSTNode* node) const
{
    if (node != NULL)
    {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->value << " (" << node->count << ") ";
    }
}

BSTNode *BST::Insert(BSTNode *node, int value)
{
    //If tree is empty, or if traversed to node with empty child, insert new node
    if(node==NULL)
    {
        node= new BSTNode;
        node->value=value;
        node->count=1;
        node->left=NULL;
        node->right=NULL;
        return node;
    }
    
    if(value==node->value) //If value already exists, increment count and return
    {
        (node->count)++;
        return node;
    }
    
    //Traverse down tree
    if(value< node->value)
        node->left= Insert(node->left, value);
    else
        node->right= Insert(node->right, value);
    
    return node;
}

void BST:: Insert(int value)
{
    //Call Insert function using root and passed value
    root=Insert(root, value);
}

BSTNode *BST::Remove(BSTNode *node, int value)
{
    //Base case
    if(root==NULL)
        return root;
    
    //Traverse tree until value found
    if(value<node->value)
        Remove(node->left, value);
    else if(value>node->value)
        Remove(node->right, value);
    
    else
    {
        //If duplicate value, decrement count
        if(node->count > 1)
        {
            (node->count--);
            return node;
        }
    
        //Else delete node
        BSTNode *temp= node;
        
        //If no left child
        if(node->left == NULL)
        {
            temp= node->right;
            delete node;
            return temp;
        }
        
        //If no right child
        else if(node->right == NULL)
        {
            temp= node->left;
            delete node;
            return temp;
        }
        
        //Node with two children
        else
        {
            temp= findMax(node->left); //Set to largest value in left subtree
            node->value= temp->value;
            node->right= Remove(node->right, temp->value);
        }
    }
    
    return node;
}

void BST:: Remove(int value)
{
    
    Remove(root, value);
    
}

BSTNode* BST:: findMin(BSTNode *node)
{
    if(root== NULL)
        return NULL;
    else
    {
        BSTNode *temp= root;
        while(temp->left != NULL)
            temp= temp->left;
        return temp; //return location of minimum value
    }
}

BSTNode* BST:: findMax(BSTNode *node)
{
    if(root== NULL)
        return NULL;
    else
    {
        BSTNode *temp= root;
        while(temp->right != NULL)
                   temp= temp->right;
        return temp; //return location of maximum value
    }
}

const int SIZE =15;

int main()
{
    BST bst;
    int values[SIZE] = {5, 2, 12, -4, 3, 9, 21, -7, 19, 25, -8, -6, -4, 3, 12};
    for (int i = 0; i < SIZE; i++)
        bst.Insert(values[i]);

    cout<< "Tree accounts for duplicate values with count.\n\n" <<endl;
    
    bst.preOrderTraversal(); /// should be 5 2 -4 -7 -8 -6 3 12 9 21 19 25
    bst.inOrderTraversal(); /// should be -8 -7 -6 -4 2 3 5 9 12 19 21 25
    bst.postOrderTraversal(); /// should be -8 -6 7 -4 3 2 9 19 25 21 12 5

    bst.Remove(3); /// Node 3 has 0 children --> delete the node and make it NULL;
    bst.Remove(-4); /// Node -4 has 1 children --> Link parent to child --> delete the node and make it NULL;
    bst.Remove(12); /// Node 12 has 2 children --> findMin for the right subtree --> swap value -> delete

    bst.preOrderTraversal(); /// should be 5 2 -7 -8 -6 19 9 21 25
    bst.inOrderTraversal(); /// should be -8 -7 -6 2 5 9 19 21 25
    bst.postOrderTraversal(); /// should be -8 -6 7 2 9 25 21 19 5
    
   
    return 0;
}

