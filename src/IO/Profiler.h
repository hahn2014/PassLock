#include <sys/stat.h>
#include <vector>
#include "Log.h"
#include "Locker.h"
#include "Hash.h"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

class Profiler {
public:
    Profiler();
    bool startup();
    std::string getProfileNames();
    void createProfile();

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
