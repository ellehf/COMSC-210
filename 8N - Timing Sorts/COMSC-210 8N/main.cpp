//
//  main.cpp
//  COMSC-210 8N
//
//  Created by Elle Hoarau on 11/3/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include<math.h>
#include <iomanip>

using namespace std;

//Global arrays for testing
int *Insert;
int *Bubble;
int *Select;
int *Heap;
int *Quick;
int *Merge;

//Insertion sort
void insertionSort(int SIZE)
{
    int i,j;
    int temp; //temp variable for swap
    
    for(i=1; i<SIZE; i++) //traverse list
    {
        j=i;
        while(j>0 && Insert[j]<Insert[j-1]) //check if value to left of position is smaller
        {
            //swap positions
            temp= Insert[j];
            Insert[j]= Insert[j-1];
            Insert[j-1]= temp;
            --j;
        }
    }
}

//Bubble Sort
void bubbleSort(int SIZE)
{
    int i= 1;
    int temp; //temp variable for swap
    bool swap= true;
    
    while(i<SIZE && swap==true)
    {
        swap= false;
        
        for(int j=0; j<SIZE; j++) //traverse list
        {
            if(Bubble[j] > Bubble[j+1]) //check if value to the right is smaller
            {
                //swap positions
                temp= Bubble[j];
                Bubble[j]= Bubble[j+1];
                Bubble[j+1]= temp;
                swap= true;
            }
        }
        i++;
    }
}

//Selection sort
void selectionSort(int SIZE)
{
    int i, j;
    int small;
    int temp; //temp variable for swap
    
    for(i=0; i< SIZE-1; ++i) //traverse list
    {
        small=i; //set first value to small
        for(j=i+1; j< SIZE; ++j)
        {
            if(Select[j]<Select[small]) //find value less than small variable
                small=j;
        }
        
        //swap positions
        temp= Select[i];
        Select[i]= Select[small];
        Select[small]= temp;
    }
}

//Heapify subtree with node i
void heapify(int SIZE, int i)
{
    int high= i; //initialize high as root
    int l= 2*i+1;
    int r= 2*i+2;
    
    if(l<SIZE && Heap[l]>Heap[high]) //if left child is larger than root
        high=l; //set high equal to left
    
    if(r<SIZE && Heap[r]>Heap[high]) //if right child is larger than root
        high=r; //set high equal to right
    
    if(high!=i) //if high is not root
    {
        //swap positions
        int temp;
        temp=Heap[i];
        Heap[i]=Heap[high];
        Heap[high]=temp;
        
        heapify(SIZE, high); //Repeat with subtree
    }
}

//Heap Sort
void heapSort(int SIZE)
{
    for(int i=SIZE/2-1; i>=0; i--) //Build heap
    {
        heapify(SIZE, i);
    }
    
    for(int i=SIZE-1; i>=0; i--)
    {
        //Swap current root to end
        int temp;
        temp= Heap[0];
        Heap[0]= Heap[i];
        Heap[i]= temp;
        
        heapify(i, 0); //Recursively call heapify
    }
}

//Move elements smaller than pivot to its left and larger elements to its right
int partition(int low, int high)
{
    int pivot= Quick[high]; //Initialize pivot
    int i= (low-1), j;
    
    for (j=low; j <= high-1; j++) //Traverse list
    {
        if (Quick[j]<=pivot) //If current element less than pivot
        {
            i++; //Increment index
            
            //Swap positions
            int temp= Quick[i];
            Quick[i]= Quick[j];
            Quick[j]= temp;
        }
    }
    
    //Swap positions
    int temp= Quick[i+1];
    Quick[i+1]= Quick[high];
    Quick[high]= temp;
    return(i+1);
}

//Quick sort
void quickSort(int l, int h)
{
    if(l<h)
    {
        int j= partition(l, h); //Partition elements
        
        //Recursively call quickSort
        quickSort(l, j-1);
        quickSort(j+1, h);
    }
}

