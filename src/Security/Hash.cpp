#include "Hash.h"

Hash::Hash() {

}

void Hash::test() {
    // static constexpr size_t AES_KEY_SIZE = 256 / 8; //AES-256
    //
    // const std::string input {"This is a secret message."};
    // std::vector<uint8_t> key(AES_KEY_SIZE);
    // std::vector<uint8_t> iv(CryptoPP::AES::BLOCKSIZE);
    //
    // CryptoPP::BlockingRng rand;
    // rand.GenerateBlock(key.data(), key.size());
    // rand.GenerateBlock(iv.data(), iv.size());
    //
    // auto cipher = Hash::encrypt(input, key, iv);
    // auto plain_text = Hash::decrypt(cipher, key, iv);
    //
    // if (plain_text != input) {
    //     std::cout << "Error: plain text doesn't match the input" << std::endl;
    // }
}

// std::string Hash::encrypt(const std::string& input, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {
//     std::string cipher;
//
//     auto aes = CryptoPP::AES::Encryption(key.data(), key.size());
//     auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Encryption(aes, iv.data());
//
//     CryptoPP::StringSource ss(
//         input,
//         true,
//         new CryptoPP::StreamTransformationFilter(
//             aes_cbc,
//             new CryptoPP::Base64Encoder(
//                 new CryptoPP::StringSink(cipher)
//             )
//         )
//     );
//
//     return cipher;
// }
//
// std::string Hash::decrypt(const std::string& cipher_text, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {
//     std::string plain_text;
//
//     auto aes = CryptoPP::AES::Decryption(key.data(), key.size());
//     auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Decryption(aes, iv.data());
//
//     CryptoPP::StringSource ss(
//         cipher_text,
//         true,
//         new CryptoPP::Base64Decoder(
//             new CryptoPP::StreamTransformationFilter(
//                 aes_cbc,
//                 new CryptoPP::StringSink(plain_text)
//             )
//         )
//     );
//
//     return plain_text;
// }
