#ifndef HASH_H
#define HASH_H

#include <iostream>
// #include <cryptopp/cryptlib.h>
// #include <cryptopp/modes.h>
// #include <cryptopp/aes.h>
// #include <cryptopp/filters.h>
// #include <cryptopp/osrng.h>
// #include <cryptopp/base64.h>

class Hash {
public:
    Hash();
    //DEBUG for testing, should not be accessible in the future
    void static test();
    // std::string static encrypt(const std::string&, const std::vector<uint8_t>&, const std::vector<uint8_t>&);
    // std::string static decrypt(const std::string&, const std::vector<uint8_t>&, const std::vector<uint8_t>&);
    // getters and setters
};

#endif
