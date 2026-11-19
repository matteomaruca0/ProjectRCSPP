//Contiene l'implementazione
#include "MyAlgorithmTest.h"

//Scegliere la struttura dati che contiene le mosse (Tabu List)
//Come salvare le mosse (in che modo salvare la mossa per esempio come salvo la mossa di scambio di archi etc...)



TabuSearchAlgo::TabuSearchAlgo(std::string name, Problem* problem) : Algorithm(name, problem){
    setType(ALGO_HEURISTIC);
}

void TabuSearchAlgo::solve() {
    //per ora genero un numero casuale di nodi tra la partenza e la fine e creo il tour di partenza in questo modo

    int numNodes = this->problem->getNumNodes();
}

std::list<int> getLenghtsTabuList(){

}

//Mossa di aggiunta di un nodo
// partendo dalla soluzione attuale aggiungo un nodo per ogni posizione tra due nodi
// rispettando vincolo di capacità poi prendo la soluzione migliore e la ritorno costruendo il vicino
// quindi per ogni nodo rimanente seleziono in quale posizione lo metto ed è ammissibile
// lo faccio per il prossimo nodo e poi vedo quale è migliore e lo tengo, ritorno il migliore
Path addNodeMove(){

}



void TabuSearchAlgo::resetAlgorithm(int reset_level) {
    clearSolutions();
    initAlgorithm();
}