#ifndef Cache_hpp
#define Cache_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <fstream>
#include "Enums.h"

// Interface for all cache placement policies
class Cache
{
    
protected:
    
    // -------------- Typedef used for organizational purposes -------------
    
    // unit = unit of measurements
    // input = variables uesd to select data
    // iterator = traverses through data set
    // hashValue = used as hash value for hash table algorithm
    typedef int unit, input, iterator, hashValue;
    
    // binary = binary data stored in each cache block
    // hex = hex data stored in each cache block
    // menu = consist of entire menu
    typedef std::string binary, hex, menu;
    
    // inputSet = Stores input values, binaryVector = Stores binary values
    typedef std::vector<std::string> inputSet, binaryVector;
    
    // Write file
    typedef std::ofstream file;
    
    // multiMap = Represents a map inside a map
    typedef std::map<binary, std::map<binary,hex>> multiMap;
    
    // Key = binary tag, values = addresses stored in queue
    typedef std::map<binary,std::queue<binary>> wayMap;
    
    // Condenses string into a single variable
    typedef std::ostringstream condensedString;
    
    // ---------------------------- File data ----------------------------
    
    file write;                // Establish file for Fully Associative,
    
    // -------------------------- Numerical data --------------------------
    
     unit cacheSize,          // Total amount of block data (Bytes)
    
          blockSize,          // Size of each block (Bytes)
    
          mainMemorySize,     // Size of main memory (Bits)
    
          offsetSize,         // Offset size  (Bits)
    
          addressSize,        // Address size (Bytes)
    
          ways,               // Total amout of ways
    
          indexSize,          // Index size (Bits)
    
          wordSize,           // Word count = (block size / word size)
    
          blockQuantity,      // Block quantity = (cache size / block size)
    
          wordCharacters,     // # of characters in a word
    
          wordQuantity;       // # of words utilized by each address
          
    
    // -------------------- Miscellaneous variables -------------------------
    
    iterator global_iterator;               // Used as a global iterator
    
    enum CACHING_ALGORITHM
    placementPolicy;                        // Select placement policy algorithm
    
    enum CONFIGURATION config;              // Determine configuration option
    
    binaryVector wordVector,                // Contains predifed word in binary form
    
                 addressList;               // Dataset that stores all existing addresses
    
        multiMap addressMap;                // Key = Address, Value = Map ( Key = binary word, Value = Hexadecimal Word )
    
          wayMap tagQueueMap;               // Key = Tag in binary, Value = Addresses stored in queue
    
 condensedString console,                   // Contains entire string to be printed to console
    
                 spreadsheet,               // Contains entired string to be print to spreadsheet
    
                 consoleToFile;             // Contains entire string to be printed to console but will printed to file

public:
    
    // Default Constructor
    Cache();
    
    // Paramaterized Constructor
    Cache(PLACEMENT_POLICY policy, CONFIGURATION config);
    
    virtual ~Cache() = default;
    
    // --------------------------- Miscellaneous -----------------------------
    
    // Assigns variables to their correct placement policies
    void Assign(PLACEMENT_POLICY policy, CONFIGURATION config);
    
    // Assign Fully Associative variables
    void FullyAssociative();
    
    // Assign Set Associative variables
    void SetAssociative();
    
    // Assign Direct Mapped variables
    void DirectMapped();
    
    // Verfies user input for fully associative cache
    void verifyFullyAssociativeInput(unit & data);
    
    // Verfies user input for set associative cache
    void verifySetAssociativeInput(unit & data);
    
    // Verfies user input for direct map cache
    void verifyDirectMappedInput(unit & data);
    
    // Assign configuration setup
    void Assign_Configurations(CONFIGURATION config);
    
    // Assign policy
    void Assign_Policy(PLACEMENT_POLICY policy);
    
    // Establishes word criteria
    void ConfigureWord();
    
    // Determine input to select for Fully Associative Cache
    INPUT FullyAssociativeInput(input number);
    
    // Determine input to select for Set Associative Cache
    INPUT SetAssociativeInput(input number);
    
    // Determine input to select for Direct Mapped Cache
    INPUT DirectMappedInput(input number);
    
    // Determine caching algorithm to select
    enum CACHING_ALGORITHM CachingEnum(input number);
    
    // Menu for Fully Associated Cache
    menu Fully_Associative_Menu(input select);
    
    // Menu for Set Associated Cache
    menu Set_Associative_Menu(input select);
    
    // Menu for Direct Mapped Cache
    menu Direct_Mapped_Menu(input select);
    
    // Create memory address for each cache block
    binaryVector GenerateAddresses();
    
    // Retreive hex value instructions
    hex GetInstruction();
    
    // ------------------------- Virtual Functions  --------------------------
    
    virtual void Print() = 0;             // Print report
    
    // -------------------------------------------------------------------------
};

#endif
