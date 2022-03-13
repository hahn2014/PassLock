#ifndef LOCKERROOM_H
#define LOCKERROOM_H

#include <vector>
#include "Locker.h"
#include "IO/Log.h"

class Lockerroom {
public:
    Lockerroom();
    Lockerroom(std::string);
    ~Lockerroom();
    void setUser(std::string);
    void setHash(std::string);
    std::vector<Locker*> getLockerroom();
    void setLockerroom(std::vector<Locker*>);
    bool createLocker();
    bool editLocker();
    void deleteLocker();
    void getLockByID();
    void getLockByName();
    void getLockByGroup();
    void printLockerroom();

    //temp dev calls
    void randLocks();

private:
    void refactorIDIndex(int);

    int lockercount;
    std::string user;
    std::string hash;
    std::vector<Locker*> lockerroom;
    std::string toLower(std::string);
};

#endif
