#include "Profiler.h"

namespace fs = std::filesystem;

bool Profiler::startup() {
    if (dir_exists("./db/")) {
        //scan for multiple .xml files
        std::string prof = getProfileNames();

        if (prof == "0") { //no .xml database profiles found, create a new one
            createProfile(); //create a user
            exportToXML({}); //export an empty lockerroom to xml (bare min user prof)
            return startup(); //recursively call startup to validate newly created ini file
        } else { //getProfileNames found at least one .xml database profile and the user picked
            setUser(prof);
            return true; //set username from user input, then wait for getLockerroom call
        }
    }
    return false;
}

std::string Profiler::getProfileNames() {
    std::string path("./db/");
    std::string ext(".xml");
    std::vector<std::string> profiles;
    for (auto &p : fs::recursive_directory_iterator(path)) {
        if (p.path().extension() == ext) {
            profiles.push_back(p.path().stem().string()); //push back each .xml name
        }
    }
    if (profiles.size() == 0) return "0";
    //get user confirmation on which profile to load
    Log::Info("%lu user profiles were found:\n", profiles.size());
    for (int i = 0; i < profiles.size(); i++) {
        printf("- %s\n", profiles.at(i).c_str());
    }
    printf("\nWhich profile should I load? -- (or 0 for new profile)\n");

    std::string profile = Log::getInput("Profile", 1, 32);

    //search the vector for the user input
    if (std::find(profiles.begin(), profiles.end(), profile) != profiles.end()) {
        return profile;
    } else {
        return "0";
    }
}

void Profiler::createProfile() {
    std::string user;
    std::string password;
    printf("\n--- New Lockerroom ---\n");

    //get username
    user = Log::getInput("Profile Username", 4, 32);

    //indefinite while loop to keep prompting a password until both values match
    while (true) {
        //get user password
        password = Log::getInput("Profile Password", 8, 64);

        //verify password is what the user wants
        if (password == Log::getInput("Confirm Password", 8, 64)) {
            Log::Info("Passwords match!\n\n");
            break;
        } else {
            Log::Error("Passwords did not match!\n");
        }
    }
    //only store the hashed username and password, no plaintext password
    setUser(user);
    setHash(Hash::hashUserPass(user, password));
}

void Profiler::setHash(std::string hash) {
    this->hash = hash;
}

std::string Profiler::getHash() {
    return this->hash;
}

void Profiler::setUser(std::string user) {
    this->user = user;
}

std::string Profiler::getUser() {
    return this->user;
}

//Minimalized import function exclusively to extract the userprofile hash value
std::string Profiler::getProfileHash() {
    std::ostringstream oss;
    oss << "./db/" << getUser() << ".xml";
    std::string userprof = oss.str();
    Log::Debug("Importing profile hash from XML Database: %s\n", oss.str().c_str());

    std::string profile_hash;

    try {
        //load XML Database
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* root_node;
    	// Read the xml file into a string vector
        std::ifstream xmlFile(userprof);
        std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	    buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);
    	// Find our root node
    	root_node = doc.first_node("Lockerroom");

        rapidxml::xml_node<>* user_prof_node = root_node->first_node("UserProfile");
        profile_hash = user_prof_node->first_attribute("hash")->value();
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error was: " << e.what() << std::endl;
    } catch (const rapidxml::parse_error& e) {
        std::cerr << "Parse error was: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error was: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
    return profile_hash;
}

std::vector<Locker*> Profiler::getLockerroom() {
    std::ostringstream oss;
    oss << "./db/" << getUser() << ".xml";
    std::string userprof = oss.str();
    //test is prof.xml even exists
    if (file_exists(userprof)) {
        return importFromXML(); //attempt to load
    } else {
        Log::Info("no user XML database was found... could not load a previously populated lockerroom\n\n");
    }
    return {};
}

void Profiler::saveLockerroom(std::vector<Locker*> lockerroom) {
    std::ostringstream oss;
    oss << "./db/" << getUser() << ".xml";
    std::string userprof = oss.str();
    //verify if xml file already exists
    if (file_exists(userprof)) {
        //delete existing database export
        if (std::remove(userprof.c_str()) != 0)
            Log::Error("Error deleting old database\n\n");
        else
            Log::Info("Outdated database successfully deleted\n\n");
    }
    exportToXML(lockerroom); //create new updated database XML
}


