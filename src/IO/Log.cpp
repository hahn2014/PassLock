#include "Log.h"


void Log::Debug() {

}

void Log::Info() {

}

void Log::Error() {

}

void Log::printHelp() {
    printf("\nWelcome to the PassLock help portal!\n\n");
    printf("0 - Exit Program\n");
    printf("1 - List ALL lockers\n");
    printf("2 - List ALL lockers by grouping\n");
    printf("3 - Create NEW locker\n");
    printf("4 - View Existing Locker (ID Needed)\n");
    printf("5 - Edit Existing Locker (ID Needed)\n");
    printf("6 - Delete Existing Locker (ID Needed)\n");
    printf("7 - Get Locker ID (Name Needed)\n");
    printf("8 - Run GUI PassLock\n\n\n");
}

std::string Log::getInput(std::string prompt, int min, int max) {
    std::string input;
    while (true) {
        input = ""; //reset the input param
        printf("%s >", prompt.c_str());
        getline(std::cin, input);

        if (input.length() >= min && input.length() <= max) {
            return input;
        } else if (input.length() < min) {
            printf("%s min length not met. %s must be at least %d characters.\n\n", prompt.c_str(), prompt.c_str(), min);
        } else if (input.length() > max) {
            printf("%s max length exceeded. %s must be less than %d characters.\n\n", prompt.c_str(), prompt.c_str(), max);
        }
    }
    return "";
}
