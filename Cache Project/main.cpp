#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Cache.h"
#include "FullyAssociated.hpp"
#include "SetAssociated.hpp"
#include "DirectMapped.hpp"
#include "Miscellaneous_Data.h"

// ------------------------- Typedef -------------------------

// input = selects from menu
typedef int input;

// ------------------------ Prototypes -----------------------

// Implement factory pattern to instantiate child class
std::unique_ptr <Cache> FactoryPattern(PLACEMENT_POLICY selection);

// Cache Placement Policy Menu
void CachePolicyMenu();

// Determines cache placement policy
PLACEMENT_POLICY PolicyEnum(int selection);

// ---------------------- Global Variable(s) ---------------------

// Determine if cache placement policy was already selected
bool isPolicySelected = false;

// -------------------------------------------------------------

int main(int argc, const char * argv[])
{
    srand(time(NULL));
    
    // Select cache placements policy
    input selectPolicy = 0;
    
    while(true)
    {
        // Input validation
        try
        {
            if(!isPolicySelected)
            {
                // Display cache placement policy menu
                CachePolicyMenu();
                
                // Select policy
                std::cin >> selectPolicy;
            }
            
            // Implement factory pattern
            std::unique_ptr <Cache> cachePtr =
            FactoryPattern(PolicyEnum(selectPolicy));
            
            // Print report
            cachePtr -> Print();
            
            // Reset isPolicySelect boolean value
            isPolicySelected = false;
            
            break;
            
        }
        
        catch(std::invalid_argument e)
        {
            std::cout << e.what();
        }
    }
    
    return 0;
}

// ------------------------------------------------------------
// Implement factory pattern to instantiate child class
std::unique_ptr <Cache> FactoryPattern(PLACEMENT_POLICY policy)
{
    
    switch(policy)
    {
        case FULLY_ASSOCIATED:
            
            isPolicySelected = true;
            
            return std::unique_ptr <Cache> (new FullyAssociated(policy));
            
        case SET_ASSOCIATED:
            
            isPolicySelected = true;
            
            return std::unique_ptr <Cache> (new SetAssociated(policy));
            
        case DIRECT_MAPPED:
            
            isPolicySelected = true;
            
            return std::unique_ptr <Cache> (new DirectMapped(policy));
            
        case EXIT:

            // Exiting program
            std::cout << "\nExit Program\n\n";
            
            exit(0);
            
        case POLICY_ERROR:
        
            throw std::invalid_argument("\nError - Incorrect option\n\nPlease re-select from the following menu\n\n");
    }
    
    return nullptr;
}

// ------------------------------------------------------------
// Determines cache placement policy
PLACEMENT_POLICY PolicyEnum(input selection)
{
    if(selection == 1)
        return PLACEMENT_POLICY :: FULLY_ASSOCIATED;
    
    else if(selection == 2)
        return PLACEMENT_POLICY :: SET_ASSOCIATED;
    
    else if(selection == 3)
        return PLACEMENT_POLICY :: DIRECT_MAPPED;
    
    else if(selection == 4)
        return PLACEMENT_POLICY :: EXIT;
    
    return PLACEMENT_POLICY :: POLICY_ERROR;
}

// ------------------------------------------------------------
// Cache Placement Policy Menu
void CachePolicyMenu()
{
    
    std::cout <<"----------- Cache Placement Policy -----------\n\n";
    
    std::cout << "1) Fully Associated\t\t2) Set Associated\n\n3) Direct Mapped\t\t4) Exit\n";
    
    std::cout <<"\n----------------------------------------------\n\n";
    
    std::cout << "Select: ";
    
}
// ------------------------------------------------------------
