// 0 1  32   243   1024    3125
//  1 31  211   781    2101
//   30 180  570   1320
//    150  390  750
//       240 360
//         120 = 1*2*3*4*5 = 5!
// Если продолжить увеличивать степени, то мы заметим,
// что низ "айсберга" всегда будет равен факториалу
// той степени, в которую мы возводим числа верхушки
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector<double> vector_init(int r, int N)
{
    vector<double> layer;
    for (double i = 0.0; i < N; i++)
    {
        layer.push_back(pow(i, r));
    }
    return layer;
}

vector<double> next_layer(vector<double> layer)
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

void print_vector(vector<double> input)
{
    for (double x : input)
        std::cout << x << " ";
    cout << endl;
}

// int main()
// {
//     int r = 5; // Степень
//     int N = r - 1;
//     int i;
//     vector<double> spisok = vector_init(r, N);
//     print_vector(spisok);
//     for (i = 0; i < r; i++)
//     {
//         spisok = next_layer(spisok);
//         print_vector(spisok);
//     }
//     return 0;
// };