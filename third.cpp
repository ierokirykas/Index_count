// Чем дальше тем интереснее... и сложнее
// Для начала, рассмотрим r == 4
// 16  1  0 1  16
//  -15  -1 1  15
//     14  2  14
//      -12 12
//        24
// С центром в виде: 0 1 2 12 24
// И также r == 5
// -32  -1 0 1   32   243
//    31  1 1  31   211
//    -30  0  30  180 // Пхех, кажется я научился строить ровные айсберги
//       30 30  150
//         0  120
//         120
// С центром в виде: 0 1 0 30 0 120
// Здесь можно заметить сразу несколько особенностей:
// 0. Из прошлого файла мы помним, что низ айсберга (последняя строка) равен факториалу r;  a_r = r!
// 1. При чётном r, чётные номера чисел в центре
//    равняются удвоенному значению предыдущего номера;  a_i = a_(i-1)*2 if r%2==0 and i%2==0
// 2. При нечётном r, чётные номера чисел в центре
//    равняются нулю; a_i = 0 if r%2==1 and i%2==0
// 2.2 Из пунктов 1 и 2 можно составить общую формулу;
//          a_i = (i%2==0) ? (r%2==0 ? a_(i-1)*2 : 0) : (any_other)

#include "second.cpp"

int r = 5;                       // Степень
bool print_only_centers = false; // Показывать только центры

vector<double> improved_init(float r)
{
    int N = (int)r / 2 + ((int)r % 2);
    vector<double> layer;
    double i = 0.0 - N;
    for (i; i < N + 1; i++)
    {
        layer.push_back(pow(i, r));
    }
    if ((int)r % 2)
        layer.erase(layer.begin());
    return layer;
}

vector<double> improved_next_layer(vector<double> layer)
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

void improved_print(vector<double> input, bool center_only = false)
{
    // Ищем центр
    auto getCenter = [](vector<double> &v) -> double
    {
        // Отношения с логикой: Всё сложно
        return v.at(v.size() / 2 - (v.size() % 2 == 0) + (v.size() % 2 == 0 and r % 2 == 0));
    };

    if (center_only)
    {
        cout << getCenter(input) << endl;
    }
    else
    {
        for (double x : input)
            std::cout << x << " ";

        cout << '\t' << getCenter(input) << endl;
    }
}

int main()
{

    int i;
    vector<double> spisok = improved_init(r);
    improved_print(spisok, print_only_centers);
    for (i = 0; i < r; i++)
    {
        spisok = improved_next_layer(spisok);
        improved_print(spisok, print_only_centers);
    }
    return 0;
};