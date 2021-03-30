//
//  ArrayQueue.h
//  COMSC-210 7N
//
//  Created by Elle Hoarau on 10/13/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#ifndef ArrayQueue_h
#define ArrayQueue_h

#include <iostream>
#include <climits>

using namespace std;

#define CAPACITY 100 //Array max size

class arrayQueue
{
public:
    arrayQueue(); //Default constructor
    void enqueue(int info); //Add elements to queue
    void dequeue(); //Remove first element of queue
    bool isFull(); //Check if queue is full
    bool isEmpty(); //Check if queue is empty
    int getFront(); //Return first element of queue
    int getBack(); //Return last element of queue
    int getSize(); //Return size of queue
    void display(); //Display queue
private:
    int Q[CAPACITY];
    int size; //Size of queue
    int front; //Front element of queue
    int back; //Last element of queue
    
};

arrayQueue::arrayQueue()
{
    size=0;
    front=back=-1;
}


void arrayQueue::enqueue(int info)
{
    if(isFull()) //If queue is full, return
    {
        cout<<"Queue is full\n";
        return;
    }
    
    else if(isEmpty()) //If queue is empty, set front and back to 0
        front=back=0;
    
    else //If queue is not full, but has space, move back one over
        back= (++back) % CAPACITY;
    
    Q[back]= info; //Set back to new element
    size++; //Increment size of array
}


void arrayQueue::dequeue()
{
    if(isEmpty()) //If queue is empty, return
    {
        cout<<"Queue is empty\n";
        return;
    }
    
    else
    {
        cout<< "Element removed is: " << Q[front] <<endl; //Display removed element
        front = (++front) % CAPACITY; //Move front one over
    }
    
    size--; //Decrememnt size of array
}

bool arrayQueue::isFull()
{
    return(size==CAPACITY); //Full if size of array equals capacity
}

bool arrayQueue::isEmpty()
{
    return(size==0); //Empty if size of array equals 0
}

int arrayQueue::getFront()
{
    if(isEmpty()) //Return if queue is empty
    {
        cout<< "Queue is empty\n";
        return -1;
    }
    
    else
        return Q[front]; //Return front element of array
}

int arrayQueue::getBack()
{
    if(isEmpty()) //Return if queue is empty
    {
        cout<< "Queue is empty\n";
        return -1;
    }
    
    else
        return Q[back]; //Return back element of array
}

int arrayQueue::getSize()
{
    return size;
}

void arrayQueue::display()
{
    if(isEmpty())
       cout<< "Queue is empty\n";
    else
       {
        for(int i=front; i<=back; i++) //Display elements of array with loop
        cout<< Q[i] << " ";
    }
}

#endif /* ArrayQueue_h */
