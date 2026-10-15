#include <iostream>
#include <vector>
#include <iomanip>
#include "solver.h"

/**
 * @brief Esempio 1: Risoluzione di un problema caricato da file di istanza (.txt).
 */
void testRisoluzioneDaFile() {
    std::cout << "\n========================================================" << std::endl;
    std::cout << "  ESEMPIO 1: Risoluzione da file di istanza (toy.txt)" << std::endl;
    std::cout << "========================================================\n" << std::endl;

    // 1. Inizializzazione del solver PathWyse
    Solver solver;

    // 2. Lettura dell'istanza
    std::string instance_path = "instances/toy.txt";
    std::cout << "[Test] Caricamento istanza: " << instance_path << "..." << std::endl;
    solver.readProblem(instance_path);

    // 3. Configurazione degli algoritmi
    solver.setupAlgorithms();

    // 4. Risoluzione del problema RCSPP
    std::cout << "[Test] Risoluzione in corso..." << std::endl;
    solver.solve();

    // 5. Stampa riassuntiva ufficiale del solver
    solver.printBestSolution();

    // 6. Accesso programmatico ai dettagli della soluzione
    if (solver.getNumberOfSolutions() > 0) {
        Path best = solver.getBestSolution();
        std::cout << "[Risultati Estratti]" << std::endl;
        std::cout << "  - Status ottimo?  : " << (best.isOptimal() ? "SI" : "NO") << std::endl;
        std::cout << "  - Valore Obiettivo: " << solver.getSolutionObjective(0) << std::endl;
        std::cout << "  - Nodi del Tour   : " << best.getTourAsString() << std::endl;
        std::cout << "  - Lunghezza Tour  : " << best.getTourLength() << " nodi" << std::endl;
        std::cout << "  - Consumo Risorsa : " << best.getConsumption(0) << std::endl;
    } else {
        std::cout << "[Test] Nessuna soluzione ammissibile trovata." << std::endl;
    }
}

/**
 * @brief Esempio 2: Creazione programmatica di un grafo vincolato (RCSPP) tramite API C++.
 */
void testCreazioneProgrammatica() {
    std::cout << "\n========================================================" << std::endl;
    std::cout << "  ESEMPIO 2: Creazione grafo e modello RCSPP via API C++" << std::endl;
    std::cout << "========================================================\n" << std::endl;

    Solver solver;

    // 1. Creazione e configurazione base del problema
    solver.createProblem();
    solver.setProblemName("EsempioGrafoProgrammatico");
    solver.setNumNodes(5);
    solver.setDirected(true);
    solver.setCyclic(true);
    solver.setOrigin(0);
    solver.setDestination(4);

    // 2. Inizializzazione della topologia (deve precedere l'aggiunta di risorse e archi)
    solver.initProblem();

    // 3. Definizione risorsa di Capacità con limite superiore UB = 12
    int cap_id = solver.addResource("CAP");
    solver.setResBounds(cap_id, 0, 12);

    // 4. Aggiunta archi e rispettivi costi
    struct Arc { int u; int v; double cost; };
    std::vector<Arc> arcs = {
        {0, 1, 54000}, {0, 2, 35000}, {0, 3, 54000},
        {1, 0, 54000}, {1, 2, 87000}, {1, 3, 75000}, {1, 4, 79000},
        {2, 0, 35000}, {2, 1, 87000}, {2, 3, 54000},
        {3, 0, 54000}, {3, 1, 75000}, {3, 2, 54000}, {3, 4, 98000},
        {4, 0, 45000}, {4, 1, 79000}, {4, 2, 59000}, {4, 3, 98000}
    };
    for (const auto& arc : arcs) {
        solver.addArc(arc.u, arc.v);
        solver.setArcCost(arc.u, arc.v, arc.cost);
    }

    // 5. Costi associati ai singoli nodi
    std::vector<std::pair<int, double>> node_costs = {
        {0, -7435}, {1, 0}, {2, -200000}, {3, -7839}, {4, -4000}
    };
    for (const auto& [node, cost] : node_costs) {
        solver.setNodeCost(node, cost);
    }

    // 6. Consumo di risorsa (capacità) associato a ciascun nodo
    std::vector<std::pair<int, int>> node_consumptions = {
        {0, 0}, {1, 2}, {2, 1}, {3, 6}, {4, 6}
    };
    for (const auto& [node, cons] : node_consumptions) {
        solver.setResNodeConsumption(cap_id, node, cons);
    }

    // 7. Costruzione finale, setup e risoluzione
    solver.buildProblem();
    solver.setupAlgorithms();
    solver.solve();

    // 8. Risultati
    solver.printBestSolution();

    Path best = solver.getBestSolution();
    std::cout << "[Risultati Modello Custom]" << std::endl;
    std::cout << "  - Tour Ottimo     : " << best.getTourAsString() << std::endl;
    std::cout << "  - Consumo Capacita: " << best.getConsumption(cap_id) << " / 12" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "============================================================" << std::endl;
    std::cout << "      PROGETTO DI PROVA PATHWYSE - ALGORITMI AVANZATI       " << std::endl;
    std::cout << "============================================================" << std::endl;

    // Test 1: Lettura da file
    testRisoluzioneDaFile();

    // Test 2: Creazione via codice C++
    testCreazioneProgrammatica();

    std::cout << "\n>>> Tutti i test con PathWyse sono stati completati con successo! <<<\n" << std::endl;
    return 0;
}
