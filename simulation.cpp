
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

void Simulation::setIsPause(bool value)
{
    isPause = value;
}

bool Simulation::getIsPause() const
{
    return isPause;
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
    int m_width;
    int m_height;
    int number_of_state;
    std::ifstream ifs(path);
    if( !ifs.is_open() ) {
        emit this->message("Unable to open "+QString::fromStdString(path)+". Exiting ...");
        return;
    }

    ifs>>m_height>>m_width>>number_of_state;

    m_width = this->config->getWidth();
    m_height = this->config->getHeight();
    //read matrix from the input file and set the value to the grid
    int stateName;

    for (int j = 0; j < this->config->getHeight(); ++j){
        for (int i = 0; i <this->config->getWidth(); ++i)
            {
                ifs >> stateName;
                if (stateName > this->config->getNumberOfState() - 1) {
                    this->isStop = true;
                    emit this->message("Input file invalid");
                    return;
                }

                State *state = this->states[stateName];

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
    try {
        std::ofstream ofs(path);
        //write to file
        for (int j = 0; j < config->getHeight(); ++j) {
            for (int i = 0; i <this->config->getWidth(); ++i) {
                ofs << this->grid->getCell(i,j)->getState()->getName() << " ";
            }
            ofs << std::endl;
        }
    } catch (exception e) {
        emit this->message(e.what());
        return;
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
        this->config->setFileRulePath("");
        emit this->message("Rule file invalid");
        return;
    }
    typedef void (*rule_t)();
    typedef vector<Rule*> (*rule_t2)();

    try {
        rule_t initRules = (rule_t) dlsym(this->handleLibRule, "initRules");
        initRules();
        rule_t2 getAllRules = (rule_t2) dlsym(this->handleLibRule, "getAllRules");
        this->rules = getAllRules();
    } catch (...) {
        this->config->setFileRulePath("");
        emit this->message("Rule file invalid");
        return;
    }

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
    this->isStop = false;
    this->isPause = false;
    this->states = this->createStates(this->config->getNumberOfState());

    Rule *rule =  this->getRuleWithRuleName(this->config->getRuleName());
    vector<NeighborPosition*> neighborPositions =  this->getNeighborPostions(this->config->getNeighborPostionText());

    this->grid = new Grid(this->config->getWidth(),this->config->getHeight(), neighborPositions, rule, this->states);

    this->readInitValueGrid(this->config->getFileInputValuePath());

    if (this->isStop){
        emit finished();
        return;
    }

    emit startGeneration();

    //TODO: foreach times (int time;) (t.kieu) -- done??
    for(int time = 1; time <= this->config->getLimitGeneration(); time++)
    {
        if (this->isStop) break;
        while(this->isPause){
            qDebug() << "pause";
            if (this->isStop){
                emit finished();
                return;
            }
        }


        this->grid->generation();
        string file_output_name = this->config->getDirectoryOutputValuePath() + "/" + to_string(time) + ".txt";
        this->writeValueGrid(file_output_name);
        emit progressChanged(time*100/this->config->getLimitGeneration());
        std::this_thread::sleep_for(std::chrono::milliseconds(this->config->getIntervalTime()));
    }
    emit finished();
}

void Simulation::quit()
{
    this->isStop = true;
}
