// Самое интересное начинается здесь
#include "second.cpp"

int r = 8; // Степень
// N нам не нужен, т.к. он зависит от r

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
    bool print_only_centers = true;
    vector<double> spisok = improved_init(r);
    improved_print(spisok, print_only_centers);
    for (i = 0; i < r; i++)
    {
        spisok = improved_next_layer(spisok);
        improved_print(spisok, print_only_centers);
    }
    return 0;
};