#include "state.h"


// constructors
State::State(string nameState, string colorState):name(nameState), color(colorState){

}

State::State(string nameState):name(nameState){

}


// destructor
State::~State() {}

// getters
string State::getName() const
{
    return name;
}

string State::getColor() const
{
    return color;
}

