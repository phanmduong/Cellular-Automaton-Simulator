#include "../rule.h"
#include <vector>

vector<Rule*> rules;

void registerRule(Rule *rule){
    rules.push_back(rule);
}

class ConwaysGameOfLife: public Rule
{
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
public:
    ConwaysGameOfLife(): Rule((string) "Conway's Game of Life"){
    }
    ~ConwaysGameOfLife(){}

    

   State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
        // const unsigned int RULE_GENS = states.size();
        // const State *state = cell->getState();
        // int currentState = stoi(state->getName());
        // int indexNextState;
        // if ( currentState == 0) {
        //             int neighborsOn = calNeighbors(neighbors);
        //                if (ruleContains(neighborsOn, RULE_BIRTH)){
        //                    indexNextState = 1;
        //                }
        //            }
        //            else if ( currentState > 0 && (currentState < (RULE_GENS - 1) || RULE_GENS == 2) ) {
        //                int neighborsOn = (sizeSurvive == 0) ? 0 : calNeighbors(neighbors);
        //                bool shouldSurvive = ruleContains(neighborsOn, RULE_SURVIVE);
        //                if (currentState == 1 && shouldSurvive)
        //                {
        //                    indexNextState = currentState;
        //                }
        //                else if (!shouldSurvive) {
        //                        indexNextState = (currentState + 1) % RULE_GENS;
        //                }

        //                if ( currentState > 1)
        //                    indexNextState = currentState + 1;
        //            }
        //            else if (currentState >= (RULE_GENS - 1)) {
        //                indexNextState = 0;
        //            }

        // return states[indexNextState];
        return states[0];
    }
};

class GameOfLife2: public Rule
{
public:
    GameOfLife2(): Rule((string) "Game of Life2"){
    }
    ~GameOfLife2(){}

    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
        return states[1];
    }
};

<<<<<<< HEAD
class StarWars: public Rule
{
    public:
    StarWars(): Rule((string) "Star Wars") {

    }
    ~StarWars() {}
    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states) {
        State* storeState;
        for (int i = 0; i < size(states); ++i) {
            if (cell->getState() == states[i]) {
                int n = 0;
                for (int j = 0; j < size(neighbors);++j) {                    
                    if (neighbors[j]->getState() == cell->getState()) {
                        n += 1;
                    }

                }
                if (n != 3 || n != 4 || n != 5) {
                    return cell->getState();
                }
            }
        }
    }
} 
=======


class Bombers: public Rule {
    // 345/24/25
    // 8 neighbors

    int RULE_SURVIVE[3] = {3,4,5};
    int RUlE_BIRTH[2] = {2,4}; 
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
                    if (currentState == 24) return states[0];
                    // 24 is the last state
                    return states[currentState + 1];
                }
            }
        }
    };




class SediMental: public Rule
{
public:
    SediMental(): Rule((string) "SediMental"){
    }
    ~SediMental(){}

    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
        
        
        return states[1];
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

>>>>>>> dev
extern "C" void initRules(){
    registerRule(new ConwaysGameOfLife());
    registerRule(new GameOfLife2());
    registerRule(new Bombers()); //t.kieu
}

extern "C" vector<Rule*> getAllRules(){
    return rules;
}
