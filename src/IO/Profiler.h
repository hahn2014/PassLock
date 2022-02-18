#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Log.h"
#include "Locker.h"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

class Profiler {
public:
    Profiler();
    bool startup();
    bool loadProfile();
    void createProfile();
    std::pair<std::string, std::string> interpretINI(std::vector<std::string>);

    std::vector<Locker*> importFromXML();
    void exportToXML(std::vector<Locker*>);

    std::vector<Locker*> getLockerroom();
    void saveLockerroom(std::vector<Locker*>);
    std::string getUser();
    void setUser(std::string);
    std::string getPass();
    void setPass(std::string);

    //profile variables
    std::string user;
    std::string pass;

private:
    bool file_exists(std::string);
    bool dir_exists(std::string);
};
