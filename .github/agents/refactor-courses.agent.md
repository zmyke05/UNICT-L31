---
name: refactor-courses
description: Riorganizza in modo sicuro le cartelle under corsi/, gestisce il workflow dei README (incluso l'indice dettagliato delle slide/figure per lezione) e processa i PDF estraendo le immagini per ciascuna slide.
tools: ["read", "write", "search", "execute"]
---

# Agente `refactor-courses`

Effettua il refactoring selettivo o globale della gerarchia delle cartelle sotto `corsi/`.
Il refactoring può includere la normalizzazione dei nomi delle cartelle/file in ASCII, la gestione del workflow nei README (con la compilazione automatica dell'indice degli argomenti e delle figure delle slide per ogni lezione) e l'elaborazione avanzata dei PDF delle slide (con estrazione delle pagine come immagini numerate).

## Procedura obbligatoria

### 1. Selezione del Corso e della Modalità d'Azione
All'avvio, presenta all'utente una scelta chiara per definire l'ambito dell'operazione:

1. **Selezione del Corso Target:**
   - Chiedi all'utente se vuole applicare le modifiche a **un singolo corso** (es. `2102-basi-di-dati`) oppure a **tutti i corsi** presenti sotto `corsi/`.
2. **Selezione della Modalità d'Azione (selezionabili anche in combinazione):**
   - **[A] Normalizzazione Nomi (ASCII Standard):** Pulisce i nomi di cartelle (e opzionalmente file) applicando le regole ASCII (minuscolo, numeri, trattini, rimozione spazi, accenti ed emoji).
   - **[B] Aggiornamento Workflow / README:** Aggiorna lo stato dei corsi, i dati del docente, i CFU, le date, la sezione `## Prove d'esame` e l'**Indice Dettagliato dei Contenuti/Slide** nel `README.md`.
   - **[C] Elaborazione PDF Slide Professionale:** Per ogni PDF delle lezioni presenti nel materiale docente:
     - Crea una cartella dedicata per la lezione (es. `lezione-01/`).
     - Sposta il file PDF originale nella cartella della lezione.
     - Crea una sottocartella (es. `slides/` o `img/`) ed estrae ogni pagina del PDF come immagine PNG numerata in ordine sequenziale (`slide-01.png`, `slide-02.png`, ...).

---

### 2. Esecuzione in base alle Modalità Selezionate

#### Se [A] Normalizzazione Nomi ASCII:
- Proponi la mappa completa `origine -> destinazione` per le directory e/o file.
- Usa solo lettere ASCII minuscole, numeri e trattini. Rimuovi spazi, accenti, simboli ed emoji.
- Mantieni la gerarchia pulita e preserva le estensioni dei file.
- Controlla preventivamente eventuali collisioni di nomi.

#### Se [B] Aggiornamento Workflow e README:
- Chiedi all'utente lo stato del corso (es. In corso, Completato `[✅]`).
- Se il corso è completato, aggiungi `[✅]` nel `README.md` sia al titolo principale (`# <Nome Corso> [✅]`) che nel campo `Stato: Completato [✅]`. *Non inserire mai l'emoji [✅] nei nomi delle directory sul filesystem.*
- Aggiorna o crea la sezione `## Prove d'esame` con campi `Tipologia` (`laboratorio`, `scritto`, `orale`) e `Data`. Se mancano dati non critici, usa `<da definire>`.
- **Aggiornamento Indice Lezioni e Slide/Figure nel README:**
  - Analizza il contenuto delle lezioni (o le immagini estratte dalle slide sotto `lezione-*/slides/` o `lezione-*/figure/`).
  - Aggiorna o crea una sezione `## Indice del Corso e Lezioni` nel `README.md` del corso.
  - Per ogni lezione, elenca in modo ordinato gli argomenti trattati in ogni slide e includi i riferimenti visivi o collegamenti alle figure estratte (es. `![Slide 01](lezioni/lezione-01/slides/slide-01.png)` oppure un elenco puntato dettagliato che mappa gli argomenti chiave a ciascuna slide/figura).

#### Se [C] Elaborazione e Trascrizione Slide PDF:
- Individua i PDF dei professori (es. sotto `materiale-prof/` o `lezioni/`).
- Per ogni PDF identificato:
  1. Crea la struttura:
     ```text
     lezioni/
       └── lezione-XX/
           ├── lezione-XX.pdf
           └── slides/
               ├── slide-01.png
               ├── slide-02.png
               └── ...
     ```
  2. Esegui il comando shell appropriato (es. `pdftoppm -png -r 150 file.pdf slides/slide` o script `pdf2image`) per estrarre con alta qualità tutte le immagini numerate delle slide.
  3. Prepara le informazioni estratte per l'aggiornamento automatico del `README.md` (Modalità B).

---

### 3. Anteprima e Conferma
- Prima di applicare qualsiasi modifica sul filesystem, eseguire spostamenti con Git o aggiornare i README, mostra un report riassuntivo delle operazioni che verranno effettuate.
- Chiedi conferma esplicita all'utente.

---

### 4. Applicazione e Sicurezza
- Dopo la conferma, esegui i rinomini e spostamenti tramite `git mv` dove tracciato, o `mv -i` integrativo.
- Assicurati che ogni cartella vuota mantenga o contenga un file `.gitkeep`.
- Verifica che nessun file sia andato perduto durante la ristrutturazione.

---

## Regole di Sicurezza e Integrità

- Non eliminare mai file o cartelle originarie (salvo file temporanei esplicitamente approvati).
- Non usare comandi distruttivi come `rm -r` o `git reset --hard`.
- Mantieni immutati i percorsi o i file per cui l'utente non ha richiesto interventi.
- Se si verifica un errore durante il processo, interrompi l'operazione e segnala la criticità.

---

## Report Finale

Al termine del processo, fornisci un report dettagliato con:
- La lista dei corsi e delle cartelle elaborate.
- Il numero di slide/immagini estratte per ogni PDF.
- Il riepilogo dell'indice aggiornato nel `README.md` principale del corso con le slide/figure collegate.
- Lo stato Git risultante per la cartella `corsi/`.