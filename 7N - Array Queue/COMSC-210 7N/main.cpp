//
//  main.cpp
//  COMSC-210 7N
//
//  Created by Elle Hoarau on 10/11/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//
#include "ArrayQueue.h"

int main()
{
    int choice, input;
    
    arrayQueue theQueue;
    
    cout << "Menu" << endl;
    cout<< "1. Enqueue\n2. Dequeue\n3. Size\n4. Get Front\n5. Get Back\n6. Display\n7. Exit\n";
        
    cin >> choice;
    
    while (choice !=7)
    {

    switch (choice)
    {
            
    case 1: //Enqueue
            
            cout << "\nEnter data to enqueue (-99 to stop): ";
            cin >> input;
            
            while ( input != -99)
            {
                theQueue.enqueue(input);
                cout << "\nEnter data to enqueue (-99 to stop): ";
                cin >> input;
            }


            break;

    case 2: //Dequeue
    
            theQueue.dequeue();
            break;

    case 3: //Size of queue

            cout<< "Queue size is: " << theQueue.getSize() <<endl;

            break;

    case 4: //Get front
    
            cout<< "Front element is: " << theQueue.getFront() <<endl;

            break;

    case 5: //Get back

            cout<< "Back element is: " << theQueue.getBack() <<endl;

            break;

    case 6: //Display
            cout<< "Queue: ";
            theQueue.display();
            break;

    default:
            cout <<"Invalid choice, please input number between (0-5).\n";
            break;
    }

    cout <<"\n\n";

    cin >> choice;
    }
    
}
