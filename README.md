# Progetto Algoritmi avanzati

## Affrontare e risolvere con algoritmi metaeuristici il problema di "Resource Constrained Shortest Path Problem (RCSPP)"

Questo progetto implementa un risolutore per l'**RCSPP (Resource-Constrained Shortest Path Problem)**, un problema fondamentale nella ricerca operativa, spesso utilizzato come sottoproblema di *pricing* per risolvere problemi di routing più complessi. L'RCSPP consiste nel trovare un percorso di costo minimo tra un nodo di partenza e uno di arrivo all'interno di un grafo, accumulando costi e premi, ma dovendo rispettare rigorosamente dei vincoli legati a una o più "risorse" limitate.

Nello specifico, la nostra implementazione si concentra sulla variante legata al **CVRP (Capacitated Vehicle Routing Problem)**. In questo scenario:
* **Vincolo (Risorsa):** Il veicolo possiede una capacità di carico massima (Q). Ogni cliente visitato ha una determinata domanda. Il percorso è valido solo se la somma delle domande dei clienti visitati non supera mai la capacità del veicolo.
* **Obiettivo (Costo):** Trovare il tragitto ottimale minimizzando il costo totale, calcolato come la somma dei costi di percorrenza degli archi attraversati meno i premi raccolti presso i nodi visitati.

#

Sono previste alcune tappe, valutate durante le lezioni di laboratorio:

1. **Studiare il problema RCSPP (Articolo da leggere).** Ogni studente legge 1 articolo scientifico relativo al problema RCSPP. Verrà erogato un questionario durante la lezione di laboratorio.
2. **Installazione libreria PathWyse.** Ogni studente deve installare e compilare sul proprio calcolatore la libreria [PathWyse](https://github.com/pathwyse) (Articolo su PathWyse: PathWyse - Journal, PathWyse - Slides ODS). 
3. **Familiarizzare con l'architettura software della libreria** e capire come la libreria prevede di integrare nuovi algoritmi. Verrà erogato un questionario durante la lezione di laboratorio.
4. **Ideazione ed implementazione di un algoritmo metaeuristico per RCSPP** integrato in PathWyse. Consegna del codice sorgente, solo dei files modificati da voi.
5. **Effettuare prove computazionali** (scaricate qui le istanze SPPRCLIB) e consegnare una tabella di risultati con commenti.
6. **(Facoltativo con Bonus)** al posto del punto 4. lo studente può cimentarsi con l'implementazione dell'algoritmo Pulse (Paper) integrandolo nella libreria PathWyse.