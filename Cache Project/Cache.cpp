#include "Cache.h"
#include <cstdlib>
#include "Miscellaneous_Data.h"

// ------------------------ Typedef used for organizational purposes ------------------------

// unit = unit of measurements
// input = variables uesd to select data
// iterator = traverses through content
typedef int unit, input, iterator;

// binary = binary data stored in each cache block
// hex = hex data stored in each cache block
typedef std::string binary, hex;

// inputSet = Stores input values
typedef std::vector<std::string> inputSet;

// Write file
typedef std::ofstream file;

// -------------------------------------------------------------------------------------------
Cache :: Cache(PLACEMENT_POLICY policy)
{
    Assign(policy);
}

// -------------------------------------------------------------------------------------------

void Cache :: Assign(PLACEMENT_POLICY policy)
{
    switch(policy)
    {
        case FULLY_ASSOCIATED:
            
            FullyAssociative();
            
            break;
            
        case SET_ASSOCIATED:
            
            SetAssociative();
            
            break;
            
        case DIRECT_MAPPED:
            
            DirectMapped();
            
            break;
            
        case POLICY_ERROR:
            
            throw std::invalid_argument("\n------------------- Error --------------------\n\nIncorrect option\n\nPlease re-select from the following menu\n\n----------------------------------------------\n");
    }
}

// -------------------------------------------------------------------------------------------

// Assign Fully Associative variables
void Cache :: FullyAssociative()
{
    
    // Input prompts used for Fully Associated Cache
   inputSet Fully_Associated_Input =
    {
        Fully_Associative_Menu(1),
        
        Fully_Associative_Menu(2),
        
        Fully_Associative_Menu(3),
        
        Fully_Associative_Menu(4),
        
        Fully_Associative_Menu(5)
    };
    
    // Select option
    input data;
    
    // Determines if banner should be displayed
    static bool isBanner = true;
    
    // Iterate through each input
    static iterator inputIterator = 0;
    
    // Fully Associative Cache Banner
    if(isBanner)
    {
        std::cout << "\n---------- Fully Associative Cache -----------\n";
        
        isBanner = false;
    }
    
    // Traverse through input values
    while(inputIterator < Fully_Associated_Input.size())
    {
        
        std::cout << Fully_Associated_Input[inputIterator];
        
        std::cin >> data;
        
        verifyFullyAssociativeInput(data,inputIterator);
        
        inputIterator += 1;
    }
    
    // Reset isBanner variable
    isBanner = false;
    
    // Reset inputIterator
    inputIterator = 0;
}

// -------------------------------------------------------------------------------------------

void Cache :: SetAssociative()
{
    // Input prompts used for Set Associated Cache
   inputSet Set_Associated_Input =
    {
        Set_Associative_Menu(1),
        
        Set_Associative_Menu(2),
        
        Set_Associative_Menu(3),
        
        Set_Associative_Menu(4),
        
        Set_Associative_Menu(5)
    };
    
    // Select option
    input data;
    
    // Determines if banner should be displayed
    static bool isBanner = true;
    
    // Iterate through each input
    static iterator inputIterator = 0;
    
    // Set Associative Cache Banner
    if(isBanner)
    {
        std::cout << "\n----------- Set Associative Cache ------------\n";
        
        isBanner = false;
    }
    
    // Traverse through input values
    while(inputIterator < Set_Associated_Input.size())
    {
        std::cout << Set_Associated_Input[inputIterator];
        
        std::cin >> data;
        
        verifySetAssociativeInput(data,inputIterator);
        
        inputIterator += 1;
    }
    
    // Reset isBanner variable
    isBanner = false;
    
    // Reset inputIterator
    inputIterator = 0;
}

// -------------------------------------------------------------------------------------------

