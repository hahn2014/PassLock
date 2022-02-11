#ifndef LOG_H
#define LOG_H

#include <string>

using namespace std;

class Log {
public:

    void Debug();
    void Info();
    void Error();
    void static printHelp();
    //void func(Args... args);
    // more functions for output formatting

};

#endif
