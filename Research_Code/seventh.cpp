// Последнее, что нам было нужно
// Здесь мы видим явную последовательность, которая похожа на треугольник паскаля
// С отличием в конце. Часть края "отсекается", поэтому значения также "сдвигаются"

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// Функция вывода вектора (числа или кортежа)
void printVector(const vector<int> &v)
{
    if (v.empty())
        return;
    // Если все элементы нули — выводим просто 0
    bool allZero = true;
    for (int x : v)
        if (x != 0)
        {
            allZero = false;
            break;
        }
    if (allZero)
    {
        cout << "0";
        return;
    }
    // Иначе выводим в скобках через запятую
    cout << "(";
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i > 0)
            cout << ",";
        cout << v[i];
    }
    cout << ")";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int N;
    cout << "Введите N (индекс лестницы): ";
    cin >> N;

    // Храним все лестницы: stairs[i] — для индекса i+1
    vector<vector<vector<int>>> stairs;

    // База: лестница для n=1 (числа: 1, 1, 0)
    stairs.push_back({{1}, {1}, {0}});

    // Построение для n = 2..N
    for (int n = 2; n <= N; ++n)
    {
        const auto &prev = stairs.back(); // лестница для n-1
        vector<vector<int>> curr;

        // Первый вектор: (0,0,...,0,1)
        vector<int> first(n, 0);
        first.back() = 1;
        curr.push_back(first);

        // Последовательное вычитание элементов предыдущей лестницы
        for (const auto &v : prev)
        {
            // Дополняем v нулём справа до длины n
            vector<int> v_ext = v;
            v_ext.push_back(0);
            // Вычитаем v_ext из последнего добавленного вектора
            vector<int> new_vec = curr.back();
            for (int i = 0; i < n; ++i)
            {
                new_vec[i] -= v_ext[i];
            }
            curr.push_back(new_vec);
        }

        // Добавляем завершающий нулевой вектор
        curr.push_back(vector<int>(n, 0));
        stairs.push_back(curr);
    }

    // Вывод всех лестниц от 1 до N
    for (int i = 0; i < N; ++i)
    {
        if (i == 0)
        {
            // Для первой лестницы выводим начальный 0
            cout << "0 -> " << endl;
        }
        else
        {
            cout << " -> " << endl;
        }

        const auto &ladder = stairs[i];
        for (size_t j = 0; j < ladder.size(); ++j)
        {
            if (j > 0)
                cout << " ";
            printVector(ladder[j]);
        }
    }
    cout << endl;

    return 0;
}
