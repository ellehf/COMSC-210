//
//  main.cpp
//  COMSC-210 11N
//
//  Created by Elle Hoarau on 12/5/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

struct nodeType
{
int d; //Total distance from the start vertex to this vertex.
nodeType *link; //Link to the next node.
};

//IntQue is a regular queue that queues ints to store adjacent vertices.
class queue
{
private:
nodeType *head;
nodeType *tail;
    
public:
queue();
void enque(int i);
void deque(int &i);
bool isEmpty();
};

queue ::queue()
{
    head= NULL;
    tail= NULL;
}

void queue:: enque(int d)
{
    //Create a node
    nodeType *ptr= new nodeType();
    ptr->d= d;
    ptr->link= NULL;
    
    //link the node
    //case empty queue
    if (head == NULL && tail== NULL)
    {
        head= ptr;
        tail= ptr;
    }
    
    //case end queue
    else
    {
        tail->link= ptr;
        tail= ptr;
    }
}

void queue:: deque(int &i)
{
    i= head->d;
    //Remove the node
    head= head->link;
    
    //Test to see if the que became empty after removal
    //In that case, make sure to set the tail to NULL
    if (head == NULL)
    tail= NULL;
}

bool queue:: isEmpty()
{
    if(head==NULL && tail==NULL)
        return true;
    else
        return false;
}

struct itemType
{
    int d; //Total distance from the start vertex to this vertex
    int path[20];//Array of all vertices in the path from the start vertex to this vertex
    int length; //Length of the above array
};

struct pNodeType
{
    int d; //Total distance from the start vertex to this vertex
    int path[20];//Array of all vertices in the path from the start vertex to this vertex
    int length; //Length of the above array
    pNodeType *link; //Link to the next node
};

//ItemQue is a priority queue that queues ItemType items.
class pQueue
{
private:
    pNodeType *head;
    pNodeType *tail;
public:
    pQueue();
    void enque(itemType n);
    void dequeue(itemType &n);
    bool isEmpty();
    void penque(itemType n);
};

pQueue:: pQueue()
{
    head= NULL;
    tail= NULL;
}

void pQueue:: penque(itemType n)
{
    //Create a node
    pNodeType *ptr= new pNodeType;
    ptr->d= n.d;
    
    int i;
    for (i=0; i<20; i++)
        ptr->path[i]= n.path[i];
    
    ptr->length= n.length;
    ptr->link= NULL;
    
    //Link the entry;
    if (head == NULL)
    {
        head= ptr;
    }
    //case: head insertion
    else if (n.d < head->d)
    {
        ptr->link= head;
        head= ptr;
    }
    //case: mid and end insertion:
    else
    {
    //use the cur to locate the point of insertion
    //let prev walk behind it.
        pNodeType *cur, *prev;
        for (prev=head, cur=head->link; cur != NULL; prev=prev->link, cur=cur->link)
        {
            if (ptr->d < cur->d)
                break;
        }
        //do the insertion using prev
        ptr->link= prev->link;
        prev->link= ptr;
    }
}

void pQueue:: enque(itemType n)
{
    //Create a node
    pNodeType *ptr= new pNodeType ;
    ptr->d= n.d;
    
    int i;
    for (i=0; i<20; i++)
        ptr->path[i]= n.path[i];
    
    ptr->length= n.length;
    ptr->link= NULL;
    
    //link the node
    //case empty queue
    if (head == NULL && tail== NULL)
    {
        head= ptr;
        tail= ptr;
    }
    //case end queue
    else
    {
        tail->link= ptr;
        tail= ptr;
    }
}

void pQueue:: dequeue(itemType &n)
{
    //fill using head.
    n.d= head->d;
    int i;
    for (i=0;i<20;i++)
    {
        n.path[i]= head->path[i];
    }
    
    n.length= head->length;
    
    //Remove the node
    head= head->link;
    //Test to see if the que became empty after removal
    //In that case, make sure to set the tail to NULL
    if (head == NULL)
        tail= NULL;
}

