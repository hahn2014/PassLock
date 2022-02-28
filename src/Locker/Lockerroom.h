#ifndef LOCKERROOM_H
#define LOCKERROOM_H

#include <vector>
#include "Locker.h"
#include "Log.h"

class Lockerroom {
public:
    Lockerroom();
    Lockerroom(std::string);
    ~Lockerroom();
    void setUser(std::string);
    std::vector<Locker*> getLockerroom();
    void setLockerroom(std::vector<Locker*>);
    bool createLocker();
    bool editLocker();
    void getLockByID();
    void getLockByName();
    void getLockByGroup();
    void deleteLocker();
    void printLockerroom();

    //temp dev calls
    void randLocks();

private:
    void addGroup(std::string);
    void refactorIDIndex(int);

    int lockercount;
    std::string user;
    std::vector<Locker*> lockerroom;
    std::string toLower(std::string);
    std::vector<std::string> groups;
};

#endif
