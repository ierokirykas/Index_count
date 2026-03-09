// Итого: Мы можем высчитывать степени чисел с помощью сумм, а не множителей.
// На высоких степенях или числах это будет неэффективно
// Но для r <= 5 можно найти применение
// Для r = 2 можно увидеть, что наша функция "Уделывает" cmath pow на значениях n вплоть до 11;
// r = 2; n = 4;
// Pure addition - Time: 0.8491 ms
// With multiplication - Time: 0.6607 ms
// cmath pow - Time: 1.9599 ms
// ______________
// r = 2; n = 11;
// Pure addition - Time: 11.0702 ms
// With multiplication - Time: 1.6755 ms
// cmath pow - Time: 1.7991 ms
// ______________
// Для r = 3 нужны ещё меньше числа для преимущества
// r = 3; n = 5;
// Pure addition - Time: 5.3638 ms
// With multiplication - Time: 2.7256 ms
// cmath pow - Time: 3.0888 ms
// _________________________
// r = 3; n = 100;
// Pure addition - Time: 28791 ms
// With multiplication - Time: 1186.51 ms
// cmath pow - Time: 1.9847 ms
// Как мы видим, большой проблемой является то, что сумма у нас производится в виде цикла.
// Поэтому при больших значениях n добавление начинает забирать время, а не добавлять его
// по bigO у нашего цикла O(n^r) сложность для pure addition и O(n^(r-1)) для multiplicative версии (Можно ли сделать O(1) версию?)
// У pow функции же сложность O(log(n)), что даёт гораздо большую эффективность при больших n...
#include <locale.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <chrono>
using namespace std;
int sum_power(int n, int r, bool mult = false)
{
    int result = 0;
    switch (r)
    {
    case 0:
        return 1;
    case 1:
        return n;
    case 2:
        if (mult)
        {
            result++;
            for (int i = 1; i < n; i++)
            {
                result += 2 * i;
                result++;
            }
            return result;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                result++;
                // cout << result << endl;
                for (int a = 1; a < i; a++)
                    result += 2;
            }
            return result;
            break;
        }
    case 3:
        if (mult)
        {
            for (int i = 1; i <= n; i++)
            {
                result++;
                // cout << result << endl;
                for (int a = 1; a < i; a++)
                    result += 6 * a;
            }
            return result;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                result++;
                // cout << result << endl;
                for (int a = 1; a < i; a++)
                    for (int b = 1; b <= a; b++)
                        result += 6;
            }
            return result;
        }
    default:
        cout << "Использую базовую настройку." << endl;
        return pow(n, r);
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int r = 3;
    int n = 100;
    cout << "r = " << r << "; n = " << n << "; \n";
    // cout << sum_power(n, r);
    // return 1;

    // 1. Получаем текущее время перед выполнением
    cout
        << "Pure addition - ";
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++)
        sum_power(n, r);
    // 3. Получаем время после выполнения
    auto end = std::chrono::high_resolution_clock::now();
    // 4. Вычисляем разницу
    std::chrono::duration<double> duration = end - start;
    // 5. Выводим результат
    std::cout << "Time: " << duration.count() * 1000 << " ms" << std::endl;

    cout << "With multiplication - ";
    // 1. Получаем текущее время перед выполнением
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++)
        sum_power(n, r, true);
    // 3. Получаем время после выполнения
    end = std::chrono::high_resolution_clock::now();
    // 4. Вычисляем разницу
    duration = end - start;
    // 5. Выводим результат
    std::cout << "Time: " << duration.count() * 1000 << " ms" << std::endl;

    // 1. Получаем текущее время перед выполнением
    cout << "cmath pow - ";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++)
        pow(n, r);
    // 3. Получаем время после выполнения
    end = std::chrono::high_resolution_clock::now();
    // 4. Вычисляем разницу
    duration = end - start;
    // 5. Выводим результат
    std::cout << "Time: " << duration.count() * 1000 << " ms" << std::endl;
}