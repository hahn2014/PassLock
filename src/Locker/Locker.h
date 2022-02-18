#ifndef LOCKER_H
#define LOCKER_H

#include <string>

class Locker {
public:
    Locker();
    //DEBUG for testing, should not be accessible in the future
    void printLocker();

    // getters and setters
    int getID();
    std::string getName();
    std::string getUsername();
    std::string getPassword();
    std::string getURL();
    std::string getGroup();

    void setID(int);
    void setName(std::string);
    void setUsername(std::string);
    void setPassword(std::string);
    void setURL(std::string);
    void setGroup(std::string);

    struct locker {
        std::string name;
        std::string username;
        std::string password;
        std::string url;
        int id;
        std::string group; //grouping filter
    };

    struct locker* lock;

private:
    void createLocker();
};

#endif
