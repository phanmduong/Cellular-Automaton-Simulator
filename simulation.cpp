
#include "simulation.h"

Rule *Simulation::getRuleWithRuleName(string ruleName)
{
    //TODO: get rule from list rule with rule name (m.duong)
}

vector<NeighborPosition *> Simulation::getNeighborPostions(string neighborPostionText)
{
    //TODO: get NeighborPosition from neightborPostionText (t.kieu)
    // an exampple of neighorPositionText: 1 0\n0 -1\n2 3\n2 -1

    vector<string> neighbor_list_str;
    vector<NeighborPosition *> neighbor_list; 

    while (neighborPostionText.length() > 4 ) {
        // value "4": need to fix 
        // still brainstorming :3
        string temp = neighborPostionText.substr(0, neighborPostionText.find("\n"));
        neighbor_list_str.push_back(temp);
        neighborPostionText.erase(0,neighborPostionText.find("\n") + 1);
    }
    neighbor_list_str.push_back(neighborPostionText);

    for (int i = 0; i <= neighbor_list_str.size() - 1; i++) {
        int blank_position = neighbor_list_str[0].find(" ");
        string x_temp = neighbor_list_str[i].substr(0,blank_position);
        neighbor_list_str[i].erase(0, blank_position + 1);
        string y_temp = neighbor_list_str[i];

        int x = stoi(x_temp);
        int y = stoi(y_temp);

        NeighborPosition a(x, y);
        neighbor_list.push_back(&a);

        return neighbor_list;
    } 
    
    
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
    // TODO: delete rules; (t.kieu) -- done
    rules.erase(rules.begin(), rules.end());
}

void Simulation::run()
{
    this->states = this->createStates(this->config->getNumberOfState());

    this->readInitValueGrid(this->config->getFileInputValuePath());

    Rule *rule =  this->getRuleWithRuleName(this->config->getRuleName());
    vector<NeighborPosition*> neighborPositions =  this->getNeighborPostions(this->config->getNeightborPostionText());

    this->grid = new Grid(this->config->getWidth(),this->config->getHeight(), neighborPositions, rule);

    //TODO: foreach times (int time;) (t.kieu) -- done??
    for(int time = 1; time <= this->config->getLimitGeneration(); time++) 
    {
        this->grid->generation();
        string file_output_name = this->config->getDirectoryOutputValuePath() + "/" + to_string(time) + ".txt";
        this->writeValueGrid(file_output_name);
    }
}
