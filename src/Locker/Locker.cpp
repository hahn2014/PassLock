#include "Locker.h"

Locker::Locker() {
    setName("Default Value");
    setID(-1);
    setURL("www.google.com");
}

Locker::Locker(string name) {
    printf("New locker created: %s\n", name.c_str());
    setName(name);
    setID(1);
    setURL("");
}

Locker::~Locker() {
    printf("locker deleted..\n");
}

//
// Getters and Setters
//

int Locker::getID() {
    return this->id;
}

void Locker::setID(int id) {
    this->id = id;
}

string Locker::getName() {
    return this->name;
}

void Locker::setName(string name) {
    this->name = name;
}

string Locker::getURL() {
    return this->url;
}

void Locker::setURL(string url) {
    this->url = url;
}
