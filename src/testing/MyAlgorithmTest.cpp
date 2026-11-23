#include <algorithm>

//Contiene l'implementazione
#include "MyAlgorithmTest.h"

//Scegliere la struttura dati che contiene le mosse (Tabu List)
//Come salvare le mosse (in che modo salvare la mossa per esempio come salvo la mossa di scambio di archi etc...)



TabuSearchAlgo::TabuSearchAlgo(std::string name, Problem* problem) : Algorithm(name, problem){
    setType(ALGO_HEURISTIC);
}

void TabuSearchAlgo::solve() {

    
}

int getLenghtsTabuList(){

}

// per ora genero un numero casuale di nodi tra la partenza e la fine 
// e creo il tour di partenza in questo modo:
// scelgo un nodo alla volta in modo casuale verificando che sia ammissibile la soluzione iniziale
std::vector<int> TabuSearchAlgo::getStartSolution(){
    std::vector<int> solutionStart;

    std::srand(std::time(nullptr)); //con l'ora attuale

    int numNodes = this->problem->getNumNodes();

    //Genero il numero di nodi da generare
    int startNode = problem->getOrigin();
    int destNode = problem->getDestination();

    Resource* capacity = problem->getRes(0);
    int load = capacity->getInitValue();
    int last = startNode;
    
    //Genero un nodo controllo che non è già compreso nel vettore e poi ripeto finche la capacità non sfora
    //quando sfora esco

    /*do {
        int generatedNode = std::rand() % (numNodes - 2) + 1;

        //Tramite la classe Resource estendo il nodo generato e poi verifico se ammissibile
        int newLoad = capacity->extend(load, last, generatedNode);

        //Cerca il nodo generato se non lo trova ritorna la fine del vettore
        if (std::find(solutionStart.begin(), solutionStart.end(), generatedNode) == solutionStart.end() &&
            capacity->isFeasible(newLoad, generatedNode)) {
            load = newLoad;
            last = generatedNode;
            solutionStart.push_back(generatedNode);
        }
    } while ();*/
    
    
    return solutionStart;
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