std::vector<Locker*> Profiler::importFromXML() {
    std::ostringstream oss;
    oss << "./db/" << getUser() << ".xml";
    std::string userprof = oss.str();
    Log::Debug("Importing from XML Database: %s\n", oss.str().c_str());

    std::vector<Locker*> lockerroom; //store a vector of lockers
    try {
        //load XML Database
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* root_node;
    	// Read the xml file into a string vector
        std::ifstream xmlFile(userprof);
        std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	    buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);
    	// Find our root node
    	root_node = doc.first_node("Lockerroom");

        rapidxml::xml_node<>* user_prof_node = root_node->first_node("UserProfile");
        setHash(user_prof_node->first_attribute("hash")->value());
        Log::Debug("Profile User-Pass Hash: %s\n", getHash().c_str());

        // Iterate over the Lockers
        for (rapidxml::xml_node<>* locker_node = root_node->first_node("Locker"); locker_node; locker_node = locker_node->next_sibling()) {
            Locker* l = new Locker(); //every new "Locker" node results in a new Locker pointer
            Log::Debug("Locker %s attributes:\n", locker_node->first_attribute("id")->value());
            //populate locker with xml data
            l->setName(locker_node->first_attribute("name")->value());
            l->setURL(locker_node->first_attribute("url")->value());
            l->setGroup(locker_node->first_attribute("grouping")->value());
            l->setID(atoi(locker_node->first_attribute("id")->value()));

            Log::Debug("\tLocker Name : %s\n", l->getName().c_str());
            Log::Debug("\tLocker URL  : %s\n", l->getURL().c_str());
            Log::Debug("\tLocker Group: %s\n", l->getGroup().c_str());
            Log::Debug("\tLocker ID   : %i\n", l->getID());

            //populate the locker's user data
            rapidxml::xml_node<>* user_node = locker_node->first_node("User");
            l->setUsername(user_node->first_attribute("user")->value());
            l->setPassword(user_node->first_attribute("pass")->value());

            Log::Debug("\t\tLocker User: %s\n", l->getUsername().c_str());
            Log::Debug("\t\tLocker Pass: %s\n", l->getPassword().c_str());

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
    std::ostringstream oss;
    oss << "./db/" << getUser() << ".xml";
    std::string userprof = oss.str();
    Log::Debug("Exporting to XML Database: %s\n", oss.str().c_str());
    //load XML Database
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    //adding default init attributes at the top of our xml
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);

    //creating a pointer for the root note "Lockerroom"
    rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "Lockerroom");

    //User profile node
    rapidxml::xml_node<>* user_prof_node = doc.allocate_node(rapidxml::node_element, "UserProfile");
    //allocate the memory for the userpass hash
    char* user_pass = doc.allocate_string(getHash().c_str());
    // char* user_name = doc.allocate_string(this->getUser().c_str());
    // char* user_pass = doc.allocate_string(this->getPass().c_str());
    user_prof_node->append_attribute(doc.allocate_attribute("hash", user_pass));
    root->append_node(user_prof_node);
    // Log::Debug("Profile User: %s\n", user_prof_node->first_attribute("user")->value());
    // Log::Debug("Profile Pass: %s\n", user_prof_node->first_attribute("pass")->value());
    Log::Debug("Profile User-Pass Hash %s\n", user_prof_node->first_attribute("hash")->value());

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
        //allocate memory for the locker's username and password encrypted text
        char* lock_user = doc.allocate_string(lockerroom.at(i)->getUsername().c_str());
        char* lock_pass = doc.allocate_string(lockerroom.at(i)->getPassword().c_str());
        user_node->append_attribute(doc.allocate_attribute("user", lock_user));
        user_node->append_attribute(doc.allocate_attribute("pass", lock_pass));

        Log::Debug("\tLocker Name : %s\n", locker_node->first_attribute("name")->value());
        Log::Debug("\tLocker URL  : %s\n", locker_node->first_attribute("url")->value());
        Log::Debug("\tLocker Group: %s\n", locker_node->first_attribute("grouping")->value());
        Log::Debug("\tLocker ID   : %s\n", locker_node->first_attribute("id")->value());
        Log::Debug("\t\tLocker User: %s\n", user_node->first_attribute("user")->value());
        Log::Debug("\t\tLocker Pass: %s\n", user_node->first_attribute("pass")->value());

        //populate current iteration of locker node
        locker_node->append_node(user_node);
        root->append_node(locker_node);
    }

    doc.append_node(root);
    std::string xml_as_string;
    rapidxml::print(std::back_inserter(xml_as_string), doc);
    std::ofstream fileStored(userprof);
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
        Log::Info("%s was not found.. Creating new database directory\n", path.c_str());
        fs::create_directory(path); //create the db directory
        return true;
    }
    return false;
}
