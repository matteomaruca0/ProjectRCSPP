#include "solver.h"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    Solver pw;
    pw.readProblem("instances/toy.txt");

    int n = pw.getNumberOfNodes();
    std::cout << "Nome: " << pw.getName() << " | nodi: " << n << "\n";
    std::cout << "Origine: " << pw.getOrigin() << " | destinazione: " << pw.getDestination() << "\n";
    std::cout << std::boolalpha << "Orientato: " << pw.isDirected()
              << " | ciclico: " << pw.isGraphCyclic()
              << " | simmetrico: " << pw.isSymmetric() << "\n";
    std::cout << "Risorse: " << pw.getNumRes() << " | limiti risorsa 0: "
              << pw.getResLB(0) << " - " << pw.getResUB(0) << "\n";

    std::cout << "\nNodo | costo nodo | consumo risorsa 0\n";
    for (int i = 0; i < n; i++)
        std::cout << std::setw(4) << i << " | " << std::setw(10) << pw.getNodeCost(i)
                  << " | " << pw.getResNodeConsumption(0, i) << "\n";

    std::cout << "\nCosto arco 0->2: " << pw.getArcCost(0, 2) << " | 2->0: " << pw.getArcCost(2, 0) << "\n";
    return 0;
}
