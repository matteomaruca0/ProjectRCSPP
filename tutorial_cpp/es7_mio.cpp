#include "network.h"
#include <iomanip>
#include <iostream>

int main(int argc, char** argv){
    std::cout << std::fixed << std::setprecision(1);

    int capacitaMax = 14;

    std::cout << "limite nodi | tour | obiettivo\n";
    for (int i = 6; i >= 2; i--)
    {
        auto pw = buildSolver(capacitaMax, i);

        pw->solve();

        if (pw->getNumberOfSolutions() == 0)
        {
            std::cout << i << " | Nessuna soluzione\n";
            continue;
        }
        

        std::cout << i << " | " << pw->getSolutionTourAsString(0) << " | " << pw->getSolutionObjective(0) << "\n";
    }

    return 0;
}