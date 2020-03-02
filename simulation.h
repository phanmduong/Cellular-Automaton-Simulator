#ifndef SIMULATION_H
#define SIMULATION_H
#include <dlfcn.h>
#include <configuration.h>
#include <grid.h>
#include <rule.h>
#include <neighbor_position.h>
#include <vector>

class Simulation
{
    Configuration *config;
    Grid *grid;
    vector<Rule *> rules;

    vector<State *> createStates(int numberOfState);

    Rule* getRuleWithRuleName(string ruleName);

    vector<NeighborPosition*> getNeighborPostions(string neighborPostionText);

    void readInitValueGrid(string const path);
    void writeValueGrid(string const path);
    void getRulesFromFile(string path);

public:
    Simulation(Configuration *config);

    ~Simulation();

    void run();

    vector<Rule *> getRules() const;
};

#endif // SIMULATION_H
