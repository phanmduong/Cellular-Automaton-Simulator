#include "configuration.h"

//bantq code 29/2/2020
//get state
int Configuration::getNumberOfState() const
{
    return this->numberOfState;
}

//set state
void Configuration::setNumberOfState(int nbState)
{
    this->numberOfState = nbState;
}

//get width
int Configuration::getWidth() const
{
    return this->width;
}

//set width
void Configuration::setWidth(int value)
{
    this->width = value;
}

//get height
int Configuration::getHeight() const
{
    return this->height;
}

//set height
void Configuration::setHeight(int value)
{
   this->height = value;
}

string Configuration::getRuleName() const
{
    return this->ruleName;
}

//set rule
void Configuration::setRuleName(const string &value)
{
    this->ruleName = value;
}

//get generation
int Configuration::getLimitGeneration() const
{
    return this->limitGeneration;
}

//set generation
void Configuration::setLimitGeneration(int value)
{
    this->limitGeneration = value;
}

string Configuration::getFileRulePath() const
{
    return fileRulePath;
}

string Configuration::getFileInputValuePath() const
{
    return fileInputValuePath;
}

string Configuration::getDirectoryOutputValuePath() const
{
    return directoryOutputValuePath;
}

string Configuration::getNeighborPostionText() const
{
    return neighborPostionText;
}

void Configuration::setNeighborPostionText(const string &value)
{
    neighborPostionText = value;
}

Configuration::Configuration()
{

}

Configuration::~Configuration()
{

}