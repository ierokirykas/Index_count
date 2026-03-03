// Я знаю, что дальше только сложнее ;(
// Здесь мы будем анализировать бета числа
// 1. бета числа b_ik - это нечётные центральные числа.
//    r = 3; n = 2; 6
//    r = 5; n = 2; 30
//    r = 7; n = 2; 126
//    r = 9; n = 2; 510
//    Бета числа справа, их "координаты" - слева
// 2. Как можно заметить, на 2 столбе их значения вычисляются по формуле (2^r - 2)
//    Это становится понятно, когда мы смотрим на "айсберг".
//    0 1       a_2
//     1    a_2-1
//      a_2-2 - это и есть beta_2 (b_2)
//    b_0 всегда равно 0, а b_1 всегда равно 1.
//    А как мы помним, a_2 - это и есть 2^r
// 3. Если продолжим смотреть дальше...
//    r = 5; n = 3; 120
//    r = 7; n = 3; 1680
//    r = 9; n = 3; 17640
//    b_3 = (3^r - 4*b_2 - 3)
//    Если быть конкретным, возьмём r = 7
//    3^7 = 2187 - 4*126 - 3 = 1680 = b_3 при r = 7
//    Получается, для каждого n есть своя формула вычисления (Которую мы рассмотрим в пятой части)
// 4. Ещё заметим, что любая a_ri, где r = i является факториалом r
//    Получается, таким нехитрым образом можно считать факториалы с помощью квадратов
//    (Что очень странно, и не факт, что эффективно)
//    Или наоборот, зная все бета числа для конкретного r, можно вычислять квадраты чисел
//    (Что имеет гораздо большее применение)
//    Формула примерно такая: k_r = $\sum\limits_{i=0}^k n_1i
#include <vector>
#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

bool add_zero = false;

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

    // Обожаю эту логику
    layer.erase(layer.begin());
    if (add_zero)
        layer.insert(layer.begin(), 0);
    add_zero = !add_zero;
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
    for (int j = 0; j < r; j++)
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

// Я писал этот код час назад, но уже ничего не понимаю =(
vector<double> get_betas(int r, int top = 999)
{
    vector<double> centers;
    vector<double> spisok = half_init(r);
    for (int i = 0; i < r; i++)
    {
        // cout << "||| i =" << i << "; top = " << top << ";\n";
        if (i > top)
            return centers;
        spisok = make_iceberg(spisok);
        // print_vector(spisok);
        if (spisok.front())
        {
            // cout << "--" << spisok.front() << endl;
            centers.push_back(spisok.front());
        }
        else
        {
            i--;
            r--;
        }
    }
    return centers;
}

void print_betas(int max_r, int beta_n)
{
    vector<double> centers;
    for (int i = 1; i < max_r + 1; i += 2)
    {
        add_zero = false;
        centers = get_betas(i, beta_n);
        // print_vector(centers);
        cout << "r = " << i << "; n = " << beta_n << "; ";
        if (centers.size() > beta_n - 1)
            cout << centers.at(beta_n - 1) << endl;
        else
        {
            cout << "-" << endl;
        }
    }
}
int main()
{
    print_betas(11, 2);
    return 0;
}