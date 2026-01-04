#include "Cache.h"
#include <cstdlib>
#include "Enums.h"

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

// binaryHexMap = Represents a map inside a map
typedef std::map<binary, std::map<binary,hex>> multiMap;

// Key = binary word, hexidecimal instruction
typedef std::map<hex,std::queue<binary>> wayMap;

// Condenses string into a single variable
typedef std::ostringstream condensedString;

// -------------------------------------------------------------------------------------------
Cache :: Cache(PLACEMENT_POLICY policy, CONFIGURATION config)
{
    Assign(policy, config);
}

// -------------------------------------------------------------------------------------------

void Cache :: Assign(PLACEMENT_POLICY policy, CONFIGURATION config)
{
    // Determine configuration
    Assign_Configurations(config);
    
    // Determine policy
    Assign_Policy(policy);
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
    
    this -> global_iterator = 0;
    
    std::cout << "\n---------- Fully Associative Cache -----------\n";
    
    switch(config)
    {
        case MANUAL:
            
            // Traverse through manual input values
            while(this -> global_iterator < Fully_Associated_Input.size())
            {
                std::cout << Fully_Associated_Input[this -> global_iterator];
                
                std::cin >> data;
                
                verifyFullyAssociativeInput(data);
                
                this -> global_iterator += 1;
            }
            
            break;
            
        case AUTOMATED:
            
            // Traverse through automated input values
            while(this -> global_iterator < Fully_Associated_Input.size())
            {
                std::cout << Fully_Associated_Input[this -> global_iterator];
                
                verifyFullyAssociativeInput(data);
                
                std::cout << data << "\n\n";
                
                this -> global_iterator += 1;
            }
            
            break;
            
    }
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
        
        Set_Associative_Menu(4)
    };
    
    // Select option
    input data;
    
    std::cout << "\n----------- Set Associative Cache ------------\n";
    
    switch(config)
    {
        case MANUAL:
            
            // Traverse through input values
            while(this -> global_iterator < Set_Associated_Input.size())
            {
                std::cout << Set_Associated_Input[this -> global_iterator];
                
                std::cin >> data;
                
                verifySetAssociativeInput(data);
                
                this -> global_iterator += 1;
            }
            
            // Automatically set # of ways to 2
            this -> ways = 2;
            
            // Reset inputIterator
            this -> global_iterator = 0;
            
            break;
            
            
        case AUTOMATED:
            
            // Traverse through input values
            while(this -> global_iterator < Set_Associated_Input.size())
            {
                std::cout << Set_Associated_Input[this -> global_iterator];
                
                verifySetAssociativeInput(data);
                
                std::cout << data << "\n\n";
                
                this -> global_iterator += 1;
            }
            
            // Automatically set # of ways to 2
            this -> ways = 2;
            
            // Reset inputIterator
            this -> global_iterator = 0;
            
            break;
    }
    
    
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
    
    std::cout << "\n------------ Direct Mapped Cache -------------\n";
    
    switch(config)
    {
        case MANUAL:
            
            // Traverse through input values
            while(this -> global_iterator < Direct_Mapped_Input.size())
            {
                std::cout << Direct_Mapped_Input[this -> global_iterator];
                
                std::cin >> data;
                
                verifyDirectMappedInput(data);
                
                this -> global_iterator += 1;
            }
            
            // Reset inputIterator
            this -> global_iterator = 0;
            
            break;
         
        case AUTOMATED:
            
            // Traverse through input values
            while(this -> global_iterator < Direct_Mapped_Input.size())
            {
                std::cout << Direct_Mapped_Input[this -> global_iterator];

                verifyDirectMappedInput(data);
                
                this -> global_iterator += 1;
            }
            
            // Reset inputIterator
            this -> global_iterator = 0;
            
            break;
            
    }
}

