#include "rule.h";
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

class Bombers: public Rule {
    // 345/24/25
    // 8 neighbors
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
        
}

extern "C" void initRules(){
    registerRule(new GameOfLife());
    registerRule(new GameOfLife2());
    registerRule(new Bombers()); //t.kieu
}

extern "C" vector<Rule*> getAllRules(){
    return rules;
}
