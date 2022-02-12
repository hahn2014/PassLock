#ifndef LOG_H
#define LOG_H

#include <string>
#include <sstream>
#include <iostream>

class Log {
public:

    void Debug();
    void Info();
    void Error();
    void static printHelp();
    std::string static getInput(std::string, int, int);
    //void func(Args... args);
    // more functions for output formatting

private:
    std::string static calculateSpaces(std::string);

};

#endif
