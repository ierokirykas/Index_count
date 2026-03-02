#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector<int> vector_init(int N, int r)
{
    vector<int> layer;
    for (int i = 0; i < N; i++)
    {
        layer.push_back(pow(i, r));
    }
    return layer;
}

vector<int> next_layer(vector<int> layer)
{
    if (layer.size() <= 1)
        return {layer[0]}; // ничего не меняем

    // Идём с конца, чтобы не потерять значения
    for (int i = layer.size() - 1; i > 0; --i)
    {
        layer[i] = layer[i] - layer[i - 1];
    }
    layer.erase(layer.begin());

    return layer;
}

void print_vector(vector<int> input)
{
    for (int x : input)
        std::cout << x << " ";
    cout << endl;
}

int main()
{
    int r = 10; // Степень
    // int N = 10; // Кол-во чисел
    int N = r + 1;
    int i;
    vector<int> spisok = vector_init(N, r);
    print_vector(spisok);
    for (i = 0; i < r; i++)
    {
        spisok = next_layer(spisok);
        print_vector(spisok);
    }
    return 0;
};