void merge(int l, int m, int h)
{
    int size1= m-l+1;
    int size2= h-m;
    
    //Temp arrays
    int *arr1= new int[size1];
    int *arr2= new int[size2];
    
    //Fill temp arrays
    for(int i=0; i<size1; i++)
        arr1[i]= Merge[l+i];
    
    for(int j=0; j<size2; j++)
        arr2[j]= Merge[m+1+j];
    
    
    int a=0, b=0, c=l;
    while (a<size1 && b<size2) //Merge temp arrays in order
    {
        if(arr1[a]<=arr2[b])
        {
            Merge[c]= arr1[a];
            a++;
        }
        
        else
        {
            Merge[c]= arr2[b];
            b++;
        }
            
        c++;
    }
    
    while(a<size1) //Copy any remaining elements in temp array to Merge
    {
        Merge[c]= arr1[a];
        a++;
        c++;
    }
    
    while(b<size2) //Copy any remaining elements in temp array to Merge
    {
        Merge[c]= arr2[b];
        b++;
        c++;
    }
   
}

//Merge sort
void mergeSort(int l, int h)
{
    int m;
    
    if(l<h)
    {
        m= l+(h-l)/2; //Set m to middle, but avoid overflow for large l and h
        
        mergeSort(l, m); //Sort first half
        mergeSort(m+1, h); //Sort second half
        
        merge(l, m, h);
    }
}

int main()
{
    srand(time(NULL));
    
    cout<< left << setw(20)<< "Data Size" << setw(15) << "Insertion" << setw(15) << "Bubble" << setw(15) << "Selection" << setw(15) << "Heap" << setw(15) << "Quick" << setw(15) << "Merge" <<endl;
    
    for(int i=10000; i<=50000; i+=10000) //Loop to benchmark each data size
    {
        Bubble= new int[i];
        Insert= new int[i];
        Select= new int[i];
        Heap= new int[i];
        Quick= new int[i];
        Merge= new int[i];
        
        for(int j=0; j<i; j++) //Loop to fill array with random values
        {
    
            int num= rand()%100; //Random values from 0-100
            Bubble[j]= num;
            Insert[j]= num;
            Select[j]= num;
            Heap[j]= num;
            Quick[j]= num;
            Merge[j]= num;
            
        }
        
        clock_t start, finish;
        start =clock( ); //time in milliseconds
        insertionSort(i);
        finish=clock( ); //time in milliseconds
        //the constant CLOCKS_PER_SEC below is equal to 1000
        double insertDuration = (double)((finish-start)/(double)CLOCKS_PER_SEC ); //time in secs.
        
        
        start =clock( ); //time in milliseconds
        bubbleSort(i);
        finish=clock( ); //time in milliseconds
        //the constant CLOCKS_PER_SEC below is equal to 1000
        double bubbleDuration = (double)((finish-start)/(double)CLOCKS_PER_SEC ); //time in secs.
        

        start =clock( ); //time in milliseconds
        selectionSort(i);
        finish=clock( ); //time in milliseconds
        //the constant CLOCKS_PER_SEC below is equal to 1000
        double selectDuration = (double)((finish-start)/(double)CLOCKS_PER_SEC ); //time in secs.

        start =clock( ); //time in milliseconds
        heapSort(i);
        finish=clock( ); //time in milliseconds
        //the constant CLOCKS_PER_SEC below is equal to 1000
        double heapDuration = (double)((finish-start)/(double)CLOCKS_PER_SEC ); //time in secs.

        start =clock( ); //time in milliseconds
        quickSort(0, i-1);
        finish=clock( ); //time in milliseconds
        //the constant CLOCKS_PER_SEC below is equal to 1000
        double quickDuration = (double)((finish-start)/(double)CLOCKS_PER_SEC ); //time in secs.
        
        start =clock( ); //time in milliseconds
        mergeSort(0, i-1);
        finish=clock( ); //time in milliseconds
        //the constant CLOCKS_PER_SEC below is equal to 1000
        double mergeDuration = (double)((finish-start)/(double)CLOCKS_PER_SEC ); //time in secs.
    
        //Display time duration in table
        cout<< left << setw(20) << i << setw(15) << insertDuration << setw(15) << bubbleDuration << setw(15) << selectDuration << setw(15) << heapDuration << setw(15) << quickDuration << setw(15) << mergeDuration <<endl;
        
    }
    
    return 0;
}
