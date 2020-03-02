
#include "simulation.h"
#include <iostream>
#include <fstream>

vector<Rule *> Simulation::getRules() const
{
    return rules;
}

vector<State *> Simulation::getStates() const
{
    return states;
}

vector<State *> Simulation::createStates(int numberOfState)
{
    vector<State *> states;
    for(int i = 0; i < numberOfState; ++i) {
         State *state = new State(to_string(i));
         states.push_back(state);
    }
    return states;
}

Rule *Simulation::getRuleWithRuleName(string ruleName)
{
    //TODO: get rule from list rule with rule name (m.duong)
    for(unsigned int i = 0; i < this->rules.size(); ++i){
        if (this->rules[i]->getName() == ruleName){
            return this->rules[i];
        }
    }

    return nullptr;
}

vector<NeighborPosition *> Simulation::getNeighborPostions(string neighborPostionText)
{
    //TODO: get NeighborPosition from neightborPostionText (t.kieu)
    // an exampple of neighorPositionText: 1 0\n0 -1\n2 3\n2 -1

    vector<string> neighbor_list_str;
    vector<NeighborPosition *> neighbor_list; 

    string detimiter = "\n";
    size_t pos = 0;

    while ( (pos = neighborPostionText.find(detimiter)) != string::npos) { 
        neighbor_list_str.push_back(neighborPostionText.substr(0, pos));
        neighborPostionText.erase(0, pos + detimiter.length());
    }
    

    for (unsigned int i = 0; i <= neighbor_list_str.size() - 1; i++) {
        int blank_position = neighbor_list_str[0].find(" ");
        string x_temp = neighbor_list_str[i].substr(0,blank_position);
        neighbor_list_str[i].erase(0, blank_position + 1);
        string y_temp = neighbor_list_str[i];

        int x = stoi(x_temp);
        int y = stoi(y_temp);

        NeighborPosition a(x, y);
        neighbor_list.push_back(&a);        
    } 

    return neighbor_list;
}

//BanTQ - 3/1/2020 - read the initialized values for the simulator from the configuration
void Simulation::readInitValueGrid(const string path)
{
    unsigned m_width;
    unsigned m_height;
    std::ifstream ifs(path);
    if( !ifs.is_open() ) {
    std::cerr<<"Unable to open "<<path<<". Exiting ..."<<std::endl;
    exit(-1);
    }
    ifs>>m_width>>m_height;
    this->config->setWidth(m_width);
    this->config->setHeight(m_height);
    //read matrix from the input file and set the value to the grid
    int A[m_width][m_height];
    for (int i = 0; i <this->config->getWidth(); ++i)
    {
        for (int j = 0; j < config->getHeight(); ++j)
        {
            ifs >> A[i][j];
            State *state = this->states[A[i][j]];
            this->grid->getCell(i,j)->setState(state);
        }
    }
    ifs.close();
    //State *state = this->states[value]; // value get in file;
    //TODO: for each cell with x, y (q.ban)
    //this->grid->getCell(x, y)->setState(state);
}

//BanTQ - 3/1/2020 - Write the result to a output file
void Simulation::writeValueGrid(const string path)
{
    //TODO: write state of cell to file
    //open file
    std::ofstream ofs(path);

    //write to file
    for (int i = 0; i <this->config->getWidth(); ++i)
    {
        for (int j = 0; j < config->getHeight(); ++j)
        {
            ofs << this->grid->getCell(i,j)->getState() << std::endl;
        }
    }

}

void Simulation::getRulesFromFile(string path)
{

    //TODO: get list rule in file .so (m.duong)
    char path_arr[path.length()];
    strcpy(path_arr, path.c_str());

    void* handle = dlopen(path_arr, RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    typedef void (*rule_t)();
    typedef vector<Rule*> (*rule_t2)();

    rule_t initRules = (rule_t) dlsym(handle, "initRules");
    initRules();
    rule_t2 getAllRules = (rule_t2) dlsym(handle, "getAllRules");
    this->rules = getAllRules();
    dlclose(handle);
}

Simulation::Simulation(Configuration *config)
{
    this->config = config;
}

Simulation::~Simulation()
{
    // TODO: delete rules; (t.kieu) -- done
    rules.erase(rules.begin(), rules.end());
}

void Simulation::run()
{
    this->states = this->createStates(this->config->getNumberOfState());

    this->readInitValueGrid(this->config->getFileInputValuePath());

    Rule *rule =  this->getRuleWithRuleName(this->config->getRuleName());
    vector<NeighborPosition*> neighborPositions =  this->getNeighborPostions(this->config->getNeighborPostionText());

    this->grid = new Grid(this->config->getWidth(),this->config->getHeight(), neighborPositions, rule, this->states);

    //TODO: foreach times (int time;) (t.kieu) -- done??
    for(int time = 1; time <= this->config->getLimitGeneration(); time++)
    {
        this->grid->generation();
        string file_output_name = this->config->getDirectoryOutputValuePath() + "/" + to_string(time) + ".txt";
        this->writeValueGrid(file_output_name);
    }
}
