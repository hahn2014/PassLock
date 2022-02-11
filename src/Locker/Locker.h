#ifndef LOCKER_H
#define LOCKER_H

#include <string>

class Locker {
public:
    Locker();
    ~Locker();
    //DEBUG for testing, should not be accessible in the future
    void printLocker();

    // getters and setters
    int getID();
    std::string getName();
    std::string getURL();

    void setID(int);
    void setName(std::string);
    void setURL(std::string);

    struct locker {
        std::string name;
        std::string url;
        int id;
    };

    struct locker* lock;

private:
    void createLocker();
};

#endif