void Cache :: DirectMapped()
{
    // Input prompts used for Direct Mapped Cache
   inputSet Direct_Mapped_Input =
    {
        Direct_Mapped_Menu(1),
        
        Direct_Mapped_Menu(2),
        
        Direct_Mapped_Menu(3),
    };
    
    // Select option
    input data;
    
    // Determines if banner should be displayed
    static bool isBanner = true;
    
    // Iterate through each input
    static iterator inputIterator = 0;
    
    // Direct Mapped Cache Banner
    if(isBanner)
    {
        std::cout << "\n------------ Direct Mapped Cache -------------\n";
        
        isBanner = false;
    }
    
    // Traverse through input values
    while(inputIterator < Direct_Mapped_Input.size())
    {
        std::cout << Direct_Mapped_Input[inputIterator];
        
        std::cin >> data;
        
        verifyDirectMappedInput(data, inputIterator);
        
        inputIterator += 1;
    }
    
    // Reset isBanner variable
    isBanner = false;
    
    // Reset inputIterator
    inputIterator = 0;
}

// -------------------------------------------------------------------------------------------
// Verify fully associative cache input
void Cache :: verifyFullyAssociativeInput(unit data, iterator & inputIterator)
{
    
    switch(InputEnum(inputIterator+ 1))
    {
            case CACHE_SIZE:
            
          
                if(data != 64 && data != 32)
                {
                    std::cerr << "\n------------------- Error --------------------\n\nCache size must be 64 or 32 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                    
                    inputIterator -= 1;
                    
                    break;
                    
                }

                    this -> cacheSize = data;
                    
                    break;
            
            case BLOCK_SIZE:
   
                if(data != 8 && data != 4 && data != 2)
                {
                    std::cerr << "\n------------------- Error --------------------\n\nBlock size must be 8, 4 or 2 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                    
                    inputIterator -= 1;
                    
                    break;
                    
                }
                    
                    this -> blockSize = data;
                    
                    break;

            
        case MAIN_MEMORY:
        
        if(data != 16 && data != 8)
        {
            std::cerr << "\n------------------- Error --------------------\n\nMain memory size must be 16 or 8 Bits\n\nPlease re-enter value:\n\n------------------------------------------------\n";
            
            inputIterator -= 1;
            
            break;
            
        }

            this -> mainMemorySize = data;
            
            break;

        break;
            
            case WAYS:
            
            if(data != 2 && data != 3)
            {
                std::cerr << "\n------------------- Error --------------------\n\nAmount of ways must be 2 or 3\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                
                inputIterator -= 1;
                
                break;
                
            }
            
                this -> ways = data;
                
                break;
            
            case CACHING_ALGORITHM:
            
            if(data != 1 && data != 2 && data != 3)
            {
                std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect option\n\nPlease re-enter from the following menu:\n";
                
                inputIterator -= 1;
                
                break;
            }
            
                this -> algorithm = CachingEnum(data);
                
                break;
            
            
            case INPUT_ERROR:
            
            std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect input\n\nPlease re-enter a valid option\n\n--------------------------------------------------\n";
    }
}

// -------------------------------------------------------------------------------------------
// Verify set associative cache input
void Cache :: verifySetAssociativeInput(unit data, iterator & inputIterator)
{
    
    switch(InputEnum(inputIterator+ 1))
    {
            case CACHE_SIZE:
            
          
                if(data != 64 && data != 32)
                {
                    std::cerr << "\n------------------- Error --------------------\n\nCache size must be 64 or 32 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                    
                    inputIterator -= 1;
                    
                    break;
                    
                }
                
                    this -> cacheSize = data;
                    
                    break;
                
            
            case BLOCK_SIZE:
   
                if(data != 8 && data != 4 && data != 2)
                {
                    std::cerr << "\n------------------- Error --------------------\n\nBlock size must be 8, 4 or 2 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                    
                    inputIterator -= 1;
                    
                    break;
                    
                }
                    this -> blockSize = data;
                    
                    break;
            
            
        case MAIN_MEMORY:
        
        if(data != 16 && data != 8)
        {
            std::cerr << "\n------------------- Error --------------------\n\nMain memory size must be 16 or 8 Bits\n\nPlease re-enter value:\n\n----------------------------------------------\n";
            
            inputIterator -= 1;
            
            break;
            
        }

            this -> mainMemorySize = data;
            
            break;

        break;
            
            case WAYS:
            
            if(data != 2 && data != 3)
            {
                std::cerr << "\n------------------- Error --------------------\n\nAmount of ways must be 2 or 3\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                
                inputIterator -= 1;
                
                break;
            }
            
                this -> ways = data;
                
                break;
            
            
            case CACHING_ALGORITHM:
            
            if(data != 1 && data != 2 && data != 3)
            {
                std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect option\n\nPlease re-enter from the following menu:\n";
                
                inputIterator -= 1;
                
                break;
            }

                this -> algorithm = CachingEnum(data);
                
                break;
            
            
            case INPUT_ERROR:
            
            std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect input\n\nPlease re-enter a valid option\n\n--------------------------------------------------\n";
    }
}

