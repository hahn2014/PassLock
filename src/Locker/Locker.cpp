#include "Locker.h"

Locker::Locker() {
    createLocker();
    setName("Default Value");
    setID(-1);
    setURL("www.google.com");
    printf("default locker created\n");
}

void Locker::createLocker() {
    int maxchar = 64;
    lock = (struct locker*)malloc(sizeof(struct locker) + sizeof(char) * maxchar);
}

Locker::~Locker() {
    printf("locker deleted..\n");
    //calloc(this->lock);
}

void Locker::printLocker() {
    printf("Locker [%d]: %s -> %s\n", lock->id, lock->name.c_str(), lock->url.c_str());
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

std::string Locker::getURL() {
    return lock->url;
}

void Locker::setURL(std::string newurl) {
    lock->url = newurl;
}
