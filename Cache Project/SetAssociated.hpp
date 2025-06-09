#ifndef SetAssociated_hpp
#define SetAssociated_hpp

#include <stdio.h>
#include "Cache.h"
#include "Miscellaneous_Data.h"

class SetAssociated : public Cache
{
    
    // ---------- Typedef for organizational purposes ----------
    
    // Unit of measurements
    typedef int units, input;
    
    // Binary values
    typedef std::vector<std::string> dataSet;
    
private:
    
    // -------------------------- Binary datasets ---------------------------
    
    dataSet addresses,              // Stores each binary address
            tag,                    // Stores each tag in binary form
            offset,                 // Stores each offset in binary form
            index,                  // Stores each index in binary form
            words,                  // Stores each word in binary form
            instructions;           // Stores each instruction in binary form
    
public:
    
    SetAssociated(PLACEMENT_POLICY policy) : Cache(policy)
    {
        
    }
    
    ~SetAssociated() override;
    
    // ---------------------- Configuration functions  -----------------------
    
     void Configure();                  // Configure binary data
    
    // ------------------- Cache Replacements Algorithms  --------------------
    
     void LRU();                        // Last Recently Used
    
     void FIFO();                       // First in First Out
    
     void LFU();                        // Least Frequently Used
    
    // ---------------------------- Print Results  -----------------------------
    
     void Print() override;             // Print report
    
     void PrintFile();                  // Output results in file
    
     void PrintConsole();               // Output results in console
    
    
};

#endif 
