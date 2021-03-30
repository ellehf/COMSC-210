//
//  main.cpp
//  COMSC-210 4N
//
//  Created by Elle Hoarau on 10/2/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct NodeType;
typedef NodeType * NodePtr;

struct RecType
{
    long id;
    string fname;
    string lname;
    double amount;
};

struct NodeType
{
    long id;
    string fname;
    string lname;
    double amount;
    NodePtr flink;
    NodePtr blink;

};

class AccountList
{
private:
    NodePtr head;
    NodePtr cursor;
public:
    AccountList ( );
    void addAccountSorted (RecType rec);
    void updateAccount (RecType rec);
    void display(ofstream &lfstream);
};

AccountList::AccountList ( )
{
    head = new NodeType;
    head->id = -1;
    head->fname = "";
    head->lname = "";
    head->amount= -999.999;
    head->flink=head;
    head->blink=head;
    cursor = head;

}
void AccountList::addAccountSorted(RecType rec)
{
    //Create the new node and fill it in.
    NodePtr newPtr = new NodeType;
    newPtr->id = rec.id;
    newPtr->fname = rec.fname;
    newPtr->lname = rec.lname;
    newPtr->amount = rec.amount;
    newPtr->flink = NULL;
    newPtr->blink = NULL;

    //find the Node of point of insertion
    NodePtr cur, prev;
    for (cur=head->flink; cur!=head; cur=cur->flink)
    {
        if (rec.id < cur->id)
            break;
    }
    //set prev
    prev = cur->blink;

    //update the two forward links
    newPtr->flink=prev->flink;
    prev->flink = newPtr;

    //update the two backward links
    newPtr->blink = cur->blink;
    cur->blink = newPtr;

}

void AccountList::updateAccount(RecType rec)
{
    //move the cursor forward if at dummy node
    if (cursor == head)
        cursor = cursor->flink;

    //cursor is at the target node. do not move it
    if (cursor->id == rec.id)
    {
        //update the account
        cursor->fname=rec.fname;
        cursor->lname=rec.lname;

        if(rec.amount>0)
            cursor->amount+=rec.amount;
        else
            cursor->amount+=rec.amount;

        //if the account became zero or negative
        //delete the node and move the cursor forward
        if(cursor->amount<=0)
        {
            NodePtr temp=cursor;
            cursor->blink->flink=cursor->flink;
            cursor->flink->blink=cursor->blink;
            cursor=cursor->flink;
            delete(temp);
        }

    }
    //cursor at id value less than update id value
    else if (cursor->id < rec.id)
    {
        //traverse forward through linked list with cursor
        while (cursor != head)
        {
            if (cursor->id >= rec.id)
                break;
            cursor = cursor->flink;
        }
        //cursor at target node
        if (cursor->id == rec.id)
        {
            //update the account
            cursor->fname=rec.fname;
            cursor->lname=rec.lname;

            if(rec.amount>0)
                cursor->amount+=rec.amount;
            else
                cursor->amount+=rec.amount;

            //if the account became zero or negative
            //delete the node and move the cursor forward.
            if(cursor->amount<=0)
            {
                NodePtr temp=cursor;
                cursor->blink->flink=cursor->flink;
                cursor->flink->blink=cursor->blink;
                cursor=cursor->flink;
                delete(temp);
            }
        }
        //if no account exists yet, add account
        else
        {
            //insert the node prior to where cursor is
            NodePtr newPtr= new NodeType;
            newPtr->id=rec.id;
            newPtr->fname=rec.fname;
            newPtr->lname=rec.lname;
            newPtr->amount=rec.amount;
            newPtr->flink=NULL;
            newPtr->blink=NULL;
            newPtr->blink=cursor->blink;
            newPtr->flink=cursor;
            cursor->blink->flink=newPtr;
            cursor->flink->blink=newPtr;
        }
    }
    //cursor at id value greater than update id value
    else
    {
        //traverse backwards through linked list with cursor
        while (cursor != head )
        {
            if (cursor->id <= rec.id)
                break;
            cursor = cursor->blink;
        }

        //cursor at target node
        if (cursor->id == rec.id)
        {
            //update the account
            cursor->fname=rec.fname;
            cursor->lname=rec.lname;
            if(rec.amount>0)
                cursor->amount+=rec.amount;
            else
                cursor->amount+=rec.amount;

            //if the account became zero or negative
            //delete the node and move the cursor forward.
            if(cursor->amount<=0)
            {
                NodePtr temp=cursor;
                cursor->blink->flink=cursor->flink;
                cursor->flink->blink=cursor->blink;
                cursor=cursor->flink;
                delete(temp);
            }

        }
        //if no account exists yet, add account
        else
        {
            //first move the cursor forward by one
            //This will make it point to the point of insertion node.
            //Then insert the node prior to where cursor is.
            NodePtr newPtr= new NodeType;
            newPtr->id=rec.id;
            newPtr->fname=rec.fname;
            newPtr->lname=rec.lname;
            newPtr->amount=rec.amount;
            newPtr->flink=NULL;
            newPtr->blink=NULL;
            cursor=cursor->flink;
            newPtr->blink=cursor->blink;
            newPtr->flink=cursor;
            cursor->blink->flink=newPtr;
            cursor->flink->blink=newPtr;
        }
    }
}

void AccountList::display(ofstream &lfout)

{
        for(NodePtr cur = head->flink; cur!=head; cur=cur->flink)
             lfout << cur->id << " " << cur->fname << " " << " " << cur->lname << " "<< cur->amount << endl;

}


int main()
{

RecType recType;
AccountList accounts;

ifstream mfile("master.txt");
ifstream tfile("tran.txt");
ofstream logfile("log.txt");
ofstream mfileUpdate("mfileUpdate.txt");
    
if(mfile.is_open())
{
    //read master file and create linked list
    while(mfile>>recType.id)
    {
        mfile >> recType.fname >> recType.lname >> recType.amount;
        accounts.addAccountSorted(recType);
    }
}
else
    cout<<" Unable to open master file\n";
    
mfile.close();

//Write updated master file
mfileUpdate<< "Updated Master File:\n";
accounts.display(mfileUpdate);

mfileUpdate.close();

//Write log file with list before updates
logfile<< "List at start:\n";
accounts.display(logfile);

if(tfile.is_open())
    {
        int i=0;
        
        //read transaction file and and update
        while(tfile>>recType.id)
        {
            
            tfile >> recType.fname >> recType.lname >> recType.amount;
            accounts.updateAccount(recType);

            //Write each updated list to log file
            i++;
            logfile << "\nList after update " << i <<endl;
            accounts.display(logfile);
              
        }
    
    }
    
else
    cout<<" Unable to open transaction file\n";

tfile.close();

logfile.close();


return 0;
}

