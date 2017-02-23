/*

Humza Abid
Secure & Dependable Systems 

Assignment 1

Transcription of Apple 'goto fail' bug
*/

#include <iostream>

#define OSStatus int 

class SSLHash{

private:
    
    bool value;
public:
    
    SSLHash(){value = 0;};
    SSLHash(const SSLHash &o){this->value = o.value;};
    ~SSLHash(){};
   
    bool update(bool hashCtx, bool serverRandom){return hashCtx & serverRandom;};
    bool final(bool hashCtx, bool hashOut){return hashCtx & hashOut;}
};

OSStatus   SSLVerifySignedServerKeyExchange(bool signedParams, bool serverRandom, bool hashCtx,
                                     bool hashOut);
void SSLFreeBuffer(bool value){}

OSStatus SSLVerifySignedServerKeyExchange( bool signedParams, bool serverRandom, 
                                            bool hashCtx, bool hashOut){
    
    OSStatus err;
    SSLHash SSLHashSHA1;
    
    if((err = SSLHashSHA1.update(hashCtx, serverRandom) != 0))
        goto fail;
    if((err = SSLHashSHA1.update(hashCtx, signedParams) !=0 ))
        goto fail;
        goto fail;
    if((err = SSLHashSHA1.final(hashCtx, hashOut) != 0))
        goto fail;
    
    
fail:
    SSLFreeBuffer(hashCtx);
    SSLFreeBuffer(hashOut);
    return err;
}

int main(){
    
    bool hashCtx = 0;
    bool signedParams = 0;
    bool serverRandom = 0;
    bool hashOut = 0;
    
    SSLVerifySignedServerKeyExchange(signedParams, serverRandom, hashCtx,
                                     hashOut);
    
    return 0;
}