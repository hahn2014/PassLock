#include "Profiler.h"

Profiler::Profiler() {
    setUser("default");
}

bool Profiler::startup() {
    //check for existing user.ini

        //user exists, load profile

        //no user exists, create profile
    return true;
}

void Profiler::loadProfile() {

}

void Profiler::createProfile() {

}

void Profiler::setUser(std::string user) {
    this->user = user;
}

std::string Profiler::getUser() {
    return this->user;
}
