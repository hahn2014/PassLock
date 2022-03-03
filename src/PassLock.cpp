#include "Locker/Lockerroom.h"
#include "IO/Log.h"
#include "IO/Profiler.h"
#include "Security/Hash.h"

static std::string VERSION = "1.0.6";
static int MIN_MENU_OPTIONS = -1;
static int MAX_MENU_OPTIONS = 10;

Lockerroom lockers;
Profiler userprof;
std::string user;

bool validMenuSelection(std::string inp) {
    if (inp != "-h") { //help command
        try {
            int selection = std::stoi(inp);
            if (selection < MIN_MENU_OPTIONS) {
                Log::Info("No menu options bellow %i are available\n\n", MIN_MENU_OPTIONS);
                throw 1;
            } else if (selection > MAX_MENU_OPTIONS) {
                Log::Info("No menu options above %i are available\n\n", MAX_MENU_OPTIONS);
                throw -1;
            }
            return true;
        } // Standard exceptions for stoi
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << "\n";
        }
        catch (const std::out_of_range& e) {
            std::cout << e.what() << "\n";
        }
        catch (...) {
            return false;
        }
    }
    return true;
}

bool interp(std::string responce) {
    char r = tolower(responce[0]);
    if (r == 'y') {
        return true;
    } else if (r == 'n') {
        return false;
    } else { //invalid character was entered, reprompt
        printf("Invalid responce. Exit without saving: y/n\n\n");
        return interp(Log::getInput("Continue? y/n", 1, 2)); // recursive call to reprompt
    }
}

int menuDelegator(std::string inp) {
    if (inp == "-h") {
        Log::printHelp();
        return 0; //continue clause
    }

    switch(stoi(inp)) {
        case -1: {
            printf("You are attempting to exit without saving!\nAny changes made will be lost.\n");
            bool exitnosave = interp(Log::getInput("Continue? y/n", 1, 2));
            if (exitnosave) {
                return 1;
            } else {
                return 0; //user canceled exit nosave
            }
        }

        case 0: {
            Log::Info("Updating user database\n\n");
            userprof.saveLockerroom(lockers.getLockerroom());
            printf("Goodbye!\n\n");
            return 1; //exit clause
        }

        case 1: {
            //Option 1 - List ALL lockers (name / url / id only)
            lockers.printLockerroom();
            return 0;
        }

        case 2: {
            //Option 2 - List ALL lockers by grouping
            lockers.getLockByGroup();
            return 0;
        }

        case 3: {
            //Option 3 - Create NEW locker
            if (lockers.createLocker()) Log::Info("Successfully created new Locker\n\n\n");
            return 0;
        }

        case 4: {
            //Option 4 - View Existing Locker (ID needed)
            lockers.getLockByID();
            return 0;
        }

        case 5: {
            //Option 5 - Edit Existing Locker (ID needed)
            if (lockers.editLocker()) Log::Info("Successfully updated Locker\n\n\n");
            return 0;
        }

        case 6: {
            //Option 6 - Delete Existing Locker (ID needed)
            lockers.deleteLocker();
            return 0;
        }

        case 7: {
            //Option 7 - Get ID (by name), if multiple site under same name, list all
            lockers.getLockByName();
            return 0;
        }

        case 8: {
            //Option 8 - Run GUI PassLock
            Log::Debug("Last area of development.. Please give me some time\n");
            return 0;
        }

        case 9: {
            //Option 9 - seceret developer setting (generate random accounts)
            lockers.randLocks();
            return 0;
        }

        case 10: {
            Hash::test();
            return 0;
        }
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
            Log::Info("Passwords match!\n\n");
        } else {
            Log::Error("Invalid password..\nShutting down.\n");
            return -1;
        }

    } else {
        Log::Error("Unexpected error occured while loading user profile.\n");
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

    std::string input;
    std::string prompt = "PassLock@";
    prompt.append(user);

    while (true) {
        input = Log::getInput(prompt, 1, 2);
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
