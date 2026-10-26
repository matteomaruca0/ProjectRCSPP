#pragma once
// Rete di esempio del tutorial: 6 nodi, origine 0, destinazione 5.
#include "solver.h"
#include <memory>
#include <vector>
#include <tuple>

struct Edge { int i, j; double cost; };

inline const std::vector<Edge> EDGES = {{0, 1, 4}, {0, 2, 2}, {1, 2, 1}, {1, 3, 5}, {2, 3, 8},
                                        {2, 4, 10}, {3, 4, 2}, {3, 5, 6}, {4, 5, 3}};
inline const std::vector<int> DEMAND = {0, 3, 2, 4, 5, 0};   // consumo di capacita' per nodo

// Il Solver non si puo' copiare (contiene un mutex): lo restituiamo con un unique_ptr.
inline std::unique_ptr<Solver> buildSolver(int capUb, int nodeLimit = -1) {
    auto pw = std::make_unique<Solver>();
    pw->createProblem();
    pw->setProblemName("Rete6");
    pw->setNumNodes(6);
    pw->setDirected(true);
    pw->setCyclic(true);
    pw->setOrigin(0);
    pw->setDestination(5);
    pw->initProblem();                       // prepara le strutture interne
    for (const Edge& e : EDGES)              // archi e costi, nei due versi
        for (auto [a, b] : {std::pair{e.i, e.j}, std::pair{e.j, e.i}}) {
            pw->addArc(a, b);
            pw->setArcCost(a, b, e.cost);
        }
    for (int node = 0; node < 6; node++) pw->setNodeCost(node, 0);

    int cap = pw->addResource("CAP");
    pw->setResBounds(cap, 0, capUb);
    for (int node = 0; node < 6; node++) pw->setResNodeConsumption(cap, node, DEMAND[node]);
    if (nodeLimit >= 0) {                    // servira' al passo 7
        int nl = pw->addResource("NODELIM");
        pw->setResBounds(nl, 0, nodeLimit);
    }
    pw->buildProblem();
    pw->setupAlgorithms();
    return pw;
}
