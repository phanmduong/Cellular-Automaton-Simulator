#include "simulation.h"

Rule *Simulation::getRuleWithRuleName(string ruleName)
{
    //TODO: get rule from list rule with rule name (m.duong)
}

vector<NeighborPosition *> Simulation::getNeighborPostions(string neightborPostionText)
{
    //TODO: get NeighborPosition from neightborPostionText (t.kieu)
}

void Simulation::readInitValueGrid(const string path)
{
    //TODO: get input value file with height and width in config, after set value state each cell (q.ban)



    State *state = this->states[value]; // value get in file;
    //TODO: foreach cell with x, y (q.ban)
    this->grid->getCell(x, y)->setState(state);
}

void Simulation::writeValueGrid(const string path)
{
    //TODO: write state of cell to file (q.ban)
}

void Simulation::getRulesFromFile(string path)
{
    //TODO: get list rule in file .so (m.duong)
}

Simulation::Simulation(Configuration *config)
{
    this->config = config;
    this->getRulesFromFile(this->config->getFileRulePath());
}

Simulation::~Simulation()
{
    // TODO: delete rules; (t.kieu)
}

void Simulation::run()
{
    this->states = this->createStates(this->config->getNumberOfState());

    this->readInitValueGrid(this->config->getFileInputValuePath());

    Rule *rule =  this->getRuleWithRuleName(this->config->getRuleName());
    vector<NeighborPosition*> neighborPositions =  this->getNeighborPostions(this->config->getNeightborPostionText());

    this->grid = new Grid(this->config->getWidth(),this->config->getHeight(), neighborPositions, rule);

    //TODO: foreach times (int time;) (t.kieu)

    {
        this->grid->generation();
        string file_output_name = this->config->getDirectoryOutputValuePath() + "/" + to_string(time) + ".txt";
        this->writeValueGrid(file_output_name);
    }
}
