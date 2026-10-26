#include "network.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    auto pw = buildSolver(10);
    pw->solve();
    std::cout << "PathWyse: " << pw->getSolutionTourAsString(0)
              << " obiettivo " << pw->getSolutionObjective(0) << "\n";

    // Controllo con la forza bruta: tutti i cammini semplici 0 -> 5 che rispettano la capacita'
    std::map<std::pair<int, int>, double> cost;
    for (const Edge& e : EDGES) cost[{e.i, e.j}] = cost[{e.j, e.i}] = e.cost;

    double bestCost = std::numeric_limits<double>::max();
    std::vector<int> bestPath;
    std::vector<int> mid = {1, 2, 3, 4};
    for (int mask = 0; mask < (1 << mid.size()); mask++) {       // sottoinsiemi dei nodi intermedi
        std::vector<int> subset;
        for (size_t b = 0; b < mid.size(); b++) if (mask >> b & 1) subset.push_back(mid[b]);
        std::sort(subset.begin(), subset.end());
        do {                                                     // tutte le permutazioni del sottoinsieme
            std::vector<int> path = {0};
            path.insert(path.end(), subset.begin(), subset.end());
            path.push_back(5);
            double tot = 0; int dem = 0; bool ok = true;
            for (size_t k = 0; k + 1 < path.size() && ok; k++) {
                auto it = cost.find({path[k], path[k + 1]});
                if (it == cost.end()) ok = false; else tot += it->second;
            }
            for (int node : path) dem += DEMAND[node];
            if (ok && dem <= 10 && tot < bestCost) { bestCost = tot; bestPath = path; }
        } while (std::next_permutation(subset.begin(), subset.end()));
    }
    std::cout << "Forza bruta: ";
    for (int node : bestPath) std::cout << node << " ";
    std::cout << "costo " << bestCost << "\n";
    return 0;
}
