#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Cache.h"
#include <limits>
#include "FullyAssociated.hpp"
#include "SetAssociated.hpp"
#include "DirectMapped.hpp"
#include "Enums.h"

// ------------------------- Typedef -------------------------

// input = selects from menu
typedef int input;

// ------------------------ Prototypes -----------------------

// Implement factory pattern to instantiate child class
std::unique_ptr <Cache> FactoryPattern(PLACEMENT_POLICY selectPolicy, CONFIGURATION selectConfig);

// Allows user to chose between manual or automation option
void Configuration_Menu(input & selectPolicy);

// Cache Placement Policy Menu
void Cache_Policy_Menu(input & selectPolicy, input selectConfig);

// Determines cache placement policy
PLACEMENT_POLICY PolicyEnum(input selection);

// Determines configuration
CONFIGURATION ConfigurationEnum(input selection);

// ---------------------- Global Variable(s) ---------------------

// Determine if cache placement policy was already selected
bool isPolicySelected = false;

// -------------------------------------------------------------

int main(int argc, const char * argv[])
{
    srand(time(NULL));
    
    // Select cache placements policy
    input selectPolicy = 0;
    
    // Select configuration
    input selectConfig = 0;
    
    while(true)
    {
        // Input validation
        try
        {
            if(!isPolicySelected)
            {
                // Allows user to chose between manual or automation option
                Configuration_Menu(selectConfig);
                
                // Display cache placement policy menu
                Cache_Policy_Menu(selectPolicy, selectConfig);
            }
            
            // Implement factory pattern
            std::unique_ptr <Cache> cachePtr =
            FactoryPattern(PolicyEnum(selectPolicy), ConfigurationEnum(selectConfig));
            
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
    
    std::cout << "\n\n";
    
    return 0;
}

// ------------------------------------------------------------
// Implement factory pattern to instantiate child class
std::unique_ptr <Cache> FactoryPattern(PLACEMENT_POLICY policy, CONFIGURATION config)
{
    switch(config)
    {
        case MANUAL:
            
            switch(policy)
            {
                case FULLY_ASSOCIATED:
                    
                    isPolicySelected = true;
                    
                    return std::unique_ptr <Cache> (new FullyAssociated(policy, config));
                    
                case SET_ASSOCIATED:
                    
                    isPolicySelected = true;
                    
                    return std::unique_ptr <Cache> (new SetAssociated(policy, config));
                    
                case DIRECT_MAPPED:
                    
                    isPolicySelected = true;
                    
                    return std::unique_ptr <Cache> (new DirectMapped(policy, config));
                    
                case EXIT:

                    std::cout << "\nExit Program\n\n";
                    
                    exit(0);
                    
                case POLICY_ERROR:
                
                    throw std::invalid_argument("\nError - Incorrect option\n\nPlease re-select from the following menu\n\n");
            }
            
            break;
            
        case AUTOMATED:
            
            int policyArray [] = {1,2,3};
            
            switch(policy = PolicyEnum(policyArray[rand() % 3]))
            {
                case FULLY_ASSOCIATED:
                    
                    isPolicySelected = true;
                    
                    return std::unique_ptr <Cache> (new FullyAssociated(policy, config));
                    
                case SET_ASSOCIATED:
                    
                    isPolicySelected = true;
                    
                    return std::unique_ptr <Cache> (new SetAssociated(policy, config));
                    
                case DIRECT_MAPPED:
                    
                    isPolicySelected = true;
                    
                    return std::unique_ptr <Cache> (new DirectMapped(policy, config));
                    
                case EXIT:

                    std::cout << "\nExit Program\n\n";
                    
                    exit(0);
                    
                case POLICY_ERROR:
                
                    throw std::invalid_argument("\nError - Incorrect option\n\nPlease re-select from the following menu\n\n");
            }
            
            break;
            
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
// Determines configuration
CONFIGURATION ConfigurationEnum(input selection)
{
    if(selection == 1)
        return CONFIGURATION :: MANUAL;
    
    else if(selection == 2)
        return CONFIGURATION :: AUTOMATED;
    
    return CONFIGURATION :: CONFIGURATION_ERROR;
}

// ------------------------------------------------------------
// Cache configuration menu
void Configuration_Menu(input & selectConfig)
{
    do
    {
        
    std::cout << "\n-----------------------------------------\n";
    std::cout << std::setw(33) << "Cache Simulation Project\n";
    std::cout << "-----------------------------------------\n\n";
    
    std::cout << "\t1) Manual\t\t2) Automated\n\n\t3) Help\t\t\t4) Exit\n";
    
    std::cout <<"\n-----------------------------------------\n\n";
   
    std::cout << "Select: ";
        
    std::cin >> selectConfig;
        
        if(selectConfig == 3)
        {
            std::cout <<"\n-----------------------------------------\n\n";
            
            std::cout << "Manual - User manual input cache placement policy and data.\n\n";
            
            std::cout << "Automated - Cache placement policy and data is randomly chosen by compiler.\n\n";
            
            std::cout << "Press any key to continue...\n";
            
            std::cin.clear();
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cin.get();
        }
        
        else if(selectConfig != 1 && selectConfig != 2 && selectConfig != 4)
            throw std::invalid_argument("\n\nError - Invalid configuration option\n\nplease re-enter.\n");
        
        else if(selectConfig == 4)
            std::exit(0);
        
        
    } while (selectConfig != 1 && selectConfig != 2);
    
 
    
}
// ------------------------------------------------------------
// Cache placement policy menu
void Cache_Policy_Menu(input & selectPolicy, input selectConfig)
{
    if(selectConfig == 1)
    {
        std::cout << "\n-----------------------------------------\n";
        std::cout << std::setw(33) << "Cache Placement Policy\n";
        std::cout << "-----------------------------------------\n\n";
        
        std::cout << "1) Fully Associative\t2) Set Associative\n\n3) Direct Mapped\t\t4) Exit\n";
        
        std::cout <<"\n-----------------------------------------\n\n";
        
        std::cout << "Select: ";
        
        // Select policy
        std::cin >> selectPolicy;
    }
    
}
// ------------------------------------------------------------

