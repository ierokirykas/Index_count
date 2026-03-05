#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

long long int n = 266765571072000;

int main()
{
    vector<int> dividers;
    for (int i = 2; i < sqrt(n) + 1; i++)
    {
        if (n % i == 0)
        {
            dividers.push_back(i);
            n /= i;
        }
    }
    for (int d : dividers)
        cout << d << " ";
    return 0;
}