// -------------------------------------------------------------------------------------------
// Verify fully associative cache input
void Cache :: verifyFullyAssociativeInput(unit & data)
{
    
    switch(FullyAssociativeInput(this -> global_iterator + 1))
    {
        case CACHE_SIZE:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 64 && data != 32)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nCache size must be 64 or 32 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                        
                    }
                    
                    this -> cacheSize = data;
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare cache size dataset
                    int cacheSizeArray [] = {32, 64};
                    
                    // Assign automated cache size
                    this -> cacheSize = cacheSizeArray [rand() % 2];
                    
                    // Assign value of data
                    data = this -> cacheSize;
                    
                    break;
            }
            
            break;
            
        case BLOCK_SIZE:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 2 && data != 4 && data != 8)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nBlock size must be 8, 4 or 2 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                    }
                    
                    // Assign block size
                    this -> blockSize = data;
                    
                    // Block quantity = ( block size / cache size )
                    this -> blockQuantity = this -> cacheSize / this -> blockSize;
                    
                    // Assign offset size
                    this -> offsetSize = std::floor(log2(blockSize));
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare block size dataset
                    int blockSizeArray [] = {2, 4, 8};
                    
                    // Assign block size
                    this -> blockSize = blockSizeArray [rand() % 3];
                    
                    // Block quantity = ( block size / cache size )
                    this -> blockQuantity = this -> cacheSize / this -> blockSize;
                    
                    // Assign offset size
                    this -> offsetSize = std::floor(log2(blockSize));
                    
                    // Assign value of data
                    data = this -> blockSize;
                    
                    break;
            }
            
            break;
            
        case MAIN_MEMORY:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 8 && data != 16)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nMain memory size must be 16 or 8 Bits\n\nPlease re-enter value:\n\n------------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                    }
                    
                    this -> mainMemorySize = data;
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare block size dataset
                    int memoryArray [] = {8, 16};
                    
                    // Assign block size
                    this -> mainMemorySize = memoryArray [rand() % 2];
                    
                    // Assign value of data
                    data = this -> mainMemorySize;
                    
                    break;
            }
            
            break;
            
        case WAYS:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 2 && data != 3)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nAmount of ways must be 2 or 3\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                        
                    }
                    
                    this -> ways = data;
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare block size dataset
                    int wayArray [] = {2, 3};
                    
                    // Assign block size
                    this -> ways = wayArray [rand() % 2];
                    
                    // Assign value of data
                    data = this -> ways;
                    
                    break;
                    
            }
            
            break;
            
        case CACHING_ALGORITHM:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 1 && data != 2 && data != 3)
                    {
                        std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect option\n\nPlease re-enter from the following menu:\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                    }
                    
                    this -> placementPolicy = CachingEnum(data);
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare algorithm array
                    int algorithmArray [] = {1, 2, 3};
                    
                    // Assign placement policy enum
                    this -> placementPolicy = CachingEnum(algorithmArray[rand() % 3]);
                    
                    // Assign value of data
                    data = this -> placementPolicy;
                    
                    break;
            }
            
            break;
            
        case INPUT_ERROR:
            
            std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect input\n\nPlease re-enter a valid option\n\n--------------------------------------------------\n";
    }
}

