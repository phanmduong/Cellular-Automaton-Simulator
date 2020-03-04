#ifndef RULE_H
#define RULE_H
#include <string>
#include <vector>
#include "cell.h"

using namespace std;

class Rule{
private:
    string name;

public:
    Rule(string ruleName);

    ~Rule();

    virtual State* excuteRule(const Cell *cell, vector<Cell*> neighbors, vector<State *> states) = 0;
    string getName() const;
};
#endif