// -------------------------------------------------------------------------------------------
// Verify set associative cache input
void Cache :: verifyDirectMappedInput(unit data, iterator & inputIterator)
{
    switch(InputEnum(inputIterator+ 1))
    {
            case CACHE_SIZE:
            
            if(data != 64 && data != 32)
            {
                std::cerr << "\n------------------- Error --------------------\n\nCache size must be 64 or 32 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                
                inputIterator -= 1;
                
                break;
            }
            
            
            this -> cacheSize = data;
            
            break;
            
            case BLOCK_SIZE:
            
            if(data != 8 && data != 4 && data != 2)
            {
                std::cerr << "\n------------------- Error --------------------\n\nBlock size must be 8, 4 or 2 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                
                inputIterator -= 1;
                
                break;
            }
            
            this -> blockSize = data;
            
            break;
            
        case MAIN_MEMORY:
        
        if(data != 16 && data != 8)
        {
            std::cerr << "/n------------------- Error --------------------\n\nMain memory size must be 16 or 8 Bits\n\nPlease re-enter value:\n\n----------------------------------------------\n";
            
            inputIterator -= 1;
            
            break;
        }

            this -> mainMemorySize = data;
            
            break;
            
            case INPUT_ERROR:
            
            std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect input\n\nPlease re-enter a valid option\n\n--------------------------------------------------\n";
    }
}

// -------------------------------------------------------------------------------------------
// Establishes word criteria
void Cache :: ConfigureWord()
{
    // Arrays that contain potential word sizes depending the current block size
    int eightBytes[] = {8,4,2},
    
        fourBytes[] = {4,2,1},
    
        twoBytes[] = {2,1};
    
    // Randomize word size
    if(blockSize == 8)
        this -> wordSize = eightBytes[rand() % 3];

    else if(blockSize == 4)
        this -> wordSize = fourBytes[rand() % 3];

    else if(blockSize == 2)
        this -> wordSize = twoBytes[rand() % 2];
    
    // Determine value of wordQuantity
    this -> wordQuantity = this -> blockSize / this -> wordSize;
    
    // Predefine values of how many words per block if word count = 4
    binary fourWords[] =  {"00", "01", "10", "11"};
    
    // Predefine values of how many words per block if word count = 2
    binary twoWords[] =  {"0", "1"};
    
    // Predefine values of how many words per block if word count = 1
    binary oneWord[] = {"Instruction"};
    
    // Assign binary word values to wordVector dataset
    if(this -> wordQuantity == 4)
        for(int i = 0; i < sizeof(fourWords) / sizeof(fourWords[0]); i++)
            wordVector.push_back(fourWords[i]);
    
    
    else if(this -> wordQuantity == 2)
        for(int i = 0; i < sizeof(twoWords) / sizeof(twoWords[0]); i++)
            wordVector.push_back(twoWords[i]);
    
    else if(this -> wordQuantity == 1)
        for(int i = 0; i < sizeof(oneWord) / sizeof(oneWord[0]); i++)
            wordVector.push_back(oneWord[i]);
    
    // Generate binary data and store in vector
    this -> addressList = GenerateAddresses();
    
    // Assign hexadecimal values to address map
    for(std::vector<binary> :: size_type i = 0; i < addressList.size(); i++)
        for(std::vector<binary> :: size_type j = 0; j < wordQuantity; j++)
            addressMap[addressList[i]][wordVector[j]] = GetInstruction();

}