// -------------------------------------------------------------------------------------------
// Verify set associative cache input
void Cache :: verifySetAssociativeInput(unit & data)
{
    
    switch(SetAssociativeInput(this -> global_iterator + 1))
    {
        case CACHE_SIZE:
            
            switch(config)
            {
                    
                case MANUAL:
                    
                    if(data != 64 && data != 32)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nCache size must be 64 or 32 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                        
                    }
                    
                    this -> cacheSize = data;
                    
                    break;
                    
                    
                case AUTOMATED:
                    
                    // Declare cache size dataset
                    int cacheSizeArray [] = {32, 64};
                    
                    // Assign automated cache size
                    this -> cacheSize = cacheSizeArray [rand() % 2];
                    
                    // Assign value of data
                    data = this -> cacheSize;
                    
                    break;
            }
            
            break;
            
        case BLOCK_SIZE:
            
            switch(config)
            {
                    
                case MANUAL:
                    
                    if(data != 8 && data != 4 && data != 2)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nBlock size must be 8, 4 or 2 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                        
                    }
                    
                    // Initialize block size
                    this -> blockSize = data;
                    
                    // Block quantity = ( block size / cache size )
                    this -> blockQuantity = this -> cacheSize / this -> blockSize;
                    
                    // Assign offset size
                    this -> offsetSize = std::floor(log2(blockSize));
                    
                    // Assign index size
                    this -> indexSize = (int)std::floor(std::log2(blockQuantity / 2));
                        
                    break;
                    
                case AUTOMATED:
                    
                    // Declare block size dataset
                    int blockSizeArray [] = {2, 4, 8};
                    
                    // Assign block size
                    this -> blockSize = blockSizeArray [rand() % 3];
                    
                    // Block quantity = ( block size / cache size )
                    this -> blockQuantity = this -> cacheSize / this -> blockSize;
                    
                    // Assign offset size
                    this -> offsetSize = std::floor(log2(blockSize));
                    
                    // Assign index size
                    this -> indexSize = (int)std::floor(std::log2(blockQuantity / 2));
                    
                    break;
            }
            
            break;
            
        case MAIN_MEMORY:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 16 && data != 8)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nMain memory size must be 16 or 8 Bits\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                        
                    }
                    
                    this -> mainMemorySize = data;
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare memory size dataset
                    int memoryArray [] = {8, 16};
                    
                    // Assign memory size
                    this -> mainMemorySize = memoryArray [rand() % 2];
                    
                    // Assign value of data
                    data = this -> mainMemorySize;

                    break;
            }
            
            break;
            
        case CACHING_ALGORITHM:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 1 && data != 2 && data != 3)
                    {
                        std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect option\n\nPlease re-enter from the following menu:\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                    }
                    
                    this -> placementPolicy = CachingEnum(data);
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare algorithm array
                    int algorithmArray [] = {1, 2, 3};
                    
                    // Assign value of placement policy enum
                    this -> placementPolicy = CachingEnum(algorithmArray[rand() % 3]);
                    
                    // Assign value of data
                    data = this -> placementPolicy;
                    
                    break;
            }
            
            break;
            
            
        case INPUT_ERROR:
            
            std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect input\n\nPlease re-enter a valid option\n\n--------------------------------------------------\n";
    }
}

// -------------------------------------------------------------------------------------------
// Verify set associative cache input
void Cache :: verifyDirectMappedInput(unit & data)
{
    switch(DirectMappedInput(this -> global_iterator + 1))
    {
        case CACHE_SIZE:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 64 && data != 32)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nCache size must be 64 or 32 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                    }
                    
                    this -> cacheSize = data;
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare cache size dataset
                    int cacheSizeArray [] = {32, 64};
                    
                    // Assign automated cache size
                    this -> cacheSize = cacheSizeArray [rand() % 2];
                    
                    // Assign value of data
                    data = this -> cacheSize;
                    
                    break;
            }
            
            break;
            
        case BLOCK_SIZE:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 8 && data != 4 && data != 2)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nBlock size must be 8, 4 or 2 Bytes\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                    }
                    
                    // Initialize block size
                    this -> blockSize = data;
                    
                    // Block quantity = ( block size / cache size )
                    this -> blockQuantity = this -> cacheSize / this -> blockSize;
                    
                    // Assign offset size
                    this -> offsetSize = std::floor(log2(blockSize));
                    
                    // Assign index size
                    this -> indexSize = (int)std::floor(std::log2(blockQuantity / 2));
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare block size dataset
                    int blockSizeArray [] = {2, 4, 8};
                    
                    // Assign block size
                    this -> blockSize = blockSizeArray [rand() % 3];
                    
                    // Block quantity = ( block size / cache size )
                    this -> blockQuantity = this -> cacheSize / this -> blockSize;
                    
                    // Assign offset size
                    this -> offsetSize = std::floor(log2(blockSize));
                    
                    // Assign index size
                    this -> indexSize = (int)std::floor(std::log2(blockQuantity / 2));
                    
                    break;
            }
            
            break;
            
        case MAIN_MEMORY:
            
            switch(config)
            {
                case MANUAL:
                    
                    if(data != 16 && data != 8)
                    {
                        std::cerr << "\n------------------- Error --------------------\n\nMain memory size must be 16 or 8 Bits\n\nPlease re-enter value:\n\n----------------------------------------------\n";
                        
                        this -> global_iterator -= 1;
                        
                        break;
                    }
                    
                    // Assignment main memory
                    this -> mainMemorySize = data;
                    
                    break;
                    
                case AUTOMATED:
                    
                    // Declare memory size dataset
                    int memoryArray [] = {8, 16};
                    
                    // Assign main memory size
                    this -> mainMemorySize = memoryArray [rand() % 2];
                    
                    // Assign value of data
                    data = this -> mainMemorySize;
                    
                    break;
            }
            
            break;
            
        case INPUT_ERROR:
            
            std::cerr << "\n--------------------- Error ----------------------\n\nIncorrect input\n\nPlease re-enter a valid option\n\n--------------------------------------------------\n";
    }
}

