//
// Humza Abid
// SaDS Homework 6
// main.cpp
//

#include "encrypt_decrypt.cpp"

// a pseudo unit test, ie. without importing the libraries for it, was conducted as below,
// since it still fulfills the requirements of the task
bool pseudoUnitTest()
{
	int ivf = 17;
    int key = 48692;
    srand((unsigned)time(NULL));
    std::string input = "";
    
    for (int i =0; i < 20; i++)
    	input += (rand() %127);
    
    std::cout << "Original: " << input << std::endl;
    
    cipherBlockChaining chainBlock(input, ivf, key);
    
    std::cout <<"\nCBC Encrypted: "<< chainBlock.getData() << std::endl;
    
    chainBlock.decrypt();
    
    std::cout << "\nDecrypted: " << chainBlock.getData() << std::endl;
    
    std::string decrypted = chainBlock.getData();
    bool flag = !(decrypted == input);
    
    return flag;
}

int main(int argc, const char * argv[])
{
    bool unit = pseudoUnitTest();
    return unit;
}