#include "network.h"
#include <iomanip>
#include <iostream>

//Capacità = Numero massimo della risorsa CAP (vedi network.h) che puo usare
int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1);

    std::cout << "Capacita | n. Soluzioni | tour | obiettivo" << "\n";
    for (int i = 2; i < 15; i++)
    {
        auto pw = buildSolver(i);

        pw->setupAlgorithms();
        pw->solve();

        if (pw->getNumberOfSolutions() == 0)
        {
            std::cout << "Non risolvibile con una capacità di: " << i << "\n";
            continue; 
        }

        std::cout << i << " | " << pw->getNumberOfSolutions() << " | " << pw->getSolutionTourAsString(0) << " | " << pw->getSolutionObjective(0) << "\n";
        
    }
    

    return 0;
}