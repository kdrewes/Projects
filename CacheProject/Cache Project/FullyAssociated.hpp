#ifndef FullyAssociated_hpp
#define FullyAssociated_hpp

#include <stdio.h>
#include <time.h>
#include <queue>
#include "Cache.h"
#include "Enums.h"

class FullyAssociated : public Cache
{
    
    // -------------- Typedef used for organizational purposes -------------
    
    // integer = numerical digit
    // unit = unit of measurements
    // input = variables uesd to select data
    // iterator = traverses through data set
    // index = represents the index of a data set
    // hashValue = used as hash value for hash table algorithm
    typedef int integer, unit, input, iterator, index, hashValue;
    
    // binary = binary data stored in each cache block
    // hex = hex data stored in each cache block
    // menu = consist of entire menu
    typedef std::string binary, hex, menu;
    
    // Used for boolean datatype
    typedef bool boolean;
    
    // inputSet = Stores input values, binaryVector = Stores binary values
    typedef std::vector<std::string> inputSet, binaryVector;
    
    // Key = Tag, Value = address
    typedef std::vector <std::pair<binary, binary>> hashAddress;
    
    // Key = tag, Value = addresses stored in queue
    typedef std::vector<std::pair<binary,std::queue<binary>>> tagAddress;
    
    // Write file
    typedef std::ofstream file;
    
    // Key = binary word, hexidecimal instruction
    typedef std::map<binary,hex> wordMap;
    
    // binaryHexMap = Represents a map inside a map
    typedef std::map<binary, std::map<binary,hex>> multiMap;
    
    // Key = tag, Value = std::vector<std::pair<address, frequenty of address detected in tagTable.second>>
    typedef std::map<binary, std::vector<std::pair<binary,integer>>> addressDetectorMap;
    
    // Condenses string into a single variable
    typedef std::ostringstream condensedString;
    
private:

    // Stores each column per row
    struct Fully_Associative_Structure
    {
        // Constructor
        Fully_Associative_Structure (FullyAssociated & f) :
        blockSize (f.blockSize), wordSize(f.wordSize), addressEvicted(""),
        address (f.addressList[std::rand() % f.addressList.size()]), wordQuantity(f.wordQuantity),
        tag (address.substr(0, address.size() - std::floor(log2(f.blockSize)))), instruction(GetInstruction()),
        offset (address.substr(address.size() - std::floor(log2(f.blockSize)), address.size())),
        wordCharacters(getWordCharacters(f.wordQuantity)), instructionMap(getInstructionMap(address,f.addressMap)),
        addressHashCode(GenerateHashCode(this -> address)), tagHashCode(GenerateHashCode(this -> tag))
        {
            instruction = GetInstruction();
        }
        
        // ----------------------------------------------------------------
        // Ensure the same address contains identical instructions
        std::map <binary,hex> getInstructionMap (binary addr, multiMap addressMap)
        {
            std::map <binary,hex> instructions;
            
            if(addressMap.find(addr) != addressMap.end())
            {
                std::map <binary,hex> tempMap = addressMap[addr];
                
                for(auto & t : tempMap)
                    instructions[t.first] = t.second;
            }

            return instructions;
        }
        
        // ----------------------------------------------------------------
        // Generate hash code for each address
        hashValue GenerateHashCode(binary binaryValue)
        {
            hashValue hashCode = 0;
            
            for(iterator i = 0; i < binaryValue.size(); i++)
            {
                if(binaryValue[i] ==  '1')
                    hashCode += pow(2,binaryValue.size() - i - 1);
            }
            
            return hashCode;
        }
        
        // ----------------------------------------------------------------
        // Find instruction for each address
        hex GetInstruction()
        {
            // Find specific word of address
            hex word;
            
            if(this -> wordQuantity != 1)
            {
                word = this -> address.substr( this -> address.size() - this -> wordCharacters, this -> address.size() );
                
                return instructionMap[word];
            }
            else
                word = instructionMap["Instruction"];

            
            return word;
        }
        
