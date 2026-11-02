#include "solver.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv) {
    std::cout << std::fixed << std::setprecision(1);

    std::string instance = (argc > 1) ? argv[1] : "instances/toy.txt";

    Solver pw;
    pw.readProblem(instance);
    std::cout << "Nome: " << pw.getName() << " | nodi: " << pw.getNumberOfNodes() << std::endl;
    std::cout << "Origine: " << pw.getOrigin() << " | destinazione: " << pw.getDestination() << std::endl;
    std::cout << "Orientato: " << ((pw.isDirected() == 1) ? "Si" : "No") << " | ciclico: " << ((pw.isGraphCyclic() == 1) ? "Si" : "No") << " | simmetrico: " << ((pw.isSymmetric() == 1) ? "Si" : "No" ) << std::endl;
    std::cout << "Risorse: " << pw.getNumRes() << " | limiti risorsa 0: " << pw.getResLB(0) << " - " << pw.getResUB(0) << std::endl;

    std::cout << std::endl;

    //per ogni nodo stampiamo
    std::cout << "Nodo | costo nodo | consumo risorsa 0" << std::endl;
    for (int i = 0; i < pw.getNumberOfNodes(); i++)
    {
        std::cout << i << " | " << pw.getNodeCost(i) << " | " << pw.getResNodeConsumption(0, i) << std::endl;
    }

    std::cout << "Costo arco 0->2: " << pw.getArcCost(0, 2) << " | 2->0: " << pw.getArcCost(2, 0) << std::endl;

    return 0;
}
