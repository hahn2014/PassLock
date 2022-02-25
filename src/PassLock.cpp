#include <stdio.h>
#include <iostream>
#include <string>
#include "Lockerroom.h"
#include "Log.h"
#include "Profiler.h"

static std::string VERSION = "1.0.5";
static int MAX_MENU_OPTIONS = 10;

Lockerroom lockers;
Profiler userprof;
std::string user;

bool validMenuSelection(std::string inp) {
    if (inp != "-h") { //help command
        try {
            int selection = std::stoi(inp);
            if (selection < 0) throw 1;
            else if (selection > MAX_MENU_OPTIONS) throw -1;
            return true;
        } catch (...) {
            std::cerr << "PassLock Menu only accepts integer inputs... Type -h for help\n";
            return false;
        }
    }
    return true;
}

int menuDelegator(std::string inp) {
    if (inp == "-h") {
        Log::printHelp();
        return 0; //continue clause
    }

    switch(stoi(inp)) {
        case 0:
            printf("Goodbye!\n\n");
            return 1; //exit clause

        case 1:
            //Option 1 - List ALL lockers (name / url / id only)
            lockers.printLockerroom();
            return 0;

        case 2:
            //Option 2 - List ALL lockers by grouping
            lockers.getLockByGroup();
            return 0;

        case 3:
            //Option 3 - Create NEW locker
            if (lockers.createLocker()) printf("Successfully created new Locker\n\n\n");
            return 0;

        case 4:
            //Option 4 - View Existing Locker (ID needed)
            lockers.getLockByID();
            return 0;

        case 5:
            //Option 5 - Edit Existing Locker (ID needed)
            if (lockers.editLocker()) printf("Successfully updated Locker\n\n\n");
            return 0;

        case 6:
            //Option 6 - Delete Existing Locker (ID needed)
            lockers.deleteLocker();
            return 0;

        case 7:
            //Option 7 - Get ID (by name), if multiple site under same name, list all
            lockers.getLockByName();
            return 0;

        case 8:
            //Option 8 - Run GUI PassLock
            printf("Last area of development.. Please give me some time\n");
            return 0;

        case 9:
            //Option 9 - seceret developer setting (generate random accounts)
            lockers.randLocks();
            return 0;
        case 10:
            //Option 10 - seceret developer setting (test save profile)
            printf("test save\n\n");
            userprof.saveLockerroom(lockers.getLockerroom());
            return 0;
    }
    return -1; //error clause
}

int main() {
    //load in user profile (/db/user.ini)
    if (userprof.startup()) {
        userprof.importFromXML();
        user = userprof.getUser();
        //confirm master password to gain access
        printf("\nHello, %s. Please confirm master password\n", user.c_str());
        std::string testpass = Log::getInput("Master Password", 8, 64);

        if (testpass == userprof.getPass()) {
            printf("Passwords match!\n\n");
        } else {
            printf("Invalid password..\nShutting down.\n");
            return -1;
        }

    } else {
        std::cerr << "Unexpected error occured while loading user profile." << std::endl;
        return -1;
    }



    //welcome screen
    printf("\nWelcome %s to PassLock! The all emcompassing Password Lockerroom.\n", user.c_str());
    printf("PassLock CLI Developed by Bryce Hahn (@hahn2014) -- v%s\n", VERSION.c_str());

    //initialize Lockerroom
    lockers.setUser(user);

    //load user database
    lockers.setLockerroom(userprof.getLockerroom());

    //program delegator
    printf("\t--Type -h for help--\n\n");

    std::string input = "";

    while (input[0] != '0') {
        input = ""; //reset the input param
        printf("PassLock@%s> ", user.c_str());

    	getline(std::cin, input);

        if (validMenuSelection(input)) {
            //Log::Debug("good input: %s\n", input.c_str()); //still need to figure out indefinite arguments
            int menuStatus = menuDelegator(input);

            if (menuStatus == -1) {
                return -1;
            } else if (menuStatus == 1) {
                return 0;
            }
        }
    }
    return 0;
}
