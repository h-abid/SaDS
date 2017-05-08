//
// Humza Abid
// SaDS Homework 6
// main.cpp
//

#include "encrypt_decrypt.cpp"

#include <fstream>

using namespace std;

int main(int argc, const char * argv[])
{
    int ivf = 150;
    int key = 48692;

    std::vector<char> data;
    std::ifstream inputFile;
    std::ofstream encryptedFile;
    
    inputFile.open("tux.png", std::ios::binary);
    
    if(!inputFile.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        exit(1);
    }
    

    // CBC Encryption
    std::string content((std::istreambuf_iterator<char>(inputFile)), (std::istreambuf_iterator<char>()));
    cipherBlockChaining fileEncryption(content, ivf, key);
    
    inputFile.close();
    
    encryptedFile.open("encryptedFile.png", std::ios::binary);
    
    if(!encryptedFile.is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        exit(1);
    }
    
    encryptedFile << fileEncryption.getData();
    encryptedFile.close();
    
    // Trivial Mode of Operation
    std::ofstream triviallyEncrypted;
    
    triviallyEncrypted.open("triviallyEncrypted.png", std::ios::binary);
    
    if(!triviallyEncrypted.is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        exit(1);
    }
    
    trivialEncryption trivialEncryption(content, key);
    
    triviallyEncrypted << trivialEncryption.getData();
    
    triviallyEncrypted.close();

    std::cout << "Both encrypted files successfully produced." << std::endl;
    return 0;
}