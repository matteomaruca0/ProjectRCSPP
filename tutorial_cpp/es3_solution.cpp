#include "solver.h"
#include <iomanip>
#include <iostream>

// Costo di un cammino = somma costi archi + somma costi dei nodi visitati
double tourCost(Solver& pw, const std::vector<int>& tour) {
    double total = 0;
    for (size_t k = 0; k + 1 < tour.size(); k++) total += pw.getArcCost(tour[k], tour[k + 1]);
    for (int node : tour) total += pw.getNodeCost(node);
    return total;
}

// Consumo di una risorsa di tipo capacita': somma dei consumi dei nodi
int tourConsumption(Solver& pw, const std::vector<int>& tour, int res = 0) {
    int total = 0;
    for (int node : tour) total += pw.getResNodeConsumption(res, node);
    return total;
}

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    Solver pw;
    pw.readProblem("instances/toy.txt");
    pw.setupAlgorithms();
    pw.solve();

    std::vector<int> tour = pw.getSolutionTour(0);
    std::cout << "Soluzioni nel pool: " << pw.getNumberOfSolutions() << "\n";
    std::cout << "Stato: " << pw.getSolutionStatus(0) << "\n";
    std::cout << "Tour: " << pw.getSolutionTourAsString(0) << "\n";
    std::cout << "Obiettivo: " << pw.getSolutionObjective(0) << "\n";
    std::cout << "Costo ricalcolato a mano: " << tourCost(pw, tour) << "\n";
    std::cout << "Consumo risorsa 0: " << tourConsumption(pw, tour)
              << " (limite " << pw.getResUB(0) << ")\n";

    // In C++ puoi anche lavorare direttamente sull'oggetto Path
    Path best = pw.getBestSolution();
    std::cout << "Path: lunghezza " << best.getTourLength()
              << ", ottimo? " << std::boolalpha << best.isOptimal()
              << ", consumo risorsa 0 = " << best.getConsumption(0)
              << ", obiettivo interno (scalato) = " << best.getObjective() << "\n";
    return 0;
}
