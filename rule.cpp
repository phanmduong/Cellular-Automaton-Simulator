#include "rule.h"

Rule::Rule(string ruleName)
{
    this->name = ruleName;
}

Rule::~Rule()
{

}

string Rule::getName() const
{
    return name;
}
