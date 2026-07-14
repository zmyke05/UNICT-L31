#include <iostream>
using namespace std;

class Errore{
    private:
        int id;

    public:
        Errore() : id(0) {}
        Errore(int i) : id(i) {}

        int get_id() const{return id;}

        virtual void print() = 0;

        virtual ~Errore() {}
};

class Warning : public Errore{
    private:

    public:
        Warning(int i) : Errore(i) {}
        void print() override{
            cout<< "Attenzione!" << get_id() << endl;
        }
};

class Runtime : public Errore{
    private:
        int time;

    public:
        Runtime() : time(0) {}
        Runtime(int i, int t) : Errore(i), time(t) {}
        
        void print() override{
            cout<< "Stop!" << get_id() << this->time;
        }
};

template <typename T> class Nodo{
    private:
        T key;
        Nodo<T>* next; 

    public:
        Nodo(const T& k) : key(k), next(nullptr) {}

        const T& get_key() const{return key;}
        Nodo<T>* get_next() const{return next;}
        
        void set_key(const T& k) {this->key = k;}
        void set_next(Nodo<T>* n) {this->next = n;}

        ~Nodo() {}
};

template <typename T> class Coda{
    private:
        Nodo<T>* testa;

    public: 
        Coda() : testa(nullptr) {}
        Coda(const T& key){
            testa = new Nodo<T>(key);
        }

        Nodo<T>* get_testa() const{return testa;}
        void set_testa(Nodo<T>* t) {this->testa = t;}

        Coda* Inserimento(const T& key){
            Nodo<T>* temp = this->get_testa();

            if(temp == nullptr){
                this->set_testa(new Nodo<T>(key));
                return this;
            }

            while(temp->get_next() != nullptr){
                temp = temp->get_next();
            }

            temp->set_next(new Nodo<T>(key));
            return this;
        }

        Coda* Cancellazione(){
            if(testa == nullptr){
                return this;
            }

            Nodo<T>* temp = this->get_testa();
            this->set_testa(temp->get_next());
            delete temp;

            return this;
        }

        void printAll(){
            if(testa == nullptr)
                return ;\
            
            Nodo<T>* temp = this->get_testa();
            while(temp != nullptr){
                temp->get_key()->print();
                cout << endl;
                temp = temp->get_next();
            }
        }

        ~Coda() {}
};

int main(){
    Coda<Errore*> coda;

    coda.Inserimento(new Warning(20));
    coda.Inserimento(new Runtime(89,145));
    coda.Inserimento(new Warning(50));

    coda.Cancellazione();
    coda.printAll();
    
}