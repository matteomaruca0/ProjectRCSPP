#include "network.h"
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    auto pw = buildSolver(10);

    // due algoritmi esatti: id 0 = PWDefault, id 1 = PWBucket (il secondo parte spento)
    pw->setAlgorithms({"PWDefault", "PWBucket"}, {true, false});
    std::cout << "Attivi all'inizio: " << pw->getEnabledAlgorithms().size()
              << " (id " << pw->getEnabledAlgorithms()[0] << ")\n";
    pw->solve();
    std::cout << "Solo PWDefault -> " << pw->getSolutionTourAsString(0) << " " << pw->getSolutionObjective(0) << "\n";

    // spengo il primo, accendo il secondo, azzero e risolvo di nuovo
    pw->disableAlgorithm(0);
    pw->enableAlgorithm(1);
    pw->resetAllAlgorithms(0);
    pw->clearSolutions();
    std::cout << "Attivi ora: id " << pw->getEnabledAlgorithms()[0] << "\n";
    pw->solve();
    std::cout << "Solo PWBucket  -> " << pw->getSolutionTourAsString(0) << " " << pw->getSolutionObjective(0) << "\n";
    return 0;
}
