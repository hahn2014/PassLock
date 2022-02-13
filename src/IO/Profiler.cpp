#include "Profiler.h"

namespace fs = std::filesystem;

Profiler::Profiler() {
    setUser("default");
}

bool Profiler::startup() {
    //check for existing user.ini
    if (dir_exists("./db/")) {
        if (file_exists("./db/user.ini")) {
            //printf("User profile ini found. Loading user profile...\n");
            return loadProfile();
        } else {
            //printf("User profile ini not found. Creating a new user profile...\n");
            createProfile();
            return startup(); //recursively call startup to validate newly created ini file
        }
    }
    return false;
}

bool Profiler::loadProfile() {
    std::ifstream prof("./db/user.ini");
    this->user = "";
    this->pass = "";

    //read ini file line by line
    if (prof.is_open()) {
        std::vector<std::string> inivals;
        std::string line;
        while (prof >> line) {
            inivals.push_back(line);
        }

        std::pair userprof = interpretINI(inivals);

        this->user = userprof.first;
        this->pass = userprof.second;

        prof.close();

    } else {
        std::cerr << "Unexpected error when opening user profile\n";
        return false;
    }
    return true;
}

void Profiler::createProfile() {
    std::string user;
    std::string password;
    printf("PassLock initial boot-up. Creating new user profile...\n\n");
    printf("--- New Lockerroom ---\n");

    //get username
    user = Log::getInput("Profile Username", 4, 32);

    //indefinite while loop to keep prompting a password until both values match
    while (true) {
        //get user password
        password = Log::getInput("Profile Password", 8, 64);

        //verify password is what the user wants
        if (password == Log::getInput("Confirm Password", 8, 64)) {
            printf("Passwords match!\n\n");
            break;
        } else {
            printf("Passwords did not match!\n");
        }
    }

    //generate ini file
    std::ofstream prof("./db/user.ini");

    //populate ini file
    if (prof.is_open()) {
        try {
            prof << "[Profile]" << std::endl;
            prof << "user=" << user << std::endl;
            prof << "pass=" << password << std::endl; //TEMPORARY. DO NOT SAVE PASSWORDS UNHASHED
        } catch (...) {
            std::cerr << "Unexpected error when writing to user profile\n";
            return;
        }
        prof.close();
    } else {
        std::cerr << "Unexpected error when opening user profile\n";
        return;
    }
}

void Profiler::setUser(std::string user) {
    this->user = user;
}

std::string Profiler::getUser() {
    return this->user;
}

void Profiler::setPass(std::string pass) {
    this->pass = pass;
}

std::string Profiler::getPass() {
    return this->pass;
}

std::pair<std::string, std::string> Profiler::interpretINI(std::vector<std::string> ini) {
    // ini file setup
    // [section name]
    // variable:value
    std::string user;
    std::string pass;

    for (int i = 1; i < ini.size(); i++) {
        if (i == 1) user = ini.at(i).substr(ini.at(i).find("=") + 1);
        else if (i == 2) pass = ini.at(i).substr(ini.at(i).find("=") + 1);
    }

    return {user, pass};
}


// https://stackoverflow.com/a/12774387
bool Profiler::file_exists(std::string name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

bool Profiler::dir_exists(std::string path) {
    if (fs::is_directory(path)) {
        //valid dir
        //printf("%s is a directory\n", path.c_str());
        return true;
    } else {
        //no dir found
        printf("%s was not found.. Creating new database directory\n", path.c_str());
        fs::create_directory(path); //create the db directory
        return true;
    }
    return false;
}
