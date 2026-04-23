#include "Lab4.h"

#include <iostream>
#include <ostream>
#include "Task1.h"
#include "Task2.h"

using namespace std;

int main()
{
    cout << "Lab 4" << endl;

    int choice = 0;
    cout << "Choose the specific task to run" << endl;
    cin >> choice;

    switch (choice)
    {
        case 1: task1();
        case 2: task2();

        default: return 0;
    }
}
