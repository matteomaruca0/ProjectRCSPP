#include "network.h"
#include <iomanip>
#include <iostream>

int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1); 

    auto pw = buildSolver(10);
    //pw->setupAlgorithms(); già chiamato dentro buildSolver
    pw->solve();

    int numSol = pw->getNumberOfSolutions();
    std::cout << "Numero di soluzioni: " << numSol << std::endl;
    pw->rankSolutions("objective");

    for (int i = 0; i < numSol; i++)
    {
        std::cout << "Soluzione " << i << " : " << pw->getSolutionTourAsString(i) << " " << pw->getSolutionObjective(i) << "\n";
    }
    
    return 0;
}