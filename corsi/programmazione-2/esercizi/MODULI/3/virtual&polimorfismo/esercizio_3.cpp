/* Esercizio PRECEDENTE (avanzato): Crea una gerarchia Conto → ContoCorrente → ContoCorrente_Premium con questi requisiti:

Conto gestisce un array dinamico di double che rappresenta lo storico delle transazioni (usa la Regola del Tre completa). Ha metodi deposita(), preleva() (no saldo negativo), stampa_storico(). Ha un attributo static num_conti. Implementa operator<<.
ContoCorrente aggiunge limite_scoperto — preleva() permette saldo negativo fino al limite. Chiama Conto::preleva() se possibile, gestisce autonomamente solo il caso scoperto.
ContoCorrente_Premium aggiunge cashback_percentuale — ogni prelievo riuscito aggiunge automaticamente il cashback% dell'importo come deposito. Ridefinisce preleva() chiamando quello di ContoCorrente.

Verifica nel main:

Ordine di costruzione e distruzione
Copia tramite costruttore di copia (deep copy dello storico)
operator<< su tutti e tre i livelli
Tutti i casi limite: prelievo oltre saldo, prelievo oltre limite scoperto, cashback applicato correttamente
Il contatore static aggiornato correttamente */

/* Esercizio 3 (avanzato): Estendi la gerarchia Conto → ContoCorrente → ContoCorrente_Premium dell'esercizio precedente. Aggiungi un metodo virtual rendiconto() che stampa un riepilogo diverso per ogni livello — Conto stampa saldo e storico, ContoCorrente aggiunge lo scoperto utilizzato, ContoCorrente_Premium aggiunge il cashback totale accumulato. Aggiungi un attributo cashback_totale che si accumula ad ogni prelievo riuscito. Crea un array polimorfico di tre puntatori a Conto, assegna uno per tipo, chiama rendiconto() su tutti — verifica che il dispatch dinamico chiami la versione giusta. Verifica che il distruttore virtual chiami la catena corretta con delete sul puntatore base. */