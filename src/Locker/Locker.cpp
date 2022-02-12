#include "Locker.h"

Locker::Locker() {
    createLocker();
    setName("Default Value");
    setID(-1);
    setURL("www.google.com");
}

void Locker::createLocker() {
    int maxchar = 64;
    lock = (struct locker*)malloc(sizeof(struct locker) + sizeof(char) * maxchar);
}

void Locker::printLocker() {
    printf("Locker [%d: %s]: %s (User: %s) -> {%s}\n", lock->id, lock->group.c_str(), lock->name.c_str(), lock->username.c_str(), lock->url.c_str());
}

//
// Getters and Setters
//

int Locker::getID() {
    return lock->id;
}

void Locker::setID(int newid) {
    lock->id = newid;
}

std::string Locker::getName() {
    return lock->name;
}

void Locker::setName(std::string newname) {
    lock->name = newname;
}

std::string Locker::getUsername() {
    return lock->username;
}

void Locker::setUsername(std::string user) {
    lock->username = user;
}

std::string Locker::getURL() {
    return lock->url;
}

void Locker::setURL(std::string newurl) {
    lock->url = newurl;
}

std::string Locker::getGroup() {
    return lock->group;
}

void Locker::setGroup(std::string group) {
    lock->group = group;
}
