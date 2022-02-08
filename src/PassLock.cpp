#include <stdio.h>
#include <iostream>
#include <string>
#include <Locker.h>
#include <Log.h>

using namespace std;

static string VERSION = "1.0.1";
static int MAX_MENU_OPTIONS = 7;


bool validMenuSelection(string inp) {
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

int menuDelegator(string inp) {
    if (inp == "-h") {
        Log::printHelp();
        return 0; //continue clause
    }

    switch(stoi(inp)) {
        case 0:
            printf("Goodbye!\n");
            return 1; //exit clause

        case 1:
            //Option 1 - List ALL lockers (name / url / id only)
            return 0;

        case 2:
            //Option 2 - List ALL lockers by grouping
            return 0;

        case 3:
            //Option 3 - Create NEW locker
            return 0;

        case 4:
            //Option 4 - View Existing Locker (ID needed)
            return 0;

        case 5:
            //Option 5 - Edit Existing Locker (ID needed)
            return 0;

        case 6:
            //Option 6 - Get ID (by name), if multiple site under same name, list all
            return 0;

        case 7:
            //Option 7 - Run GUI PassLock (implement once system in general is working)
            printf("Last area of development.. Please give me some time\n");
            return 0;

    }
    return -1; //error clause
}

int main() {
    //confirm master password to gain access


    //welcome screen
    printf("\nWelcome to PassLock! The all emcompassing Password Lockerroom.\n");
    printf("PassLock CLI Developed by Bryce Hahn (@hahn2014) -- v%s\n", VERSION.c_str());

    //load in user profile

    //if no previous user exists, make new

    printf("\t--Type -h for help--\n");

    string input = "";
    string user = "hahnsolo";

    while (input[0] != '0') {
        input = ""; //reset the input param
        printf("PassLock@%s> ", user.c_str());

    	getline(cin, input);

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
