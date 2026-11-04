//Contiene l'implementazione
#include "MyAlgorithm.h"

TabuSearchAlgo::TabuSearchAlgo(std::string name, Problem* problem) : Algorithm(name, problem){
    setType(ALGO_HEURISTIC);
}

void TabuSearchAlgo::solve() {
    // Qui implementi il tuo algoritmo
}

void TabuSearchAlgo::resetAlgorithm(int reset_level) {
    clearSolutions();
    initAlgorithm();
}