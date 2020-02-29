#include "configuration.h"

int Configuration::getNumberOfState() const
{
    return this->numberOfState;
}

void Configuration::setNumberOfState(int nbState)
{
    this->numberOfState = nbState;
}

int Configuration::getWidth() const
{
    return this->width;
}

void Configuration::setWidth(int value)
{
    this->width = value;
}

int Configuration::getHeight() const
{
    return this->height;
}

void Configuration::setHeight(int value)
{
   this->height = value;
}

string Configuration::getNeightborPostionText() const
{
    return this->neightborPostionText;
}

void Configuration::setNeightborPostionText(const string &value)
{
    this->neightborPostionText = value;
}

string Configuration::getRuleName() const
{
    return this->ruleName;
}

void Configuration::setRuleName(const string &value)
{
    this->ruleName = value;
}

int Configuration::getLimitGeneration() const
{
    return this->limitGeneration;
}

void Configuration::setLimitGeneration(int value)
{
    this->limitGeneration = value;
}

Configuration::Configuration()
{

}
