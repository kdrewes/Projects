#include "DirectMapped.hpp"

DirectMapped :: ~DirectMapped() = default;

void DirectMapped :: Router()
{
    // Determine word quantity binary words used
    ConfigureWord();
    
    // Generate binary data and store in vector
    this -> addressList = GenerateAddresses();
    
    // Determine address size
    this -> addressSize = addressList[0].size();
    
    // Assign hexadecimal values to address map
    for(std::vector<binary> :: size_type i = 0; i < addressList.size(); i++)
        for(std::vector<binary> :: size_type j = 0; j < wordQuantity; j++)
            addressMap[addressList[i]][wordVector[j]] = GetInstruction();
    
    // Implement hash table
    HashTable();
    
    // Insert CacheData properties into Fully_Associative_Vector vector
    for(int i = 0; i < this -> blockQuantity; i++)
        Direct_Mapping_Vector.push_back(Direct_Mapping_Structure(*this));
    
    std::cout << "\nAddress\t\t\tTag\t\t\tIndex\tOffset\n";
    
    for(int i = 0; i < Direct_Mapping_Vector.size(); i++)
    {
        std::cout << Direct_Mapping_Vector[i].address << "\t\t"
        << Direct_Mapping_Vector[i].tag << "\t\t"
        << Direct_Mapping_Vector[i].setIndex << "\t\t"
        << Direct_Mapping_Vector[i].offset << "\n\n";
    }
    
}

void DirectMapped :: Controller()
{
    // Display title
    Title();
  
    // Display data
    Data();
    
    // Display header
    Header();
       
    // Produce and display table
    Table();
    
    
}

// -------------------------------------------------------------------------------------------
// Create hash table
void DirectMapped :: HashTable()
{
    this -> addressTable.resize(addressList.size() * 2);
    
    this -> indexTable.resize(addressList.size() * 2);
}

// -------------------------------------------------------------------------------------------
// Assign hash index to addressTable or tagTable
void DirectMapped :: AssignHashIndex()
{
    switch(table)
    {
        case ADDRESS_TABLE:
        {
            // Retrieve hashed index and assign it to addressTable
            int hashIndex = GetHashIndex(Direct_Mapping_Vector[global_iterator].addressHashCode);
            
            // Assign data to designated hashed subscript of addressTable
            if(addressTable[hashIndex].first.empty() &&  addressTable[hashIndex].second.empty())
            {
                addressTable[hashIndex] = { Direct_Mapping_Vector[global_iterator].setIndex,Direct_Mapping_Vector[global_iterator].address };
                
                this -> hitOrMiss = false;
            }
            
            else
                this -> hitOrMiss = true;
            
            break;
            
        }
            
        case INDEX_TABLE:
        {
            // Retrieve hashed index and assign it to tagTable
            this->hashIndex = GetHashIndex(Direct_Mapping_Vector[global_iterator].indexHashCode);
            
            if(indexTable[hashIndex].first.empty() && indexTable[hashIndex].second.empty())
                indexTable[hashIndex] = { Direct_Mapping_Vector[global_iterator].setIndex, Direct_Mapping_Vector[global_iterator].tag };
            
            else
            {
               if((indexTable[hashIndex].first != Direct_Mapping_Vector[global_iterator].setIndex) || (indexTable[hashIndex].second != Direct_Mapping_Vector[global_iterator].tag))
               {
                   indexTable[hashIndex].first = Direct_Mapping_Vector[global_iterator].setIndex;
                   
                   indexTable[hashIndex].second = Direct_Mapping_Vector[global_iterator].tag;
               }
                   
            }
            
            break;
        }
            
        case HASH_TABLE_ERROR:
        {
            throw std::invalid_argument("\n\nError - Invalid table, please re-enter option.\n");
        }
    }
}

