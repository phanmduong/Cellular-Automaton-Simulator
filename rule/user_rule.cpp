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
extern "C" void initRules(){
    registerRule(new ConwaysGameOfLife());
    registerRule(new GameOfLife2());
}

extern "C" vector<Rule*> getAllRules(){
    return rules;
}
