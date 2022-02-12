#include <string>

class Profiler {
public:
    Profiler();
    bool startup();
    void loadProfile();
    void createProfile();
    std::string getUser();
    void setUser(std::string);

private:
    std::string user;
};
