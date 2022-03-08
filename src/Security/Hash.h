#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

class Hash {
public:
    //DEBUG for testing, should not be accessible in the future
    void static hashFile(char*);
    std::string static hashUserPass(std::string, std::string);
};

#endif
