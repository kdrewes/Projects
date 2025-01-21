#include "removeComments.h"
#include <fstream>

// Constructor
removeComments :: removeComments(std::vector<std::string> TestFiles)
{
    this -> TestFiles = TestFiles;
}
// ------------------------------------------------------------------
// Initiates process of collecting content from each file
void removeComments :: Execute()
{
    // Extracting information onto the output vector
    for(std::vector<std::string>::size_type i = 0; i < TestFiles.size(); i++){
        this -> Files.push_back(this -> ReadFile(this -> TestFiles[i], i+1));
    }
    
    TestFiles.clear();
}
// ------------------------------------------------------------------
// Reads each file and removes comments
std::string removeComments :: ReadFile(std::string fileName, int count){
    
    // Contains all the file content excluding the comments
    std::string fileContent;
    
    // File variable which reads content of file
    std::ifstream read(fileName,std::ios::in);
    
    // Determines if there are comments or quotation marks in a file
    std::map<BOOLEAN,bool>BooleanMap;
    
    // Initialize BooleanMap
    for(int i = 0; i < BOOLEAN::BOOLEAN_SIZE; i++)
        BooleanMap[static_cast<BOOLEAN>(i)] = false;
    
    // Perform input validation
    if(read.is_open())
        for(char character = '\0'; !read.eof(); read >> std::noskipws >> character){
            fileContent += Read_Character(Read_Character_Helper(BooleanMap), read, character, BooleanMap);
            if(BooleanMap[BOOLEAN::NEW_LINE]){
                BooleanMap[BOOLEAN::NEW_LINE] = false;
                fileContent += '\n';
            }
        }
    
    else{
        std::cerr << "file is not open.\n";
        exit(1);
    }
    
    read.close();
    
    return fileContent;
    
}
// --------------------------------------------------------------------------------------------
// Write file contents
void removeComments :: WriteFile(int count, std::string fileContents){
    std::ofstream write("textFile" + std::to_string(count) + ".txt", std::ios::out);
    {
        write << fileContents << std::endl;
    }
    write.close();
}
// --------------------------------------------------------------------------------------------
// Returns the character read from each file
char removeComments :: Read_Character(DFA dfa, std::ifstream &read, char character, std::map<BOOLEAN,bool> &BooleanMap){
    
    switch(dfa){
        case SINGLE_LINE_COMMENTS:
            if(read.peek() == '\n')
                BooleanMap[BOOLEAN::BOOLEAN_SINGLE_LINE_COMMENTS] = false;
            character = ' ';
            break;
            
        case MULTI_LINE_COMMENTS:
            if(character == '*')
                if(read.peek() == '/'){
                    BooleanMap[BOOLEAN::BOOLEAN_MULTI_LINE_COMMENTS] = false;
                    read.ignore();
                }
            character = ' ';
            break;
            
        case CHARACTER:
            if(character == ' ')
                return ' ';
            
            if(read.peek() == '\n')
                BooleanMap[BOOLEAN::NEW_LINE] = true;
            
            if(character != '/' && character != '*')
                break;
            
            else if(character == '/'){
                
                if(read.peek() != '/' && read.peek() != '*')
                    break;
                else{
                    if(read.peek() == '/')
                        BooleanMap[BOOLEAN::BOOLEAN_SINGLE_LINE_COMMENTS] = true;
                    else if(read.peek() == '*')
                        BooleanMap[BOOLEAN::BOOLEAN_MULTI_LINE_COMMENTS] = true;
                    
                    read.ignore();
                    character = ' ';
                }
            }
    }
    
    return character;
}

// --------------------------------------------------------------------------------------------
// Returns the appropiate enum
DFA removeComments :: Read_Character_Helper(std::map<BOOLEAN,bool> BooleanMap){
    
    if(BooleanMap[BOOLEAN::BOOLEAN_SINGLE_LINE_COMMENTS])
        return DFA::SINGLE_LINE_COMMENTS;
    
    else if(BooleanMap[BOOLEAN::BOOLEAN_MULTI_LINE_COMMENTS])
        return DFA::MULTI_LINE_COMMENTS;
    
    return DFA::CHARACTER;
}
// --------------------------------------------------------------------------------------------
std::ostream & operator << (std::ostream &output, removeComments &r)
{
    
    // Display information of Output Vector
    for(std::vector<std::string>::size_type i = 0; i < r.Files.size(); i++){
        output << "------------------ " << "File " << i + 1 << " ------------------\n";
        output <<  r.Files[i] << std::endl << std::endl;
        
        // Write file
        r.WriteFile(i+1,r.Files[i]);
    }
    
    return output;
}
// ------------------------------------------------------------------
