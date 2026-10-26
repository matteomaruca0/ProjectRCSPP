#include "network.h"
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    std::cout << "limite nodi | tour | obiettivo\n";
    for (int limit : {6, 5, 4, 3, 2}) {
        auto pw = buildSolver(14, limit);       // capacita' larga: conta solo il limite di nodi
        pw->solve();
        if (pw->getNumberOfSolutions() == 0)
            std::cout << limit << " | nessuna soluzione\n";
        else
            std::cout << limit << " | " << pw->getSolutionTourAsString(0) << " | " << pw->getSolutionObjective(0) << "\n";
    }
    return 0;
}
