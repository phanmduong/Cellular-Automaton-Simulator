#ifndef RULE_H
#define RULE_H
#include <string>
#include "cell.h"

using namespace std;

class Rule{
private: 
    string name;
public:
    Rule(string ruleName){
        name = ruleName;
    }
    ~Rule(){}
    string getName(){
        return name;
    }

    virtual State excuteRule(const Cell *cell, Cell neighbors[]) = 0;
};

#endif // RULE_H