// -------------------------------------------------------------------------------------------
// Menu used for Fully Associated Cache
std::string Cache :: Fully_Associative_Menu(input select)
{
    if(select == 1)
        return "\n1) Cache Size (64 or 32 bytes): ";
    
    else if(select == 2)
        return "\n2) Block Size (8,4 or 2 bytes): ";
    
    else if(select == 3)
        return "\n3) Main Memory Size (16 or 8 bits): ";
    
    else if(select == 4)
        return "\n4) Enter number of ways (2 or 3): ";
        
    else if(select == 5)
        return "\n--------------- Caching Algorithms ---------------\n\n1) Last Recently Used\t\t2) Last Frequently Used\n\n3) First In First Out\n\n--------------------------------------------------\n\nSelect: ";
    
    return "";
}

// -------------------------------------------------------------------------------------------
// Menu used for Set Associative Cache
std::string Cache :: Set_Associative_Menu(input select)
{
    if(select == 1)
        return "\n1) Cache Size (64 or 32 bytes): ";
    
    else if(select == 2)
        return "\n2) Block Size (8,4 or 2 bytes): ";
    
    else if(select == 3)
        return "\n3) Main Memory Size (16 or 8 bits): ";
    
    else if(select == 4)
        return "\n4) Enter number of ways (2 or 3): ";
        
    else if(select == 5)
        return "\n--------------- Caching Algorithms ---------------\n\n1) Last Recently Used\t\t2) Last Frequently Used\n\n3) First In First Out\n\n--------------------------------------------------\n\nSelect: ";
    
    return "";
}

// -------------------------------------------------------------------------------------------
// Menu used for Direct Mapped Cache
std::string Cache :: Direct_Mapped_Menu(input select)
{
    if(select == 1)
        return "\n1) Cache Size (64 or 32 bytes): ";
    
    else if(select == 2)
        return "\n2) Block Size (8,4 or 2 bytes): ";
    
    else if(select == 3)
        return "\n3) Main Memory Size (16 or 8 bits): ";
    
    return "";
}

// -------------------------------------------------------------------------------------------
// Determine input to select
INPUT Cache :: InputEnum(input number)
{
    if(number == 1)
        return INPUT :: CACHE_SIZE;
    
    else if(number == 2)
        return INPUT :: BLOCK_SIZE;
    
    else if(number == 3)
        return INPUT :: MAIN_MEMORY;
    
    else if(number == 4)
        return INPUT :: WAYS;
    
    else if(number == 5)
        return INPUT :: CACHING_ALGORITHM;
    
    return INPUT :: INPUT_ERROR;
}

// -------------------------------------------------------------------------------------------
// Determine caching algorithm to select
enum CACHING_ALGORITHM  Cache :: CachingEnum(input select)
{
    if(select == 1)
        return CACHING_ALGORITHM :: LRU;
    
    else if(select == 2)
        return CACHING_ALGORITHM :: LFU;
    
    else if(select == 3)
        return CACHING_ALGORITHM :: FIFO;
    
    return CACHING_ALGORITHM :: ALGORITHMIC_ERROR;
}

// -------------------------------------------------------------------------------------------

// Create memory address for each cache block
std::vector <std::string> Cache :: GenerateAddresses()
{
    // Collect each address
    std::string address = "";
    
    // Store all addresses
    std::vector <std::string> cacheAddresses;
   
    // Amount of addresses should be half the # of slots for demonstration purposes
    for(int i = 0; i < this -> slots / 2; i++)
    {
                
        for(int x = 0; x < this -> mainMemorySize; x++)
        {
            address += std::to_string(rand() % 2);
        }

        cacheAddresses.push_back(address);
        
        address = "";
    }
    
    return cacheAddresses;
}

// -------------------------------------------------------------------------------------------
// Retreive instruction designed as dummy hex value
hex Cache :: GetInstruction()
{
    // Used as iterator
    iterator it = 0;
    
    hex instruction = "0x";
  
    // Instruction will be the same size as block
    while(it < this -> blockSize)
    {
        // Determine if next random value is digit or character
        int randomValue =  rand() % 2;
        
        // Next random value is a digit
        if(randomValue == 0)
            instruction += char(48 + (std::rand() % (57 - 48 + 1)));
        
        // Next random value is a character
        else if(randomValue == 1)
            instruction += char(65 + (std::rand() % (70 - 65 + 1)));
        
        // increment iterator
        it += 1;
    }
    
    return instruction;
    
}
