#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        cout << pow(i, 2) << " ";
    }
    cout << endl;
    for (i = 0; i < 10; i++)
    {
        cout << pow(i, 2) - pow(i - 1, 2) << " ";
    }
    cout << endl;
    for (i = 0; i < 10; i++)
    {
        cout << pow(i, 2) - pow(i - 1, 2) - (pow(i - 1, 2) - pow(i - 2, 2)) << " ";
    }
    cout << endl;
    return 0;
};