//Contiene la classe
#pragma once

#include "solver.h"


class TabuSearchAlgo : public Algorithm {
    public:
        TabuSearchAlgo(std::string name, Problem* problem);

        //Solve
        void solve() override;

        //Reset
        void resetAlgorithm(int reset_level) override;

    protected:
    private:
};