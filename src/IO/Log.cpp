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
    printf("1 - List ALL lockers (name / url / id only)\n");
    printf("2 - List ALL lockers by grouping\n");
    printf("3 - Create NEW locker\n");
    printf("4 - View Existing Locker (ID needed)\n");
    printf("5 - Edit Existing Locker (ID needed)\n");
    printf("6 - Get ID (by name), if multiple site under same name, list all\n");
    printf("7 - Run GUI PassLock (implement once system in general is working)\n\n");
}

// template<class... Args>
// void func(Args... args) {
//     (std::cout << ... << args) << "\n";
// }
