# Tutorial PathWyse in C++ — ogni step un esercizio

Versione C++ del tutorial (la precedente era solo Python). Tutti gli esempi sono stati compilati ed eseguiti: gli output riportati sono quelli veri. Niente di difficile: l'obiettivo è capire **come si usano la libreria e i suoi oggetti**.

---

## 0. Regole del gioco (leggi prima di iniziare)

1. **Esegui sempre dalla cartella radice del repo** (`pathwyse/`). Due motivi: il file di configurazione `pathwyse.set` viene letto dalla cartella corrente, e le librerie `bin/libpathwyse_core.so` sono trovate con un rpath relativo.
2. **Un solo punto di ingresso: la classe `Solver`** (`src/core/solver.h`). Fa quello che fa il wrapper Python: crea il problema, aggiunge risorse, sceglie gli algoritmi, risolve, restituisce le soluzioni.
3. I setter restituiscono `RETURN_OK` (1) oppure `RETURN_ERROR` (0).
4. **I costi sono interi scalati** internamente (`getCostScaleFactor()`): `Path::getObjective()` restituisce il valore scalato, `Solver::getSolutionObjective()` restituisce il `double` vero. Usa sempre il secondo.
5. **Ordine di costruzione**: `createProblem → setNumNodes/Origin/Destination/... → initProblem → addArc/setArcCost/setNodeCost → addResource → buildProblem → setupAlgorithms`. Se chiami `addArc` prima di `initProblem` va in segfault (la documentazione dice il contrario, ma l'ordine giusto è questo).
6. `Solver` **non è copiabile** (contiene un mutex): se vuoi restituirlo da una funzione usa `std::unique_ptr<Solver>`.

### Gli oggetti, in una tabella

| Oggetto | A cosa serve | Come ci arrivi |
|---|---|---|
| `Solver` | Entry point: costruisce, configura, risolve | `Solver pw;` |
| `Problem` | Grafo + risorse del problema | `pw.getProblem()` |
| `Resource` | Una risorsa (sottoclassi `Capacity`, `Time`, `TimeWindow`, `NodeLim`, `DefaultCost`) | `problem->getRes(i)`, `problem->getObj()` per i costi |
| `Algorithm` | Classe astratta (`solve()`, `resetAlgorithm(int)`) di ogni algoritmo | `new PWDefault`, o la tua sottoclasse |
| `Path` | Una soluzione: tour, costo, consumi, stato | `pw.getBestSolution()` |
| `Parameters` | Parametri letti da `pathwyse.set` | automatico |

Tipi di risorsa per `addResource`: `"CAP"`, `"TIME"`, `"TW"`, `"NODELIM"`.

### Come compilare

```bash
cd pathwyse/tutorial_cpp
mkdir build && cd build
cmake .. && make -j8
cd ../..                    # torna alla radice del repo
./bin/es1_hello             # gli eseguibili finiscono in pathwyse/bin
```

(Il repo va già compilato una volta con `./install.sh`, così esiste `bin/libpathwyse_core.so`.)

---

## Passo 0 — Usare PathWyse "da riga di comando"

Prima di scrivere codice, usa il programma già pronto:

```bash
./bin/pathwyse instances/toy.txt
```

Il file `instances/toy.txt` descrive il problema (5 nodi, 1 risorsa, origine 0, destinazione 4). L'output finisce con:

```
[ Solution ]
  Solution Status                 : Optimal
  Obj                             : -10435.000000
  Tour Length                     : 4
  Tour                            : 0 2 1 4
  Consumption                     : 9
```

**Esercizio 0.** Apri `instances/toy.txt`, trova il limite della risorsa (`RES_BOUND`, qui 12), mettilo a 8 e rilancia; poi a 5.

**Soluzione.** Con 8 il tour diventa `0 1 4` con obiettivo 121565 (il tour ottimo di prima, `0 2 1 4`, consuma 9 e con limite 8 non è più ammissibile). Con 5 non esiste alcun cammino ammissibile: *Problem Status: Infeasible*.

---

## Passo 1 — Hello PathWyse (`es1_hello.cpp`)

```cpp
#include "solver.h"

int main(int argc, char** argv) {
    std::string instance = (argc > 1) ? argv[1] : "instances/toy.txt";

    Solver pw;                    // 1) crea il solver (legge pathwyse.set)
    pw.readProblem(instance);     // 2) legge il problema da file
    pw.setupAlgorithms();         // 3) prepara gli algoritmi
    pw.solve();                   // 4) risolve
    pw.printBestSolution();       // 5) stampa la soluzione migliore
    return 0;
}
```

Sono i 5 gesti fondamentali: **crea → leggi → prepara → risolvi → stampa**.

**Esercizio 1.** Compila ed esegui `./bin/es1_hello`, poi `./bin/es1_hello instances/spprclib/A-n54-k7-149.sppcc` (o un'altra istanza della cartella `instances/`). Quanti nodi ha il problema? Qual è l'obiettivo?

**Soluzione.** Il toy ha 5 nodi, tour `0 2 1 4`, obiettivo −10435. La istanza A-n54-k7-149 ha 55 nodi, obiettivo −12492 e un tour di lunghezza 12.

> Se `verbosity = 0` in `pathwyse.set` **non stampa nulla** (neanche l'intestazione). Con 1 stampa il riepilogo come sopra.

---

## Passo 2 — Ispezionare il problema (`es2_inspect.cpp`)

Il `Solver` espone getter per leggere cosa c'è dentro il problema: `getName`, `getNumberOfNodes`, `getOrigin`, `getDestination`, `isDirected`, `isGraphCyclic`, `isSymmetric`, `getNumRes`, `getResLB`, `getResUB`, `getNodeCost`, `getResNodeConsumption`, `getArcCost`.

**Esercizio 2.** Scrivi un programma che per il toy stampi nome, nodi, origine/destinazione, proprietà del grafo, limiti della risorsa e una tabella con costo e consumo di ogni nodo (più il costo dell'arco 0→2 e di 2→0).

**Soluzione** (sorgente completo in `es2_inspect.cpp`), output:

```
Nome: Toy | nodi: 5
Origine: 0 | destinazione: 4
Orientato: true | ciclico: true | simmetrico: false
Risorse: 1 | limiti risorsa 0: 0 - 12

Nodo | costo nodo | consumo risorsa 0
   0 |    -7435.0 | 0
   1 |        0.0 | 2
   2 |  -200000.0 | 1
   3 |    -7839.0 | 6
   4 |    -4000.0 | 6

Costo arco 0->2: 35000.0 | 2->0: 35000.0
```

Il **costo dei nodi** è un guadagno quando è negativo: PathWyse minimizza, quindi un nodo con costo −200000 è un "premio" enorme per passarci.

---

## Passo 3 — Leggere la soluzione (`es3_solution.cpp`)

```cpp
std::vector<int> tour = pw.getSolutionTour(0);          // soluzione di indice 0
pw.getSolutionStatus(0);                                // 2 = PATH_OPTIMAL, 3 = PATH_FEASIBLE
pw.getSolutionTourAsString(0);
pw.getSolutionObjective(0);                             // double vero (non scalato)

Path best = pw.getBestSolution();                       // oggetto Path completo
best.getTourLength(); best.isOptimal();
best.getConsumption(0);                                 // consumo della risorsa 0
best.getObjective();                                    // scalato!
```

**Esercizio 3.** Dopo aver risolto il toy, ricalcola **a mano** il costo del tour (somma costi archi + somma costi nodi) e il consumo della risorsa, e controlla che coincidano con quelli di PathWyse.

**Soluzione.** Output:

```
Soluzioni nel pool: 1
Stato: 2
Tour: 0 2 1 4
Obiettivo: -10435.0
Costo ricalcolato a mano: -10435.0
Consumo risorsa 0: 9 (limite 12)
Path: lunghezza 4, ottimo? true, consumo risorsa 0 = 9, obiettivo interno (scalato) = -1043500
```

Nota il fattore 100 tra `-10435.0` e `-1043500`: è la scala interna dei costi.

---

## Passo 4 — Costruire un problema da zero (`network.h`, `es4_build.cpp`)

Rete di 6 nodi (origine 0, destinazione 5), archi simmetrici con costo, e una risorsa capacità che si consuma nei nodi:

| Arco | 0-1 | 0-2 | 1-2 | 1-3 | 2-3 | 2-4 | 3-4 | 3-5 | 4-5 |
|---|---|---|---|---|---|---|---|---|---|
| Costo | 4 | 2 | 1 | 5 | 8 | 10 | 2 | 6 | 3 |

Domanda per nodo: `{0, 3, 2, 4, 5, 0}`.

Funzione `buildSolver` (in `network.h`):

```cpp
inline std::unique_ptr<Solver> buildSolver(int capUb, int nodeLimit = -1) {
    auto pw = std::make_unique<Solver>();
    pw->createProblem();
    pw->setProblemName("Rete6");
    pw->setNumNodes(6);
    pw->setDirected(true);
    pw->setCyclic(true);
    pw->setOrigin(0);
    pw->setDestination(5);
    pw->initProblem();                       // prepara le strutture interne
    for (const Edge& e : EDGES)              // archi e costi, nei due versi
        for (auto [a, b] : {std::pair{e.i, e.j}, std::pair{e.j, e.i}}) {
            pw->addArc(a, b);
            pw->setArcCost(a, b, e.cost);
        }
    for (int node = 0; node < 6; node++) pw->setNodeCost(node, 0);

    int cap = pw->addResource("CAP");
    pw->setResBounds(cap, 0, capUb);
    for (int node = 0; node < 6; node++) pw->setResNodeConsumption(cap, node, DEMAND[node]);
    if (nodeLimit >= 0) {                    // servirà al passo 7
        int nl = pw->addResource("NODELIM");
        pw->setResBounds(nl, 0, nodeLimit);
    }
    pw->buildProblem();
    pw->setupAlgorithms();
    return pw;
}
```

**Esercizio 4.** Costruisci il problema con capacità massima 10, risolvilo e verifica il risultato con una **forza bruta** (prova tutti i sottoinsiemi di nodi intermedi in tutti gli ordini con `std::next_permutation`).

**Soluzione.**

```
PathWyse: 0 2 1 3 5  obiettivo 14.0
Forza bruta: 0 2 1 3 5 costo 14.0
```

Il percorso `0 2 1 3 5` costa 2+1+5+6 = 14 e consuma 0+2+3+4+0 = 9 ≤ 10.

---

## Passo 5 — Cambiare i limiti di una risorsa (`es5_bounds.cpp`)

**Esercizio 5.** Risolvi la rete variando la capacità da 2 a 14 e stampa, per ciascun valore, soluzioni trovate / tour / obiettivo. Quando il problema diventa infeasible? Quando la soluzione migliora?

**Soluzione.**

```
UB capacita' | n. soluzioni | tour | obiettivo
2..5 | 0 | (nessun cammino ammissibile)
6 | 1 | 0 2 3 5  | 16.0
7 | 1 | 0 1 3 5  | 15.0
8 | 1 | 0 1 3 5  | 15.0
9 | 1 | 0 2 1 3 5  | 14.0
10 | 1 | 0 2 1 3 5  | 14.0
11 | 1 | 0 2 1 3 5  | 14.0
12 | 1 | 0 1 3 4 5  | 14.0
13 | 1 | 0 1 3 4 5  | 14.0
14 | 1 | 0 2 1 3 4 5  | 13.0
```

Più capacità = più cammini ammissibili = costo che può solo scendere (16 → 13). Sotto 6 nessun cammino 0→5 è ammissibile: il più leggero (`0 2 3 5`) consuma proprio 6.

---

## Passo 6 — Scegliere gli algoritmi (`es6_algorithms.cpp`)

Gli algoritmi vivono in una lista con un id (0, 1, 2…). Metodi principali:

```cpp
pw->setAlgorithms({"PWDefault", "PWBucket"}, {true, false});  // nomi + quali attivi
pw->getEnabledAlgorithms();      // id attivi
pw->enableAlgorithm(id);  pw->disableAlgorithm(id);  pw->disableAllAlgorithms();
pw->resetAllAlgorithms(0);       // riporta gli algoritmi allo stato iniziale
pw->clearSolutions();            // svuota il pool di soluzioni
```

Se non la chiami, la lista viene da `pathwyse.set` (`algo_names`, `algo_active`): di default `PWDefault, PWDefaultRelaxDom, PWDefaultRelaxQueue` con solo il primo attivo.

**Esercizio 6.** Sulla rete (cap 10) risolvi prima con solo `PWDefault`, poi spegnilo, accendi `PWBucket`, azzera e risolvi di nuovo. Il risultato cambia?

**Soluzione.**

```
Attivi all'inizio: 1 (id 0)
Solo PWDefault -> 0 2 1 3 5  14.0
Attivi ora: id 1
Solo PWBucket  -> 0 2 1 3 5  14.0
```

Sono due algoritmi **esatti**: stessa soluzione, cambia solo il modo (e il tempo) con cui la trovano.

### Esercizio 6b — più soluzioni nel pool (`es6b_pool.cpp`)

Per tenere più di una soluzione cambia in `pathwyse.set`:

```
algo/requested_solutions = 3
```

Poi:

```cpp
int n = pw->getNumberOfSolutions();
pw->rankSolutions("objective");        // ordina dalla migliore
for (int k = 0; k < n; k++) std::cout << k << " " << pw->getSolutionTourAsString(k) << "\n";
```

Output reale con 3 soluzioni richieste (capacità 10):

```
Soluzioni trovate: 3
0 0 2 1 3 5  14.0
1 0 2 1 3 5  14.0
2 0 1 3 5  15.0
```

(la prima colonna è l'indice `k`). Attenzione: le prime due sono **la stessa soluzione duplicata** — il pool non elimina i duplicati. Ricordati di rimettere `algo/requested_solutions = 1` dopo la prova.

---

## Passo 7 — Due risorse insieme (`es7_two_resources.cpp`)

Aggiungiamo `"NODELIM"`: limita il **numero di nodi** del cammino. Il valore iniziale è 1 e conta *tutti* i nodi, origine e destinazione compresi.

**Esercizio 7.** Con capacità 14 (larga, così conta solo l'altro limite) imposta il limite di nodi da 6 a 2 e osserva il tour.

**Soluzione.**

```
limite nodi | tour | obiettivo
6 | 0 2 1 3 4 5  | 13.0
5 | 0 2 1 3 5  | 14.0
4 | 0 1 3 5  | 15.0
3 | nessuna soluzione
2 | nessuna soluzione
```

Con meno nodi concessi il percorso si accorcia e costa di più; sotto 4 nodi non c'è nessun cammino 0→5 (nella rete non c'è un arco diretto e il più corto ha 4 nodi).

---

## Passo 8 — Scrivere un proprio algoritmo (`es8_custom_algorithm.cpp`)

Questo è il passo che ha senso **solo in C++** ed è quello per cui il professore ti ha dato la libreria. Basta ereditare da `Algorithm` e implementare due metodi:

```cpp
class GreedyAlgo : public Algorithm {
public:
    GreedyAlgo(std::string name, Problem* problem) : Algorithm(name, problem) {
        setType(ALGO_HEURISTIC);
    }
    void solve() override { /* costruisci un Path e chiama addSolution(path) */ }
    void resetAlgorithm(int reset_level) override { clearSolutions(); initAlgorithm(); }
};
```

Dentro `solve()` (nearest neighbour):

- `Problem* p = getProblem(); Resource* obj = p->getObj();` per costi (interi scalati);
- `p->getNeighbors(cur, true)` dà i vicini raggiungibili da `cur` (true = archi uscenti);
- per ogni risorsa `res->isFeasible(res->extend(value[r], cur, next), next)` dice se estendere verso `next` rispetta i limiti;
- alla fine si riempie un `Path` (`setTour`, `setArcCost`, `setNodeCost`, `setObjective`, `setConsumption`, `setElementary(true)`, `setStatus(PATH_FEASIBLE)`), si chiama `addSolution(path)` e `setStatus(ALGO_DONE)`.

Come si registra:

```cpp
pw->setAlgorithms({"PWDefault"});                                // pool pulito: id 0 = PWDefault
pw->addAlgorithm(*new GreedyAlgo("Greedy", pw->getProblem()));   // id 1 = Greedy
```

**Va allocato con `new`**: il `Solver` ne prende possesso e lo cancella lui. Se non fai prima `setAlgorithms({"PWDefault"})`, `setupAlgorithms()` ha già creato i 3 algoritmi di `pathwyse.set` e il tuo avrebbe id 3.

**Esercizio 8.** Confronta l'algoritmo esatto (id 0) con il greedy (id 1) sulla rete con capacità 14, 10 e 7.

**Soluzione.**

```
capacita' 14 | esatto : 0 2 1 3 4 5  costo 13.0
capacita' 14 | greedy : 0 2 1 3 4 5  costo 13.0
capacita' 10 | esatto : 0 2 1 3 5  costo 14.0
capacita' 10 | greedy : 0 2 1 3 5  costo 14.0
capacita' 7 | esatto : 0 1 3 5  costo 15.0
capacita' 7 | greedy : nessuna soluzione
```

Con capacità 7 il greedy sceglie subito l'arco più economico (0→2, costo 2), ma poi finisce in un vicolo cieco e non trova nulla; l'esatto invece trova `0 1 3 5`. È la differenza tra euristica (ammissibile, senza garanzie) ed algoritmo esatto (ottimo garantito).

---

## Esercizio finale (`es_finale.cpp`)

**Problema.** Rete di consegne con 7 nodi (origine 0, destinazione 6). Archi simmetrici:

`0-1:3, 0-2:5, 1-2:2, 1-3:6, 2-3:3, 2-4:7, 3-4:2, 3-5:4, 4-5:3, 4-6:6, 5-6:2`

- Costi dei nodi (bonus di visita): `{0, 0, -4, -1, -5, 0, 0}`
- Domanda (capacità): `{0, 2, 3, 1, 4, 2, 0}`
- Risorse: `CAP` e `NODELIM`.

**Compito.** Costruisci il problema per questi 5 scenari (capacità, limite nodi): (12,7), (8,7), (8,5), (6,5), (4,4); risolvi con PathWyse e verifica ogni risultato con una forza bruta.

**Soluzione** (output vero):

```
cap | max nodi | PathWyse                | obiettivo | forza bruta | ok?
 12 |        7 | 0 2 3 4 5 6             |       5.0 |         5.0 | si
  8 |        7 | 0 2 3 4 6               |       6.0 |         6.0 | si
  8 |        5 | 0 2 3 4 6               |       6.0 |         6.0 | si
  6 |        5 | 0 2 3 5 6               |       9.0 |         9.0 | si
  4 |        4 | nessuna soluzione       |           | nessuna | si
```

Verifica a mano del primo: tour `0 2 3 4 5 6` → archi 5+3+2+3+2 = 15, nodi −4−1−5 = −10, totale **5**; consumo capacità 3+1+4+2 = 10 ≤ 12; nodi 6 ≤ 7.

---

## Cose strane trovate (da sapere)

- **`getSolutionNodeCost` non è affidabile**: `Algorithm::buildPath` conta il nodo origine due volte e non conta la destinazione. Sul toy (tour `0 2 1 4`) dà −214870 invece di −211435 (−7435 −200000 +0 −4000): conta −7435 due volte e perde −4000. Il valore buono è `getSolutionObjective`, che è corretto. Per questo nel passo 3 ricalcolo il costo a mano.
- **Ordine di costruzione**: `initProblem()` prima di `addArc` (la documentazione dice il contrario → segfault).
- **Il pool non toglie i duplicati** (passo 6b).
- **`verbosity = 0` non stampa neanche l'intestazione.**
- **`Solver` non copiabile**: serve `unique_ptr`.
- **Un algoritmo custom va allocato con `new`** (il Solver lo cancella).
