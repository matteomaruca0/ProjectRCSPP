#include "network.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>

std::pair<std::vector<int>, double> bruteForce() {
    // Costi degli archi, in entrambe le direzioni
    std::map<std::pair<int, int>, double> costs;

    for (const Edge& edge : EDGES) {
        costs[{edge.i, edge.j}] = edge.cost;
        costs[{edge.j, edge.i}] = edge.cost;
    }

    std::vector<int> intermediate = {1, 2, 3, 4};
    std::vector<int> bestPath;
    double bestCost = std::numeric_limits<double>::max();

    // Prova tutti i sottoinsiemi dei nodi intermedi
    for (int mask = 0; mask < (1 << intermediate.size()); mask++) {
        std::vector<int> subset;

        for (std::size_t i = 0; i < intermediate.size(); i++) {
            if (mask & (1 << i)) {
                subset.push_back(intermediate[i]);
            }
        }

        // next_permutation richiede un vettore ordinato
        std::sort(subset.begin(), subset.end());

        // Prova tutti gli ordini del sottoinsieme
        do {
            std::vector<int> path = {0};
            path.insert(path.end(), subset.begin(), subset.end());
            path.push_back(5);

            double cost = 0.0;
            int consumption = 0;
            bool valid = true;

            // Calcola costo degli archi
            for (std::size_t i = 0; i + 1 < path.size(); i++) {
                auto it = costs.find({path[i], path[i + 1]});

                if (it == costs.end()) {
                    valid = false;
                    break;
                }

                cost += it->second;
            }

            // Calcola consumo della capacità
            for (int node : path) {
                consumption += DEMAND[node];
            }

            // Mantieni solo percorsi esistenti e compatibili con capacità 10
            if (valid && consumption <= 10 && cost < bestCost) {
                bestCost = cost;
                bestPath = path;
            }

        } while (std::next_permutation(subset.begin(), subset.end()));
    }

    return {bestPath, bestCost};
}

int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1);

    auto pw = buildSolver(10);

    pw->setupAlgorithms();
    pw->solve();
    
    if (pw->getNumberOfSolutions() == 0)
    {
        std::cout << "No soluzioni" << std::endl;
        return 0;
    }

    std::vector<int> tour = pw->getSolutionTour(0);
    std::cout << "Soluzione migliore: " << pw->getSolutionTourAsString(0) << "\n";
    std::cout << "Obbiettivo: " << pw->getSolutionObjective(0) << "\n";

    auto result = bruteForce();

    const std::vector<int>& bestPath = result.first;
    double bestCost = result.second;

    std::cout << "Forza bruta: ";

    for (int node : bestPath) {
        std::cout << node << " ";
    }

    std::cout << "costo " << bestCost << "\n";

    return 0;
}