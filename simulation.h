#ifndef SIMULATION_H
#define SIMULATION_H
#include <configuration.h>
#include <grid.h>
#include <rule.h>

class Simulation
{
    Configuration config;
    Grid grid;
    vector<Rule*> rules;
    string fileRulePath;

    string readInitValueGrid(string const path);
    void writeValueGrid(string const path);
    void getRulesFromFile();

public:
    Simulation(Configuration config, string fileRulePath); // Kieu

    void run();
};

#endif // SIMULATION_H
