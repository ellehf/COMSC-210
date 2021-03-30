//
//  linkedStack.h
//  COMSC-210 6N
//
//  Created by Elle Hoarau on 10/4/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#ifndef linkedStack_h
#define linkedStack_h

#include <iostream>
#include <cassert>

using namespace std;

//Max stack size
int SIZE=100;

//Definition of the node
template <class Type>
struct nodeType
{
Type info;
nodeType<Type> *link;
};

template <class Type>
class linkedStackType
{
private:
    nodeType<Type> *stackTop; //pointer to the stack
    
    int sizeStack; //stack size counter

    //Function to make a copy of otherStack.
    //Postcondition: A copy of otherStack is created and assigned to this stack.
    void copyStack(const linkedStackType<Type> &otherStack);

public:
   
    //Default constructor
    //Postcondition: stackTop = nullptr;
    linkedStackType();

    //Copy constructor
    linkedStackType(const linkedStackType<Type>& otherStack);
    
    //Overload the assignment operator.
    const linkedStackType<Type>& operator=(const linkedStackType<Type> &otherStack);

    //Function to determine whether the stack is empty.
    //Postcondition: Returns true if the stack is empty;
    // otherwise returns false.
    bool isEmptyStack() const;

    //Function to determine whether the stack is full.
    //Postcondition: Returns false.
    bool isFullStack() const;

    //Function to initialize the stack to an empty state.
    //Postcondition: The stack elements are removed;
    // stackTop = nullptr;
    void initializeStack();

    //Function to add newItem to the stack.
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem
    // is added to the top of the stack.
    void push(const Type& newItem);

    //Function to return the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program
    // terminates; otherwise, the top element of the stack is returned.
    Type top() const;

    //Function to remove the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top
    // element is removed from the stack.
    void pop();

    //Destructor
    //Postcondition: All the elements of the stack are
    // removed from the stack.
    ~linkedStackType();
    
    void display();
    
};

//Default Constructor
template<class Type>
linkedStackType<Type>::linkedStackType()
{
    stackTop=nullptr;
    sizeStack=0;
}

//Copy function
template<class Type>
void linkedStackType<Type>:: copyStack(const linkedStackType<Type>& otherStack)
{
    //Initialize stack if not already
    while(stackTop != nullptr)
    {
        nodeType<Type> *temp= stackTop;
        stackTop= stackTop->link;
        delete temp;
    }

    stackTop= nullptr;
    nodeType<Type> *prev= nullptr;
    nodeType<Type> *curr = otherStack.stackTop;

    //Traverse otherstack with curr
    while(curr != nullptr)
    {
        if(stackTop == nullptr)
        {
            stackTop= new nodeType<Type>;
            stackTop->info= curr->info; //Copy elements to stack
            stackTop->link= nullptr;
            prev= stackTop;
        }
        else
        {
            nodeType<Type> *temp= new nodeType<Type>;
            temp->info= curr->info;
            temp->link= nullptr;
            prev->link= temp;
            prev= temp;
        }

        curr = curr->link;

    }
}

//Copy constructor
template<class Type>
linkedStackType<Type>::linkedStackType(const linkedStackType<Type> &otherStack)
{
    stackTop=nullptr;
    sizeStack= otherStack.sizeStack;
    copyStack(otherStack);
}

//Assignment operator
template<class Type>
const linkedStackType<Type>& linkedStackType<Type>:: operator=(const linkedStackType<Type> &otherStack)
{
    if(this != &otherStack)
    {
        sizeStack= otherStack.sizeStack;
        copyStack(otherStack);
    }
    return*this;
}


template<class Type>
bool linkedStackType<Type>:: isEmptyStack() const
{
    //Check if stack is empty
    if(stackTop==nullptr)
        return true;
    else
        return false;
}

template<class Type>
bool linkedStackType<Type>:: isFullStack() const
{
    //Check if stack is full
    if(sizeStack>=SIZE)
        return true;
    else
        return false;
}

//Initialize function
template<class Type>
void linkedStackType<Type>:: initializeStack()
{
    //Delete elements in stack
    while(stackTop != nullptr)
    {
        //Traverse linked list with temp, delete elements
        nodeType<Type> *temp= stackTop;
        stackTop= stackTop->link;
        delete temp;
        sizeStack--;
    }
    
    stackTop=nullptr;
}

//Push function
template<class Type>
void linkedStackType<Type>:: push(const Type& newItem)
{
    //Create new node in linked list
    nodeType<Type> *newNode = new nodeType<Type>;
    newNode->info = newItem;
    newNode->link = nullptr;
    
    //If stack has space, add element
    if(!isFullStack())
        
    {
    //If stack is empty
    if(stackTop==nullptr)
        stackTop=newNode;
    else
    {
        //Add element to top of stack
        newNode->link=stackTop;
        stackTop=newNode;
    }
    
    sizeStack++;
    
    }
    
    else
        cout<< "Stack is full\n";
    
}

template<class Type>
Type linkedStackType<Type>:: top() const
{
    //If stack is empty, no top element
    if(isEmptyStack())
    {
        cout<< "Stack is empty\n";
        exit(1);
    }
    else
        return(stackTop->info);
}

//Pop function
template<class Type>
void linkedStackType<Type>:: pop()
{
    //If stack is empty, no elements to pop
    if(isEmptyStack())
    {
        cout<< "Stack is empty\n";
        exit(1);
    }
    else
    {
        //Create temp node to assign stacktop
        nodeType<Type> *node= stackTop;
        stackTop= stackTop->link; //Move stacktop forward
        delete node;
        sizeStack--;
    }
}

//Destructor
template<class Type>
linkedStackType<Type>:: ~linkedStackType()
{
    //Uses initialize function to clear elements
    initializeStack();
}

//Display function
template<class Type>
void linkedStackType<Type>:: display()
{
    nodeType<Type> *curr= stackTop;
    
    if(stackTop==nullptr)
        cout<< "Stack is empty\n";
    else
    {
        //Traverse linked list with curr to print elements
        while(curr != nullptr)
        {
            cout<< curr->info << " ";
            curr= curr->link;
        }
        
        cout<<endl;
    }
}

#endif /* linkedStack_h */
