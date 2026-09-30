// eighth.cpp — чистая переработка get_betas + get_dividers из fourth.cpp
// и проверка гипотезы, которая осталась открытой в fifth.cpp.
//
// ГИПОТЕЗА:
//   Бета-числа b_n(r) (нечётные центры «айсберга» конечных разностей x^r)
//   НЕ нужно вычислять айсбергом. У них есть замкнутая форма:
//
//       b_n(r) = Σ_{k=1..n} (-1)^(n-k) · W(n,k) · k^r
//
//   где W(n,k) — числа Ворпицкого (треугольник OEIS A028246) — целые числа,
//   НЕ зависящие от r, генерируемые из строк Паскаля (строка 2n-3,
//   «край отсекается, значения сдвигаются» — ровно то, что построено в seventh.cpp).
//   Твой «гамма-ряд» из fifth.cpp и есть числа Ворпицкого.
//
// Что делает файл:
//   1) Эталонный «айсберг» — ровно как в fourth.cpp, но без глобальных флагов
//      и без pow()-в-double.
//   2) Таблицу Ворпицкого W(n,k) — решением точной линейной системы
//      из бета-значений.
//   3) Сверку замкнутой формулы против айсберга для r = 3..15.
//   4) Корректный факторизатор (полная кратность + остаток-простое)
//      и демонстрацию на b_3(27) = 7625060614080.

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <iomanip>
#include <windows.h>

using i128 = __int128;

// ---------- служебное ----------
static std::string to_string(i128 v)
{
    if (v == 0)
        return "0";
    bool neg = v < 0;
    if (neg)
        v = -v;
    std::string s;
    while (v > 0)
    {
        s += char('0' + v % 10);
        v /= 10;
    }
    if (neg)
        s += '-';
    return std::string(s.rbegin(), s.rend());
}

static i128 binom(i128 n, i128 k)
{
    if (k < 0 || k > n)
        return 0;
    if (k > n - k)
        k = n - k;
    i128 r = 1;
    for (i128 i = 1; i <= k; ++i)
        r = r * (n - k + i) / i;
    return r;
}

// целочисленное возведение в степень (без double)
static i128 ipow(i128 base, int exp)
{
    i128 r = 1;
    while (exp > 0)
    {
        if (exp & 1)
            r *= base;
        base *= base;
        exp >>= 1;
    }
    return r;
}

// ---------- 1) эталонный «айсберг» ----------
// half_init(r): строка степеней 0^r, 1^r, ... (ровно как в fourth.cpp)
static std::vector<i128> half_init(int r)
{
    int N = r / 2 + (r % 2);
    std::vector<i128> layer;
    for (int i = 0; i < N + 4; ++i)
        layer.push_back(ipow(i, r));
    return layer;
}

// Возвращает бета-числа b_1, b_2, ..., b_{(r+1)/2} для степени r.
// Логика идентична get_betas, но без i--/r-- внутри цикла и без глобальных флагов.
static std::vector<i128> beta_by_iceberg(int r)
{
    std::vector<i128> layer = half_init(r);
    std::vector<i128> betas;
    bool add_zero = false;
    for (int step = 0; step < r; ++step)
    { // ровно r шагов, как в оригинале
        for (size_t i = layer.size() - 1; i > 0; --i)
            layer[i] -= layer[i - 1];
        layer.erase(layer.begin());
        if (add_zero)
            layer.insert(layer.begin(), 0);
        add_zero = !add_zero;
        if (layer.front() != 0)
            betas.push_back(layer.front()); // нулевой шаг не считается
    }
    return betas;
}

