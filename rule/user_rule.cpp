#include "../rule.h"
#include <vector>
#include <random>
#include <iostream>
std::random_device rd;

vector<Rule*> rules;

void registerRule(Rule *rule){
    rules.push_back(rule);
}

class ConwaysGameOfLife: public Rule
{
     int RULE_SURVIVE[3]={2,3};
     int RULE_BIRTH[1]={3};

    int sizeSurvive = (sizeof(RULE_SURVIVE)/sizeof(*RULE_SURVIVE));
    int sizeBirth = (sizeof(RULE_BIRTH)/sizeof(*RULE_BIRTH));

    int calNeighbors(vector<Cell*> neighbors){
        int totalSum = 0;
        for(unsigned i = 0; i < neighbors.size(); ++i){
            if (stoi(neighbors[i]->getState()->getName()) == 1){
                ++totalSum;
            }
        }
        return totalSum;
    }
    bool ruleContains(int n, int rule[]) {
        int size = (sizeof(rule)/sizeof(*rule));
        for(int i=0; i < size; i++) {
            if ( rule[i] == n )
                return true;
        }
        return false;
    }
public:
    ConwaysGameOfLife(): Rule((string) "Conway's Game of Life"){
    }
    ~ConwaysGameOfLife(){}

    

   State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
        const unsigned int RULE_GENS = states.size();
        const State *state = cell->getState();
        int currentState = stoi(state->getName());
        int indexNextState = 0;
        if ( currentState == 0) {
        int neighborsOn = calNeighbors(neighbors);
            if (ruleContains(neighborsOn, RULE_BIRTH)){
                indexNextState = 1;
            }
        }
        else if ( currentState > 0 && (currentState < (RULE_GENS - 1) || RULE_GENS == 2) ) {
            int neighborsOn = (sizeSurvive == 0) ? 0 : calNeighbors(neighbors);
            bool shouldSurvive = ruleContains(neighborsOn, RULE_SURVIVE);
            if (currentState == 1 && shouldSurvive)
            {
                indexNextState = currentState;
            }
            else if (!shouldSurvive) {
                    indexNextState = (currentState + 1) % RULE_GENS;
            }

            if ( currentState > 1)
                indexNextState = currentState + 1;
        }
        else if (currentState >= (RULE_GENS - 1)) {
            indexNextState = 0;
        }

        return states[indexNextState];
    }
};

//BanTQ - Star War 345/2/4
class StarWars: public Rule
{
    public:
    int RULE_SURVIVE[3]={3,4,5};
     int RULE_BIRTH[1]={2};

    int sizeSurvive = (sizeof(RULE_SURVIVE)/sizeof(*RULE_SURVIVE));
    int sizeBirth = (sizeof(RULE_BIRTH)/sizeof(*RULE_BIRTH));

    int calNeighbors(vector<Cell*> neighbors){
        int totalSum = 0;
        for(unsigned i = 0; i < neighbors.size(); ++i){
            if (stoi(neighbors[i]->getState()->getName()) == 1){
                ++totalSum;
            }
        }
        return totalSum;
    }
    bool ruleContains(int n, int rule[]) {
        int size = (sizeof(rule)/sizeof(*rule));
        for(int i=0; i < size; i++) {
            if ( rule[i] == n )
                return true;
        }
        return false;
    }

    int sameStateNeighbors(vector<Cell*> neighbors, int currentState) {
        // count number of neighbors that are in the SAME STATE with current cell
        int count = 0;
        for (int i = 0; i < neighbors.size(); i++) {
            if (stoi(neighbors[i]->getState()->getName()) == currentState) {
                ++count;
            }
        }
        return count;
    }
    