// -------------------------------------------------------------------------------------------
// Retreive hash index
DirectMapped :: index DirectMapped :: GetHashIndex(hashValue hashCode)
{
    switch(table)
    {
        case ADDRESS_TABLE:
        {
            // Declare hash code
            hashCode %= this -> addressTable.size();
            
            // Create copy of hashCode
            hashValue hashCopy = hashCode;
            
            // Iterator used to resolve any potential collisions
            index iterator = 0;
            
            while(true)
            {
                // Determine if subscript of addressTable[hashCode] is empty
                if(this -> addressTable[hashCode].first.empty() && this -> addressTable[hashCode].second.empty())
                    return hashCode;
                
                // Implement quadratic probing formula
                else
                {
                    // Determine if address is currently stored in hash table
                    if( (addressTable[hashCode].first == Direct_Mapping_Vector[global_iterator].setIndex) &&
                       (addressTable[hashCode].second == Direct_Mapping_Vector[global_iterator].address))
                        return hashCode;
                    
                    // Assign value of modified hash code
                    hashCode = (hashCopy + static_cast<index>(pow(iterator,2))) % this -> addressTable.size();
                    
                    // Increment iterator
                    iterator += 1;
                }
            }
            
            break;
        }
            
        case INDEX_TABLE:
        {
            // Declare hash code
            hashCode %= this -> indexTable.size();
            
            // Create copy of hashCode
            hashValue hashCopy = hashCode;
            
            // Iterator used to resolve any potential collisions
            index iterator = 0;
            
            while(true)
            {
                // Determine if subscript of tagTable[hashCode] is empty
                if(( this -> indexTable[hashCode].first.empty() && this -> indexTable[hashCode].second.empty() ) ||
                   indexTable[hashCode].first == Direct_Mapping_Vector[global_iterator].setIndex)
                    return hashCode;
                
                
                else
                {
                    // Assign value of modified hash code
                    hashCode = (hashCopy + static_cast<index>(pow(iterator,2))) % this -> indexTable.size();
                    
                    // Increment iterator
                    iterator += 1;
                }
            }
            
            break;
        }
            
        case HASH_TABLE_ERROR:
        {
            throw std::invalid_argument("\n\nError - Invalid table, please re-enter option.\n");
        }
            
    }
    
    return hashCode;
}

// -------------------------------------------------------------------------------------------
// Create Title
void DirectMapped :: Title()
{
    // Display Title
    console << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";

    console <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDirect Mapping Placement Policy\n";

    console <<"\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";


    spreadsheet <<"---------------------------------------------------- Direct Mapping Placement Policy ----------------------------------------------------\n";


    consoleToFile << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";

    consoleToFile <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDirect Mapping Placement Policy\n";

    consoleToFile <<"\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";
}

// -------------------------------------------------------------------------------------------
// Produce and display metrics
void DirectMapped :: Data()
{
    
    console << "\n\t\t\t\t\t\t\t\t\t\tCache Size = "   << this -> cacheSize                    << " Bytes\t\tBlock Size = "  << this -> blockSize    << " Bytes"
    
    << "\t\t# of Blocks = "                            << this -> blockQuantity                << " Bytes"
    
    << "\n\n\t\t\t\t\t\t\t\t\t\tIndex Size = "         << this -> indexSize                    << " Bytes\t\tOffset Size = " << this -> offsetSize  << " Bits"
    
    << "\t\tRam Size = "                               << this -> mainMemorySize               << " Bytes" << "\n\n\t\t\t\t\t\t\t\t\t\tWord Size  = "
    
    << this -> wordSize                                << " Bytes\t\t# of Words = "            << this -> wordQuantity
    
    << " Bytes"                                        << "\t\tTag Size = "                    << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes\n\n";
    
    
    
    spreadsheet << "\nCache Size," << "Block Size," << "# of Blocks," << "Offset Size,"  << "Ram Size," << "Word Size," << "# of Words," << "Tag Size\n";
    
    spreadsheet << this -> cacheSize << " Bytes" << ',' << this -> blockSize << " Bytes"  << ',' << this -> blockQuantity << " Bytes" << ','
    
    << this -> offsetSize << " Bits" << ',' << this -> mainMemorySize << " Bytes" << ',' << this -> wordSize << " Bytes" << ',' << this -> wordQuantity << " Bytes"
    
    << ',' << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes" << "\n\n";
    
    
    consoleToFile << "\n\t\t\t\t\t\t\t\t\t\tCache Size = "   << this -> cacheSize                    << " Bytes\t\tBlock Size = "  << this -> blockSize    << " Bytes"
    
    << "\t\t# of Blocks = "                            << this -> blockQuantity                << " Bytes"
    
    << "\n\n\t\t\t\t\t\t\t\t\t\tIndex Size = "         << this -> indexSize                    << " Bytes\t\tOffset Size = " << this -> offsetSize  << " Bits"
    
    << "\t\tRam Size = "                               << this -> mainMemorySize               << " Bytes" << "\n\n\t\t\t\t\t\t\t\t\t\tWord Size  = "
    
    << this -> wordSize                                << " Bytes\t\t# of Words = "            << this -> wordQuantity
    
    << " Bytes"                                        << "\t\tTag Size = "                    << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes\n\n";
    
}

