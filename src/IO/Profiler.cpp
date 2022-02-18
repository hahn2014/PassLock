#include "Profiler.h"

namespace fs = std::filesystem;

Profiler::Profiler() {
    setUser("default");
}

bool Profiler::startup() {
    //check for existing user.ini
    if (dir_exists("./db/")) {
        if (file_exists("./db/user.ini")) {
            //printf("User profile ini found. Loading user profile...\n");
            return loadProfile();
        } else {
            //printf("User profile ini not found. Creating a new user profile...\n");
            createProfile();
            return startup(); //recursively call startup to validate newly created ini file
        }
    }
    return false;
}

bool Profiler::loadProfile() {
    std::ifstream prof("./db/user.ini");
    this->user = "";
    this->pass = "";

    //read ini file line by line
    if (prof.is_open()) {
        std::vector<std::string> inivals;
        std::string line;
        while (prof >> line) {
            inivals.push_back(line);
        }

        std::pair userprof = interpretINI(inivals);

        this->user = userprof.first;
        this->pass = userprof.second;

        prof.close();

    } else {
        std::cerr << "Unexpected error when opening user profile\n";
        return false;
    }
    return true;
}

void Profiler::createProfile() {
    std::string user;
    std::string password;
    printf("PassLock initial boot-up. Creating new user profile...\n\n");
    printf("--- New Lockerroom ---\n");

    //get username
    user = Log::getInput("Profile Username", 4, 32);

    //indefinite while loop to keep prompting a password until both values match
    while (true) {
        //get user password
        password = Log::getInput("Profile Password", 8, 64);

        //verify password is what the user wants
        if (password == Log::getInput("Confirm Password", 8, 64)) {
            printf("Passwords match!\n\n");
            break;
        } else {
            printf("Passwords did not match!\n");
        }
    }

    //generate ini file
    std::ofstream prof("./db/user.ini");

    //populate ini file
    if (prof.is_open()) {
        try {
            prof << "[Profile]" << std::endl;
            prof << "user=" << user << std::endl;
            prof << "pass=" << password << std::endl; //TEMPORARY. DO NOT SAVE PASSWORDS UNHASHED
        } catch (...) {
            std::cerr << "Unexpected error when writing to user profile\n";
            return;
        }
        prof.close();
    } else {
        std::cerr << "Unexpected error when opening user profile\n";
        return;
    }
}

void Profiler::setUser(std::string user) {
    this->user = user;
}

std::string Profiler::getUser() {
    return this->user;
}

void Profiler::setPass(std::string pass) {
    this->pass = pass;
}

std::string Profiler::getPass() {
    return this->pass;
}

std::pair<std::string, std::string> Profiler::interpretINI(std::vector<std::string> ini) {
    // ini file setup
    // [section name]
    // variable:value
    std::string user;
    std::string pass;

    for (int i = 1; i < ini.size(); i++) {
        if (i == 1) user = ini.at(i).substr(ini.at(i).find("=") + 1);
        else if (i == 2) pass = ini.at(i).substr(ini.at(i).find("=") + 1);
    }

    return {user, pass};
}

std::vector<Locker*> Profiler::getLockerroom() {
    //test is prof.xml even exists
    if (file_exists("./db/prof.xml")) {
        return importFromXML(); //attempt to load
    } else {
        printf("no user XML database was found... could not load a previously populated lockerroom\n\n");
    }
    return {};
}

void Profiler::saveLockerroom(std::vector<Locker*> lockerroom) {
    //verify if xml file already exists
    if (file_exists("./db/prof.xml")) {
        //delete existing database export
        if (std::remove("./db/prof.xml") != 0)
            perror("Error deleting old database\n\n");
        else
            puts("Outdated database successfully deleted\n\n");
    }
    exportToXML(lockerroom); //create new updated database XML
}


std::vector<Locker*> Profiler::importFromXML() {
    std::vector<Locker*> lockerroom; //store a vector of lockers
    try {
        //load XML Database
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* root_node;
    	// Read the xml file into a string vector
        std::ifstream xmlFile("./db/prof.xml");
        std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	    buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);
    	// Find our root node
    	root_node = doc.first_node("Lockerroom");

        // Iterate over the Lockers
        for (rapidxml::xml_node<>* locker_node = root_node->first_node("Locker"); locker_node; locker_node = locker_node->next_sibling()) {
            Locker* l = new Locker(); //every new "Locker" node results in a new Locker pointer

            //populate locker with xml data
            l->setName(locker_node->first_attribute("name")->value());
            l->setURL(locker_node->first_attribute("url")->value());
            l->setGroup(locker_node->first_attribute("grouping")->value());
            l->setID(atoi(locker_node->first_attribute("id")->value()));
            //populate the locker's user data
            rapidxml::xml_node<>* user_node = locker_node->first_node("User");
            l->setUsername(user_node->first_attribute("user")->value());
            l->setPassword(user_node->first_attribute("pass")->value());

            lockerroom.push_back(l); //add new locker to lockerroom vector
        }

    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error was: " << e.what() << std::endl;
    } catch (const rapidxml::parse_error& e) {
        std::cerr << "Parse error was: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error was: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
    return lockerroom;
}

void Profiler::exportToXML(std::vector<Locker*> lockerroom) {
    //load XML Database
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    //adding default init attributes at the top of our xml
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);

    //creating a pointer for the root note "Lockerroom"
    rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "Lockerroom");

    for (int i = 0; i < lockerroom.size(); i++) {
        rapidxml::xml_node<>* locker_node = doc.allocate_node(rapidxml::node_element, "Locker");
        //for each new attribute associated with the locker, we must allocate a string in order
            //to iterate through the vector database without corrupting the locker values
        char* lock_name = doc.allocate_string(lockerroom.at(i)->getName().c_str());
        char* lock_url = doc.allocate_string(lockerroom.at(i)->getURL().c_str());
        char* lock_group = doc.allocate_string(lockerroom.at(i)->getGroup().c_str());
        char* lock_id = doc.allocate_string(std::to_string(lockerroom.at(i)->getID()).c_str());
        locker_node->append_attribute(doc.allocate_attribute("name", lock_name));
        locker_node->append_attribute(doc.allocate_attribute("url", lock_url));
        locker_node->append_attribute(doc.allocate_attribute("grouping", lock_group));
        locker_node->append_attribute(doc.allocate_attribute("id", lock_id));

        //user credentials
        rapidxml::xml_node<>* user_node = doc.allocate_node(rapidxml::node_element, "User");
        char* lock_user = doc.allocate_string(lockerroom.at(i)->getUsername().c_str());
        char* lock_pass = doc.allocate_string(lockerroom.at(i)->getPassword().c_str());
        user_node->append_attribute(doc.allocate_attribute("user", lock_user));
        user_node->append_attribute(doc.allocate_attribute("pass", lock_pass));

        //populate current iteration of locker node
        locker_node->append_node(user_node);
        root->append_node(locker_node);
    }

    doc.append_node(root);
    std::string xml_as_string;
    rapidxml::print(std::back_inserter(xml_as_string), doc);
    std::ofstream fileStored("./db/prof.xml");
    fileStored << xml_as_string;
    fileStored.close();
    doc.clear();
}

// https://stackoverflow.com/a/12774387
bool Profiler::file_exists(std::string name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

bool Profiler::dir_exists(std::string path) {
    if (fs::is_directory(path)) {
        return true; //valid dir
    } else {
        //no dir found
        printf("%s was not found.. Creating new database directory\n", path.c_str());
        fs::create_directory(path); //create the db directory
        return true;
    }
    return false;
}
