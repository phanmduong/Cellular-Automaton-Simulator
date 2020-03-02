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
    string neighborPostionText;
    string ruleName;
    int limitGeneration;

    string fileRulePath =  "";
    string fileInputValuePath = "";
    string directoryOutputValuePath = "";

public:
    Configuration();
    ~Configuration();

    int getNumberOfState() const; //a.ban
    void setNumberOfState(int value); //a.ban

    int getWidth() const; //a.ban
    void setWidth(int value); //a.ban

    int getHeight() const; //a.ban
    void setHeight(int value); //a.ban

    string getRuleName() const; //a.ban
    void setRuleName(const string &value); //a.ban

    int getLimitGeneration() const; //a.ban
    void setLimitGeneration(int value); //a.ban

    string getFileRulePath() const;// a.ban
    string getFileInputValuePath() const; //a.ban
    string getDirectoryOutputValuePath() const; //a.ban

    string getNeighborPostionText() const; //a.ban
    void setNeighborPostionText(const string &value); //a.ban
    void setFileRulePath(const string &value);
    void setFileInputValuePath(const string &value);
    void setDirectoryOutputValuePath(const string &value);
};

#endif // CONFIGURATION_H
