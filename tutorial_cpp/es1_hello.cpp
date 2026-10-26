#include "solver.h"

int main(int argc, char** argv) {
    std::string instance = (argc > 1) ? argv[1] : "instances/toy.txt";

    Solver pw;                    // 1) crea il solver (legge pathwyse.set)
    pw.readProblem(instance);     // 2) legge il problema da file
    pw.setupAlgorithms();         // 3) prepara gli algoritmi
    pw.solve();                   // 4) risolve
    pw.printBestSolution();       // 5) stampa la soluzione migliore
    return 0;
}
