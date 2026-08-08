#include "DirectMapped.hpp"

// Initialize Deconstructor
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
    
}

void DirectMapped :: Controller()
{
    // Execute document skeleton of html
    HTML();
    
    // Execute css syntax
    CSS();
    
    // Display title
    Title();
  
    // Display data
    Data();
    
    // Display header
    Header();
       
    // Produce and display table
    Table();
    
    // End HTML logic
    EndHTML();
    
}

// -------------------------------------------------------------------------------------------
// Create hash table
void DirectMapped :: HashTable()
{
    this -> addressTable.resize(addressList.size() * 2);
    
    this -> indexTable.resize(addressList.size() * 2);
}

// -------------------------------------------------------------------------------------------
// Assign hash index to addressTable or indexTable
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
                // Assign pair value of index and address to address table
                addressTable[hashIndex] = { Direct_Mapping_Vector[global_iterator].setIndex,Direct_Mapping_Vector[global_iterator].address };
            }
            
            break;
            
        }
            
        case INDEX_TABLE:
        {
            // Retrieve hashed index and assign it to indexTable
            this->hashIndex = GetHashIndex(Direct_Mapping_Vector[global_iterator].indexHashCode);
            
            // Declare variable of current set
            const binary & currentSet = Direct_Mapping_Vector[global_iterator].setIndex;
            
            // Declare variable of current tag
            const binary & currentTag = Direct_Mapping_Vector[global_iterator].tag;
            
            // Declare variable of current address
            const binary & incomingAddress = Direct_Mapping_Vector[global_iterator].address;
            
            // Execute condition if set and tag is currently empty
            if(indexTable[hashIndex].first.empty() && indexTable[hashIndex].second.empty())
            {
                // Assign pair value of set and tag to formulate indexTable
                indexTable[hashIndex] = { currentSet, currentTag };
                
                // Assign address to designated set
                cachedAddressByIndex[currentSet] = incomingAddress;
                
                // Reset Direct_Mapping_Vector
                Direct_Mapping_Vector[global_iterator].addressEvicted.clear();
                
                // Reset hitOrMiss booleon variable
                this -> hitOrMiss = false;
            }
            
            // Execute condition if indexTable[hashIndex].first or indexTable[hashIndex].second is currently occupied
            else
            {
                // Declare a hit has occurred if the current set and tag are currently stored in cache
                const bool directMappedHit = indexTable[hashIndex].first == currentSet && indexTable[hashIndex].second == currentTag;
                
                // Execute if hit occurs
                if(directMappedHit)
                {
                    // Clear previous evictioned address
                    Direct_Mapping_Vector[global_iterator].addressEvicted.clear();
                    
                    // Confirm a hit occured
                    this -> hitOrMiss = true;
                }
                
                // Execute condition if a direct mapped miss occurs
                else
                {
                    // Declare variable to determine if current set is currently stored in cache but current tag is not stored in cache
                    const bool directMappedConflict = !indexTable[hashIndex].second.empty() && indexTable[hashIndex].first == currentSet && indexTable[hashIndex].second != currentTag;
                    
                    // Execute condition if current index is currently stored in cache
                    if(directMappedConflict && cachedAddressByIndex.find(currentSet) != cachedAddressByIndex.end())
                        
                        // Replace previous evicted address with current evicted address
                        Direct_Mapping_Vector[global_iterator].addressEvicted = cachedAddressByIndex[currentSet];
                    
                    else
                        // Clear previous evicted address if current address is not being replaced
                        Direct_Mapping_Vector[global_iterator].addressEvicted.clear();
                    
                    // Include current set in indexTable
                    indexTable[hashIndex].first = currentSet;
                    
                    // Include current tag in indexTable
                    indexTable[hashIndex].second = currentTag;
                    
                    // Include address in cachedAddressByIndex map
                    cachedAddressByIndex[currentSet] = incomingAddress;
                    
                    // Reset hitOrMiss variable
                    this -> hitOrMiss = false;
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
// Execute document skeleton of html
void DirectMapped :: HTML()
{
    html << "<!DOCTYPE html>";
    html << R"(<html lang="en">)";
    html << "<head>";
    html << R"(<meta charset="UTF-8">)";
    html << R"(<meta name="viewport" content="width=device-width, initial-scale=1.0">)";
    html << "<title>Cache Project</title>";
    html << R"(<link rel="stylesheet" href="stylesheet.css">)";
    html << "</head>";
    html << "<body>";
    html << R"(<div class="background">)";
    html << R"(<div class="foundation">)";
}

// -------------------------------------------------------------------------------------------
// Include CSS logic
void DirectMapped :: CSS()
{
    css << "@import url('https://fonts.googleapis.com/css2?family=Anonymous+Pro:ital,wght@0,400;0,700;1,400;1,700&family=Yanone+Kaffeesatz:wght@200..700&display=swap');";
    css << "@import url('https://fonts.googleapis.com/css2?family=League+Spartan:wght@100..900&display=swap');";
    css << "@import url('https://fonts.googleapis.com/css2?family=Anaheim:wght@400..800&display=swap');";

    // ------------------------------------------------------
    css << "body";
    css << "{";
    css << "  background: rgb(230, 230, 230);";
    css << "  margin: 0;";
    css << "  padding: 0;";
    css << "}";

    // ------------------------------------------------------
    css << ".background ";
    css << "{";
    css << "  background: linear-gradient(to top,rgba(0, 0, 0, 0.7),rgba(255, 255, 255, 0.5)),";
    css << "  url(\"blue.jpg\");";
    css << "  background-size: cover;";
    css << "  background-position:center;";
    css << "  background-repeat: no-repeat;";
    css << "  min-height: 1000px;";
    css << "  animation: opacityEffect 2s ease-out forwards;";
    css << "}";

    // ------------------------------------------------------
    css << ".foundation {";
    css << "  width: fit-content;";
    css << "}";

    // ------------------------------------------------------
    css << ".header";
    css << "{";
    css << "  height: 35px;";
    css << "  background: rgba(0, 0, 0, 1);";
    css << "  transform: translate(350px,200px);";
    css << "  border-radius: 5px;";
    css << "  text-align: center;";
    css << "  font-size: 20px;";
    css << "  color: white;";
    css << "  opacity: 0;";
    css << "  font-family: \"Anonymous Pro\";";
    css << "  display: flex;";
    css << "  justify-content: center;";
    css << "  align-items: center;";
    css << "  animation: opacityEffect 1.7s ease-out 1.2s forwards;";
    css << "}";

    // ------------------------------------------------------
    css << ".data";
    css << "{";
    css << "  margin-top: 3px;";
    css << "  margin-bottom: 25px;";
    css << "  text-align: center;";
    css << "}";

    css << ".data td";
    css << "{";
    css << "  background-color: transparent;";
    css << "  border: none;";
    css << "}";

    // ------------------------------------------------------
    css << ".data table ";
    css << "{";
    css << "  width: 100%;";
    css << "}";

    css << ".cache";
    css << "{";
    css << " height: auto;";
    css << " padding-top: 200px;";
    css << " animation: opacityEffect 1.5s ease-out forwards,";
    css << "            slideFromTop 1.2s ease-out forwards;";
    css << "}";

    // ------------------------------------------------------
    css << "table ";
    css << "{";
    css << "  border-spacing: 0;";
    css << "  border-radius: 5px;";
    css << "  overflow: hidden;";
    css << "}";

    // ------------------------------------------------------
    css << "th ";
    css << "{";
    css << "  font-size: 13px;";
    css << "  font-family: \"Anonymous Pro\";";
    css << "  padding: 8px 8px;";
    css << "  text-align: left;";
    css << "  background-color: rgba(0, 0, 0);";
    css << "  color: white;";
    css << "}";

    // ------------------------------------------------------
    css << "td";
    css << "{";
    css << "  border-bottom: solid rgba(255, 255, 255, 0.5) 1px;";
    css << "  padding: 6px 13px 6px 13px;";
    css << "  font-size: 12px;";
    css << "  font-family: \"Anonymous Pro\";";
    css << "  background-color:rgba(255, 255, 255, .2);";
    css << "}";

    // ------------------------------------------------------
    css << "p ";
    css << "{";
    css << "  font-family: \"Anonymous Pro\";";
    css << "  text-align: center;";
    css << "}";

    // ------------------------------------------------------
    // Animations
    css << "@keyframes opacityEffect{";
    css << "    0%{";
    css << "        opacity: 0;";
    css << "    }";
    css << "    100%{";
    css << "        opacity: 1;";
    css << "    }";
    css << "}";

    // ------------------------------------------------------
    css << "@keyframes slideFromTop{";
    css << "    0%{";
    css << "       transform: translate(350px,-460px);";
    css << "    }";
    css << "    100%{";
    css << "        transform: translate(350px,10px);";
    css << "    }";
    css << "}";
}


// -------------------------------------------------------------------------------------------
// Create Title
void DirectMapped :: Title()
{
    
    // ------------------------ Create title for html ------------------------

        html << R"(<div class="header">)";
    
        html <<  "Direct Mapping Placement Policy";
    
        html << "</div>";
    
    // ------------------------ Create title for console ------------------------
    
    console << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";

    console <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDirect Mapping Placement Policy\n";

    console <<"\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";

    // ------------------------ Create title for spreadsheet ------------------------
    
    spreadsheet <<"---------------------------------------------------- Direct Mapping Placement Policy ----------------------------------------------------\n";


    consoleToFile << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";

    consoleToFile <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDirect Mapping Placement Policy\n";

    consoleToFile <<"\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";
}

// -------------------------------------------------------------------------------------------
// Produce and display metrics
void DirectMapped :: Data()
{
    // ------------------------ Create data for html ------------------------
    
    html << R"(<div class="cache">)";
    html << R"(<div class="data">)";
    html << "<table>";
    html << "<tr>";
    html << "<td>Cache Size = " << this -> cacheSize << " Bytes" << "</td>";
    html << "<td>Block Size = " << this -> blockSize << " Bytes" << "</td>";
    html << "<td># of Blocks = " <<  this -> blockQuantity << " Bytes" << "</td>";
    html << "</tr>";
    html << "<tr>";
    html << "<td> Index Size = " << this -> indexSize << " Bytes" << "</td>";
    html << "<td>Offset Size = " << this -> offsetSize  << " Bits" << "</td>";
    html << "<td>Ram Size = " <<  this -> mainMemorySize << " Bytes" << "</td>";
    html << "</tr>";
    html << "<tr>";
    html << "<td>Word Size = " << this -> wordSize << " Bytes" << "</td>";
    html << "<td>Word Quantity = " << this -> wordQuantity  << " Bytes" << "</td>";
    html << "<td>Tag Size= " <<  this -> addressSize - this -> indexSize - std::floor(log2(this -> blockSize)) << " Bytes" << "</td>";
    html << "</tr>";
    html << "</table>";
    html << "</div>";
    
    // ------------------------ Create data for console ------------------------
    
    console << "\n\t\t\t\t\t\t\t\t\t\tCache Size = "   << this -> cacheSize                    << " Bytes\t\tBlock Size = "  << this -> blockSize    << " Bytes"
    
    << "\t\t# of Blocks = "                            << this -> blockQuantity                << " Bytes"
    
    << "\n\n\t\t\t\t\t\t\t\t\t\tIndex Size = "         << this -> indexSize                    << " Bytes\t\tOffset Size = " << this -> offsetSize  << " Bits"
    
    << "\t\tRam Size = "                               << this -> mainMemorySize               << " Bytes" << "\n\n\t\t\t\t\t\t\t\t\t\tWord Size  = "
    
    << this -> wordSize                                << " Bytes\t\t# of Words = "            << this -> wordQuantity
    
    << " Bytes"                                        << "\t\tTag Size = "                    << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes\n\n";
    
    
    // ------------------------ data title for spreadsheet ------------------------
    
    spreadsheet << "\nCache Size," << "Block Size," << "# of Blocks," << "Offset Size,"  << "Ram Size," << "Word Size," << "# of Words," << "Tag Size\n";
    
    spreadsheet << this -> cacheSize << " Bytes" << ',' << this -> blockSize << " Bytes"  << ',' << this -> blockQuantity << " Bytes" << ','
    
    << this -> offsetSize << " Bits" << ',' << this -> mainMemorySize << " Bytes" << ',' << this -> wordSize << " Bytes" << ',' << this -> wordQuantity << " Bytes"
    
    << ',' << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes" << "\n\n";
    
    
    // ------------------------ data title for console file ------------------------
    
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
    
    // Include html logic
    html << "<table>";
    html << "<tr>";
    
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
                html << "<th>Address</th>";
                
                console << "\t\t\t\t\t\t\tAddress";
                
                spreadsheet << "Address,";
                
                consoleToFile << "\t\t\t\t\t\t\tAddress";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Address</th>";
                
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
                html << "<th>Set #</th>";
                
                console << "\t\tSet #";
                
                spreadsheet << "Set #,";
                
                consoleToFile << "\t\tSet #";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Set #</th>";
                
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
                html << "<th>Tag</th>";
                
                console << "\tTag";
                
                spreadsheet << "Tag,";
                
                consoleToFile << "\tTag";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Tag</th>";
                
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
                html << "<th>Offset</th>";
                
                console << "\t\t\tOffset";
                
                spreadsheet << "Offset,";
                
                consoleToFile << "\t\t\tOffset";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Offset</th>";
                
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
                html << "<th>H/M</th>";
                
                console << "\t\tH/M\t";
                
                spreadsheet << "H/M,";
                
                consoleToFile << "\t\tH/M\t";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>H/M</th>";
                
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
                            html << "<th>" << wordVector[i] << "</th>";
                            
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
                                html << "<th>" << wordVector[i] << "</th>";
                                
                                console << "\t" << wordVector[i] << "\t\t\t\t";
                                
                                spreadsheet << "=\""  << wordVector[i] << "\",";
                                
                                consoleToFile << "\t" << wordVector[i] << "\t\t\t\t";
                            }
                            else
                            {
                                html << "<th>" << wordVector[i] << "</th>";
                                
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
                            html << "<th>" << wordVector[i] << "</th>";
                            
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
                                html << "<th>" << wordVector[i] << "</th>";
                                
                                console << "\t\t\t\t" << wordVector[i] << "\t";
                                
                                spreadsheet << "=\""  << wordVector[i] << "\",";
                                
                                consoleToFile << "\t\t\t\t" << wordVector[i]  << "\t";
                            }
                            else
                            {
                                html << "<th>" << wordVector[i] << "</th>";
                                
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
                    html << "<th>Instruction</th>";
                    
                    console << "\t\tInstruction";
                    
                    spreadsheet << "Instruction,";
                    
                    consoleToFile << "\t\tInstruction";
                }
                else
                {
                    html << "<th>Instruction</th>";
                    
                    console << "\tInstruction";
                    
                    spreadsheet << "Instruction,";
                    
                    consoleToFile << "\tInstruction";
                }
            }
            
            else if(this -> mainMemorySize == 16)
            {
                if(this -> wordQuantity == 1 || this -> wordQuantity == 2)
                {
                    html << "<th>Instruction</th>";
                    
                    console << "\t\t\tInstruction";
                    
                    spreadsheet << "Instruction,";
                    
                    consoleToFile << "\t\t\tInstruction";
                }
                else
                {
                    html << "<th>Instruction</th>";
                    
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
                html << "<th>Address(es) Evicted</th>";
                
                console << "\t\t\tAddress(es) Evicted\n\n";
                
                spreadsheet << "Address(es) Evicted\n";
                
                consoleToFile << "\t\t\tAddress(es) Evicted\n\n";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Address(es) Evicted</th>";
                
                console << "\t\t\tAddress(es) Evicted\n\n";
                
                spreadsheet << "Address(es) Evicted\n";
                
                consoleToFile << "\t\t\tAddress(es) Evicted\n\n";
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            // End html header logic
            html << "</tr>";
            
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
    
    // Include html logic
    html << "<tr>";
    
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
            html << "<td>" << Direct_Mapping_Vector[global_iterator].address << "</td>";
            
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
            
            html << "<td>" << this -> indexTable[hashIndex].first << "</td>";
            
            console << "\t" << this -> indexTable[hashIndex].first << "\t|";
            
            spreadsheet << "=\""   << this -> indexTable[hashIndex].first  << "\",";
            
            consoleToFile << "\t" << this -> indexTable[hashIndex].first << "\t|";
        }
            
            break;
            
        case TAG :
        {
            html << "<td>" << this -> indexTable[hashIndex].second << "</td>";
            
            console << "\t" << indexTable[hashIndex].second << "\t|";
            
            spreadsheet << "=\""   << indexTable[hashIndex].second << "\",";
            
            consoleToFile << "\t" << indexTable[hashIndex].second << "\t|";
        }
            
            break;
            
        case OFFSET :
        {
            html << "<td>" << this -> Direct_Mapping_Vector[global_iterator].offset << "</td>";
            
            console << "\t  " << this -> Direct_Mapping_Vector[global_iterator].offset << " \t| ";
            
            spreadsheet << "=\""  << this -> Direct_Mapping_Vector[global_iterator].offset << "\",";
            
            consoleToFile << "\t  " << this -> Direct_Mapping_Vector[global_iterator].offset << " \t| ";
        }
            
            break;
            
        case HIT_MISS :
        {
            if(hitOrMiss)
            {
                html << "<td>" << "Hit" << "</td>";
                
                console << "\tHit \t| ";
                
                spreadsheet << "=\""  << "Hit" << "\",";
                
                consoleToFile << "\tHit\t| ";
                
                hitOrMiss = false;
            }
            
            else
            {
                html << "<td>" << "Miss" << "</td>";
                
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
                    html << "<td>" << Direct_Mapping_Vector[global_iterator].instructionMap[wordVector[i]] << "</td>";
                    
                    console << Direct_Mapping_Vector[global_iterator].instructionMap[wordVector[i]] << " | ";
                    
                    spreadsheet << "=\"" << Direct_Mapping_Vector[global_iterator].instructionMap[wordVector[i]] << "\",";
                    
                    consoleToFile << Direct_Mapping_Vector[global_iterator].instructionMap[wordVector[i]] << " | ";
                }
            }
        }
            
            break;
            
        case INSTRUCTION_RETREIVED :
        {
            html << "<td>" << this -> Direct_Mapping_Vector[global_iterator].instruction << "</td>";
            
            console << "      " << this -> Direct_Mapping_Vector[global_iterator].instruction << "\t\t|";
            
            spreadsheet << "=\""  << this -> Direct_Mapping_Vector[global_iterator].instruction << "\",";
            
            consoleToFile << "      " << this -> Direct_Mapping_Vector[global_iterator].instruction << "\t\t|";
        }
            
            break;
            
        case EVICTIONS :
            
            if(!this -> Direct_Mapping_Vector[global_iterator].addressEvicted.empty())
            {
                html << "<td>" << this -> Direct_Mapping_Vector[global_iterator].addressEvicted << "</td>";
                
                console  << "\t\t\t" << this -> Direct_Mapping_Vector[global_iterator].addressEvicted << '\n';
                
                spreadsheet << this -> Direct_Mapping_Vector[global_iterator].addressEvicted << '\n';
                
                consoleToFile  << "\t\t\t" << this -> Direct_Mapping_Vector[global_iterator].addressEvicted << '\n';
                
            }
            
            else
            {
                html << "<td>" << '-' << "</td>";
                
                console << '\t' << '\t' << '\t' << '\t' << '-' << '\n';
                
                spreadsheet << '-' << '\n';
                
                consoleToFile << '\t' << '\t' << '\t' << '\t' << '-' << '\n';
            }
            
            // End html row
            html << "</tr>";
            
            break;
            
        case COLUMN_ERROR :
            
            std::cout << "\nCOLUMN_ERROR - iterator = " << this -> global_iterator;
            throw std::invalid_argument("\n\nError - incorrect column header\n\nPlease correct command\n\n");
    }
}

// -------------------------------------------------------------------------------------------
// End html logic
void DirectMapped :: EndHTML()
{
    html << "</table>";
    html << "</div>";
    html << "</div>";
    html << "</div>";
    html << "</body>";
    html << "</html>";
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
    // Produce microsoft word file
    file write("testFile.doc");
    
    // Write to file
    write << console.str();

    // Write to console
    std::cout << console.str();
    
    // Close file
    write.close();
    
    // Produce excel spreadsheet file
    write.open("testFile.csv");
    
    // Write to spreadsheet
    write << spreadsheet.str();
    
    // Close file
    write.close();
    
    // Produce html file
    write.open("index.html");
    
    // Write to html.index
    write << html.str();
    
    // Close file
    write.close();
    
    // Produce css file
    write.open("stylesheet.css");
    
    // Write to html.index
    write << css.str();
    
    // Close file
    write.close();
}
