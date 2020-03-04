
#include "simulation.h"
#include <iostream>
#include <fstream>
#include <QDebug>

vector<Rule *> Simulation::getRules() const
{
    return rules;
}

vector<State *> Simulation::getStates() const
{
    return states;
}

Grid *Simulation::getGrid() const
{
    return grid;
}

string rgb2hex(int r, int g, int b, bool with_head)
{
  stringstream ss;
  if (with_head)
    ss << "#";
  ss << std::hex << (r << 16 | g << 8 | b );
  return ss.str();
}

vector<State *> Simulation::createStates(int numberOfState)
{
    this->clearStates();
    vector<State *> states;
    int range = 0;
    if (numberOfState - 1 <= 1){
        range = 255;
    } else{
        range = (int) (255 / (numberOfState - 1));
    }

    for(int i = 0; i < numberOfState; ++i) {
        int colorNumber = range * i;
        string color = rgb2hex(colorNumber, colorNumber, colorNumber, true);
        State *state = new State(to_string(i), color);
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

    while (neighborPostionText[neighborPostionText.size()-1] == '\n') {
        neighborPostionText.erase(neighborPostionText.size()-1,1);
    }

    while ( (pos = neighborPostionText.find(detimiter)) != string::npos ) {
        neighbor_list_str.push_back(neighborPostionText.substr(0, pos));
        neighborPostionText.erase(0, pos + detimiter.length());
    }
    neighbor_list_str.push_back(neighborPostionText);

    for (int i = 0; i <= neighbor_list_str.size() - 1; i++) {
        int blank_position = neighbor_list_str[i].find(" ");
        string x_temp = neighbor_list_str[i].substr(0,blank_position);
        neighbor_list_str[i].erase(0, blank_position + 1);
        string y_temp = neighbor_list_str[i];

        int x = stoi(x_temp);
        int y = stoi(y_temp);

        NeighborPosition *a = new NeighborPosition(x, y);
        neighbor_list.push_back(a);
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

//    ifs>>m_width>>m_height;
//    this->config->setWidth(m_width);
//    this->config->setHeight(m_height);

    m_width = this->config->getWidth();
    m_height = this->config->getHeight();
    //read matrix from the input file and set the value to the grid
    int A[m_width][m_height];
    for (int j = 0; j < this->config->getHeight(); ++j){
    for (int i = 0; i <this->config->getWidth(); ++i)
        {
            ifs >> A[i][j];
            State *state = this->states[A[i][j]];
            if (this->grid->getCell(i,j) != nullptr){
                this->grid->getCell(i,j)->setState(state);
            }

        }
    }
    ifs.close();
}

//BanTQ - 3/1/2020 - Write the result to a output file
void Simulation::writeValueGrid(const string path)
{
    //TODO: write state of cell to file
    //open file
    std::ofstream ofs(path);
    //write to file
    for (int j = 0; j < config->getHeight(); ++j)
    {

    for (int i = 0; i <this->config->getWidth(); ++i)
    {   
            ofs << this->grid->getCell(i,j)->getState()->getName() << " ";
        }
        ofs << std::endl;
    }

}

void Simulation::clearRules()
{
    this->rules.clear();
}

void Simulation::clearStates()
{
    for(unsigned int i = 0; i < this->states.size(); ++i){
        delete states[i];
    }
    this->states.clear();
}

Simulation::Simulation(Configuration *config)
{
    this->config = config;
}

void Simulation::getRulesFromFile(string path)
{
    this->clearRules();
    //TODO: get list rule in file .so (m.duong)
    char path_arr[path.length()];
    strcpy(path_arr, path.c_str());

    this->handleLibRule = dlopen(path_arr, RTLD_LAZY);
    if (!this->handleLibRule) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    typedef void (*rule_t)();
    typedef vector<Rule*> (*rule_t2)();

    rule_t initRules = (rule_t) dlsym(this->handleLibRule, "initRules");
    initRules();
    rule_t2 getAllRules = (rule_t2) dlsym(this->handleLibRule, "getAllRules");
    this->rules = getAllRules();
//    dlclose(handle);
}

Simulation::~Simulation()
{
    // TODO: delete rules; (t.kieu) -- done
    dlclose(this->handleLibRule);
    rules.erase(rules.begin(), rules.end());
}

void Simulation::run()
{
    this->states = this->createStates(this->config->getNumberOfState());

    Rule *rule =  this->getRuleWithRuleName(this->config->getRuleName());
    vector<NeighborPosition*> neighborPositions =  this->getNeighborPostions(this->config->getNeighborPostionText());

    this->grid = new Grid(this->config->getWidth(),this->config->getHeight(), neighborPositions, rule, this->states);

    this->readInitValueGrid(this->config->getFileInputValuePath());

    emit startGeneration();

    //TODO: foreach times (int time;) (t.kieu) -- done??
    for(int time = 1; time <= this->config->getLimitGeneration(); time++)
    {
        this->grid->generation();
        string file_output_name = this->config->getDirectoryOutputValuePath() + "/" + to_string(time) + ".txt";
        this->writeValueGrid(file_output_name);
        emit progressChanged(time*100/this->config->getLimitGeneration());
        std::this_thread::sleep_for(std::chrono::milliseconds(this->config->getIntervalTime()));
    }
    emit finished();
}
