//
// Humza Abid
// SaDS Homework 6
// encrypt_decrypt.h
//

#ifndef encrypt_decrypt_h
#define encrypt_decrypt_h

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <string>
#include <time.h>

// Abstract classes
class symmetricEncryption 
{
public:
    virtual void encrypt(void) = 0;
    virtual void decrypt(void) = 0;
};

class blockCipher
{
public:
    virtual void encrypt(void) = 0;
    virtual void decrypt(void) = 0;
};

// Concrete classes
class substitutionCipher: public blockCipher
{
public:
    substitutionCipher(){data = 0; key = 0; }
    substitutionCipher(char newInput, int newKey);
    ~substitutionCipher(){};
    
    void encrypt(void);
    void decrypt(void);
    
    char substitute(char c);
    char invertSub(char c);
    char permute(char c);
    char invertPer(char c);
    char xorKey(char c, int key);

    char getData(){return this->data;} 

 private:
    char data;
    int key;   
};


class cipherBlockChaining: public symmetricEncryption
{  
public:
    cipherBlockChaining(){data = "" , ivf = 0; key = 0;}
    cipherBlockChaining(std::string newDat, int vf, int key);
    ~cipherBlockChaining(){blocks.clear();};
    
    void decrypt();
    void encrypt();
    
    std::string getData();

private:
    std::string data;
    int ivf;
    int key;
    std::vector<substitutionCipher> blocks;
};

class trivialEncryption:public symmetricEncryption{
public:
    trivialEncryption(){data ="" ; key = 0;}
    trivialEncryption(std::string newData, int newKey);
    ~trivialEncryption(){BlockCyphers.clear();};
    
    void decrypt();
    void encrypt();
    
    std::string getData();

private:
    std::string data;
    int key;
    std::vector<substitutionCipher> BlockCyphers;    
};

#endif