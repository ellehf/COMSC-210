//
//  main.cpp
//  COMSC 210 - 2N
//
//  Created by Elle Hoarau on 9/11/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>
using namespace std;

class DynamicStringArray
{
private:
    string *dynamicArray;
    int size;
public:
    DynamicStringArray();
    DynamicStringArray(int s);
    int getSize();
    void addEntry(string entry);
    bool deleteEntry(string entry);
    string getEntry(const int n);
    DynamicStringArray(const DynamicStringArray& copy);
    DynamicStringArray& operator==(const DynamicStringArray& other);
    ~DynamicStringArray();
};

//Default constructor
DynamicStringArray::DynamicStringArray()
{
    dynamicArray=NULL;
    size=0;
}

//Constructor taking parameter
DynamicStringArray::DynamicStringArray(int s)
{
    dynamicArray= new string[s];
    size=s;
}

//Accessor function to return size
int DynamicStringArray::getSize()
{
    return size;
}

//Function to add element to end of array
void DynamicStringArray::addEntry(string entry)
{
    string *newDynamicArray= new string[size+1];
    
    int i;
    
    for(i=0;i<size;i++)
    {
        newDynamicArray[i]=dynamicArray[i];
    }
    
    newDynamicArray[i]=entry;
    
    size++;
    
    delete[] dynamicArray;
    
    dynamicArray=newDynamicArray;
}

//Function to delete element from array
bool DynamicStringArray::deleteEntry(string entry)
{
    int i;
    
    for(i=0; i<size; i++)
        if(dynamicArray[i].compare(entry)==0)
            break;
    
    if(i==size)
        return false;
    
    string *newDynamicArray= new string[size-1];
    
    int j=0;
    
    for(i=0; i<size; i++)
    {
        if(dynamicArray[i].compare(entry)!=0)
            newDynamicArray[j++]=dynamicArray[i];
    }
    
    delete[] dynamicArray;
    
    size--;
    
    dynamicArray= newDynamicArray;
    
    return true;
}

//Function that returns element of array at specified position
string DynamicStringArray::getEntry(int n)
{
    if(n<0 || n>size)
        return NULL;
    
    return dynamicArray[n];
}

//Copy constructor
DynamicStringArray::DynamicStringArray(const DynamicStringArray& copy)
{
    size=copy.size;
    
    dynamicArray= new string[size];
    
    for(int i=0; i<size; i++)
        dynamicArray[i]= copy.dynamicArray[i];
}

//Assignment operator
DynamicStringArray& DynamicStringArray::operator==(const DynamicStringArray& other)
{
    if (dynamicArray != NULL)
    {
        delete[] dynamicArray;
    }
    if (other.size == 0)
    {
        size = 0;
        dynamicArray = NULL;
    }
    else
    {
        size = other.size;
        dynamicArray = new string[size];
        for (int i = 0; i < size; i++)
        {
            dynamicArray[i] = other.dynamicArray[i];
        }
    }
    return (*this);
}

//Destructor
DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}

int main()
{
    DynamicStringArray names;
    
    // List of names
    names.addEntry("Frank");
    names.addEntry("Wiggum");
    names.addEntry("Nahasapeemapetilon");
    names.addEntry("Quimby");
    names.addEntry("Flanders");
    
    // Output list
    cout << "List of names:" << endl;
    for (int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;
    
    // Add and remove some names
    names.addEntry("Spuckler");
    cout << "After adding a name:" << endl;
    for (int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;
    
    names.deleteEntry("Nahasapeemapetilon");
    cout << "After removing a name:" << endl;
    for (int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;
    
    names.deleteEntry("Skinner");
    cout << "After removing a name that isn't on the list:" << endl;
    for (int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;
    
    names.addEntry("Muntz");
    cout << "After adding another name:" << endl;
    for (int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;
    
    // Remove all of the names by repeatedly deleting the last one
    while (names.getSize() > 0) {
        names.deleteEntry(names.getEntry(names.getSize() - 1));
    }
    
    cout << "After removing all of the names:" << endl;
    for (int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;
    
    names.addEntry("Olivia");
    cout << "After adding a name:" << endl;
    for (int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;
    
    cout << "Testing copy constructor" << endl;
    DynamicStringArray names2(names);
    // Remove Olivia from names
    names.deleteEntry("Olivia");
    cout << "Copied names:" << endl;
    for (int i = 0; i < names2.getSize(); i++)
        cout << names2.getEntry(i) << endl;
    cout << endl;
    
    cout << "Testing assignment" << endl;
    DynamicStringArray names3 = names2;
    // Remove Olivia from names2
    names2.deleteEntry("Olivia");
    cout << "Copied names:" << endl;
    for (int i = 0; i < names3.getSize(); i++)
        cout << names3.getEntry(i) << endl;
    cout << endl;
    
    cout << "Enter a character to exit." << endl;
    char wait;
    cin >> wait;
    return 0;
}


