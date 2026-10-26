#include "network.h"
#include <iomanip>
#include <iostream>
#include <list>

// Un algoritmo "fatto in casa": nearest neighbour.
// Parte dall'origine e va sempre al vicino non visitato piu' economico che rispetta le risorse.
class GreedyAlgo : public Algorithm {
public:
    GreedyAlgo(std::string name, Problem* problem) : Algorithm(name, problem) {
        setType(ALGO_HEURISTIC);
    }

    void solve() override {
        setStatus(ALGO_OPTIMIZING);
        Problem* p = getProblem();
        Resource* obj = p->getObj();                        // costi (gia' scalati a interi)
        int cur = p->getOrigin(), dest = p->getDestination();

        std::list<int> tour = {cur};
        std::vector<bool> visited(p->getNumNodes(), false);
        visited[cur] = true;
        std::vector<int> value(p->getNumRes());             // consumo corrente di ogni risorsa
        for (int r = 0; r < p->getNumRes(); r++) value[r] = p->getRes(r)->getInitValue();

        long long arcCost = 0, nodeCost = obj->getNodeCost(cur);
        while (cur != dest) {
            int bestNext = -1, bestCost = INFPLUS;
            for (int next : p->getNeighbors(cur, true)) {   // true = archi uscenti
                if (visited[next]) continue;
                bool feasible = true;
                for (int r = 0; r < p->getNumRes(); r++) {
                    Resource* res = p->getRes(r);
                    if (!res->isFeasible(res->extend(value[r], cur, next), next)) feasible = false;
                }
                int c = obj->getArcCost(cur, next);
                if (feasible && c < bestCost) { bestCost = c; bestNext = next; }
            }
            if (bestNext < 0) { setStatus(ALGO_DONE); return; }   // vicolo cieco: nessuna soluzione
            for (int r = 0; r < p->getNumRes(); r++)
                value[r] = p->getRes(r)->extend(value[r], cur, bestNext);
            arcCost += bestCost;
            nodeCost += obj->getNodeCost(bestNext);
            visited[bestNext] = true;
            tour.push_back(bestNext);
            cur = bestNext;
        }

        Path path;                                          // costruisco la soluzione
        path.setTour(tour);
        path.setArcCost(arcCost);
        path.setNodeCost(nodeCost);
        path.setObjective(arcCost + nodeCost);
        path.setConsumption(value);
        path.setElementary(true);
        path.setStatus(PATH_FEASIBLE);                      // ammissibile, ma NON garantita ottima
        addSolution(path);
        setStatus(ALGO_DONE);
    }

    void resetAlgorithm(int reset_level) override {
        clearSolutions();
        initAlgorithm();
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(1);   // un decimale
    for (int cap : {14, 10, 7}) {
        auto pw = buildSolver(cap);
        pw->setAlgorithms({"PWDefault"});                                   // pool pulito: id 0 = PWDefault
        pw->addAlgorithm(*new GreedyAlgo("Greedy", pw->getProblem()));   // NB: "new", il Solver la cancella lui
        // id 0 = PWDefault (esatto), id 1 = Greedy: li provo uno alla volta
        for (int id : {0, 1}) {
            pw->disableAllAlgorithms();
            pw->enableAlgorithm(id);
            pw->clearSolutions();
            pw->resetAllAlgorithms(0);
            pw->solve();
            std::cout << "capacita' " << cap << (id == 0 ? " | esatto : " : " | greedy : ");
            if (pw->getNumberOfSolutions() == 0) std::cout << "nessuna soluzione\n";
            else std::cout << pw->getSolutionTourAsString(0) << " costo " << pw->getSolutionObjective(0) << "\n";
        }
    }
    return 0;
}
