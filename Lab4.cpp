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
    cout << "1 - VectorFloat" << endl;
    cout << "2 - CountryCapitalList" << endl;
    cin >> choice;

    if (choice == 1)
        task1();
    if (choice == 2)
        task2();

    return 0;
}
