// Самое интересное начинается здесь
#include "second.cpp"

vector<double> improved_init(float r)
{
    vector<double> layer;
    double i = 0.0 - r;
    for (i; i < (r + 1); i++)
    {
        layer.push_back(pow(i, r));
    }
    return layer;
}

int main()
{
    int r = 4; // Степень
    // N нам не нужен, т.к. он зависит от r
    int i;
    vector<double> spisok = improved_init(r);
    print_vector(spisok);
    for (i = 0; i < r; i++)
    {
        spisok = next_layer(spisok);
        print_vector(spisok);
    }
    return 0;
};