    StarWars(): Rule((string) "Star Wars") {

    }
    ~StarWars() {}
    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states) {
        const unsigned int RULE_GENS = states.size();
        const State *state = cell->getState();
        int currentState = stoi(state->getName());
        
        // for birth: 0 -> 2
        //for survive: 1 -> 3, 4, 5
            if (currentState == 0) {
                if (calNeighbors(neighbors) == 2)
                    return states[1];
                return states[0];    
            } 
            else {
                int n_sameNeighbors = sameStateNeighbors(neighbors, currentState);
                if (n_sameNeighbors == 3 || n_sameNeighbors == 4 || n_sameNeighbors == 5)
                    return states[currentState];
                else {
                    if (currentState == RULE_GENS - 1) return states[0];
                    return states[currentState + 1];
                }
            }        
    }    
}; 

//BanTQ - Probability rules
class ProbabilisticStarWar: public Rule {
    public:
    int RULE_SURVIVE[3]={3,4,5};
     int RULE_BIRTH[1]={2};

    int sizeSurvive = (sizeof(RULE_SURVIVE)/sizeof(*RULE_SURVIVE));
    int sizeBirth = (sizeof(RULE_BIRTH)/sizeof(*RULE_BIRTH));

    int calNeighbors(vector<Cell*> neighbors){
        int totalSum = 0;
        for(unsigned i = 0; i < neighbors.size(); ++i){
            if (stoi(neighbors[i]->getState()->getName()) == 1){
                ++totalSum;
            }
        }
        return totalSum;
    }
    bool ruleContains(int n, int rule[]) {
        int size = (sizeof(rule)/sizeof(*rule));
        for(int i=0; i < size; i++) {
            if ( rule[i] == n )
                return true;
        }
        return false;
    }

    int sameStateNeighbors(vector<Cell*> neighbors, int currentState) {
        // count number of neighbors that are in the SAME STATE with current cell
        int count = 0;
        for (int i = 0; i < neighbors.size(); i++) {
            if (stoi(neighbors[i]->getState()->getName()) == currentState) {
                ++count;
            }
        }
        return count;
    }
    
    ProbabilisticStarWar(): Rule((string) "Probabilistic Star Wars") {

    }
    ~ProbabilisticStarWar() {}
    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states) {
        //Generate the random value
          //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(1, 1000);
        //assign state with the probabilistics
        //state 0: prob <= 0.5; state 1: prob <= 0.75; state 2: prob <=0.9; state 3: prob <=0.99
 
        const unsigned int RULE_GENS = states.size();
        const State *state = cell->getState();
        int currentState = stoi(state->getName());
        double ran = dis(gen)/1000;
        //if (RULE_GENS != 4) {
        //     std::cerr<<"The number of state is not correct, it should be 4 ..."<<std::endl;
        //  exit(-1);
        //  } 
        //check wether the state satisfies the rules
        //345/2/4
        //if cell's state = i (i: 0 to 4) and neighboring states have 3 or 4 or 5 one that the same as the cell then the the cell changes state
        //otherwise it keep the state as origin
        //if two neighboring states are different from the cell/s state then the cell's state is not changed, otherwise it keeps the original state 
        if (currentState == 0) {
                if (calNeighbors(neighbors) == 2)
                    if (ran <= 0.5) {
                        return states[0]; 
                    } else if (ran > 0.5 && ran <= 0.75) {
                        return states[1];
                    } else if (ran > 0.75 && ran <= 0.9) {
                        return states[2];
                    } else if (ran > 0.9 && ran <= 1)  {
                        return states[3];
                    }   
                return states[0];    
            } 
            else {
                int n_sameNeighbors = sameStateNeighbors(neighbors, currentState);
                if (n_sameNeighbors == 3 || n_sameNeighbors == 4 || n_sameNeighbors == 5) {
                    if (ran <= 0.5) {
                        return states[currentState]; 
                    } else if (ran > 0.5 && ran <= 0.75) {
                        return states[1];
                    } else if (ran > 0.75 && ran <= 0.9) {
                        return states[2];
                    } else if (ran > 0.9 && ran <= 1)  {
                        return states[3];
                    } 
                }      
                else {
                    if (currentState == RULE_GENS - 1) return states[0];
                    return states[(currentState + 1) % RULE_GENS];
                }
            }  
    }
    
};

