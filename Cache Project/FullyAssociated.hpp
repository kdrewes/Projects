#ifndef FullyAssociated_hpp
#define FullyAssociated_hpp

#include <stdio.h>
#include <time.h>
#include "Cache.h"
#include "Miscellaneous_Data.h"

class FullyAssociated : public Cache
{
    
    // -------------- Typedef used for organizational purposes --------------
    
    // unit = unit of measurements
    // input = variables uesd to select data
    typedef int units, input;
    
    // binary = binary data stored in each cache block
    // hex = hex data stored in each cache block
    typedef std::string binary, hex;
    
private:

    // Stores all cache data that works in parallel
    struct CacheData
    {
        // -------------------------- Constructor --------------------------
        
        CacheData(FullyAssociated & f) :
        blockSize (f.blockSize), wordSize(f.wordSize),
        address (f.addressList[std::rand() % f.addressList.size()]),
        tag (address.substr(0, address.size() - std::floor(log(f.blockSize)))),
        offset (address.substr(address.size() - std::floor(log(f.blockSize)), address.size())),
        instructionMap (getInstructions(address,f.addressMap)) {}
        
        // -------------------------- Functions ---------------------------
        
        // Ensure the same address contains the identical instructions
        std::map <binary,hex> getInstructions(binary addr, std::map<binary,std::map<binary,hex>> addressMap)
        {
            std::map <binary,hex> instructions;
            
            if(addressMap.find(addr) != addressMap.end())
            {
                std::map <binary,hex> tempMap = addressMap[address];
                
                for(auto & t : tempMap)
                    instructions[t.first] = t.second;
            }
   
            return instructions;
        }
        // ------------------------- Binary Data --------------------------
        
         binary address,          // Binary address
        
                tag,              // Tag in binary form
        
                offset;           // Offset in binary form
        
                unit blockSize,   // Size of each block (Bytes)
        
                     wordSize;    // Word count = (block size / word size)
        
                std::map          // Key = binary value of word
                <binary,hex>
                instructionMap;   // Value = Hex value of each instructions
        
    };

    // -------------------------- Binary datasets ---------------------------
    
    // Stores all properties located in CacheData structure
    std::vector <CacheData> cacheStorage;

public:
    
    FullyAssociated(PLACEMENT_POLICY policy) : Cache(policy)
    {
        Configure();
    }
    
    ~FullyAssociated() override;
    
    // ---------------------- Configuration function  -----------------------
    
     void Configure();                  // Configure binary data
    
    // ------------------- Cache Replacements Algorithms  --------------------
    
     void LRU();                        // Last Recently Used
    
     void FIFO();                       // First in First Out
    
     void LFU();                        // Least Frequently Used
    
    // ---------------------------- Print Results  -----------------------------
    
     void Print() override;             // Print report
    
     void PrintFile();                  // Output results in file
    
     void PrintConsole();               // Output results in console
    
    // --------------------------- Getter Functions ----------------------------
    
    // Retreive cacheStorage
    std::vector <CacheData> getCacheStorage();
    
    // Retreive addressList
    std::vector <std::string> getAddressList();
    
};

#endif 
