#include <iostream>
#include <map>
#include <fstream>
#include "removeComments.h"
#include "Tokenize.h"
// ---------------------------------------- Prototypes ----------------------------------------

// Returns the contents of each file
std::string ReadFile(std::string fileName);

// Returns the character read from each file
char Read_Character(DFA dfa, std::ifstream &read, char character, std::map<BOOLEAN,bool> &BooleanMap);

// Returns the appropiate enum
DFA Read_Character_Helper(std::map<BOOLEAN,bool> BooleanMap);
// --------------------------------------------------------------------------------------------
int main(int argc, const char * argv[]) {
    
    removeComments remove({
        "testFile1.c",
        "testFile2.c",
        "testFile3.c",
        "testFile4.c",
        "testFile5.c",
        "testFile6.c"
    });
    
    remove.Execute();
    
    //std::cout << remove << std::endl;
    
    Tokenize token({
        "textFile1.txt",
        "textFile2.txt",
        "textFile3.txt",
        "textFile4.txt",
        "textFile5.txt",
        "textFile6.txt"
    });
    
    token.Execute();
    
    return 0;
}
// --------------------------------------------------------------------------------------------
