#include "network.h"
#include <iomanip>
#include <iostream>

int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1);

    auto pw = buildSolver(10);

    pw->setAlgorithms({"PWDefault", "PWBucket"}, {false, false});
    //std::vector<int> id = pw->getEnabledAlgorithms(); restituisce quelli attivi

    //Prima solo PWDefault
    pw->enableAlgorithm(0); // enable PWDefault algorithm
    std::vector<int> id = pw->getEnabledAlgorithms();

    pw->solve();

    std::cout << "Solo PWDefault:\n";
    std::cout << "Algoritmi attivi: " << id.size() << "\n";
    if (pw->getNumberOfSolutions() == 0)
    {
        std::cout << "Non risolvibile" << std::endl;
    } else {
        std::cout << "Soluzione: " << pw->getSolutionTourAsString(0) << " | " << pw->getSolutionObjective(0) << "\n";
    }

    //puliamo
    pw->clearSolutions();
    pw->resetAllAlgorithms(0);

    //Disabilita il primo
    pw->disableAlgorithm(0);
    
    //Dopo solo PWBucket
    pw->enableAlgorithm(1); // enable PWBucket algorithm
    id = pw->getEnabledAlgorithms();

    pw->solve();

    std::cout << "Solo PWBucket:\n";
    std::cout << "Algoritmi attivi: " << id.size() << "\n";
    if (pw->getNumberOfSolutions() == 0)
    {
        std::cout << "Non risolvibile" << std::endl;
    } else {
        std::cout << "Soluzione: " << pw->getSolutionTourAsString(0) << " | " << pw->getSolutionObjective(0) << "\n";
    }


    return 0;
}