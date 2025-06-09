#ifndef DirectMapped_hpp
#define DirectMapped_hpp

#include <stdio.h>

#include <stdio.h>
#include "Cache.h"
#include "Miscellaneous_Data.h"

class DirectMapped : public Cache
{
    
    // ---------- Typedef for organizational purposes ----------
    
    // unit = unit of measurements, input = 
    typedef int unit, input;
    
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
    
    DirectMapped(PLACEMENT_POLICY policy) : Cache(policy)
    {
        
    }
    
    ~DirectMapped() override;
    
    // ---------------------- Configuration functions  -----------------------
    
    void Configure();                  // Configure binary data
    
    // ---------------------------- Print Results  -----------------------------
    
    void Print() override;             // Print report
    
    void PrintFile();                  // Output results in file
    
    void PrintConsole();               // Output results in console
    
};


#endif
