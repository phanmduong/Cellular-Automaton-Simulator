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

    public:
        Bombers(): Rule((string) "Bombers") {}
        ~Bombers() {}

        virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
            int cnt_live_neighbor = 0;
            for (int i = 0; i < neighbors.size(); i++) {
                if (neighbors[i]->getState() != cell->getState()) cnt_live_neighbor++;
            }
            if (cnt_live_neighbor >= 3 && cnt_live_neighbor <=5) {
                
            }
            
            return states[2];
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
