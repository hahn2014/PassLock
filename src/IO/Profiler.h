#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include "Log.h"

class Profiler {
public:
    Profiler();
    bool startup();
    bool loadProfile();
    void createProfile();
    std::string getUser();
    void setUser(std::string);
    std::string getPass();
    void setPass(std::string);
    std::pair<std::string, std::string> interpretINI(std::vector<std::string>);

    //profile variables
    std::string user;
    std::string pass;

private:
    bool file_exists(std::string);
    bool dir_exists(std::string);
};
