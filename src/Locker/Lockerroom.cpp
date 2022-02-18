#include "Lockerroom.h"

Lockerroom::Lockerroom() {
    setUser("user");
    lockercount = 0;
}

Lockerroom::Lockerroom(std::string user) {
    //lockerroom
    setUser(user);
    lockercount = 0;
}

Lockerroom::~Lockerroom() {
    //cleanup

    //lockerroom memory wipe
    lockerroom.clear();
    lockerroom.shrink_to_fit();
}

void Lockerroom::printLockerroom() {
    printf("\n--- %s Lockerroom ---\n", this->user.c_str());
    for (int i = 0; i < lockerroom.size(); i++) {
        lockerroom[i]->printLocker();
    }
    if (lockerroom.size() == 0) {
        printf("There is nothing here yet...\n\n");
    }
    printf("\n\n");
}

bool Lockerroom::createLocker() {
    Locker* l = new Locker();
    lockercount++;
    l->setID(lockercount);
    std::string input;

    printf("\n--- New Locker Setup {%d} ---\n", lockercount);

    //get name
    input = ""; //input reset
    input = Log::getInput("Locker Name", 2, 64);
    l->setName(input);

    //get url
    input = ""; //input reset
    input = Log::getInput("Locker URL", 4, 128);
    l->setURL(input);

    //get group
    input = ""; //input reset
    input = Log::getInput("Locker Grouping", 1, 64);
    l->setGroup(input);

    //get username
    input = ""; //input reset
    input = Log::getInput("Locker Username", 3, 64);
    l->setUsername(input);

    //get password
    // input = "";
    // input = Log::getInput("Locker Password", 8, 128);
    // l->setPassword(input);

    //update lockerroom with new locker
    lockerroom.push_back(l);
    return true; //error exit clause
}

bool Lockerroom::editLocker() {
    int id;
    Locker* l = new Locker();
    std::string input;
    //step 1 get the locker by ID
    try {
        id = stoi(Log::getInput("Locker ID", 1, 64));
    } catch (...) {
        std::cerr << "Invalid ID. Please use a valid integer!" << std::endl;
        return false;
    }
    //verify inputed ID is a valid Locker
    for (int i = 0; i < lockerroom.size(); i++) {
        if (lockerroom.at(i)->getID() == id) {
            l->setID(id);

            printf("\n--- Locker Editor {%d} ---\n", id);

            //get name
            input = ""; //input reset
            input = Log::getInput("Locker Name", 2, 64);
            l->setName(input);

            //get url
            input = ""; //input reset
            input = Log::getInput("Locker URL", 4, 128);
            l->setURL(input);

            //get group
            input = ""; //input reset
            input = Log::getInput("Locker Grouping", 1, 64);
            l->setGroup(input);

            //get username
            input = ""; //input reset
            input = Log::getInput("Locker Username", 3, 64);
            l->setUsername(input);

            //get password
            // input = "";
            // input = Log::getInput("Locker Password", 8, 128);
            // l->setPassword(input);

            lockerroom.at(id) = l;
            return true;
        }
    }
    printf("Locker %d does not exist\n", id);
    return false;
}

void Lockerroom::randLocks() {
    for (int i = 0; i < 9; i++) {
        lockercount++;
        Locker* l = new Locker();

        std::stringstream ss;
        ss << "test" << i;

        l->setName(ss.str());
        l->setID(lockercount);
        l->setURL("www.github.com/hahn2014");
        l->setGroup("Programming");
        l->setUsername("HahnSolo");

        lockerroom.push_back(l);
    }
}

void Lockerroom::getLockByID() {
    int id = 0;
    std::string input;
    printf("\n--- Locker ID Querry ---\n");

    try {
        id = stoi(Log::getInput("Locker ID", 1, 64));
        //if you have > 64 chars worth of IDs then get help...
    } catch (...) {
        std::cerr << "Invalid ID. Please use a valid integer!" << std::endl;
    }

    //find locker by ID
    for (int i = 0; i < lockerroom.size(); i++) {
        if (lockerroom[i]->getID() == id) {
            lockerroom[i]->printLocker();
            printf("\n\n");
            return;
        }
    }
    printf("Locker %d does not exist in the Lockerroom\n\n\n", id);
}

void Lockerroom::getLockByName() {
    std::string input;
    int namematch = 0;
    printf("\n--- Locker Name Querry ---\n");

    input = ""; //input reset
    input = Log::getInput("Locker Name", 2, 64);

    //find locker by Name
    for (int i = 0; i < lockerroom.size(); i++) {
        if (lockerroom[i]->getName() == input) {
            lockerroom[i]->printLocker();
            namematch++;
        }
    }
    if (namematch > 0) {
        printf("\n\n");
        return; //found as many values as we could
    } //no names matched, break out of loop and notify user

    printf("Locker %s does not exist in the Lockerroom\n\n\n", input.c_str());
}

void Lockerroom::getLockByGroup() {
    std::string input;
    int groupmatch = 0;
    printf("\n--- Locker Group Querry ---\n");

    input = ""; //input reset
    input = Log::getInput("Locker Grouping", 1, 64);

    //find locker by Group
    for (int i = 0; i < lockerroom.size(); i++) {
        if (lockerroom[i]->getGroup() == input) {
            lockerroom[i]->printLocker();
            groupmatch++;
        }
    }
    if (groupmatch > 0) {
        printf("\n\n");
        return; //found as many values as we could
    } //no names matched, break out of loop and notify user

    printf("Locker Group %s does not exist in the Lockerroom\n\n\n", input.c_str());
}

void Lockerroom::deleteLocker() {
    int id = 0;
    printf("\n--- Delete Locker ---\n");

    try {
        id = stoi(Log::getInput("Locker ID", 1, 64));
        //if you have > 64 chars worth of IDs then get help...
    } catch (...) {
        std::cerr << "Invalid ID. Please use a valid integer!" << std::endl;
    }

    //find locker by ID
    for (int i = 0; i < lockerroom.size(); i++) {
        if (lockerroom[i]->getID() == id) {
            lockerroom.erase(lockerroom.begin() + i);
            refactorIDIndex(i); //fix ID index for lockers i+1 and above (if any)
            printf("Locker Deleted!\n\n\n");
            return;
        }
    }
    printf("Locker %d does not exist in the Lockerroom\n\n\n", id);
}

void Lockerroom::refactorIDIndex(int startindex) {
    int tmp = 0;
    if (startindex < lockerroom.size()) {
        for (int i = startindex; i < lockerroom.size(); i++) {
            tmp = lockerroom[i]->getID();
            lockerroom[i]->setID(tmp - 1); // move all IDs down by 1
        }
    } else {
        printf("Locker %d was the end of the vector\n", startindex);
    }
}

void Lockerroom::setUser(std::string newUser) {
    this->user = newUser;
}

void Lockerroom::setLockerroom(std::vector<Locker*> import) {
    if (import.size() > 0) { //import is not an empty vector
        this->lockerroom = import;
        this->lockercount = import.size(); //keep the lockercount updated with imported count
    }
}

std::vector<Locker*> Lockerroom::getLockerroom() {
    return this->lockerroom;
}

void Lockerroom::addGroup(std::string group) {
    if (std::find(groups.begin(), groups.end(), group) != groups.end()) {
        std::cout << "Grouping found";
    }
    else {
        std::cout << "Grouping not found, adding...";
        groups.push_back(group);
    }
}
