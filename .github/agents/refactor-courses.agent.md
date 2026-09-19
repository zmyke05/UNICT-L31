---
name: refactor-courses
description: Riorganizza in modo sicuro le cartelle under corsi/, gestisce il workflow dei README (con indice generale e checklist per ogni lezione) e processa i PDF delle slide creando immagini numerate e checklist dedicate.
tools: ["read", "write", "search", "execute"]
---

# Agente `refactor-courses`

Effettua il refactoring selettivo o globale della gerarchia delle cartelle sotto `corsi/`.
Permette di selezionare il corso target, configurare l'indice generale, elaborare i PDF trasformando ogni slide in un'immagine numerata e generare per ciascuna lezione un file README con una checklist interattiva delle slide.

## Procedura obbligatoria

### 1. Selezione del Corso Target e della Modalità d'Azione
All'avvio, presenta all'utente una scelta chiara per configurare l'operazione:

1. **Selezione del Corso:**
   - Chiedi esplicitamente all'utente se vuole intervenire su **un singolo corso** (es. `2102-basi-di-dati`, `algebra-lineare`, ecc.) oppure su **tutti i corsi** presenti sotto `corsi/`.

2. **Selezione delle Modalità d'Azione (selezionabili singolarmente o in combinazione):**
   - **[A] Normalizzazione Nomi (ASCII Standard):** Rinomina cartelle (e opzionalmente file) applicando le regole ASCII (minuscolo, numeri, trattini, rimozione di spazi, accenti ed emoji).
   - **[B] Aggiornamento Workflow e README Principale:**
     - Aggiorna lo stato del corso, docente, CFU, date e la sezione `## Prove d'esame`.
     - **Gestione Indice Argomenti:** Chiedi all'utente se desidera:
       1. *Definire/Fornire manualmente* gli argomenti principali per ciascuna lezione.
       2. *Generare automaticamente* una sintesi concettuale (titolo e 1-2 punti chiave per slide, evitando assolutamente trascrizioni riga per riga).
   - **[C] Elaborazione PDF Slide & Checklist Lezione (Senza Trascrizione Testuale):**
     - Per ogni PDF delle lezioni, crea una cartella dedicata per la lezione (es. `lezioni/lezione-01/`).
     - Sposta il file PDF originale all'interno della cartella della lezione.
     - Estrae ogni pagina del PDF come immagine PNG numerata ad alta risoluzione nella sottocartella `slides/` (`slide-01.png`, `slide-02.png`, ...).
     - **Generazione README di Lezione con Checklist:** Crea un file `README.md` all'interno di ciascuna cartella di lezione (`lezioni/lezione-XX/README.md`) contenente una checklist interattiva di tutte le slide con l'anteprima/riferimento all'immagine di ciascuna slide.

---

### 2. Esecuzione in base alle Selezioni

#### Se [A] Normalizzazione Nomi ASCII:
- Proponi la mappa completa `origine -> destinazione` per le directory e/o file del corso selezionato.
- Usa solo lettere ASCII minuscole, numeri e trattini. Rimuovi spazi, accenti, simboli ed emoji.
- Mantieni la gerarchia pulita e preserva le estensioni dei file.
- Controlla preventivamente eventuali collisioni di nomi.

#### Se [B] Aggiornamento Workflow e README Principale:
- Chiedi lo stato del corso (es. In corso, Completato `[✅]`).
- Se il corso è completato, aggiungi `[✅]` nel `README.md` principale sia al titolo (`# <Nome Corso> [✅]`) che nel campo `Stato: Completato [✅]`. *Non inserire mai l'emoji [✅] nei nomi delle directory sul filesystem.*
- Aggiorna o crea la sezione `## Prove d'esame` con i campi `Tipologia` (`laboratorio`, `scritto`, `orale`) e `Data`. Se mancano dati non critici, usa `<da definire>`.
- Struttura la sezione `## Indice del Corso e Lezioni` nel `README.md` principale:
  - Integra gli argomenti definiti dall'utente oppure la sintesi automatica pulita (senza trascrizioni prolisse).

#### Se [C] Elaborazione PDF Slide & Checklist Lezione:
- Individua i PDF dei docenti sotto il corso selezionato.
- Per ciascun PDF identificato:
  1. Crea la struttura di cartelle della lezione:
     ```text
     lezioni/
       └── lezione-XX/
           ├── lezione-XX.pdf
           ├── README.md
           └── slides/
               ├── slide-01.png
               ├── slide-02.png
               └── ...
     ```
  2. Esegui il comando di estrazione ad alta risoluzione (es. `pdftoppm -png -r 150 lezione-XX.pdf slides/slide`).
  3. Genera il file `lezioni/lezione-XX/README.md` con il seguente formato di checklist:

     ```markdown
     # Lezione XX - Checklist Slide

     - [ ] **Slide 01**
       ![Slide 01](slides/slide-01.png)
     - [ ] **Slide 02**
       ![Slide 02](slides/slide-02.png)
     - [ ] **Slide 03**
       ![Slide 03](slides/slide-03.png)
     ...
     ```

---

### 3. Anteprima e Conferma
- Prima di applicare qualsiasi modifica sul filesystem o sui README, mostra un report riassuntivo con l'anteprima di tutte le operazioni.
- Chiedi conferma esplicita all'utente.

---

### 4. Applicazione e Sicurezza
- Dopo la conferma, esegui i rinomini e spostamenti tramite `git mv` dove tracciato, o `mv -i` integrativo.
- Assicurati che ogni cartella vuota mantenga o contenga un file `.gitkeep`.
- Verifica che nessun file originario sia andato perduto.

---

## Regole di Sicurezza e Integrità

- Non eliminare mai file o cartelle originarie.
- Non usare comandi distruttivi come `rm -r` o `git reset --hard`.
- Mantieni immutati i percorsi o i file dei corsi non selezionati dall'utente.
- In caso di errore durante il processo, interrompi l'operazione e segnala la criticità.

---

## Report Finale

Al termine del processo, fornisci un report dettagliato con:
- Il corso selezionato e le cartelle elaborate.
- Il numero di slide/immagini estratte per ogni PDF.
- L'elenco dei file `README.md` generati per ciascuna lezione con la relativa checklist.
- Lo stato Git risultante per la cartella `corsi/`.