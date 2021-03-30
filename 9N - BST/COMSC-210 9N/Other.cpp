//
//  Other.cpp
//  COMSC-210 9N
//
//  Created by Elle Hoarau on 11/26/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <stdio.h>

/*BSTNode *back= NULL;
BSTNode *temp= root;
BSTNode *dParent;
BSTNode *dNode; //Node to be deleted

//Traverse tree until value is found
while(temp != NULL && temp->value != value)
{
    back=temp;
    if(value<temp->value)
        temp= temp->left;
    else
        temp= temp->right;
}

//If tree does not contain value, exit
if(temp == NULL)
{
    cout<< "Value not found.\n";
    exit(-1);
}

//If tree contains value
else
{
    if(temp == root) //If value to delete is root
    {
        dNode= root;
        dParent= back;
    }
    else
    {
        dNode= temp;
        dParent= back;
    }
}

if(dNode->right == NULL) //Deleting node with right child or no child
{
    if(dParent == NULL) //Deleting root with no right child
    {
        root= dNode->left;
        delete dNode;
    }
    else
    {
        if(dParent->left == dNode)
            dParent->left= dNode->left;
        else
            dParent->right= dNode->left;
        delete dNode;
    }
}

else if(dNode->left == NULL) //Deleting node with left child or no child
{
    if(dParent == NULL) //Deleting root with no left child
    {
        root= dNode->right;
        delete dNode;
    }
    else
    {
        if(dParent->left == dNode)
            dParent->left= dNode->right;
        else
            dParent->right= dNode->right;
        delete dNode;
    }
}

else //Deleting node with two children
{
    temp= dNode->left;
    back= dNode;
    
    while(temp->right != NULL)
    {
        back= temp;
        temp= temp->right;
    }
    
    dNode->value= temp->value;
    
    if(back == dNode)
        back->left= temp->left;
    else
        back->right= temp->left;
    delete temp;
}*/
