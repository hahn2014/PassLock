# PassLock

### Welcome to PassLock, the all-encompassing *Local Password Manager*.
PassLock is a portable database manager with industry-standard password hashing security. Developed by [@hahn2014](https://github.com/hahn2014/) in order to get around the paywalls being put in place on most Online Password Manager alternatives (LastPass, OnePass, etc...). PassLock is free and always will be. Period. While I am tempted to implement a cross-platform syncing function (and even more convenient, phone app with sync), I am committed to the concept of local storage. Data is incredibly valuable, not only to my users but to anyone attempting to access said data. Keeping the user's credentials locally stored and encrypted guarantees privacy and safety. An encrypted database export is a possible option in the future for cross-platform syncing; however, this *fix* would only be a temporary solution to the syncing dilemma.

---

## Uses

> *Why should you use a local password manager rather than the convenience of online PMs such as LastPass or OnePass?*

PassLock keeps your private data and passwords stored in a local database that will never see the light of day on the internet. Privacy is a huge concern in today's ever-evolving world of tech. With a locally stored database, PassLock is the best way to quickly add/edit/view your login credentials without ever having to worry about the next big data breach from big tech.

> *What steps are being taken for password security and encryption?*

Currently, I have omitted any form of password storage until I can guarantee industry-standard password hashing and encryption. I plan to utilize SHA3-256/512 to hash usernames and passwords in order to guarantee local cryptography.

> *Can I use PassLock even though it is still in active development?*

PassLock is currently still in development and thus will have some unforeseen memory leaks or other vulnerabilities. If you choose to use the nightly source rather than a staged release, please proceed with caution. That being said, I do my best to test for bug and memory leaks prior to pushing to main; However, nobody is perfect and I may miss something here or there, please use the [issue reporting](https://github.com/hahn2014/PassLock/issues) page on the repository to submit any found bugs/compilation errors/etc... (bug testers welcome!)

> *Can I fork PassLock and make my own implementation?*

Open Source is the best form of software development. I welcome anyone to fork my repository and would love to get updates on how you choose to implement your own Password Manager.

---

## Development Roadmap

- [x] Initial Command Line Interface backbone
    - [x] Create Lockers
    - [x] Delete Lockers
    - [x] Search Lockers
    - [x] Edit Lockers
- [x] User profile creation and loading
    - [x] Startup password access
    - [x] Lockerroom XML data populating
        - [x] Import previous session database on startup
        - [x] Export current lockerroom and update prof.xml on shutdown
        - [x] Exit without updating changes to database
    - [x] Exclusive XML database parsing
    - [x] Choice between multiple profile databases at startup
- [ ] Password hashing and encryption
    - [ ] SHA3-256 SHA3-512 Hashing Algorithm implementation
        - [ ] Initial hash compare to verify user password with hashfile
        - [ ] XML database hashing
- [ ] Simple Graphical User Interface implementation
- [ ] Multi-platform executable ports
- [ ] Database encrypted export/import
- [ ] More to come...

---

## Compiling
- **MacOS - Windows 10/11 - Linux/Unix Systems**

Compiling from source code should be as simple as calling `make` in the root directory. If you are unable to compile using the provided makefile, try the `gcc` compiler command below.


- **GCC CLI Compiling**

Firstly, we need to make the build dir to compile all our .o files into. Enter this into your terminal: `mkdir build`

Then, we can call the compilation statement:
`gcc -I./src/IO/ -I./src/Locker/ -I./src/Security/ -I./lib/rapidxml/ -std=c++17 -c ./src/PassLock.cpp -O1 -g -v -o ./build/PassLock`
