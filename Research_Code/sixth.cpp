#include <vector>
#include <iostream>
using namespace std;
using Matrix = vector<vector<int>>;

int N = 5;
void print_vector(vector<int> input)
{
    for (int x = 0; x < input.size(); x++)
        std::cout << input[x] << " ";
    cout << "|| ";
}

vector<int> gamma_gen(int N)
{
    Matrix M(1);
    vector<int> last(1);
    vector<int> first(1);
    for (int i = 0; i < N; i++)
    {
        // Инициализируем первую ступеньку
        if (i == 1)
            first[0] = 1;
        else if (i)
        {
            first.push_back(1);
            // cout << "hi";
        }
        else
            last[0] = 0;
        // Идём вверх по лестнице
        // if (last.size() == 1 and last[0] == 0)
        //     M[i] = last;
        // else
        // {
        //     for (int s = 0; s < M.size(); s++)
        //     {
        //         vector<int> X = M[s];
        //         last = first;
        //         for (int j = 0; j < X.size(); j++)
        //             first[j] -= X[j];
        //         M[s] = last;
        //     }
        // }

        // for (vector<int> X : M)
        //     print_vector(X);
        last = first;
        print_vector(last);
        cout << endl;
        first.assign(first.size(), 0);
    }
    return last;
}
int main()
{
    gamma_gen(4);
    return 0;
}