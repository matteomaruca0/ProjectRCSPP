#include "network.h"
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    // prima di lanciare: in pathwyse.set metti  algo/requested_solutions = 3
    auto pw = buildSolver(10);
    pw->solve();

    int n = pw->getNumberOfSolutions();
    std::cout << "Soluzioni trovate: " << n << "\n";
    pw->rankSolutions("objective");            // ordina dalla migliore
    for (int k = 0; k < n; k++)
        std::cout << k << " " << pw->getSolutionTourAsString(k) << " " << pw->getSolutionObjective(k) << "\n";
    return 0;
}
