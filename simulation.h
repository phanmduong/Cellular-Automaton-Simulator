#ifndef SIMULATION_H
#define SIMULATION_H
#include <configuration.h>
#include <grid.h>
#include <rule.h>
#include <neighbor_position.h>
#include <vector>

class Simulation
{
    Configuration *config;
    Grid *grid;
    vector<Rule*> rules;
    vector<State*> states;

    vector<State*> createStates(int numberOfState);

    Rule* getRuleWithRuleName(string ruleName);

    vector<NeighborPosition*> getNeighborPostions(string neightborPostionText);

    void readInitValueGrid(string const path);
    void writeValueGrid(string const path);
    void getRulesFromFile(string path);

public:
    Simulation(Configuration *config);

    ~Simulation();

    void run();
};

#endif // SIMULATION_H