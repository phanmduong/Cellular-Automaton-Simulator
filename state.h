#ifndef STATE_H
#define STATE_H
#include <string>

using namespace std;

class State
{
    string name;
    string color;
public:
    State(string name, string color);
    State(string name);

    void setName(const string &value);
    void setColor(const string &color);

    string getName() const; // Kieu
    string getColor() const; //Kieu
};

#endif // STATE_H
