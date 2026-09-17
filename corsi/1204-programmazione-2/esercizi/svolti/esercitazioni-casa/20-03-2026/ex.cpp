#include <iostream>
#include <typeinfo>

using namespace std;

// classe astratta
// = 0: perché questa funzione non ha implementazione, deve essere implementatata dalle classi derivate
class Printable { 
    virtual void stampaInfo() const = 0; 
};

class Veicolo : public Printable
{
private:
    // attributi
    string marca;
    string modello;
    int anno;

public:
    // costruttore -> chiama Veicolo(...)
    Veicolo(const string &marca, const string &modello, int anno) : marca(marca), modello(modello), anno(anno) {}
    // string &marca perché cosí evito copie inutili ed é piú efficiente e puó riferirsi SOLO a variabili esistenti (iValues)
    // differerenza tra Ivalues e Rvalues
    // - Ivalues -> ha un nome e una posizione in memoria stabile come "string s = 'BMW'"
    // - Rvalues -> é temporaneo e non ha un nome stabile come "BMW"
    Veicolo() = default;  // costruttore vuoto automatico
    ~Veicolo() = default; // distruttore

    // getter/setter
    // get()
    // const string &get() -> ritorna un riferimento non una copia
    // const finale -> NON modifica l'oggetto
    const string &getMarca() const
    {
        return this->marca;
    }

    const string &getModello() const
    {
        return this->modello;
    }

    const int &getAnno() const
    {
        return this->anno;
    }

    // set()
    void setMarca(const string &marca)
    {
        this->marca = marca;
    }

    void setModello(const string &modello)
    {
        this->modello = modello;
    }

    void setAnno(const int &anno)
    {
        this->anno = anno;
    }

    // virtual stampaInfo()
    // virtual -> dico "questo comporamento puó cambiare in base al tipo reale dell'oggetto"
    virtual void stampaInfo() const
    {
        cout << this->marca << " " << this->modello << " " << this->anno;
    }
};

class Auto : public Veicolo
{

private:
    // attributi
    int numero_porte;

public:
    // costrutture
    Auto(const string &marca, const string &modello, int anno, const int &numero_porte) : Veicolo(marca, modello, anno), numero_porte(numero_porte) {}
    Auto() = default;
    ~Auto() = default;

    // getter/setter
    const int &getNumeroPorte()
    {
        return this->numero_porte;
    }

    void setNumeroPorte(const int &numero_porte)
    {
        this->numero_porte = numero_porte;
    }

    // stampaInfo()
    void stampaInfo() const override
    {
        Veicolo::stampaInfo();
        cout << " Numero Porte:" << this->numero_porte;
    }
};

class Camion : public Veicolo
{

private:
    // attributi
    int capacitaCarico;

public:
    // costrutture
    Camion(const string &marca, const string &modello, int anno, const int &capacitaCarico) : Veicolo(marca, modello, anno), capacitaCarico(capacitaCarico) {}
    Camion() = default;
    ~Camion() = default;

    // getter/setter
    const int &getCapacitaCarico()
    {
        return this->capacitaCarico;
    }

    void setCapacitaCarico(const int &capacitaCarico)
    {
        this->capacitaCarico = capacitaCarico;
    }

    // stampaInfo()
    void stampaInfo() const override
    {
        Veicolo::stampaInfo();
        cout << " Capacita Carico:" << this->capacitaCarico;
    }
};

class Moto : public Veicolo
{

private:
    // attributi
    int cilindrata;

public:
    // costrutture
    Moto(const string &marca, const string &modello, int anno, const int &cilindrata) : Veicolo(marca, modello, anno), cilindrata(cilindrata) {}
    Moto() = default;
    ~Moto() = default;

    // getter/setter
    const int &getCilindrata()
    {
        return this->cilindrata;
    }

    void setCilindrata(const int &cilindrata)
    {
        this->cilindrata = cilindrata;
    }

    // stampaInfo()
    void stampaInfo() const override
    {
        Veicolo::stampaInfo();
        cout << " Cilindrata:" << this->cilindrata;
    }
};

class Bicicletta : public Veicolo
{

private:
    // attributi
    string tipo;

public:
    // costrutture
    Bicicletta(const string &marca, const string &modello, int anno, const string &tipo) : Veicolo(marca, modello, anno), tipo(tipo) {}
    Bicicletta() = default;
    ~Bicicletta() = default;

    // getter/setter
    const string &getTipo()
    {
        return this->tipo;
    }

    void setTipo(const string &tipo)
    {
        this->tipo = tipo;
    }

    // stampaInfo()
    void stampaInfo() const override
    {
        Veicolo::stampaInfo();
        cout << " Tipo:" << this->tipo;
    }
};

int main()
{
    const int size = 9;
    // VEICOLI
    Veicolo *veicoli[size] = {
        new Veicolo("Veicolo", "Modello", 2020),
        new Veicolo("Veicolo1", "Modello1", 2021),

        new Auto("BMW", "Serie 3", 2025, 4),
        new Auto("Peugeot", "208", 2017, 5),

        new Camion("Volvo", "FH", 2023, 12000),

        new Moto("Yamaha", "R1", 2022, 1000),
        new Moto("Ducati", "Panigale", 2021, 1100),

        new Bicicletta("Bianchi", "Oltre XR4", 2023, "Strada"),
        new Bicicletta("Trek", "Marlin", 2022, "Mountain")};

    // STAMPA
    cout << "=== TUTTI I VEICOLI ===" << endl;

    for (int i = 0; i < size; i++)
    {
        veicoli[i]->stampaInfo();
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        cout << "[" << i << "] ";

        if (typeid(*veicoli[i]) == typeid(Auto))
            cout << "Auto -> ";
        else if (typeid(*veicoli[i]) == typeid(Camion))
            cout << "Camion -> ";
        else if (typeid(*veicoli[i]) == typeid(Moto))
            cout << "Moto -> ";
        else if (typeid(*veicoli[i]) == typeid(Bicicletta))
            cout << "Bicicletta -> ";
        else
            cout << "Veicolo -> ";

        veicoli[i]->stampaInfo();
        cout << endl;
    }

    // DEALLOCAZIONE
    for (int i = 0; i < size; i++)
    {
        delete veicoli[i];
    }

    return 0;
}
