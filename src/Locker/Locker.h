#include <string>

using namespace std;

class Locker {
public:
    Locker();
    Locker(string);
    ~Locker();
    string name;
    string url;
    int id;

    // getters and setters
    int getID();
    string getName();
    string getURL();

    void setID(int);
    void setName(string);
    void setURL(string);

private:

};
