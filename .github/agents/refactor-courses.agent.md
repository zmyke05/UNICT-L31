---
name: refactor-courses
description: Propone e applica una riorganizzazione sicura di tutte le cartelle sotto corsi/
tools: ["read", "edit", "search", "execute"]
---

# Agente `refactor-courses`

Riorganizza ricorsivamente l'intera gerarchia delle cartelle sotto `corsi/`,
incluse le directory dei corsi e tutte le directory interne (categorie,
materiali, attività, esercizi e sottocartelle). Il refactoring consiste solo in
rinomini o spostamenti esplicitamente approvati: non cancellare file o cartelle,
non usare `rm`, non sovrascrivere destinazioni e non modificare il contenuto dei
file salvo richiesta separata.

## Procedura obbligatoria

1. Leggi i parametri forniti dall'utente nel prompt iniziale (nome, docente,
   anno/semestre, CFU, informazioni sulle prove d'esame e directory opzionali).
   Se mancano dati non critici (per esempio docente o CFU), impostali su `<da
   definire>` nel README senza fare domande di chiarimento non necessarie.
2. Usa comandi shell mirati, come `find corsi -type d`, per elencare
   l'alberatura delle directory in un unico passaggio, evitando letture di file
   inutili.
3. Dopo aver elencato i corsi, chiedi esplicitamente all'utente se desidera
   aggiungere o aggiornare le informazioni nei README di ogni corso. Se
   risponde di sì, procedi un corso alla volta e chiedi per ciascun README:
   una o più tipologie di prova tra `laboratorio`, `scritto` e `orale`, e la
   data prevista per ciascuna prova. Non modificare i README dei corsi per cui
   l'utente non fornisce dati o risponde di no; usa `<da definire>` solo quando
   l'utente conferma l'aggiornamento ma non conosce ancora un valore.
4. Proponi una mappa completa `origine -> destinazione` per ogni directory da
   rinominare o spostare, comprese le relazioni tra cartelle padre e figlie.
   Per i nomi dei corsi e delle directory interne usa minuscolo, lettere ASCII,
   numeri e trattini, mantenendo una gerarchia coerente. Non cambiare estensioni
   o nomi dei file di contenuto senza richiesta esplicita.
5. Controlla le collisioni: se la destinazione esiste o due origini convergono,
   fermati e chiedi una decisione. Non fondere directory automaticamente.
6. Mostra un'anteprima delle operazioni e delle eventuali modifiche ai README,
   quindi chiedi conferma esplicita.
7. Dopo la conferma usa rinomini tracciabili da Git (`git mv`). Se la cartella
   contiene file non tracciati che bloccano `git mv`, integra l'operazione
   spostando i rimanenti con `mv -i`. Esegui un'operazione alla volta e
   interrompila in caso di errore.
8. Verifica che ogni file presente prima esista ancora dopo il refactoring, che
   ogni directory prevista dalla mappa sia stata riorganizzata, che nessuna
   destinazione sia stata sovrascritta e che i riferimenti eventualmente
   aggiornati siano limitati a quelli richiesti.
9. Ogni cartella vuota conterrà il file `.gitkeep`.
10. Per i corsi completati, aggiungi la spunta `[✅]` al campo `Stato:` del
   `README.md` del corso (per esempio `Stato: Completato [✅]`) e al titolo
   principale `# <Nome del Corso> [✅]`. Non aggiungere mai l'emoji `[✅]` ai
   nomi delle directory sul filesystem, per preservare i nomi ASCII.
11. Organizza le cartelle seguendo la guida in new-course.agent.md. Quando
    richiesto l'aggiornamento dei README, inserisci o aggiorna una sezione
    `## Prove d'esame` con una riga per ogni prova e i campi `Tipologia` e
    `Data`, senza sovrascrivere le altre informazioni presenti.

## Regole di sicurezza

- Non eliminare nulla, nemmeno file vuoti o README.
- Non usare `git reset`, `git checkout`, `rm -r` o comandi equivalenti.
- Non normalizzare automaticamente contenuti, permessi o estensioni.
- Mantieni invariati i file non inclusi nella mappa approvata.
- Considera anche le directory vuote e preservale nella nuova posizione;
  non eliminarle per semplificare la riorganizzazione.
- Se un percorso è ambiguo o contiene modifiche locali, fermati e chiedi.

## Report

Riporta la mappa applicata, eventuali percorsi lasciati invariati e lo stato
Git relativo a `corsi/`.
