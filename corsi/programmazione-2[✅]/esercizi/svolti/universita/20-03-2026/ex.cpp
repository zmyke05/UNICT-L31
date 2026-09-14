#include <iostream>

using namespace std;

class Veicolo
{
private:	
	string marca;
	string modello;
	int anno;
public:
	Veicolo(const string& marca, const string& modello, const int& anno)
		: marca(marca), modello(modello), anno(anno) {}
	Veicolo() = default;
	~Veicolo() = default;

	const string& get_marca() const { return marca; }
	const string& get_modello() const { return modello; }
	const int& get_anno() const { return anno; }

	void set_marca(string& marca) { this->marca = marca; }
	void set_modello(string& modello) { this->modello = modello; }
	void set_anno(int& anno) { this->anno = anno; }

	void stampaInfo() const
	{
		cout << this->marca << " " << this->modello << " "<< this->anno;
	}
};

class Auto : public Veicolo
{
private:
	int numero_porte;
public:
	Auto(const string& marca, const string& modello, const int& anno, const int& numero_porte)
		: Veicolo(marca, modello, anno), numero_porte(numero_porte) {}
	Auto() = default;
	~Auto() = default;

	const int& get_numero_porte() const { return this->numero_porte; }
	void set_numero_porte(const int& numero_porte) { this->numero_porte = numero_porte; }
	void stampaInfo() const
	{
		Veicolo::stampaInfo();
		cout << " " << get_numero_porte();
	}
};

int main()
{
	size_t size = 2;
	

	Veicolo** veicoli = new Veicolo*[size];
	veicoli[0] = new Veicolo("Veicolo", "Modello", 0);
	veicoli[1] = new Veicolo("Veicolo1", "Modello1", 0);

	for (size_t i = 0; i < size; i++)
	{
		veicoli[i]->stampaInfo();
		cout << endl;
	}

	Auto* macchine[size];
	macchine[0] = new Auto("BMW", "Serie 3", 2025, 6);
	macchine[1] = new Auto("Pegeaut", "2008", 2017, 6);

	for (size_t i = 0; i < size; i++)
	{
		macchine[i]->stampaInfo();
		cout << endl;
	}

	for (size_t i = 0; i < size; i++)
	{
		delete veicoli[i];
		delete macchine[i];
	}
	delete veicoli;

	return 0;
}