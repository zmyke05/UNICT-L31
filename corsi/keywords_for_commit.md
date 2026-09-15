# Convenzione per i messaggi di commit

Formato generale:

```text
<type>(<materia>): <descrizione breve>
```

- Scrivere la descrizione in forma concisa e all'infinito o al participio,
  mantenendo lo stesso stile in tutto il repository.
- Usare una materia coerente con il nome della relativa directory, ad esempio
  `algebra`, `prog2` o `sistemi-operativi`.
- Omettere `(materia)` solo quando la modifica riguarda più corsi o il
  repository nel suo insieme.

## Tipo di modifica

| Keyword | Quando usarla | Esempio |
| --- | --- | --- |
| `docs` | Appunti, slide, schemi, riassunti in Markdown/LaTeX o note teoriche. | `docs(algebra): aggiunti appunti su autovalori e autovettori` |
| `feat` | Prima risoluzione o stesura di un esercizio, progetto o laboratorio di programmazione. | `feat(prog2): implementata lista concatenata in C++` |
| `fix` | Correzione di errori nel codice o di sviste negli appunti, incluso il refactoring di un esercizio. | `fix(prog2): corretto memory leak nel distruttore` |
| `ex` | Esercitazioni, esercizi risolti o tracce d'esame. | `ex(algebra): risolta traccia d'esame del 21 settembre` |
| `lab` | Attività, consegne o materiale specifici del laboratorio. | `lab(sistemi-operativi): aggiunta esercitazione sui processi` |
| `assets` | Immagini, PDF di libri o slide, diagrammi e schemi grafici. | `assets(architettura): aggiunti schemi dei circuiti logici` |

## Stato e avanzamento (opzionali)

Usare questi prefissi per tracciare lo stato di completamento di una sezione.

| Keyword | Quando usarla | Esempio |
| --- | --- | --- |
| `wip` | Lavoro iniziato ma non ancora concluso. | `wip(algebra): iniziato formulario sulle forme quadratiche` |
| `review` | Modifiche effettuate dopo aver ricontrollato un esercizio o dopo un confronto con i compagni. | `review(prog2): ottimizzata la complessità del codice` |
| `done` | Argomento o sezione d'esame completata e archiviata definitivamente. | `done(algebra): completata la revisione di tutto il programma` |

## Gestione delle cartelle

| Keyword | Quando usarla | Esempio |
| --- | --- | --- |
| `chore` | Manutenzione generale, eliminazione di file obsoleti o creazione della struttura iniziale. | `chore(algebra): rimossi vecchi bozzetti e file temporanei` |
| `style` | Riorganizzazione, spostamento o rinomina di cartelle e file senza modificarne il contenuto. | `style(prog2): spostati gli esercizi nella sottocartella laboratorio` |
| `refactor` | Ristrutturazione significativa della disposizione del materiale per renderlo più fruibile prima dell'esame. | `refactor(algebra): riorganizzati gli appunti per capitoli d'esame` |

Per la creazione della struttura iniziale di un corso, si può omettere la
materia:

```text
chore: creata struttura cartelle per il nuovo semestre
```