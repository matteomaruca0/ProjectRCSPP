//Contiene la classe
#pragma once

#include "solver.h"

struct Solution {
    std::vector<int>  nodes;     // origine, ..., destinazione (in ordine di visita)
    std::vector<char> inPath;    // inPath[v] = 1 se il nodo v è nel cammino
    long long cost;              // costo totale corrente (archi + nodi), interi scalati
    std::vector<int> load;       // consumo corrente di ogni risorsa
};

class TabuSearchAlgo : public Algorithm {
    public:
        TabuSearchAlgo(std::string name, Problem* problem);
        ~TabuSearchAlgo() = default;

        //Solve
        void solve() override;

        //Reset
        void resetAlgorithm(int reset_level) override;

    protected:
    private:
        std::vector<int> getStartSolution(); 
        Solution currentSolution;
};