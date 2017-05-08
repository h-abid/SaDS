//
// Humza Abid
// SaDS Homework 6
// encrypt_decrypt.cpp
//

#include "encrypt_decrypt.h"

substitutionCipher::substitutionCipher(char newInput, int newKey)
{
    data = newInput; 
    key = newKey;
    
    encrypt();
}

void substitutionCipher::encrypt()
{
    int k1, k2;
    int k = 0;
    char c= 0, temp = 0;
    char encrypted = this->data;

    k1 = this->key>>8;
    k2 = this->key & 255;

    for(int j = 0; j < 2; j++)
    {
        temp = encrypted & 15;
        c = encrypted >> 4;
        c = c & 15;
        
        c = substitute(c);
        temp = substitute(temp);
        
        c = c<<4;
        c = c | temp;
        
        c = permute(c);
        
        if(j == 0)
        	k = k1;
        else if(j == 1)
        	k = k2;
        
        c = xorKey(c, k);
        encrypted = c;
    }
    
    this->data = encrypted;
}

void substitutionCipher::decrypt()
{
    int k1, k2;
    int k = 0;
    char c = 0, temp = 0;
    char decrypted = this->data;
 
    k1 = this->key>>8;
    k2 = this->key & 255;
    
    
    for (int j = 1; j >= 0 ; j--)
    {
        c = decrypted;
        if(j == 0)
        	k = k1;
        else if(j == 1)
        	k = k2;
       
        c = xorKey(c, k);
        c = invertPer(c);
        
        temp = c & 15;
        c = c >> 4;
        c = c &15;
        
        c= invertSub(c);
        temp = invertSub(temp);
        
        c = c<<4;
        c = c | temp;
        decrypted = c;
    }

    this->data = decrypted;
}

char substitutionCipher::substitute(char c)
{  
    c = ((c + 1) * 7) % 17 - 1;
    
    return c;
}

char substitutionCipher::invertSub(char c) // implementing the inverse of the modulo was cumbersome, excuse the brute nature
{
    int inputAsInt = c;

    switch (inputAsInt) {
        case 0:
            c = 4;
            break;
        case 1:
            c = 9;
            break;
        case 2:
            c = 14;
            break;
        case 3:
            c = 2;
            break;
        case 4:
            c = 7;
            break;
        case 5:
            c = 12;
            break;
        case 6:
            c = 0;
            break;
        case 7:
            c = 5;
            break;
        case 8:
            c = 10;
            break;
        case 9:
            c = 15;
            break;
        case 10:
            c = 3;
            break;
        case 11:
            c = 8;
            break;
        case 12:
            c = 13;
            break;
        case 13:
            c = 1;
            break;
        case 14:
            c = 6;
            break;
        case 15:
            c = 11;
            break;
            
        default:
            std::cout << "Error!" << std::endl;
            std::exit(1);
            break;
    }
    return c;
}

char substitutionCipher::permute(char c)
{
    char pb = c & (64+128);
    
    pb = pb >> 6;
    pb = pb & 3;
    
    c = c<<2;
    c = c | pb;
    
    return c;
}

char substitutionCipher::invertPer(char c)
{
    int i = c;
    char pb = i & 3;
    
    pb = pb << 6;
    
    c = c >>2;
    c = c & (1+2+4+8+16+32);
   	c = c | pb;
  
    return c;
}

char substitutionCipher::xorKey(char c, int k) 
{
    c ^= k;
    return c;
}

cipherBlockChaining::cipherBlockChaining(std::string newdat, int vf, int nkey)
{
    data = newdat;
    ivf = vf;
    key = nkey;
    
    this->encrypt();
}

void cipherBlockChaining::encrypt()
{
	std::string blockEncrypted = this->data;
    int ci[blockEncrypted.size()];
    ci[0] = this->ivf;
      
    for(int i = 0; i < blockEncrypted.size(); i++){
        blockEncrypted[i] ^= ci[i];
        this->blocks.push_back(substitutionCipher(blockEncrypted[i], this->key));
        blockEncrypted[i]= blocks[i].getData();
        ci[i+1] = blocks[i].getData();
    }
    this->data = blockEncrypted;
}

void cipherBlockChaining::decrypt()
{
    std::string blockDecrypted = this->data;
    int ci[blockDecrypted.size()];
    ci[0] = this->ivf;
   
    for(int i = 0; i < blockDecrypted.size(); i++)
    {
        if(i+1 != blockDecrypted.size())
        	ci[i+1] = blockDecrypted[i];
        
        blocks[i].decrypt();
        blockDecrypted[i] = blocks[i].getData();
        blockDecrypted[i] ^= ci[i];
    }
    
    this->data = blockDecrypted;
    
}

std::string cipherBlockChaining::getData()
{
    return this->data;
}
