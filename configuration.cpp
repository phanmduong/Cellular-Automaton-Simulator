#include "configuration.h"

int Configuration::getNumberOfState() const
{
    return numberOfState;
}

void Configuration::setNumberOfState(int value)
{
    numberOfState = value;
}

int Configuration::getWidth() const
{
    return width;
}

void Configuration::setWidth(int value)
{
    width = value;
}

int Configuration::getHeight() const
{
    return height;
}

void Configuration::setHeight(int value)
{
    height = value;
}

string Configuration::getNeightborPostionText() const
{
    return neightborPostionText;
}

void Configuration::setNeightborPostionText(const string &value)
{
    neightborPostionText = value;
}

string Configuration::getRuleName() const
{
    return ruleName;
}

void Configuration::setRuleName(const string &value)
{
    ruleName = value;
}

int Configuration::getLimitGeneration() const
{
    return limitGeneration;
}

void Configuration::setLimitGeneration(int value)
{
    limitGeneration = value;
}

Configuration::Configuration()
{

}
