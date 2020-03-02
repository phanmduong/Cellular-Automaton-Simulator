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

    

    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
        const unsigned int RULE_GENS = states.size();
        const State *state = cell->getState();
        int currentState = stoi(state->getName());
        int indexNextState;
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



class Bombers: public Rule {
    // 345/24/25
    // 8 neighbors

    int RULE_SURVIVE[3] = {3,4,5};
    int RUlE_BIRTH[2] = {2,4}; 
    // birth: from 0 to 1, needs 2 or 4 neighbour which are in state 1;

    public:
        Bombers(): Rule((string) "Bombers") {}
        ~Bombers() {}

        virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
            const unsigned int n_states = states.size();
            int currentState = stoi(cell->getState()->getName());
            int nextState;

            int cnt_same_neighbor = 0; 
            int cnt_live_neighbor = 0;

            

            for (int i = 0; i < neighbors.size(); i++) {
                if (neighbors[i]->getState() != cell->getState()) cnt_live_neighbor++;
            }
            if (cnt_live_neighbor >= 3 && cnt_live_neighbor <=5) {
                
            }
            
            return states[2];
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

extern "C" void initRules(){
    registerRule(new ConwaysGameOfLife());
    registerRule(new GameOfLife2());
    registerRule(new Bombers()); //t.kieu
}

extern "C" vector<Rule*> getAllRules(){
    return rules;
}
