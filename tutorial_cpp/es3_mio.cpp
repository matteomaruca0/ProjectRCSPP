#include "solver.h"
#include <iomanip>
#include <iostream>

double tourCost(Solver& sw, const std::vector<int>& tour) {
    double cost = 0;

    //Costo degli archi
    for (int i = 0; i + 1 < tour.size(); i++)
    {
        double costo_arco = sw.getArcCost(tour[i], tour[i+1]);
        std::cout << "Costo arco " << tour[i] << " - " << tour[i+1] << " : " << costo_arco << std::endl;
        cost += costo_arco;
    }

    //Costo dei premi
    for (const int node : tour)
    {
        double costo_nodo = sw.getNodeCost(node);
        std::cout << "Costo nodo " << node << " : " << costo_nodo << std::endl;
        cost += costo_nodo;
    }
    
    return cost;
}

//Consumo della risorsa per ogni nodo
int tourConsumption(Solver& sw, const std::vector<int>& tour, int resource) {
    int total = 0;

    for(const int node : tour){
        int consumption = sw.getResNodeConsumption(resource, node);
        std::cout << "Consumo della risorsa al nodo " << node << ": " << consumption << std::endl;
        total += consumption;
    }

    return total;
}

int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1);

    Solver sw;

    sw.readProblem("instances/toy.txt");
    std::cout << "Nome: " << sw.getName() << std::endl;
    std::cout << "Numero di nodi: " << sw.getNumberOfNodes() << std::endl;
    std::cout << "Nodo partenza: " << sw.getOrigin() << " | Nodo di arrivo: " << sw.getDestination() << std::endl;

    //Risolviamo in modo autoamtico dato da pathwhyse
    sw.setupAlgorithms();
    sw.solve();

    //Parte nuova
    if (sw.getNumberOfSolutions() == 0) {
    std::cout << "Nessuna soluzione trovata\n";
    return 0;
    }
    std::vector<int> tour = sw.getSolutionTour(0);
    std::cout << "Numero di soluzioni: " << sw.getNumberOfSolutions() << "\n";
    std::cout << "Stato della soluzione 0: " << sw.getSolutionStatus(0) << " (2 ottimo, 3 ammissibile)" << "\n";
    std::cout << "Tour della soluzione 0: " << sw.getSolutionTourAsString(0) << "\n";
    std::cout << "Valore della funzione obbiettivo della soluzione 0: " << sw.getSolutionObjective(0) << "\n";

    std::cout << "Costo del tour, calcolato manualmente:\n " << tourCost(sw, tour) << "\n";
    std::cout << "Consumo della risorsa 0 del tour 0:\n " << tourConsumption(sw, tour, 0) << "\n";

    return 0;
}