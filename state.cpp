#include "state.h"


State::State(string nameState, string colorState):name(nameState), color(colorState){

}

State::State(string nameState):name(nameState){

}

string State::getName() const
{
    return name;
}

void State::setName(const string &value)
{
    this->name = value;
}

string State::getColor() const
{
    return name;
}

void State::setColor(const string &color)
{
    this->color = color;
}