// -------------------------------------------------------------------------------------------
// Create Header
void DirectMapped :: Header()
{
    // Predefine header
    std::string header[] = { "Address", "Index", "Tag", "Offset", "Hit_Miss", "Word", "instruction", "Evictions" };
    
    // Display Header banner
    console << "\n\t\t------------------------------------------------------------ Direct Mapping Cache Table ------------------------------------------------------------\n\n";

    spreadsheet << "------------------------------------------------------ Direct Mapping Cache Table ------------------------------------------------------\n\n";
    
    consoleToFile << "\n\t\t------------------------------------------------------------ Direct Mapping Cache Table ------------------------------------------------------------\n\n";
    
    // Display header
    for(int i = 0; i < sizeof(header) / sizeof(header[0]); i++)
        CreateHeader(FindHeader(header[i]));
    
}

// -------------------------------------------------------------------------------------------
// Produce column header
void DirectMapped :: CreateHeader(COLUMNS c)
{
    switch(c)
    {
        case ADDRESS :
            
            // Display each address
            if(this -> mainMemorySize == 8)
            {
                
                console << "\t\t\t\t\t\t\tAddress";
                
                spreadsheet << "Address,";
                
                consoleToFile << "\t\t\t\t\t\t\tAddress";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                console << "\t\t\t\t\t\t\tAddress\t";
                
                spreadsheet << "Address,";
                
                consoleToFile << "\t\t\t\t\t\t\tAddress\t";
            }
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            
            break;
            
        case INDEX :
            
            // Display each address
            if(this -> mainMemorySize == 8)
            {
                
                console << "\t\tSet #";
                
                spreadsheet << "Set #,";
                
                consoleToFile << "\t\tSet #";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                console << "\t\t\tSet #\t";
                
                spreadsheet << "Set #,";
                
                consoleToFile << "\t\t\tSet #";
            }
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case TAG :
            
            // Display each tag
            if(this -> mainMemorySize == 8)
            {
                console << "\tTag";
                
                spreadsheet << "Tag,";
                
                consoleToFile << "\tTag";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                console << "\t\tTag";
                
                spreadsheet << "Tag,";
                
                consoleToFile << "\t\tTag";
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            
            break;
            
        case OFFSET :
            
            // Display each offset
            if(this -> mainMemorySize == 8)
            {
                console << "\t\t\tOffset";
                
                spreadsheet << "Offset,";
                
                consoleToFile << "\t\t\tOffset";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                console << "\t\t\t\t\tOffset";
                
                spreadsheet << "Offset,";
                
                consoleToFile << "\t\t\t\t\tOffset";
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case HIT_MISS :
            
            // Display whether each address has a hit or miss
            if(this -> mainMemorySize == 8)
            {
                console << "\t\tH/M\t";
                
                spreadsheet << "H/M,";
                
                consoleToFile << "\t\tH/M\t";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                console << "\t\tH/M";
                
                spreadsheet << "H/M,";
                
                consoleToFile << "\t\tH/M";
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case WORD :
            
            // Skip if there is only one word present
            if(this -> mainMemorySize == 8)
            {
                if(wordVector.size() != 1)
                {
                    if(this -> wordQuantity == 2)
                    {
                        // Display each individual word in binary format
                        for(binaryVector :: size_type i = 0; i < wordVector.size(); i++)
                        {
                            console << "\t\t" << wordVector[i];
                            
                            spreadsheet << "=\""  << wordVector[i] << "\",";
                            
                            consoleToFile << "\t\t" << wordVector[i];
                        }
                    }
                    
                    else
                    {
                        for(binaryVector :: size_type i = 0; i < wordVector.size(); i++)
                        {
                            if(i == 0)
                            {
                                console << "\t" << wordVector[i] << "\t\t\t\t";
                                
                                spreadsheet << "=\""  << wordVector[i] << "\",";
                                
                                consoleToFile << "\t" << wordVector[i] << "\t\t\t\t";
                            }
                            else
                            {
                                console << wordVector[i] << "\t\t ";
                                
                                spreadsheet << "=\""  << wordVector[i] << "\",";
                                
                                consoleToFile << wordVector[i] << "\t\t ";
                            }
                        }
                    }
                }
            }
            
            else if(this -> mainMemorySize == 16)
            {
                if(wordVector.size() != 1)
                {
                    if(this -> wordQuantity == 2)
                    {
                        // Display each individual word in binary format
                        
                        for(binaryVector :: size_type i = 0; i < wordVector.size(); i++)
                        {
                            console << "\t\t  " << wordVector[i];
                            
                            spreadsheet << "=\""  << wordVector[i] << "\",";
                            
                            consoleToFile << "\t\t  " << wordVector[i];
                        }
                    }
                    
                    else
                    {
                        for(binaryVector :: size_type i = 0; i < wordVector.size(); i++)
                        {
                            if(i == 0)
                            {
                                console << "\t\t\t\t" << wordVector[i] << "\t";
                                
                                spreadsheet << "=\""  << wordVector[i] << "\",";
                                
                                consoleToFile << "\t\t\t\t" << wordVector[i]  << "\t";
                            }
                            else
                            {
                                console << wordVector[i] << "\t\t";
                                
                                spreadsheet << "=\""  << wordVector[i] << "\",";
                                
                                consoleToFile << wordVector[i] << "\t\t";
                            }
                        }
                    }
                }
            }
            
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case INSTRUCTION_RETREIVED :
            
            // Display which instruction was retreived
            if(this -> mainMemorySize == 8)
            {
                if(this -> wordQuantity == 1 || this -> wordQuantity == 2)
                {
                    console << "\t\tInstruction";
                    
                    spreadsheet << "Instruction,";
                    
                    consoleToFile << "\t\tInstruction";
                }
                else
                {
                    console << "\tInstruction";
                    
                    spreadsheet << "Instruction,";
                    
                    consoleToFile << "\tInstruction";
                }
            }
            
            else if(this -> mainMemorySize == 16)
            {
                if(this -> wordQuantity == 1 || this -> wordQuantity == 2)
                {
                    console << "\t\t\tInstruction";
                    
                    spreadsheet << "Instruction,";
                    
                    consoleToFile << "\t\t\tInstruction";
                }
                else
                {
                    console << "\t\t\tInstruction";
                    
                    spreadsheet << "Instruction,";
                    
                    consoleToFile << "\t\t\tInstruction";
                }
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case EVICTIONS :
            
            // Display if there were any evictions
            if(this -> mainMemorySize == 8)
            {
                console << "\t\t\tAddress(es) Evicted\n\n";
                
                spreadsheet << "Address(es) Evicted\n";
                
                consoleToFile << "\t\t\tAddress(es) Evicted\n\n";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                console << "\t\t\tAddress(es) Evicted\n\n";
                
                spreadsheet << "Address(es) Evicted\n";
                
                consoleToFile << "\t\t\tAddress(es) Evicted\n\n";
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case COLUMN_ERROR :
            throw std::invalid_argument("\n\nError - incorrect column header\n\nPlease correct command\n\n");
    }
}

// -------------------------------------------------------------------------------------------
// Display table
void DirectMapped :: Table()
{
    // Predefine table
    std::string table[] = { "Address", "Index", "Tag", "Offset", "Hit_Miss", "Word", "instruction", "Evictions" };
    
    // Traverse through each category for each individual subscript of Fully_Associative_Vector
    for(this -> global_iterator = 0; this -> global_iterator < Direct_Mapping_Vector.size(); this -> global_iterator++)
        for(int j = 0; j < sizeof(table) / sizeof(table[0]); j++)
            CreateTable(FindColumn(table[j]));
}

// -------------------------------------------------------------------------------------------
// Produce rows and columns in table
void DirectMapped :: CreateTable(COLUMNS columns)
{
    switch(columns)
    {
        case ADDRESS :
        {
            // Assign value to Hash table object
            this -> table = FindTable("Address");
            
            // Assign each address to its designated hash index
            AssignHashIndex();
            
            // Insert address data to each ostringstream variable
            console << "\t\t\t\t\t\t\t" << Direct_Mapping_Vector[global_iterator].address << " | ";
            
            spreadsheet << "=\""  << Direct_Mapping_Vector[global_iterator].address << "\",";
            
            consoleToFile << "\t\t\t\t\t\t\t" << Direct_Mapping_Vector[global_iterator].address << " | ";
            
            break;
        }
            
        case INDEX :
        {
            // Assign value to Hash table object
            this -> table = FindTable("Index");
            
            // Assign each address to its designated hash index
            AssignHashIndex();
            
            console << "\t" << this -> indexTable[hashIndex].first << "\t|";
            
            spreadsheet << "=\""   << this -> indexTable[hashIndex].first  << "\",";
            
            consoleToFile << "\t" << this -> indexTable[hashIndex].first << "\t|";
        }
            
            break;
            
        case TAG :
        {
            console << "\t" << indexTable[hashIndex].second << "\t|";
            
            spreadsheet << "=\""   << indexTable[hashIndex].second << "\",";
            
            consoleToFile << "\t" << indexTable[hashIndex].second << "\t|";
        }
            
            break;
            
        case OFFSET :
        {
            
            console << "\t  " << this -> Direct_Mapping_Vector[global_iterator].offset << " \t| ";
            
            spreadsheet << "=\""  << this -> Direct_Mapping_Vector[global_iterator].offset << "\",";
            
            consoleToFile << "\t  " << this -> Direct_Mapping_Vector[global_iterator].offset << " \t| ";
        }
            
            break;
            
        case HIT_MISS :
        {
            if(hitOrMiss)
            {
                console << "\tHit \t| ";
                
                spreadsheet << "=\""  << "Hit" << "\",";
                
                consoleToFile << "\tHit\t| ";
                
                hitOrMiss = false;
            }
            
            else
            {
                console << "\tMiss\t| ";
                
                spreadsheet << "=\""  << "Miss" << "\",";
                
                consoleToFile << "\tMiss\t| ";
                
            }
        }
            
            break;
            
        case WORD :
        {
            if(wordVector.size() != 1)
            {
                // Display each individual instruction in hexadecimal format
                for(binaryVector :: size_type i = 0; i < wordVector.size(); i++)
                {
                    console << Direct_Mapping_Vector[global_iterator].instructionMap[wordVector[i]] << " | ";
                    
                    spreadsheet << "=\"" << Direct_Mapping_Vector[global_iterator].instructionMap[wordVector[i]] << "\",";
                    
                    consoleToFile << Direct_Mapping_Vector[global_iterator].instructionMap[wordVector[i]] << " | ";
                }
            }
        }
            
            break;
            
        case INSTRUCTION_RETREIVED :
        {
            console << "      " << this -> Direct_Mapping_Vector[global_iterator].instruction << "\t\t|";
            
            spreadsheet << "=\""  << this -> Direct_Mapping_Vector[global_iterator].instruction << "\",";
            
            consoleToFile << "      " << this -> Direct_Mapping_Vector[global_iterator].instruction << "\t\t|";
        }
            
            break;
            
        case EVICTIONS :
            
            if(!this -> Direct_Mapping_Vector[global_iterator].addressEvicted.empty())
            {
                console  << "\t\t\t" << this -> Direct_Mapping_Vector[global_iterator].addressEvicted << '\n';
                
                spreadsheet << this -> Direct_Mapping_Vector[global_iterator].addressEvicted << '\n';
                
                consoleToFile  << "\t\t\t" << this -> Direct_Mapping_Vector[global_iterator].addressEvicted << '\n';
                
            }
            
            else
            {
                console << '\t' << '\t' << '\t' << '\t' << '-' << '\n';
                
                spreadsheet << '-' << '\n';
                
                consoleToFile << '\t' << '\t' << '\t' << '\t' << '-' << '\n';
            }
            
            
            break;
            
        case COLUMN_ERROR :
            
            std::cout << "\nCOLUMN_ERROR - iterator = " << this -> global_iterator;
            throw std::invalid_argument("\n\nError - incorrect column header\n\nPlease correct command\n\n");
    }
}


// -------------------------------------------------------------------------------------------
// Make each string lower case
std::string DirectMapped :: toLower(std::string header)
{
    for(int i = 0; i < header.size(); i++)
        header[i] = std::tolower(header[i]);
    
    return header;
}

// -------------------------------------------------------------------------------------------
// Find header for each column
COLUMNS DirectMapped :: FindHeader (std::string header)
{
    if(toLower(header) == "address")
        return COLUMNS :: ADDRESS;
    
    else if (toLower(header) == "index")
        return COLUMNS :: INDEX;
    
    else if(toLower(header) == "tag")
        return COLUMNS :: TAG;
    
    else if(toLower(header) == "offset")
        return COLUMNS :: OFFSET;
    
    else if(toLower(header) == "hit_miss")
        return COLUMNS :: HIT_MISS;
    
    else if(toLower(header) == "evictions")
        return COLUMNS :: EVICTIONS;
    
    else if(toLower(header) == "word")
        return COLUMNS :: WORD;
    
    else if(toLower(header) == "instruction_retreived" || toLower(header) == "instruction")
        return COLUMNS :: INSTRUCTION_RETREIVED;
    
    return COLUMNS :: COLUMN_ERROR;
}

// -------------------------------------------------------------------------------------------
// Find column for each row
COLUMNS DirectMapped :: FindColumn (std::string column)
{
    if(toLower(column) == "address")
        return COLUMNS :: ADDRESS;
    
    else if (toLower(column) == "index")
        return COLUMNS :: INDEX;
    
    else if(toLower(column) == "tag")
        return COLUMNS :: TAG;
    
    else if(toLower(column) == "offset")
        return COLUMNS :: OFFSET;
    
    else if(toLower(column) == "hit_miss")
        return COLUMNS :: HIT_MISS;
    
    else if(toLower(column) == "evictions")
        return COLUMNS :: EVICTIONS;
    
    else if(toLower(column) == "word")
        return COLUMNS :: WORD;
    
    else if(toLower(column) == "instruction_retreived" || toLower(column) == "instruction")
        return COLUMNS :: INSTRUCTION_RETREIVED;
    
    return COLUMNS :: COLUMN_ERROR;
}

// -------------------------------------------------------------------------------------------
// Find addressTable or tagTag hashing formula
HASH_TABLE DirectMapped :: FindTable (std::string table)
{
    if(toLower(table) == "address" || toLower(table) == "address table")
        return HASH_TABLE :: ADDRESS_TABLE;
    
    else if(toLower(table) == "index" || toLower(table) == "index table")
        return HASH_TABLE :: INDEX_TABLE;
    
    return HASH_TABLE :: HASH_TABLE_ERROR;
}

// -------------------------------------------------------------------------------------------
void DirectMapped :: Print()
{
    std::cout << console.str();
    
    file write("testFile.csv");
    
    write << spreadsheet.str();
    
    write.close();
}
