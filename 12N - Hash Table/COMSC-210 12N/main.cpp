//
//  main.cpp
//  COMSC-210 12N
//
//  Created by Elle Hoarau on 12/8/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

struct RecType
{
   int id;
   string fName;
   string lName;
};

class StudentHT
{
public:
   struct NodeType
   {
       int id; //student ID
       string fName; //student first name
       string lName; //student last name
       NodeType *next;
   };
   struct NodeType **hashPtr;

   int size; //Size of hash table
   int numNodeSearch;
   int numIdSearch;
   double avg;

    StudentHT(int htSize);
    int hashFunc(int studentID);
    void insert(RecType item);
    RecType search(RecType item);
    void startStatistics();
    void endStatistics();
    void displayStatistics();
   
};

//Constructor to initialize hash table
StudentHT:: StudentHT(int HTsize)
 {
     size= HTsize;
     
     hashPtr= new NodeType *[size]; //Array to intialize  table

     //Initialize pointer with NULL values
     for (int i=0; i<size; i++)
         hashPtr[i]= NULL;
 }

//Calculate hash value
int StudentHT:: hashFunc(int studentID)
{
    return (studentID % size);
}

// Insert node into hash table
void StudentHT:: insert(RecType item)
{
    int hashValue= hashFunc(item.id); //Calculate hash value

    struct NodeType *newItem= new struct NodeType;
    
    // Copy to NodeType item
    newItem->id= item.id;
    newItem->fName= item.fName;
    newItem->lName= item.lName;
    newItem->next= NULL;

    //If first position in table
    if (hashPtr[hashValue] == NULL)
        hashPtr[hashValue]= newItem;
    
    //Otherwise, insert node in the linked list
    else
    {
        struct NodeType *temp= hashPtr[hashValue];
        while (temp->next != NULL)
            temp= temp->next;
        temp->next= newItem;
    }
}

//Search for node in hash table
RecType StudentHT:: search(RecType item)
{
    numIdSearch++; //Increment number if ID searches
    int hashValue= hashFunc(item.id);

    //Search for item
    RecType *itemSearch= new RecType;
    if (hashPtr[hashValue] != NULL)
    {
        struct NodeType *temp= hashPtr[hashValue];

        temp= hashPtr[hashValue];
        while (temp != NULL)
        {
            //Increment number of node searches
            numNodeSearch++;
            if (temp->id == item.id)
            {
                itemSearch->id= temp->id;
                itemSearch->fName= temp->fName;
                itemSearch->lName= temp->lName;
                return *itemSearch;
            }
            temp= temp->next;
        }
    }

    itemSearch->id= -1;
    return *itemSearch;
}

//Initialization for stats
void StudentHT:: startStatistics()
{
    numIdSearch= 0;
    numNodeSearch= 0;
    avg= 0;
}

//End of stats, compute avg search
void StudentHT:: endStatistics()
{
    avg= (double)numNodeSearch/numIdSearch;
}

//Display stats
void StudentHT:: displayStatistics()
{
    cout<< "Total number of ID's searched: " << numIdSearch <<endl;
    cout<< "Total number of nodes searched: " << numNodeSearch <<endl;
    cout<< "Average number of nodes searched per ID searched: " << avg <<endl;
}

int main()
{
   ifstream infile;
   int studentID;
    
   StudentHT hashtable(100); //Create array of hash tables
   struct RecType studentRec;
    
   hashtable.startStatistics(); //Start stats

   infile.open("add.txt");

   while (!infile.eof())
   {
       infile>> studentID; //Read in data from file
      
       struct RecType item; // Create item and fill with data
       item.id = studentID;
       
       hashtable.insert(item);// Insert item in hash table
   }

   infile.close();
   
   infile.open("search.txt"); //Open search file
  
   while (!infile.eof())
   {
       
       infile >> studentID; //Read student id from file
       
       struct RecType item;// Create item and fill with data
       item.id = studentID;
       
       studentRec = hashtable.search(item);// Search for item in hash table
       
       if (studentRec.id == -1) //If id is not found
       {
           cout<< "Student ID: " << studentID << " was not found in our records." <<endl;
       }
       
       else //If id is found
       {
           cout<< "Student ID: " << studentRec.id << " was found." << endl;
       }
   }
   
   infile.close();

   hashtable.endStatistics();
    
   hashtable.displayStatistics(); //Display search stats
    
   return 0;
}

