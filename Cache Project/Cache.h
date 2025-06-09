#ifndef Cache_hpp
#define Cache_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <fstream>
#include "Miscellaneous_Data.h"

// Interface for all cache placement policies
class Cache
{
    
protected:
    
    // -------------- Typedef used for organizational purposes -------------
    
    // unit = unit of measurements
    // input = variables uesd to select data
    // iterator = traverses through content
    typedef int unit, input, iterator;
    
    // binary = binary data stored in each cache block
    // hex = hex data stored in each cache block
    // menu = consist of entire menu
    typedef std::string binary, hex, menu;
    
    // inputSet = Stores input values, binaryVector = Stores binary values
    typedef std::vector<std::string> inputSet, binaryVector;
    
    // Write file
    typedef std::ofstream file;
    
    // binaryHexMap = Represents a map inside a map
    typedef std::map<binary, std::map<binary,hex>> binaryHexMap;
    
    typedef std::ostringstream condensedString;
    
    // ---------------------------- File data ----------------------------
    
    file write;                // Establish file for Fully Associative,
    
    // -------------------------- Numerical data --------------------------
    
     unit cacheSize,          // Total amount of block data (Bytes)
          blockSize,          // Size of each block (Bytes)
          mainMemorySize,     // Size of main memory (Bits)
          slots,              // slots = cacheSize / blockSize
          offsetSize,         // Offset size  (Bits)
          ways,               // Total amout of ways
          indexSize,          // Index size (Bits)
          wordSize,           // Word count = (block size / word size)
          wordQuantity;       // # of words utilized
    
    // -------------------- Miscellaneous variables -------------------------
    
    enum CACHING_ALGORITHM algorithm;       // Select caching algorithm
    
    binaryVector wordVector,                // Contains predifed word in binary form
    
                 addressList,               // Temporary storage for all existing addresses
    
                 addressTable;              // Store address in hash table
    
    binaryHexMap addressMap;                // Key = Address, Value = Map ( Key = binary word, Value = Hexadecimal Word )
    
    condensedString console,                // Contains entire string to be printed to console
    
                    spreadsheet,            // Contains entired string to be print to spreadsheet
    
                    consoleToFile;          // Contains entire string to be printed to console but will printed to file

public:
    
    // Default Constructor
    Cache();
    
    // Paramaterized Constructor
    Cache(PLACEMENT_POLICY policy);
    
    virtual ~Cache() = default;
    
    // ------------------------- Virtual Functions  --------------------------
    
    virtual void Print() = 0;             // Print report
    
    // --------------------------- Miscellaneous -----------------------------
    
    // Assigns variables to their correct placement policies
    void Assign(PLACEMENT_POLICY policy);
    
    // Assign Fully Associative variables
    void FullyAssociative();
    
    // Assign Set Associative variables
    void SetAssociative();
    
    // Assign Direct Mapped variables
    void DirectMapped();
    
    // Verfies user input for fully associative cache
    void verifyFullyAssociativeInput(unit data, iterator & inputIterator);
    
    // Verfies user input for set associative cache
    void verifySetAssociativeInput(unit data, iterator & inputIterator);
    
    // Verfies user input for direct map cache
    void verifyDirectMappedInput(unit data, iterator & inputIterator);
    
    // Establishes word criteria
    void ConfigureWord();
    
    // Determine input to select
    INPUT InputEnum(input number);
    
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
    
    // -------------------------------------------------------------------------
};

#endif
