#include "network.h"
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    std::cout << "UB capacita' | n. soluzioni | tour | obiettivo\n";
    for (int ub = 2; ub <= 14; ub++) {
        auto pw = buildSolver(ub);
        pw->solve();
        if (pw->getNumberOfSolutions() == 0)
            std::cout << ub << " | 0 | (nessun cammino ammissibile)\n";
        else
            std::cout << ub << " | " << pw->getNumberOfSolutions() << " | "
                      << pw->getSolutionTourAsString(0) << " | " << pw->getSolutionObjective(0) << "\n";
    }
    return 0;
}
