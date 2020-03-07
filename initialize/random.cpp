#include <iostream>
#include <fstream>
#include <vector>
#include "time.h"

using namespace std;


string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int main(void) {
    //Initialize matrix
    unsigned int height = 20;
    unsigned int width = 20;
    unsigned int no_state = 3;
    string filename;

    std::cout << "[INPUT 3 VALUES] - height and width and number of state for a matrix" << std::endl << std::endl;
    std::cin >> height >> width >> no_state;

    std::cout << "[INPUT FILE NAME] - " << std::endl << std::endl;
    std::cin >> filename;

    //initialize random seed:
    srand(time(NULL));

    ofstream textfile;
    textfile.open (filename, ofstream::out);

    textfile << height << " " << width << " " << no_state << endl;
    
    for (unsigned i = 0; i < height; i++)
    {
        string line = "";
        for (unsigned j = 0; j < width; j++)
        {
            int rd_value = rand() % no_state;
            line += std::to_string(rd_value) + " ";
            //line = trim(line);
        }
        textfile << line << endl;
    }
    textfile.close();
}