        // ----------------------------------------------------------------
        // Get # of word characters
        integer getWordCharacters(unit wrdQuantity)
        {
            integer numOfCharacters = 0;
            
            if(wrdQuantity == 4)
                numOfCharacters = 2;
            
            else if(wrdQuantity == 2)
                numOfCharacters = 1;
            
            else if(wrdQuantity == 1)
                numOfCharacters = 0;
            
            return numOfCharacters;
        }
        
        // ------------------------- Binary Data --------------------------
        
        
         binary address,          // Binary address
        
                tag,              // Tag in binary form
        
                offset,           // Offset in binary form
        
                instruction,      // Instruction of address
        
                addressEvicted;   // Address evicted from way
        
      hashValue tagHashCode,      // hash code of each tag
        
                addressHashCode;  // hash code of each address
        
           unit blockSize,        // Size of each block (Bytes)
        
                wordSize,         // Word count = (block size / word size)
        
                wordQuantity,     // # of words utilized by each address
                
                wordCharacters,   // # of characters in a word
        
                binaryWord;       // Binary word value
        
        wordMap instructionMap;   // Key = binary value of word
        
                                  // Value = Hex value of each instruction
                
    };
    
    // ----------------------------- Varaibles ------------------------------
    
    hashValue hashIndex;      // Assigned hash index
    
    boolean hitOrMiss;        // Determines hit or miss
    
    
    // --------------------------- Enum Variable ----------------------------
    
    // Select which hash table to use (address or tag)
    enum HASH_TABLE table;

    // -------------------------- Binary datasets ---------------------------
    
    // Stores all properties located in CacheData structure
    std::vector <Fully_Associative_Structure> Fully_Associative_Vector;
    
    // Hash table used to store addresses (Detects hit or miss)
    // Key = Tag, Value = address
    hashAddress addressTable;
    
    // Hash table used to store multiple ways
    // Key = tag, value = addresses stored in queue
    tagAddress tagTable;
    
    // Key = tag, Value = std::vector<std::pair<address, frequenty of address detected in tagTable.second>>
    addressDetectorMap addressDetector;
    
    // Declare queue to hold data for each way
    std::queue <binary> wayQueue;

public:
    
    FullyAssociated(PLACEMENT_POLICY policy, CONFIGURATION config) : Cache(policy, config)
    {
        Router();
        
        Controller();
    }
    
    ~FullyAssociated() override;
    
    // ------------------- Router & Controller functions  --------------------
    
     void Router();                     // Configure binary data
    
     void Controller();                 // Execute binary data
    
    // ----------------------- Hash Table Algorithms -------------------------
    
     void HashTable();                  // Performs implementation on hash table
    
     void AssignHashIndex();            // Assign addresses to their designated index
    
     index GetHashIndex                 // Retreive hash index
     (hashValue hashCode);
    
    // ------------------- Cache Replacements Algorithms  --------------------
    
     void Least_Recently_Used();        // Least Recently Used
     
     void Least_Frequently_Used();      // Least Frequently Used
    
     void First_In_First_Out();         // First in First Out
    
    // ---------------------------- Print Results  -----------------------------
    
     void Print() override;             // Print report
    
     void PrintFile();                  // Output results in file
    
     void PrintConsole();               // Output results in console
    
    // --------------------------- Misc Functions  -----------------------------

     void Title();                       // Display Title
   
     void Data();                        // Display data
    
     void Header();                      // Display header
    
     void CreateHeader                   // Produce column header
     (COLUMNS c);
    
     void Table();                       // Display chart
    
     void CreateTable                    // Produce rows and columns in table
     (COLUMNS c);
    
     void PlacementPolicy                // Contains placement policy algorithms
     (enum HASH_TABLE);
    
     std::string toLower                 // Make each string lower case
     (std::string header);
    
     COLUMNS FindHeader                  // Find header for each column
     (std::string header);
    
     COLUMNS FindColumn                  // Find column for each row
     (std::string column);
    
     HASH_TABLE FindTable                // Find addressTable or tagTag hashing formula
     (std::string table);
    
     
};

#endif

