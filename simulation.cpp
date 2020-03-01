#include "simulation.h"

vector<Rule *> Simulation::getRules() const
{
    return rules;
}

vector<State *> Simulation::getStates() const
{
    return states;
}

Rule *Simulation::getRuleWithRuleName(string ruleName)
{
    //TODO: get rule from list rule with rule name (m.duong)
    for(int i = 0; i < this->rules.size(); ++i){
        if (this->rules[i]->getName() == ruleName){
            return this->rules[i];
        }
    }
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
    void* handle = dlopen("./rule.so", RTLD_LAZY);
    typedef void (*rule_t)();
    typedef vector<Rule*> (*rule_t2)();
    dlerror();
    rule_t initRules = (rule_t) dlsym(handle, "initRules");
    initRules();
    rule_t2 getAllRules = (rule_t2) dlsym(handle, "getAllRules");
    this->rules = getAllRules();
    dlclose(handle);
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