class Bombers: public Rule {
    // 345/24/25
    // 8 neighbors
    // birth: from state 0 to 1, needs 2 or 4 neighbour which are in state 1;

    int calFiringNeighbors(vector<Cell*> neighbors) { 
        //count number of neighbors that are in state 1
        int count = 0;
        for (int i = 0; i < neighbors.size(); i++) {
            if (stoi(neighbors[i]->getState()->getName()) == 1) {
                ++count;
            }
        }
        return count;
    }

    int sameStateNeighbors(vector<Cell*> neighbors, int currentState) {
        // count number of neighbors that are in the SAME STATE with current cell
        int count = 0;
        for (int i = 0; i < neighbors.size(); i++) {
            if (stoi(neighbors[i]->getState()->getName()) == currentState) {
                ++count;
            }
        }
        return count;//BanTQ updated
    }

    public:
        Bombers(): Rule((string) "Bombers") {}
        ~Bombers() {}

        virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
            const unsigned int RULE_GENS = states.size();
            const State *state = cell->getState();
            int currentState = stoi(state->getName());
            
            // for birth: 0 -> 1
            if (currentState == 0) {
                if (calFiringNeighbors(neighbors) == 2 || calFiringNeighbors(neighbors) == 4)
                    return states[1];
                return states[0];    
            } 
            else {
                int n_sameNeighbors = sameStateNeighbors(neighbors, currentState);
                if (n_sameNeighbors == 3 || n_sameNeighbors == 4 || n_sameNeighbors == 5)
                    return states[currentState];
                else {
                    if (currentState == RULE_GENS - 1) return states[0];
                    return states[currentState + 1];
                }
            }
        }
};


class Bloomerang: public Rule {
    // 234/34678/24
    int calFiringNeighbors(vector<Cell*> neighbors) {
        int cnt = 0;
        for (int i = 0; i < neighbors.size(); i++) {
            if (stoi(neighbors[i]->getState()->getName()) == 1) {
                ++cnt;
            }
        }
        return cnt;
    }

    int sameStateNeighbors(vector<Cell*> neighbors, int currentState) {
        // count number of neighbors that are in the SAME STATE with current cell
        int count = 0;
        for (int i = 0; i < neighbors.size(); i++) {
            if (stoi(neighbors[i]->getState()->getName()) == currentState) {
                ++count;
            }
        }
    }

    public:
    Bloomerang(): Rule((string) "Bloomerang") {}
    ~Bloomerang() {}

    State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states) {
        const unsigned int RULE_GENS = states.size();
        const State *state = cell->getState();
        int currentState = stoi(state->getName());

        if (currentState == 0) {
            if (calFiringNeighbors(neighbors) == 3 || calFiringNeighbors(neighbors) == 4
            ||  calFiringNeighbors(neighbors) == 6
            ||  calFiringNeighbors(neighbors) == 7
            ||  calFiringNeighbors(neighbors) == 8)
                return states[1];
            return states[0];    
        } 
        else {
            int n_sameNeighbors = sameStateNeighbors(neighbors, currentState);
                if (n_sameNeighbors == 3 || n_sameNeighbors == 4 || n_sameNeighbors == 2)
                    return states[currentState];
                else {
                    if (currentState == RULE_GENS - 1) return states[0];
                    return states[currentState + 1];
                }
        }
        
    }

};





//BanTQ - 3/5/2020
class SediMental: public Rule
{
public:
    int RULE_SURVIVE[5]={4,5,6,7,8};
     int RULE_BIRTH[5]={2,5,6,7,8};

    int sizeSurvive = (sizeof(RULE_SURVIVE)/sizeof(*RULE_SURVIVE));
    int sizeBirth = (sizeof(RULE_BIRTH)/sizeof(*RULE_BIRTH));

