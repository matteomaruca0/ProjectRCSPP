#include <iostream>
#include <vector>
#include <iomanip>
#include "solver.h"

int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1);

    Solver pw;
    pw.readProblem("instances/toy.txt");
    pw.setupAlgorithms();
    pw.solve();

    std::cout << "Nome: " << pw.getName() << " | nodi: " << pw.getNumberOfNodes() << std::endl;
    std::cout << "Origine: " << pw.getOrigin() << " | destinazione: " << pw.getDestination() << std::endl;
    std::cout << "Orientato: " << ((pw.isDirected() == 1) ? "Si" : "No") << " | ciclico: " << ((pw.isGraphCyclic() == 1) ? "Si" : "No") << " | simmetrico: " << ((pw.isSymmetric() == 1) ? "Si" : "No" ) << std::endl;
    std::cout << "Risorse (numero di risorse diverse): " << pw.getNumRes() << " | limiti risorsa 0: " << pw.getResLB(0) << " - " << pw.getResUB(0) << std::endl;

    std::cout << std::endl;

    //per ogni nodo stampiamo
    std::cout << "Nodo | costo nodo | consumo risorsa 0" << std::endl;
    for (int i = 0; i < pw.getNumberOfNodes(); i++)
    {
        std::cout << i << " | " << pw.getNodeCost(i) << " | " << pw.getResNodeConsumption(0, i) << std::endl;
    }

    if (pw.getNumberOfSolutions() == 0)
    {
        std::cout << "Nessuna soluzione" << std::endl;
        return 0;
    }

    std::vector<int> tour = pw.getSolutionTour(0);

    int resourceUsed = 0;
    for (int node : tour) {
        resourceUsed += pw.getResNodeConsumption(0, node);
    }

    std::cout << "Soluzione: " << pw.getSolutionTourAsString(0) << " | Costo totale: " << pw.getSolutionObjective(0) << "\n";
    std::cout << "Risorsa usata: " << resourceUsed << " / " << pw.getResUB(0) << "\n";
    
    return 0;
}