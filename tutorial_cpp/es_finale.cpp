#include "solver.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

const int N = 7;
struct Edge { int i, j; double cost; };
const std::vector<Edge> EDGES = {{0, 1, 3}, {0, 2, 5}, {1, 2, 2}, {1, 3, 6}, {2, 3, 3}, {2, 4, 7},
                                 {3, 4, 2}, {3, 5, 4}, {4, 5, 3}, {4, 6, 6}, {5, 6, 2}};
const std::vector<double> BONUS  = {0, 0, -4, -1, -5, 0, 0};   // costo dei nodi (negativo = guadagno)
const std::vector<int>    DEMAND = {0, 2, 3, 1, 4, 2, 0};      // consumo di capacita'

std::unique_ptr<Solver> build(int capUb, int nodeLimit) {
    auto pw = std::make_unique<Solver>();
    pw->createProblem();
    pw->setProblemName("Finale");
    pw->setNumNodes(N);
    pw->setDirected(true);
    pw->setCyclic(true);
    pw->setOrigin(0);
    pw->setDestination(6);
    pw->initProblem();
    for (const Edge& e : EDGES)
        for (auto [a, b] : {std::pair{e.i, e.j}, std::pair{e.j, e.i}}) {
            pw->addArc(a, b);
            pw->setArcCost(a, b, e.cost);
        }
    for (int node = 0; node < N; node++) pw->setNodeCost(node, BONUS[node]);
    int cap = pw->addResource("CAP");
    pw->setResBounds(cap, 0, capUb);
    for (int node = 0; node < N; node++) pw->setResNodeConsumption(cap, node, DEMAND[node]);
    int nl = pw->addResource("NODELIM");
    pw->setResBounds(nl, 0, nodeLimit);
    pw->buildProblem();
    pw->setupAlgorithms();
    return pw;
}

double tourCost(Solver& pw, const std::vector<int>& tour) {
    double total = 0;
    for (size_t k = 0; k + 1 < tour.size(); k++) total += pw.getArcCost(tour[k], tour[k + 1]);
    for (int node : tour) total += pw.getNodeCost(node);
    return total;
}

// Forza bruta: tutti i cammini semplici 0 -> 6 che rispettano capacita' e numero di nodi
std::optional<double> bruteForce(int capUb, int nodeLimit) {
    std::map<std::pair<int, int>, double> cost;
    for (const Edge& e : EDGES) cost[{e.i, e.j}] = cost[{e.j, e.i}] = e.cost;
    std::optional<double> best;
    for (int mask = 0; mask < (1 << (N - 2)); mask++) {
        std::vector<int> subset;
        for (int b = 0; b < N - 2; b++) if (mask >> b & 1) subset.push_back(b + 1);
        do {
            std::vector<int> p = {0};
            p.insert(p.end(), subset.begin(), subset.end());
            p.push_back(6);
            if ((int)p.size() > nodeLimit) continue;
            int dem = 0; for (int node : p) dem += DEMAND[node];
            if (dem > capUb) continue;
            double tot = 0; bool ok = true;
            for (size_t k = 0; k + 1 < p.size() && ok; k++) {
                auto it = cost.find({p[k], p[k + 1]});
                if (it == cost.end()) ok = false; else tot += it->second;
            }
            if (!ok) continue;
            for (int node : p) tot += BONUS[node];
            if (!best || tot < *best) best = tot;
        } while (std::next_permutation(subset.begin(), subset.end()));
    }
    return best;
}

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    std::cout << "cap | max nodi | PathWyse                | obiettivo | forza bruta | ok?\n";
    for (auto [capUb, limit] : std::vector<std::pair<int, int>>{{12, 7}, {8, 7}, {8, 5}, {6, 5}, {4, 4}}) {
        auto pw = build(capUb, limit);
        pw->solve();
        auto bf = bruteForce(capUb, limit);
        std::cout << std::setw(3) << capUb << " | " << std::setw(8) << limit << " | ";
        if (pw->getNumberOfSolutions() == 0) {
            std::cout << "nessuna soluzione       |           | "
                      << (bf ? std::to_string(*bf) : "nessuna") << " | " << (!bf ? "si" : "NO") << "\n";
            continue;
        }
        double obj = pw->getSolutionObjective(0);
        bool ok = bf && obj == tourCost(*pw, pw->getSolutionTour(0)) && obj == *bf;
        std::cout << std::left << std::setw(23) << pw->getSolutionTourAsString(0) << std::right
                  << " | " << std::setw(9) << obj << " | " << std::setw(11) << (bf ? *bf : 0.0)
                  << " | " << (ok ? "si" : "NO") << "\n";
    }
    return 0;
}
