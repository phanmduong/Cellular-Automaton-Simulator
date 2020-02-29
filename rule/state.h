#ifndef STATE_H
#define STATE_H
#include <string>

using namespace std;

class State{
private: 
    string name;
    string color;
public:
    State(string name, string color);
    ~State();
    string getName();
    string getColor();
};

#endif 
