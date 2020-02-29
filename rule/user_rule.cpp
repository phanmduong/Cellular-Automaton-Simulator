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

    virtual State excuteRule(const Cell *cell, Cell neighbors[]){

    }
};

class GameOfLife2: public Rule
{
public:
    GameOfLife2(): Rule((string) "Game of Life2"){
    }
    ~GameOfLife2(){}

    virtual State excuteRule(const Cell *cell, Cell neighbors[]){

    }
};

extern "C" void initRules(){
    registerRule(new GameOfLife());
    registerRule(new GameOfLife2());
}

extern "C" vector<Rule*> getAllRules(){
    return rules;
}
