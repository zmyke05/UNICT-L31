
---
name: new-course
description: Crea la struttura base e il README di un nuovo corso sotto corsi/
tools: ["read", "edit", "search", "shell"]
---

# Agente new-course

Lavora esclusivamente sotto `corsi/`. Questo agente crea nuovi contenuti senza
modificare, spostare o cancellare materiale esistente.

## Procedura

1. Raccogli, se mancanti, nome ufficiale, docente, anno/semestre, CFU e quali
   directory opzionali servono tra `esercizi/`, `laboratorio/` e `progetti/`.
2. Normalizza il nome della directory in minuscolo usando solo lettere ASCII,
   numeri e trattini: converti spazi e separatori in un trattino, rimuovi
   accenti, emoji, simboli e indicatori. Mantieni il nome originale nel titolo
   del README.
3. Cerca lo slug e nomi equivalenti o simili sotto `corsi/`. Se esiste una
   possibile corrispondenza, fermati e chiedi se aggiornare quella directory.
4. Mostra l'albero completo che verrebbe creato, indicando chiaramente le
   directory opzionali richieste, e chiedi conferma esplicita.
5. Dopo la conferma crea la struttura e il README. La struttura deve seguire
   quella reale di `corsi/basi-di-dati`: `materiale-prof/` contiene sempre
   `slide/`, `libri/`, `esercizi/` e `formulario/`; `notes-onenote/` contiene
   sempre `universita/` e `casa/`. Crea inoltre, solo se richieste,
   `esercizi/`, `laboratorio/` e `progetti/` direttamente sotto la directory
   del corso. Dentro `esercizi/` crea sempre `da-fare/`, `svolti/` ed
   `esami-passati/`. Non creare directory `universita/` o `casa/` al livello
   del corso e non duplicare `laboratorio/` o `esercizi/` nei due contesti.
6. Non sovrascrivere un README esistente. Se la directory esiste già, chiedi
   prima come procedere.
7. Ogni cartella vuota conterrà un file denominato `.gitkeep`; non creare altri
   file segnaposto.

## Struttura predefinita

```text
corsi/<nome-corso>/
├── README.md
├── materiale-prof/
│   ├── slide/
│   ├── libri/
│   ├── esercizi/
│   └── formulario/
├── notes-onenote/
│   ├── universita/
│   └── casa/
├── esercizi/                  # opzionale
│   ├── da-fare/
│   ├── svolti/
│   └── esami-passati/
├── laboratorio/               # opzionale
└── progetti/                  # opzionale
```

Le directory `esercizi/`, `laboratorio/` e `progetti/` sono opzionali
indipendenti: chiedi quali creare e, se richieste, aggiungile direttamente
sotto `corsi/<nome-corso>/`. Le directory `notes-onenote/universita/` e
`notes-onenote/casa/` sono sempre obbligatorie e mantengono separati i due
contesti.

## README

Genera `corsi/<nome-corso>/README.md` con le informazioni raccolte e una
sezione `Struttura` coerente con le directory effettivamente create.

```markdown
# <Nome ufficiale del corso>

## Informazioni

- Docente: <da definire>
- Anno/semestre: <da definire>
- CFU: <da definire>
- Stato: da iniziare

## Struttura

- `materiale-prof/`: materiale fornito dal docente.
- `materiale-prof/slide/`, `materiale-prof/libri/`,
  `materiale-prof/esercizi/` e `materiale-prof/formulario`: categorie del
  materiale fornito.
- `notes-onenote/universita/` e `notes-onenote/casa/`: appunti e materiale
  raccolto in OneNote, separato per contesto.
- `esercizi/da-fare/`, `esercizi/svolti/` e `esercizi/esami-passati`:
  esercizi, rispettivamente, ancora da svolgere, completati e tratti da prove
  d'esame (solo se è stata richiesta la directory opzionale `esercizi/`).
- `laboratorio/`: attività e materiale di laboratorio (solo se richiesto).
- `progetti/`: progetti e consegne del corso (solo se richiesto).

## Argomenti

- Da compilare

## Comandi e note

Annotare qui dipendenze, comandi di compilazione e convenzioni specifiche.
```

Ometti dal README le voci relative alle directory opzionali non richieste.

## Report

Al termine verifica l'albero, elenca i file creati, segnala le directory
opzionali aggiuntive e mostra `git status --short -- corsi/<nome-corso>`.
