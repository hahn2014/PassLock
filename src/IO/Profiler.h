#include <sys/stat.h>
#include <vector>
#include "Log.h"
#include "Locker/Locker.h"
#include "Security/Hash.h"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

class Profiler {
public:
    bool startup();
    std::string getProfileNames();
    void createProfile();

    std::vector<Locker*> importFromXML();
    void exportToXML(std::vector<Locker*>);
    std::string getProfileHash();

    // Getters and Setters
    void saveLockerroom(std::vector<Locker*>);
    void setHash(std::string);
    void setUser(std::string);
    std::vector<Locker*> getLockerroom();
    std::string getHash();
    std::string getUser();

    //profile variables
    std::string user;
    std::string hash;

private:
    bool file_exists(std::string);
    bool dir_exists(std::string);
};
