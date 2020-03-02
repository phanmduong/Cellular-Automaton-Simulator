#include "../rule.h";
#include <vector>;

vector<Rule*> rules;

void registerRule(Rule *rule){
    rules.push_back(rule);
}

class GameOfLife: public Rule
{
public:
    GameOfLife(): Rule((string) "Game of Life"){
    }
    ~GameOfLife(){}

    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states){
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
    registerRule(new GameOfLife());
    registerRule(new GameOfLife2());
}

extern "C" vector<Rule*> getAllRules(){
    return rules;
}
