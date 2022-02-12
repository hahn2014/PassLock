#ifndef LOCKERROOM_H
#define LOCKERROOM_H

#include "Locker.h"
#include "Log.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <sstream>

class Lockerroom {
public:
    Lockerroom();
    Lockerroom(std::string);
    ~Lockerroom();
    void setUser(std::string);
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