    int calNeighbors(vector<Cell*> neighbors){
        int totalSum = 0;
        for(unsigned i = 0; i < neighbors.size(); ++i){
            if (stoi(neighbors[i]->getState()->getName()) == 1){
                ++totalSum;
            }
        }
        return totalSum;
    }
    bool ruleContains(int n, int rule[]) {
        int size = (sizeof(rule)/sizeof(*rule));
        for(int i=0; i < size; i++) {
            if ( rule[i] == n )
                return true;
        }
        return false;
    }

    int sameStateNeighbors(vector<Cell*> neighbors, int currentState) {
        // count number of neighbors that are in the SAME STATE with current cell
        int count = 0;
        for (int i = 0; i < neighbors.size(); i++) {
            if (stoi(neighbors[i]->getState()->getName()) == currentState) {
                ++count;
            }
        }
        return count;//BanTQ updated
    }
    SediMental(): Rule((string) "SediMental"){
    }
    ~SediMental(){}

    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
        const unsigned int RULE_GENS = states.size();
        const State *state = cell->getState();
        int currentState = stoi(state->getName());
        
        // for birth: 0 -> 2, 5, 6, 7, 8
        //for survive: 1 -> 4, 5, 6, 7, 8
            if (currentState == 0) {
                if (calNeighbors(neighbors) == 2|| calNeighbors(neighbors) == 5 || 
                calNeighbors(neighbors) == 6|| calNeighbors(neighbors) == 7||calNeighbors(neighbors) == 8)
                    return states[1];
                return states[0];    
            } 
            else {
                int n_sameNeighbors = sameStateNeighbors(neighbors, currentState);
                if (n_sameNeighbors == 4 || n_sameNeighbors == 5 || n_sameNeighbors == 6
                    || n_sameNeighbors == 7 || n_sameNeighbors == 8)
                    return states[currentState];
                else {
                    if (currentState == RULE_GENS - 1) return states[0];
                    return states[(currentState + 1) % RULE_GENS];
                }
            }       
    }
};

class Brain: public Rule
{
    int RULE_BIRTH[1]={2};
    int calFiringNeighbors(vector<Cell*> neighbors){
        int totalSum = 0;
        for(unsigned i = 0; i < neighbors.size(); ++i){
            if (stoi(neighbors[i]->getState()->getName()) == 1){// "firing" is 1
                ++totalSum;
            }
        }
        return totalSum;
    }

public:
    Brain(): Rule((string) "Brian's Brain"){
    }
    ~Brain(){}

    /*
    Brian's Brain	/2/3
    If we name the possible cell values based on a simplistic neural analogy,
    viz. 0 = "ready", 1 = "firing", 2 = "refractory", then this simple rule 
    can be stated thusly: Only a cell in the ready state may fire and it will 
    only do so if exactly 2 of its neighbors are firing. After firing for one step, 
    a cell spends a step in the refractory state before regaining readiness.
    */

    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
        const unsigned int RULE_GENS = states.size();
        const State *state = cell->getState();
        int currentState = stoi(state->getName());
        int indexNextState;

        //For this rule: states[0]=0, states[1]=1, states[2]=2
        if (currentState == 1)//current state is "firing"
        {
            return states[2];//next state is "refactory" without checking neighbor cells' state
        }else if (currentState == 2)//current state is "refactory"
        {
            return states[0];//next state turns back to "ready" without checking neighbor cells' state
        }else //current state is "ready"
        {
            //need to check condition to firing: exactly 2 of its neighbors are firing
            if(calFiringNeighbors(neighbors)==2)
                return states[1];//next state is "firing"
        }
        
        return states[0];
    }
};

extern "C" void initRules(){
    rules.clear();
    registerRule(new ConwaysGameOfLife());//DuongPM
    registerRule(new Bombers()); //t.kieu
    registerRule(new Bloomerang()); //t.kieu
    registerRule(new Brain());//DuongHIV
    registerRule(new StarWars());//BanTQ
    registerRule(new ProbabilisticStarWar());//BanTQ
    registerRule(new SediMental());//BanTQ
}

extern "C" vector<Rule*> getAllRules(){
    return rules;
}
