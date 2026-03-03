// Я знаю, что дальше только сложнее ;(
// Здесь мы будем анализировать бета числа
// бета числа b_ik - это нечётные центральные числа.
#include <vector>
#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

bool delete_even = false;

// Зачем инициализировать 2 стороны, если можно работать с одной?
vector<double> half_init(float r)
{
    vector<double> layer;
    int N = (int)r / 2 + ((int)r % 2);
    double i = 0.0;
    for (i; i < N + 1; i++)
    {
        layer.push_back(pow(i, r));
    }
    return layer;
}

vector<double> make_iceberg(vector<double> layer)
{
    if (layer.size() <= 1)
        return {layer[0]}; // ничего не меняем

    // Идём с конца, чтобы не потерять значения
    for (int i = layer.size() - 1; i > 0; --i)
    {
        layer[i] = layer[i] - layer[i - 1];
    }
    if (delete_even)
    {
        layer.erase(layer.begin());
        layer.insert(layer.begin(), 0);
        delete_even = false;
    }
    else
    {
        layer.erase(layer.begin());
        delete_even = true;
    }
    return layer;
}

void print_vector(vector<double> input)
{
    for (double x : input)
        std::cout << std::fixed << std::setprecision(0) << x << " ";
    cout << endl;
}

void print_iceberg(int r)
{
    vector<double> spisok = half_init(r);

    print_vector(spisok);
    for (int i = 0; i < r; i++)
    {
        spisok = make_iceberg(spisok);
        print_vector(spisok);
    }
    cout << endl;
}

vector<double> get_centers(int r)
{
    vector<double> centers;
    vector<double> spisok = half_init(r);
    centers.push_back(spisok.front());
    for (int i = 0; i < r; i++)
    {
        spisok = make_iceberg(spisok);
        centers.push_back(spisok.front());
    }
    return centers;
}

vector<double> get_betas(int r)
{
    vector<double> centers;
    vector<double> spisok = half_init(r);
    for (int i = 0; i < r; i++)
    {
        spisok = make_iceberg(spisok);
        if (spisok.front())
            centers.push_back(spisok.front());
    }
    return centers;
}

int main()
{
    vector<double> centers;
    for (int i = 0; i < 21; i++)
    {
        i++;
        delete_even = false;
        centers = get_betas(i);
        print_vector(centers);
    }
    return 0;
}