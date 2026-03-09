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
// ____Добавлено вычисление делителей____
// 5. Рассмотрим пример print_betas(25, 3, true) с выводом делителей
// r = 5; n = 3; 120
// 2 3 4
// r = 7; n = 3; 1680
// 2 3 4 5
// r = 9; n = 3; 17640
// 2 3 4 5 7
// r = 11; n = 3; 168960
// 2 3 4 5 8 -11-
// r = 13; n = 3; 1561560
// 2 3 4 5 7 -11- -13-
// r = 15; n = 3; 14217840
// 2 3 4 5 6 7 -13-
// r = 17; n = 3; 128615880
// 2 3 4 5 -17- 67
// r = 19; n = 3; 1160164320
// 2 3 4 5 7 -17- -19-
// r = 21; n = 3; 10451964600
// 2 3 4 5 7 9 11 15 -19- 21
// r = 23; n = 3; 94109624400
// 2 3 4 5 10 11 -23- 107
// r = 25; n = 3; 847154391720
// 2 3 4 5 7 13 -23-
// Сразу, что можно заметить - это "начальные делители" (2,3,4) - они есть везде.
// делитель 5 также есть в начальных, кроме самого малого значения (120)
// 6. Увеличивающиеся дополнительные делители
// Если посмотреть на остальные делители, то можно заметить, как они появляются в порядке возрастания
// Для удобства, выделю их дефисами.
// Но! если посмотреть на r = 27 мы увидим прерывание закономерности
// b_3 = 3^27 - 4*(2^27 - 2) - 3 = 7 625 060 614 080
// С делителями [2 3 4 5 6 7 13 14 1637]

#include <vector>
#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

bool add_zero = false;

// Зачем инициализировать 2 стороны, если можно работать с одной?
vector<long long int> half_init(float r)
{
    vector<long long int> layer;
    int N = (int)r / 2 + ((int)r % 2);
    long long int i = 0.0;
    for (i; i < N + 4; i++)
    {
        layer.push_back(pow(i, r));
    }
    return layer;
}

vector<long long int> make_iceberg(vector<long long int> layer)
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

void print_vector(vector<long long int> input)
{
    for (long long int x : input)
        std::cout << x << " ";
    cout << endl;
}

void print_iceberg(int r)
{
    vector<long long int> spisok = half_init(r);
    add_zero = false;
    print_vector(spisok);
    for (int j = 0; j < r; j++)
    {
        spisok = make_iceberg(spisok);
        print_vector(spisok);
    }
    cout << endl;
}

vector<long long int> get_centers(int r)
{
    add_zero = false;
    vector<long long int> centers;
    vector<long long int> spisok = half_init(r);
    centers.push_back(spisok.front());
    for (int i = 0; i < r; i++)
    {
        spisok = make_iceberg(spisok);
        centers.push_back(spisok.front());
    }
    return centers;
}

// Я писал этот код час назад, но уже ничего не понимаю =(
vector<long long int> get_betas(int r, int top = 999)
{
    vector<long long int> centers;
    vector<long long int> spisok = half_init(r);
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

long long int get_beta(int r, int top)
{

    vector<long long int> v = get_betas(r, top - 1);
    // print_vector(v);
    return v.at(top - 1);
}

vector<long long int> get_dividers(long long int beta)
{
    vector<long long int> dividers;
    for (int i = 2; i < sqrt(beta) + 1; i++)
    {
        if (beta % i == 0)
        {
            dividers.push_back(i);
            beta /= i;
        }
    }
    return dividers;
}
void print_betas(int max_r, int beta_n, bool dividers = true)
{
    vector<long long int> centers;
    for (int i = 1; i < max_r + 1; i += 2)
    {
        add_zero = false;
        centers = get_betas(i, beta_n);
        // print_vector(centers);
        cout << "r = " << i << "; n = " << beta_n << "; ";
        if (centers.size() > beta_n - 1)
        {
            cout << centers.at(beta_n - 1) << endl;
            if (dividers)
            {
                print_vector(get_dividers(centers.at(beta_n - 1)));
            }
        }
        else
        {
            cout << "-" << endl;
        }
    }
}
int main()
{
    print_betas(21, 2);
    // print_vector(get_dividers(7625060614080));
    print_iceberg(5);
    vector<long long int> centers;
    centers = get_centers(5);
    for (auto n : centers)
    {
        cout << n << " ";
        print_vector(get_dividers(n));
    }
    return 0;
}
