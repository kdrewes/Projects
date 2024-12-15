
#ifndef removeComments_hpp
#define removeComments_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include "Tokenize.h"

// Create enums which are used as a labeling techiques
enum DFA {SINGLE_LINE_COMMENTS, MULTI_LINE_COMMENTS, QUOTATION_MARKS, CHARACTER, SIZE};
enum BOOLEAN {BOOLEAN_SINGLE_LINE_COMMENTS, BOOLEAN_MULTI_LINE_COMMENTS, BOOLEAN_QUOTATION_MARKS, BOOLEAN_SIZE, NEW_LINE};

class removeComments
{
    
private:
    // Contains all files
    std::vector<std::string>TestFiles;
    
    // Declarle vector that holds the file output for each file
    std::vector<std::string>Files;

public:
    
    // Constructor
    removeComments(std::vector<std::string> TestFiles);
    
    // Collects output of each file
    void Execute();
    
    // Once comment are removed, contents will be written to separate file
    void WriteFile(int count, std::string fileContents);
    
    // Returns the character read from each file
    char Read_Character(DFA dfa, std::ifstream &read, char character, std::map<BOOLEAN,bool> &BooleanMap);

    // Returns the appropiate enum
    DFA Read_Character_Helper(std::map<BOOLEAN,bool> BooleanMap);
    
    // Returns the contents of each file
    std::string ReadFile(std::string fileName, int count);
    
    // Output remove comments object
    friend std::ostream & operator << (std::ostream &, removeComments &);
    
};

#endif
