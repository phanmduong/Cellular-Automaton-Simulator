#ifndef SIMULATION_H
#define SIMULATION_H
#include <iostream>
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
    vector<State *> states;
    void* handleLibRule;

    vector<State *> createStates(int numberOfState);

    Rule* getRuleWithRuleName(string ruleName);

    vector<NeighborPosition*> getNeighborPostions(string neightborPostionText);

    void readInitValueGrid(string const path);
    void writeValueGrid(string const path);
public:
    Simulation(Configuration *config);

    ~Simulation();

    void run();

    vector<Rule *> getRules() const;
    vector<State *> getStates() const;
    void getRulesFromFile(string path);

};

#endif // SIMULATION_H
