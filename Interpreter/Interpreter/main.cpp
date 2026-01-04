#include <iostream>
#include <map>
#include <fstream>
#include "removeComments.h"
#include "Tokenize.h"

int main(int argc, const char * argv[]) {
    
    removeComments remove
    ({
        "testFile1.c",
        "testFile2.c",
        "testFile3.c",
        "testFile4.c",
        "testFile5.c",
        "testFile6.c"
    });
    
   // Execute removal of comments
   // std::cout << remove << std::endl;
    
    Tokenize token
    ({
        "textFile1.txt",
        "textFile2.txt",
        "textFile3.txt",
        "textFile4.txt",
        "textFile5.txt",
        "textFile6.txt"
    });
    
    // Execute tokenization
    std::cout << token << std::endl;
    
    return 0;
}
// --------------------------------------------------------------------------------------------
