#include <iostream>

using namespace std;

template <typename T>
T somma_array(T array[], int dim)
{
    T somma{};
    for (int i = 0; i < dim; i++)
    {
        somma += array[i];
    }
    return somma;
}

template <>
string somma_array<string>(string array[], int dim)
{
    string somma = "";
    for (int i = 0; i < dim; i++)
    {
        if (array[i].length() > 3)
        {
            somma+=array[i];
        }
    }
    return somma;
}

int main()
{
}