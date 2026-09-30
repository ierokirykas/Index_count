#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;
using Matrix = vector<vector<int>>;
Matrix getPascalTriangle(int numRows)
{
    Matrix triangle;
    for (int i = 0; i < numRows; i++)
    {
        vector<int> row(i + 1, 1);
        // Вычисляем значения для элементов внутри строки (не считая краевых единиц)
        for (int j = 1; j < i; ++j)
        {
            // Каждый элемент равен сумме двух элементов над ним из предыдущей строки
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
        // Добавляем готовую строку в наш треугольник
        triangle.push_back(row);
    }
    return triangle;
}
// 2. Функция вывода
void printMatrix(const Matrix &M)
{
    int numRows = M.size();

    for (int i = 0; i < numRows; ++i)
    {
        // Вычисляем отступы слева для центрирования (по 3 пробела на "уровень")
        cout << string((numRows - i - 1) * 3, ' ');

        // Выводим элементы текущей строки с выравниванием по 6 символов
        for (int val : M[i])
        {
            cout << setw(6) << val;
        }
        cout << endl;
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int rows;
    cout << "Введите количество строк треугольника Паскаля: ";
    cin >> rows;

    if (rows <= 0)
    {
        cout << "Ошибка: количество строк должно быть больше нуля!" << endl;
        return 1;
    }
    Matrix triangle = getPascalTriangle(rows);
    printMatrix(triangle);
    return 0;
}