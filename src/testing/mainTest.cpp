#include <iostream>
#include <vector>
#include <iomanip>
#include "solver.h"
#include "MyAlgorithmTest.h"

//Creato un main di test per determinare la grandezza della lista tabu e la soluzione iniziale
// Noi sappiamo che la grandezza della lista non può essere scelta a caso, 
// se troppo piccola permette cicli e non impedisce scelte già prese poco tempo prima,
// se troppo grande rifiuta scelte che sono da tempo nella lista tabu e che potrebbero essere diventate ottimali
int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1);

    Solver pw;
    pw.readProblem("instances/toy.txt");
    pw.setAlgorithms({"PWDefault"});
    pw.addAlgorithm(*new TabuSearchAlgo("Tabu Search Test", pw.getProblem()));
    pw.solve();

    //Dati del problema
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