/* Esercizio 2 (avanzato): Crea una classe Stringa che gestisce una stringa come array di char allocato dinamicamente (senza usare std::string internamente). Implementa la Regola del Tre completa. Aggiungi un metodo lunghezza() e un metodo stampa(). Testala con copia e assegnazione. */
#include <iostream>
#include <string.h>

using namespace std;

class Stringa
{
private:
    int len;
    char *buffer;

public:
    Stringa(const char *s = "") : len(strlen(s)), buffer(new char[len + 1])
    {
        strcpy(buffer, s);
    }

    ~Stringa()
    {
        delete[] buffer;
    }

    Stringa(const Stringa &s) : len(strlen(s.buffer)), buffer(new char[len + 1])
    {
        strcpy(buffer, s.buffer);
    }

    Stringa &operator=(const Stringa &s)
    {
        if (this == &s)
        {
            return *this;
        }

        delete[] buffer;

        len = strlen(s.buffer);
        buffer = new char[len + 1];
        strcpy(buffer, s.buffer);

        return *this;
    }

    int lunghezza() const { return len; }
    void stampa() const { cout << buffer << endl; }
};

int main()
{
    std::cout << "--- Inizio Test ---\n";

    Stringa s1("Catania"); // Costruttore standard
    Stringa s2 = s1;       // Costruttore di copia (Deep Copy)

    Stringa s3("Informatica");
    s3 = s1; // Operatore di assegnamento

    std::cout << "\nContenuto s3: ";
    s3.stampa();
    std::cout << "Lunghezza s3: " << s3.lunghezza() << "\n\n";

    std::cout << "--- Fine Test (entrano in gioco i distruttori) ---\n";
    return 0;
}
