#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/default.h>

class Hash {
public:
    //DEBUG for testing, should not be accessible in the future
    void static hashFile(char*);
    std::string static hashUserPass(std::string, std::string);
    bool static compareHash(std::string, std::string);

    //  Crypto++ Documentation for AES encryption/decryption
    // https://cryptopp.com/wiki/DefaultEncryptorWithMAC
    std::string static encrypt(std::string, std::string);
    std::string static decrypt(std::string, std::string);
};

#endif
