#ifndef STATE_H
#define STATE_H
#include <string>

using namespace std;

class State
{
    string name;
    string color;
public:
    // constructors
    State(string name, string color);
    State(string name);

    // destructor
    ~State();

    // getters
    string getName() const;
    string getColor() const;
};

#endif // STATE_H
