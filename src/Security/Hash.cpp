#include "Hash.h"

std::string Hash::hashUserPass(std::string user, std::string pass) {
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    std::string salt, output;

    //create the username and password salt
    salt = user + pass;
    hash.CalculateDigest(digest, (const CryptoPP::byte*)salt.c_str(), salt.size());

    CryptoPP::HexEncoder encoder;
    CryptoPP::StringSink* SS = new CryptoPP::StringSink(output);
    encoder.Attach(SS);
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}

void Hash::hashFile(char* filename) {
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::FileSource f(filename, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

    std::cout << digest << std::endl;
}
