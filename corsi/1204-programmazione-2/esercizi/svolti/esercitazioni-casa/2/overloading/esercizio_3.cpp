/* Esercizio 3 (avanzato): Crea una classe Matrice2x2 che rappresenta una matrice 2x2 di double. Implementa operator+, operator* (prodotto matriciale), operator== e operator<<. Per il prodotto matriciale ricorda: */
#include <iostream>

using namespace std;

class Matrice
{
private:
    double **matrix;

public:
    Matrice() : matrix(new double *[2])
    {
        for (int i = 0; i < 2; i++)
        {
            this->matrix[i] = new double[2];
        }
    }
    ~Matrice()
    {
        for (int i = 0; i < 2; i++)
        {
            delete[] matrix[i];
        }
        delete[] this->matrix;
    }

    // costruttore di copia
    Matrice(const Matrice& altro) : matrix(new double*[2]) {
    for (int i = 0; i < 2; i++) {
        matrix[i] = new double[2];
        for (int j = 0; j < 2; j++)
            matrix[i][j] = altro.matrix[i][j];
    }
}

    // setter
    void set_matrix(const double **matrix)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                this->matrix[i][j] = matrix[i][j];
            }
        }
    }
    void set_val_matrix(int r, int c, const double val) { matrix[r][c] = val; }

    // getter
    const double **get_matrix() const
    {
        return this->matrix;
    }
    const double get_val_matrix(int r, int c) const { return matrix[r][c]; }

    Matrice &operator=(const Matrice &altro)
    {
        if (this == &altro)
            return *this;

        // libera memoria attuale
        for (int i = 0; i < 2; i++)
            delete[] matrix[i];
        delete[] matrix;

        // alloca e copia
        matrix = new double *[2];
        for (int i = 0; i < 2; i++)
        {
            matrix[i] = new double[2];
            for (int j = 0; j < 2; j++)
                matrix[i][j] = altro.matrix[i][j];
        }
        return *this;
    }

    Matrice operator+(const Matrice &altro) const
    {
        Matrice risultato;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                risultato.matrix[i][j] = matrix[i][j] + altro.matrix[i][j];
        return risultato;
    }

    Matrice operator*(const Matrice &altro) const
    {
        Matrice risultato;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
            {
                risultato.matrix[i][j] = 0;
                for (int k = 0; k < 2; k++)
                    risultato.matrix[i][j] += matrix[i][k] * altro.matrix[k][j];
            }
        return risultato;
    }

    bool operator==(const Matrice &altro) const
    {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (matrix[i][j] != altro.matrix[i][j])
                    return false;
        return true;
    }

    friend ostream &operator<<(ostream &os, const Matrice &m);
};

ostream &operator<<(ostream &os, const Matrice &m)
{
    for (int i = 0; i < 2; i++)
    {
        os << "| ";
        for (int j = 0; j < 2; j++)
            os << m.matrix[i][j] << " ";
        os << "|" << endl;
    }
    return os;
}

int main()
{
    Matrice A, B;

    // inizializza A
    A.set_val_matrix(0, 0, 1);
    A.set_val_matrix(0, 1, 2);
    A.set_val_matrix(1, 0, 3);
    A.set_val_matrix(1, 1, 4);

    // inizializza B
    B.set_val_matrix(0, 0, 5);
    B.set_val_matrix(0, 1, 6);
    B.set_val_matrix(1, 0, 7);
    B.set_val_matrix(1, 1, 8);

    cout << "A:" << endl
         << A;
    cout << "B:" << endl
         << B;
    cout << "A+B:" << endl
         << (A + B);
    cout << "A*B:" << endl
         << (A * B);
    cout << "B*A:" << endl
         << (B * A);
    cout << "(A*B)==(B*A): " << ((A * B) == (B * A)) << endl; // atteso: 0
}