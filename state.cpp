#include "state.h"

string State::getName() const
{
    return name;
}

void State::setName(const string &value)
{
    name = value;
}

string State::getName() const
{
    return name;
}

string State::getColor() const
{
    return color;
}

State::State(string nameState, string colorState):name(nameState), color(colorState){

}

State::State(string nameState):name(nameState){

}
