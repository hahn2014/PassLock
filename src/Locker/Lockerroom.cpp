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
    //allocateLocker();
    Locker* l = new Locker();
    lockercount++;
    l->setID(lockercount);
    std::string input;

    printf("\n--- New Locker Setup {%d} ---\n", lockercount);

    //get name
    while (true) {
        input = ""; //reset the input param
        printf("Locker Name     >");
        getline(std::cin, input);

        if (input.length() > 2 && input.length() <= 64) { //no longer than 64 char
            l->setName(input);
            break; //break out of name loop
        } else {
            printf("Locker Name size overflow. Please keep the name < 64 characters.\n\n");
        }
    }
    //get url
    while (true) {
        input = ""; //reset the input param
        printf("Locker URL      >");
        getline(std::cin, input);

        if (input.length() <= 256) { //no longer than 64 char
            l->setURL(input);
            break; //break out of name loop
        } else {
            printf("Locker URL size overflow. Please keep the URL < 256 characters.\n\n");
        }
    }
    //get group
    while (true) {
        input = ""; //reset the input param
        printf("Locker Grouping >");
        getline(std::cin, input);

        if (input.length() > 0) { //no longer than 64 char
            l->setGroup(input);
            break; //break out of name loop
        } else {
            printf("Locker Group min size not met. Grouping name must be > 1 character.\n\n");
        }
    }
    //get username
    while (true) {
        input = ""; //reset the input param
        printf("Locker Username >");
        getline(std::cin, input);

        if (input.length() > 3) { //no smaller than 3 char
            l->setUsername(input);
            break; //break out of name loop
        } else {
            printf("Locker Username min length not met. Please use a username > 3 characters.\n\n");
        }
    }

    printf("Locker Password >");

    lockerroom.push_back(l);

    return true; //error exit clause
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

    while (true) {
        input = "";
        printf("Locker ID       >");
        getline(std::cin, input);

        if (input.length() > 0) { //must be at least 1 char long
            try {
                id = stoi(input);
            } catch (...) {
                printf("Invalid ID! You did not enter an integer..\n");
            }

            break; //break out of name loop
        } else {
            printf("Locker ID can not be bellow 0.\n\n");
        }
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

    while (true) {
        input = "";
        printf("Locker Name     >");
        getline(std::cin, input);

        if (input.length() > 0) { //must be at least 1 char long
            //find locker by ID
            for (int i = 0; i < lockerroom.size(); i++) {
                if (lockerroom[i]->getName() == input) {
                    lockerroom[i]->printLocker();
                    namematch++;
                }
            }
            if (namematch > 0) {
                printf("\n\n");
                return; //found as many values as we could
            } else break; //no names matched, break out of loop and notify user
        } else {
            printf("Locker name overflow. Invalid string length: %lu\n\n", input.length());
        }
    }

    printf("Locker %s does not exist in the Lockerroom\n\n\n", input.c_str());
}

void Lockerroom::getLockByGroup() {
    std::string input;
    int groupmatch = 0;
    printf("\n--- Locker Group Querry ---\n");

    while (true) {
        input = "";
        printf("Locker Group    >");
        getline(std::cin, input);

        if (input.length() > 0) { //must be at least 1 char long
            //find locker by ID
            for (int i = 0; i < lockerroom.size(); i++) {
                if (lockerroom[i]->getGroup() == input) {
                    lockerroom[i]->printLocker();
                    groupmatch++;
                }
            }
            if (groupmatch > 0) {
                printf("\n\n");
                return; //found as many values as we could
            } else break; //no names matched, break out of loop and notify user
        } else {
            printf("Locker grouping overflow. Invalid string length: %lu\n\n", input.length());
        }
    }

    printf("Locker Group %s does not exist in the Lockerroom\n\n\n", input.c_str());
}

void Lockerroom::editLocker() {
    //step 1 get the locker by ID

    //step 2 get which part of the locker to edit

    //step 3 get input for new value

    //step 4 set the new value and replace vector

}

void Lockerroom::deleteLocker() {
    int id = 0;
    std::string input;
    printf("\n--- Delete Locker ---\n");

    while (true) {
        input = "";
        printf("Locker ID       >");
        getline(std::cin, input);

        if (input.length() > 0) { //must be at least 1 char long
            try {
                id = stoi(input);
            } catch (...) {
                printf("Invalid ID! You did not enter an integer..\n");
            }

            break; //break out of name loop
        } else {
            printf("Locker ID can not be bellow 0.\n\n");
        }
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

void Lockerroom::addGroup(std::string group) {
    if (std::find(groups.begin(), groups.end(), group) != groups.end()) {
        std::cout << "Grouping found";
    }
    else {
        std::cout << "Grouping not found, adding...";
        groups.push_back(group);
    }
}
