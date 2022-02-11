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
    printf("8 - Run GUI PassLock\n\n");
}

// template<class... Args>
// void func(Args... args) {
//     (std::cout << ... << args) << "\n";
// }
