/* Esercizio 1 (base): Crea una classe Contatore con un attributo static num_istanze che tiene traccia di quanti oggetti esistono in memoria in un dato momento. Il costruttore incrementa il contatore, il distruttore lo decrementa. Aggiungi un metodo static get_num_istanze(). Testalo nel main creando oggetti sia nello stack che con new/delete, verificando che il contatore sia sempre corretto. */
#include <iostream>

using namespace std;

class Contatore
{
    private:
        static int num_instanze;
    
    public:
        Contatore() { num_instanze++; }
        ~Contatore() { num_instanze--; }

        static int get_num()
        {
            return num_instanze;
        }
};

int Contatore::num_instanze = 0;

int main()
{
    cout << Contatore::get_num() << endl;

    Contatore a, b, c;

    cout << Contatore::get_num() << endl;
}