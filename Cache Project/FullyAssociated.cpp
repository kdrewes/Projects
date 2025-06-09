#include <time.h>
#include "Cache.h"
#include "FullyAssociated.hpp"
#include "Miscellaneous_Data.h"
#include <vector>

// -------------------------------------------------------------------------------------------

FullyAssociated :: ~FullyAssociated() = default;

void FullyAssociated :: Configure()
{
    // Calculate # of slots
    this -> slots = this -> cacheSize / this -> blockSize;

    // Determine word quantity binary words used
    ConfigureWord();
    
    std::cout << "\n# of slots = " << this -> slots << '\n';

    // Insert CacheData properties into cacheStorage vector
    for(int i = 0; i < this -> slots; i++)
        cacheStorage.push_back(CacheData(*this));
    
    // For test purposes
    for(int i = 0; i < cacheStorage.size(); i++)
    {
        std::cout << "\nAddress = " << cacheStorage[i].address << std::endl;
        std::cout << "\nBlock = " << cacheStorage[i].blockSize << std::endl;
        std::cout << "\nOffset = " << cacheStorage[i].offset << std::endl;
        std::cout << "\nTag = " << cacheStorage[i].tag << std::endl;
        std::cout << "\nWord Size = " << cacheStorage[i].wordSize << std::endl << std::endl;
        for(auto & [binary,hex] : cacheStorage[i].instructionMap)
        {
            std::cout << "binary = " << binary << ", hex = " << hex << std::endl;
        }
        
        std::cout << "\n----------------------------------------------------------\n";

    }
}

// -------------------------------------------------------------------------------------------


void FullyAssociated :: Print()
{
    std::cout << "\nPrint Fully Associated Cache\n\n";
}

// -------------------------------------------------------------------------------------------

void FullyAssociated::PrintFile()
{
    
}


// -------------------------------------------------------------------------------------------

void FullyAssociated :: LRU()
{
   
}

// -------------------------------------------------------------------------------------------

void FullyAssociated :: FIFO()
{
  
}

// -------------------------------------------------------------------------------------------

void FullyAssociated :: LFU()
{
  
}

// -------------------------------------------------------------------------------------------

// Retreive cacheStorage
std::vector<FullyAssociated::CacheData> FullyAssociated :: getCacheStorage()
{
    return cacheStorage;
}

// -------------------------------------------------------------------------------------------

// Retreive addressList
std::vector <std::string> FullyAssociated :: getAddressList() 
{
    return addressList;
}

// -------------------------------------------------------------------------------------------
