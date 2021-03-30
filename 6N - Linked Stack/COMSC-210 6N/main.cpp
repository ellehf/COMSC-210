//
//  main.cpp
//  COMSC-210 6N
//
//  Created by Elle Hoarau on 10/3/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include "linkedStack.h"


int main()
{
    linkedStackType<int> stack1;
    linkedStackType<int> stack2;
    
    int choice, data;

    while(1)
    {
    /* Menu */
    cout <<"------------------------------------\n";
    cout <<" STACK IMPLEMENTATION PROGRAM \n";
    cout <<"------------------------------------\n";
    cout <<"1. Push\n";
    cout <<"2. Pop\n";
    cout <<"3. Display top element of stack\n";
    cout <<"4. Print Stack\n";
    cout<< "5. Use copy constructor and display stack\n";
    cout <<"6. Use assignment operator and display stack\n";
    cout <<"7. Initialize stack\n";
    cout <<"8. Check if stack is empty\n";
    cout <<"9. Check if stack is full\n";
    cout <<"10. Exit\n";
    cout <<"------------------------------------\n";
    cout <<"Enter your choice: ";

    cin >>choice;

    switch(choice)
    {
    case 1:
            cout <<"Enter data to push into stack: ";
            cin >> data;

            // Push element to stack
            stack1.push(data);
            break;

    case 2:
    
            //Pop element from stack
            stack1.pop();
            break;

    case 3:
            cout<< stack1.top() <<endl;
            break;
    
    case 4:
            //Print stack
            stack1.display();
            break;
            
    case 5:
        {
            //Use copy constructor
            linkedStackType<int> stack3=stack1;
            stack3.display();
            break;
        }
            
    case 6:
            //Use assignment operator
            stack2=stack1;
            stack2.display();
            break;

    case 7:
            //Use initialize function
            stack1.initializeStack();
            break;
            
    case 8:
            //Use check empty function
            cout<< stack1.isEmptyStack() <<endl;
            break;
            
    case 9:
            //Use check full function
            cout<< stack1.isFullStack() <<endl;
            break;
        
    case 10:
            cout <<"Exiting from app.\n";
            exit(0);
            break;

    default:
            cout <<"Invalid choice, please try again.\n";
    
    }

    cout <<"\n\n";
    }
    
    return 0;
}
