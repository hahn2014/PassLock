#include "Hash.h"

// encryptiong and hashing overview and basic ideas from:
// credit where credit is due: https://crypto.stackexchange.com/questions/32648/questions-about-a-sha3-cipher-stream-encryption-scheme

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

std::string Hash::encrypt(std::string plaintext, std::string hash_salt) {
    std::string encryptedtext;

    CryptoPP::StringSource ss1(plaintext, true,
        new CryptoPP::DefaultEncryptorWithMAC(
            (CryptoPP::byte*)&hash_salt[0], hash_salt.size(),
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(encryptedtext)
            )
        )
    );
    return encryptedtext;
}

std::string Hash::decrypt(std::string crypttext, std::string hash_salt) {
    std::string decryptedtext;

    CryptoPP::StringSource ss2(crypttext, true,
        new CryptoPP::HexDecoder(
            new CryptoPP::DefaultDecryptorWithMAC(
            (CryptoPP::byte*)&hash_salt[0], hash_salt.size(),
                new CryptoPP::StringSink(decryptedtext)
            )
        )
    );
    return decryptedtext;
}

bool Hash::compareHash(std::string hashA, std::string hashB) {
    return hashA == hashB;
}

void Hash::hashFile(char* filename) {
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::FileSource f(filename, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

    std::cout << digest << std::endl;
}
