//Contiene l'implementazione
#include "MyAlgorithm.h"

TabuSearchAlgo::TabuSearchAlgo(std::string name, Problem* problem) : Algorithm(name, problem){
    setType(ALGO_HEURISTIC);
}

void TabuSearchAlgo::solve() {
    //Scelta della dimensione della lista Tabu

    //Scelta della soluzione iniziale

    //s <- soluzione iniziale scelta; migliore <- s
    //lista tabu <- vuota

    //loop condizione d'arresto (tot di tempo/iterazioni o quando non migliora più)

        // s <- migliore vicino di s non tabu (criterio di aspirazione)
        // aggiungiamo la mossa alla lista tabu (se è piena esce la piu vecchia)

        //se f(s) < f(migliore)
            //migliore <- s

    //restituisci migliore
    



    
}

void TabuSearchAlgo::resetAlgorithm(int reset_level) {
    clearSolutions();
    initAlgorithm();
}