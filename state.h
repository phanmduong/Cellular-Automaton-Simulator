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
    string getName() const; // Kieu
    string getColor() const; //Kieu

    // setters
    void setName(const string &name);
    void setColor(const string &color);


};

#endif // STATE_H
