//
//  main.cpp
//  COMSC-210 10N
//
//  Created by Elle Hoarau on 11/26/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>
using namespace std;

const int SIZE=50;

struct client
{
    int priority;
    string name;
};

class priorityQueue
{
private:
    int tail;
    client line[SIZE]; //Max size of line
    void maxReheapifyUp(client line[], int last); //Heapsort array
    void maxReheapifyDown(client line[], int last); //Heapsort array
    int findLargeChild(client line[], int parent, int last); //Find index of largest child
public:
    priorityQueue(); //Default Constructor
    void penqueue(string name, int value); //Enqueue clients
    client pdequeue(); //Return next client in line
    bool isEmpty(); //Check if line is empty
    client userInput;
};

//Default constructor
priorityQueue:: priorityQueue()
{
    tail=-1;
}

//Enqueue clients
void priorityQueue:: penqueue(string name, int value)
{
    tail++; //Increment tail index
    
    //Insert data
    line[tail].priority=value;
    line[tail].name=name;
    
    //Reheapify priority queue
    maxReheapifyUp(line, tail);
}

//Dequeue clients
client priorityQueue:: pdequeue()
{
    client next= line[0]; //Get data for next client
    line[0]= line[tail]; //Remove from line and decrement
    tail--;
    
    //Reheapify priority queue
    maxReheapifyDown(line, tail);
    
    return next;
}

//Check is queue is empty
bool priorityQueue:: isEmpty()
{
    if(tail<0)
        return 1;
    else
        return 0;
}

//Reheapify queue
void priorityQueue:: maxReheapifyUp(client line[], int last)
{
    int parent;
    int child=tail;
    
    //Traverse up max heap
    while(child>0)
    {
        parent= child/2;
        
        if(line[child].priority <= line[parent].priority)
            break;
        else
        {
            //Swap data at child index and parent index
            client temp;
            temp.priority= line[child].priority;
            temp.name= line[child].name;
            
            line[child].priority= line[parent].priority;
            line[child].name= line[parent].name;
            
            line[parent].priority= temp.priority;
            line[parent].name= temp.name;
            
            //Update child index to parent index
            child=parent;
        }
        
    }
}

void priorityQueue:: maxReheapifyDown(client line[], int last)
{
    int parent=0;
    int largeChild;
    
    //Traverse down max heap
    while(parent<tail)
    {
        largeChild= findLargeChild(line, parent, last); //Find index of largest child
        
        if(largeChild < 0 || line[largeChild].priority <= line[parent].priority)
            break;
        
        else
        {
            //Swap data at parent index with child index
            client temp;
            temp.priority= line[parent].priority;
            temp.name= line[parent].name;
            
            line[parent].priority= line[largeChild].priority;
            line[parent].name= line[largeChild].name;
            
            line[largeChild].priority= temp.priority;
            line[largeChild].name= temp.name;
            
            //Update parent index
            parent=largeChild;
        }
    }
}

int priorityQueue:: findLargeChild(client line[], int parent, int last)
{
    //Initialize left and right child index
    int l= (2*parent)+1; //
    int r= (2*parent)+2;
    
    //If both children exist
    if(r <= last && l <= last)
    {
        if(line[r].priority > line[l].priority)
            return r;
        else
            return l;
    }
    
    //If only left child
    else if(l <= last)
        return l;
    
    //If no children
    else
        return -1;
}

int main()
{
    priorityQueue recordList;

    while (recordList.userInput.priority >= 0)
    {
        cout << "Input priority status:" << endl;
        cin >> recordList.userInput.priority;
        if (recordList.userInput.priority == -1)
            break;
        cout << "Input Name:" << endl;
        cin >> recordList.userInput.name;

        recordList.penqueue(recordList.userInput.name, recordList.userInput.priority);
    }

    cout<< "\nOutput"<<endl;
    while (!recordList.isEmpty())
    {
        recordList.userInput = recordList.pdequeue();
        cout << recordList.userInput.priority << " " << recordList.userInput.name << endl;

    
    }
    return 0;
}
