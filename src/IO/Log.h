#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <iostream>
#include <stdarg.h>

// colored text
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

class Log {
public:

    void static Debug(const char* fmt, ...);
    void static Info(const char* fmt, ...);
    void static Error(const char* fmt, ...);
    void static printHelp();
    std::string static getInput(std::string, int, int);

private:
    std::string static calculateSpaces(std::string);

};

#endif