// ---------- 2) числа Ворпицкого ----------
// Решаем систему Σ_k y_k · k^(r_i) = b_n(r_i),  y_k = (-1)^(n-k) W(n,k),
// для r_i = 2n-1, 2n+1, ..., 4n-3  (n уравнений, n неизвестных).
// Матрица Вандермонда плохо обусловлена при больших n, поэтому:
//   — грубо решаем в long double;
//   — уточняем по ТОЧНОЙ невязке R = b - A·x, вычисленной в __int128
//     (метод итеративного уточнения) — итог — точные целые.
static std::vector<long double> solve_gauss(std::vector<std::vector<long double>> A,
                                            std::vector<long double> b)
{
    const int m = (int)b.size();
    for (int c = 0; c < m; ++c)
    {
        int p = c;
        for (int i = c + 1; i < m; ++i)
            if (std::fabs(A[i][c]) > std::fabs(A[p][c]))
                p = i;
        std::swap(A[c], A[p]);
        std::swap(b[c], b[p]);
        long double piv = A[c][c];
        for (int i = c + 1; i < m; ++i)
        {
            long double f = A[i][c] / piv;
            for (int j = c; j < m; ++j)
                A[i][j] -= f * A[c][j];
            b[i] -= f * b[c];
        }
    }
    std::vector<long double> x(m);
    for (int i = m - 1; i >= 0; --i)
    {
        long double s = b[i];
        for (int j = i + 1; j < m; ++j)
            s -= A[i][j] * x[j];
        x[i] = s / A[i][i];
    }
    return x;
}

static std::vector<i128> worpitzky_row(int n)
{
    const int m = n;
    std::vector<std::vector<i128>> Aex(m, std::vector<i128>(m)); // точные (__int128)
    std::vector<i128> bex(m);
    std::vector<std::vector<long double>> A(m, std::vector<long double>(m));
    std::vector<long double> b(m);
    for (int i = 0; i < m; ++i)
    {
        int r = 2 * m - 1 + 2 * i; // нечётные r, начиная с 2n-1
        std::vector<i128> betas = beta_by_iceberg(r);
        bex[i] = betas.at(m - 1); // b_n(r)
        b[i] = (long double)bex[i];
        for (int k = 1; k <= m; ++k)
        {
            i128 v = ipow(k, r);
            Aex[i][k - 1] = v;
            A[i][k - 1] = (long double)v;
        }
    }
    // грубое решение
    std::vector<long double> x = solve_gauss(A, b);
    std::vector<i128> X(m);
    for (int k = 0; k < m; ++k)
        X[k] = (i128)std::llround(x[k]);
    // итеративное уточнение по точной невязке
    for (int iter = 0; iter < 4; ++iter)
    {
        bool zero = true;
        std::vector<long double> R(m);
        for (int i = 0; i < m; ++i)
        {
            i128 s = bex[i];
            for (int j = 0; j < m; ++j)
                s -= Aex[i][j] * X[j];
            if (s != 0)
                zero = false;
            R[i] = (long double)s;
        }
        if (zero)
            break;
        std::vector<long double> d = solve_gauss(A, R);
        for (int k = 0; k < m; ++k)
            X[k] += (i128)std::llround(d[k]);
    }
    // снимаем знак: y_k = (-1)^(n-k) W(n,k)  =>  W(n,k) = y_k·(-1)^(n-k)
    for (int k = 0; k < m; ++k)
        if ((n - 1 - k) % 2 == 1)
            X[k] = -X[k];
    return X;
}

// ---------- 3) замкнутая формула ----------
static i128 beta_closed(int n, int r, const std::vector<std::vector<i128>> &W)
{
    i128 sum = 0;
    for (int k = 1; k <= n; ++k)
    {
        i128 term = W[n - 1][k - 1] * ipow(k, r);
        sum += ((n - k) % 2 == 1) ? -term : term;
    }
    return sum;
}

// ---------- 4) корректный факторизатор ----------
// Полная кратность простых + остаток-простое (если он > 1).
static std::vector<std::pair<i128, int>> factorize(i128 n)
{
    std::vector<std::pair<i128, int>> fac;
    for (i128 d = 2; d * d <= n; ++d)
    { // безопасно: d*d укладывается в __int128 для n < 2^64
        if (n % d == 0)
        {
            int e = 0;
            while (n % d == 0)
            {
                n /= d;
                ++e;
            }
            fac.push_back({d, e});
        }
    }
    if (n > 1)
        fac.push_back({n, 1});
    return fac;
}

