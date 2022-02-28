#include "Log.h"


void Log::Debug(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    printf(KMAG "[DEBUG]: " KWHT);
    vprintf(fmt, arg);
    va_end(arg);
}

void Log::Info(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    printf(KGRN "[INFO]: " KWHT);
    vprintf(fmt, arg);
    va_end(arg);
}

void Log::Error(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    printf(KRED "[ERROR]: " KWHT);
    vprintf(fmt, arg);
    va_end(arg);
}

void Log::printHelp() {
    printf("\nWelcome to the PassLock help portal!\n\n");
    printf("<< -1 >> Exit without saving\n");
    printf("0 - Save and Exit Program\n");
    printf("1 - List ALL lockers\n");
    printf("2 - List ALL lockers by grouping\n");
    printf("3 - Create NEW locker\n");
    printf("4 - View Existing Locker (ID Needed)\n");
    printf("5 - Edit Existing Locker (ID Needed)\n");
    printf("6 - Delete Existing Locker (ID Needed)\n");
    printf("7 - Get Locker ID (Name Needed)\n");
    printf("8 - Run GUI PassLock\n");
    printf("9 - Developer test: Generate random lockers\n");
    printf("10 - Developer test: Generate hash value\n");
}

std::string Log::getInput(std::string prompt, int min, int max) {
    std::string input;
    while (true) {
        input = ""; //reset the input param
        printf("%s%s> ", prompt.c_str(), calculateSpaces(prompt).c_str());
        getline(std::cin, input);

        if (input.length() >= min && input.length() <= max) {
            return input;
        } else if (input.length() < min) {
            Error("%s min length not met. %s must be at least %d characters.\n\n", prompt.c_str(), prompt.c_str(), min);
        } else if (input.length() > max) {
            Error("%s max length exceeded. %s must be less than %d characters.\n\n", prompt.c_str(), prompt.c_str(), max);
        }
    }
    return "";
}

std::string Log::calculateSpaces(std::string prompt) {
    int maxlength = 20;
    std::stringstream spaces;
    for (int i = 0; i < (maxlength - prompt.length()); i++) {
        spaces << " ";
    }
    return spaces.str();
}