bool pQueue:: isEmpty()
{
    if(head==NULL && tail==NULL)
        return true;
    else
        return false;
}

class Graph
{
private:
  string vertices[20];
  int edges[20][20];
  int size;
    
public:
  Graph();
  void addVertex(string vertex);
  void addEdge(int hereV, int thereV, int weight);
  void getAdjacent(int vertex, queue &adjQ);
  void MinPath(int here, int there);
};

Graph:: Graph()
{
  size= 0;
  for (int i=0; i<20; i++)
  {
    for (int j=0; j<20; j++)
        edges[i][j]= 0;
  }
}

void Graph:: addEdge(int hereV, int thereV, int weight)
{
  //set to weight the appropriate element in the matrix
  edges[hereV][thereV]= weight;
  edges[thereV][hereV]= weight;
}

void Graph:: getAdjacent(int vertex, queue &adjQ)
{
  //Any vertex to which i have an edge present is my adjacent vertex.
  for (int i=0; i<size; i++)
  {
    if(edges[vertex][i] > 0)
      adjQ.enque(i);
  }
}

void Graph:: addVertex(string vertex)
{
  //add the next vertex at the next index in the array
  vertices[size]= vertex;
  size++;
}

void Graph:: MinPath(int here, int there)
{
    pQueue mq;
    queue adjq;
    itemType item;

    int Pvertex; //parent vertex #
    int Pdist; //total distance of the parent vertex from the start vertex.
    int Plength;//the length of path.
    
    int adjver; //a vertex
    int marked[20];//array to keep track of which vertices are marked.

    //unmark all vertices.
    for (int i=0;i<20;i++)
        marked[i]= 0;

    //Initialize the path array to be all zeros.
    for (int i=0;i<20;i++)
        item.path[i]= 0;
    
    //Initialize
    item.d= 0;
    item.path[0]= here;
    item.length= 1;

    mq.penque(item);
    //start the deque/enque loop
    
    while(!(mq.isEmpty()))
    {
        //Deque the item.
        mq.dequeue(item);
        //break if target is reached.
        if (item.path[item.length-1] == there)
            break;
            
        Pdist= item.d;
        Pvertex= item.path[item.length-1];
        Plength= item.length;
        

        if(marked[item.path[item.length-1]] == 0 )
        {
            //mark the item
            marked[item.path[item.length-1]] = 1;
            getAdjacent (item.path[item.length-1], adjq);

            while ( !(adjq.isEmpty()) )
            {
                adjq.deque (adjver);

                if (marked[adjver] == 0)
                {
                    item.d= Pdist + edges[Pvertex][adjver];
                    //add the vertex to the path list in the item
                    item.path[Plength]= adjver;
                    //update the length of the used verix array list
                    item.length= Plength + 1;
                    //enque the item in the priority que
                    mq.penque(item);
                }
            }
        }
    }
    
    //Output distance
    cout << "Minimum distance from " << vertices[here] << " to " << vertices[there] << " is "<< item.d << endl;
    cout << "Path:" << endl;
    int i;
    for (i=0;i<item.length;i++)
    {
        cout << vertices[item.path[i]] << endl;
    }
}

int main()
{
    Graph graph;
    string vertexName [20];
    int verNum;
    string verName;

    ifstream fin;
    fin.open ("MinPath2.txt");
    fin >> verNum;
    while (verNum >= 0)
    {
        fin>> verName;
          //add the vertex to the graph
        graph.addVertex(verName);
        fin>> verNum;
    }
    
    int startVertex, endVertex, weight;
    fin>> startVertex;
    
    while (startVertex >= 0)
    {
        fin>> endVertex;
        fin>> weight;
          //add the vertex to the graph
          //register the edge in edges matrix.
        graph.addEdge(startVertex, endVertex, weight);
        fin>> startVertex;
    }
 
    graph.MinPath(0,5);
    
    return 0;
}