// -------------------------------------------------------------------------------------------
// Assign configuration setup
void Cache :: Assign_Configurations(CONFIGURATION config)
{
    this -> config = config;
}

// -------------------------------------------------------------------------------------------

// Assign policy
void Cache :: Assign_Policy(PLACEMENT_POLICY policy)
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
    this -> wordQuantity = (this -> blockSize / this -> wordSize);
    
    // Predefine values of how many words per block if word count = 4
    binary fourWords[] =  {"00", "01", "10", "11"};
    
    // Predefine values of how many words per block if word count = 2
    binary twoWords[] =  {"0", "1"};
    
    // Predefine values of how many words per block if word count = 1
    binary oneWord[] = {"Instruction"};
    
    // Assign binary word value of 4 to wordVector dataset
    if(this -> wordQuantity == 4)
        for(int i = 0; i < sizeof(fourWords) / sizeof(fourWords[0]); i++)
            wordVector.push_back(fourWords[i]);
    
    // Assign binary word value of 2 to wordVector dataset
    else if(this -> wordQuantity == 2)
        for(int i = 0; i < sizeof(twoWords) / sizeof(twoWords[0]); i++)
            wordVector.push_back(twoWords[i]);
    
    // Assign binary word value of 1 to wordVector dataset
    else if(this -> wordQuantity == 1)
        for(int i = 0; i < sizeof(oneWord) / sizeof(oneWord[0]); i++)
            wordVector.push_back(oneWord[i]);
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
        return "\n--------------- Caching Algorithms ---------------\n\n1) Least Recently Used\t\t2) Least Frequently Used\n\n3) First In First Out\n\n--------------------------------------------------\n\nSelect: ";
    
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
// Determine input to select for Fully Associative Cache
INPUT Cache :: FullyAssociativeInput(input number)
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
// Determine input to select for Set Associative Cache
INPUT Cache :: SetAssociativeInput(input number)
{
    if(number == 1)
        return INPUT :: CACHE_SIZE;
    
    else if(number == 2)
        return INPUT :: BLOCK_SIZE;
    
    else if(number == 3)
        return INPUT :: MAIN_MEMORY;
    
    else if(number == 4)
        return INPUT :: CACHING_ALGORITHM;
    
    return INPUT :: INPUT_ERROR;
}

// -------------------------------------------------------------------------------------------
// Determine input to select for Fully Associative Cache
INPUT Cache :: DirectMappedInput(input number)
{
    if(number == 1)
        return INPUT :: CACHE_SIZE;
    
    else if(number == 2)
        return INPUT :: BLOCK_SIZE;
    
    else if(number == 3)
        return INPUT :: MAIN_MEMORY;
    
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
binaryVector Cache :: GenerateAddresses()
{
    // Collect each address
    binary address = "";
    
    // Store all addresses: key = binary address, value = hash value
    binaryVector cacheAddresses;
    
    // Declare vector to store predefined tags
    binaryVector tagVector;
    
    // Declare temporary tag value
    binary tempTag;
    
    // Tag size
    std::size_t tagSize = mainMemorySize - log2(this -> blockSize);
    
    // Predefine tags - this makes it so each tag will have multiple addresses in each way
    for(int i = 0; i < (this -> blockQuantity / 2); i++)
    {
        for(int x = 0; x < tagSize; x++)
        {
            int randomValue = rand() % 2;
            
            tempTag += std::to_string(randomValue);
        }
        
        tagVector.push_back(tempTag);
        
        tempTag = "";
    }
    
    // Amount of addresses should be half the # of slots for demonstration purposes
    for(int i = 0; i < this -> blockQuantity / 2; i++)
    {
        // Assign random tag value to address
        address = tagVector[rand() % tagVector.size()];
        
        for(int x = tagSize; x < this -> mainMemorySize; x++)
        {
            int randomValue = rand() % 2;
            
            address += std::to_string(randomValue);
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
// -------------------------------------------------------------------------------------------