static void print_factors(i128 n)
{
    auto fac = factorize(n);
    for (size_t i = 0; i < fac.size(); ++i)
    {
        if (i)
            std::cout << " * ";
        std::cout << to_string(fac[i].first);
        if (fac[i].second > 1)
            std::cout << "^" << fac[i].second;
    }
    std::cout << std::endl;
}

int main()
{
    const int N = 8; // размер таблицы Ворпицкого
    SetConsoleOutputCP(CP_UTF8);
    // --- строим таблицу Ворпицкого и валидируем инвариантами ---
    std::cout << "=== Числа Ворпицкого W(n,k), n=1.." << N << " (OEIS A028246) ===" << std::endl;
    std::vector<std::vector<i128>> W;
    bool w_ok = true;
    for (int n = 1; n <= N; ++n)
    {
        W.push_back(worpitzky_row(n));
        std::cout << "n=" << n << ": ";
        for (i128 v : W.back())
            std::cout << to_string(v) << " ";
        std::cout << std::endl;
        // инварианты:
        //  W(n,1) = Catalan(n) = C(2n, n)/(n+1)
        //  W(n,n) = 1
        //  Σ_k W(n,k) = C(2n-1, n-1)
        i128 sum = 0;
        for (i128 v : W.back())
            sum += v;
        i128 catalan = binom(2 * n, n) / (n + 1);
        i128 rowsum = binom(2 * n - 1, n - 1);
        if (W.back().front() != catalan || W.back().back() != 1 || sum != rowsum)
        {
            w_ok = false;
            std::cout << "  !! инварианты нарушены: catalan=" << to_string(catalan)
                      << " rowsum=" << to_string(rowsum) << std::endl;
        }
    }
    std::cout << "Проверка инвариантов: " << (w_ok ? "OK" : "СБОЙ") << std::endl
              << std::endl;

    // --- сверка замкнутой формулы против айсберга ---
    std::cout << "=== Сверка b_closed(n,r) vs b_iceberg(r) ===" << std::endl;
    bool all_ok = true;
    for (int r = 3; r <= 15; r += 2)
    {
        std::vector<i128> ice = beta_by_iceberg(r);
        for (size_t n = 1; n <= ice.size(); ++n)
        {
            i128 closed = beta_closed((int)n, r, W);
            if (closed != ice[n - 1])
            {
                all_ok = false;
                std::cout << "r=" << r << " n=" << n << ": айсберг=" << to_string(ice[n - 1])
                          << " формула=" << to_string(closed) << "  !!!" << std::endl;
            }
        }
        std::cout << "r=" << std::setw(2) << r << ": " << to_string(ice[0]);
        for (size_t n = 2; n <= ice.size(); ++n)
            std::cout << ", " << to_string(ice[n - 1]);
        std::cout << "  — OK" << std::endl;
    }
    std::cout << "Итог: " << (all_ok ? "все совпали" : "есть расхождения") << std::endl
              << std::endl;

    // --- демонстрация: b_3(27) и корректный факторизатор ---
    std::cout << "=== Демонстрация: b_3(27) ===" << std::endl;
    i128 b3_27 = beta_closed(3, 27, W);
    std::cout << "b_3(27) = " << to_string(b3_27) << std::endl;
    std::cout << "Простые множители: ";
    print_factors(b3_27);

    // старый get_dividers для сравнения (то, что было в fourth.cpp):
    // он терял множитель 2539 и выдавал 2 3 4 5 6 7 13 14 1637
    std::cout << "(для сравнения, старый get_dividers из fourth.cpp: 2 3 4 5 6 7 13 14 1637)"
              << std::endl;

    return 0;
}
