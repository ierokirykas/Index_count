// 0 1 4 9 16   25   36   49   64   81
//  1 3 5 7   9   11   13   15   17
//   2 2 2  2   2    2    2    2
// Как мы видим, разница между степенями имеет свою последовательность

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