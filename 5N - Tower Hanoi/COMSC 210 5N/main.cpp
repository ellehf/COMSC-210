//
//  main.cpp
//  COMSC 210 5N
//
//  Created by Elle Hoarau on 9/29/19.
//  Copyright © 2019 Elle Hoarau. All rights reserved.
//

#include <iostream>

using namespace std;

void towerHanoi(int n, char x, char y, char z)
{
    if(n==1)
    {
        cout<< "Move a disk from post " << x << " to post " << y <<endl;
        return;
    }
        towerHanoi(n-1, x, z, y);
        cout<< "Move a disk from post " << x << " to post " << y <<endl;
        towerHanoi(n-1, z, y, x);
}

int main()
{
    int n;
    
    cout<< "Enter number of disks\n";
    cin>>n;
    
    towerHanoi(n, 'A', 'B', 'C');
    
    return 0;
}
