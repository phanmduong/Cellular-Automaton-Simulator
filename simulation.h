#ifndef SIMULATION_H
#define SIMULATION_H
#include <iostream>
#include <dlfcn.h>
#include <configuration.h>
#include <grid.h>
#include <rule.h>
#include <neighbor_position.h>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include <QObject>

class Simulation : public QObject
{
    Q_OBJECT;
    Configuration *config;
    Grid *grid;
    vector<Rule *> rules;
    vector<State *> states;
    void* handleLibRule;
    bool isStop;
    bool isPause;

    vector<State *> createStates(int numberOfState);

    Rule* getRuleWithRuleName(string ruleName);

    vector<NeighborPosition*> getNeighborPostions(string neightborPostionText);

    void readInitValueGrid(string const path);
    void writeValueGrid(string const path);

    void clearStates();
    void clearRules();

public:
    Simulation(Configuration *config);

    ~Simulation();

    vector<Rule *> getRules() const;
    vector<State *> getStates() const;
    void getRulesFromFile(string path);

    Grid *getGrid() const;
    void quit();

    void setIsPause(bool value);

    bool getIsPause() const;

signals:
    void progressChanged(float value);
    void startGeneration();
    void finished();


    // QThread interface
public slots:
    void run();

};

#endif // SIMULATION_H
