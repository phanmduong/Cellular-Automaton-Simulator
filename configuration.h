#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>
#include <neighbor_position.h>

using namespace std;

class Configuration
{
    int numberOfState;
    int width;
    int height;
    string neightborPostionText;
    string ruleName;
    int limitGeneration;

    string fileRulePath = "./rule/rule.so";
    string fileInputValuePath = "./input.txt";
    string directoryOutputValuePath = "./output";

public:
    Configuration();
    ~Configuration();

    int getNumberOfState() const; //a.ban
    void setNumberOfState(int value); //a.ban

    int getWidth() const; //a.ban
    void setWidth(int value); //a.ban

    int getHeight() const; //a.ban
    void setHeight(int value); //a.ban

    string getNeightborPostionText() const; //a.ban
    void setNeightborPostionText(const string &value); //a.ban

    string getRuleName() const; //a.ban
    void setRuleName(const string &value); //a.ban

    int getLimitGeneration() const; //a.ban
    void setLimitGeneration(int value); //a.ban

    string getFileRulePath() const;
    string getFileInputValuePath() const;
    string getDirectoryOutputValuePath() const;
};

#endif // CONFIGURATION_H
