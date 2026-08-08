#include "SetAssociated.hpp"

SetAssociated :: ~SetAssociated() = default;

void SetAssociated :: Router()
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
        Set_Associative_Vector.push_back(Set_Associative_Structure(*this));
}

// -------------------------------------------------------------------------------------------
// Execute binary data
void SetAssociated :: Controller()
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
void SetAssociated :: HashTable()
{
    this -> addressTable.resize(addressList.size() * 2);
    
    this -> indexTable.resize(addressList.size() * 2);
}

// -------------------------------------------------------------------------------------------
// Assign hash index to addressTable or tagTable
void SetAssociated :: AssignHashIndex()
{
    switch(table)
    {
        case ADDRESS_TABLE:
        {
            // Retrieve hashed index and assign it to addressTable
            int hashIndex = GetHashIndex(Set_Associative_Vector[global_iterator].addressHashCode);
            
            // Assign data to designated hashed subscript of addressTable
            if(addressTable[hashIndex].first.empty() &&  addressTable[hashIndex].second.empty())
            {
                addressTable[hashIndex] = {Set_Associative_Vector[global_iterator].setIndex,Set_Associative_Vector[global_iterator].address};
                
                this -> hitOrMiss = false;
            }
            
            else
                this -> hitOrMiss = true;
            
            break;
            
        }
            
        case INDEX_TABLE:
        {
            // Select placement policy algorithm
            this -> PlacementPolicy(table);
            
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
SetAssociated :: index SetAssociated :: GetHashIndex(hashValue hashCode)
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
                    if( (addressTable[hashCode].first == Set_Associative_Vector[global_iterator].setIndex) &&
                       (addressTable[hashCode].second == Set_Associative_Vector[global_iterator].address) )
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
                   indexTable[hashCode].first == Set_Associative_Vector[global_iterator].setIndex)
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
void SetAssociated :: HTML()
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
void SetAssociated :: CSS()
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
void SetAssociated :: Title()
{
    
    // ------------------------ Create title for html ------------------------
    
    if(placementPolicy == CACHING_ALGORITHM :: LRU)
    {
        html << R"(<div class="header">)";
        html <<  "Set Associative Placement Policy - LRU";
        html << "</div>";
    }
    
    else if(placementPolicy == CACHING_ALGORITHM :: LFU)
    {
        html << R"(<div class="header">)";
        html <<  "Set Associative Placement Policy - LFU";
        html << "</div>";
    }
    
    else if(placementPolicy == CACHING_ALGORITHM :: FIFO)
    {
        html << R"(<div class="header">)";
        html <<  "Set Associative Placement Policy - FIFO";
        html << "</div>";
    }
    
    // ------------------------ Create title for console ------------------------
    
    console << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";

    if(placementPolicy == CACHING_ALGORITHM :: LRU)
        console <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tSet Associative Placement Policy - LRU\n";

    else if(placementPolicy == CACHING_ALGORITHM :: LFU)
        console <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tSet Associative Placement Policy - LFU\n";

    else if(placementPolicy == CACHING_ALGORITHM :: FIFO)
        console <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tSet Associative Placement Policy - FIFO\n";

    console <<"\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";
    
    // ------------------------ Create title for spreadsheet ------------------------

    if(placementPolicy == CACHING_ALGORITHM :: LRU)
        spreadsheet <<"---------------------------------------------------- Set Associative Placement Policy - LRU ----------------------------------------------------\n";

    else if(placementPolicy == CACHING_ALGORITHM :: LFU)
        spreadsheet <<"---------------------------------------------------- Set Associative Placement Policy - LFU ----------------------------------------------------\n";

    else if(placementPolicy == CACHING_ALGORITHM :: FIFO)
        spreadsheet <<"---------------------------------------------------- Set Associative Placement Policy - FIFO ----------------------------------------------------\n";

    // ------------------------ Create title for console to file ------------------------

    consoleToFile << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";

    if(placementPolicy == CACHING_ALGORITHM :: LRU)
        consoleToFile <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tSet Associative Placement Policy - LRU\n";

    else if(placementPolicy == CACHING_ALGORITHM :: LFU)
        consoleToFile <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tSet Associative Placement Policy - LFU\n";

    else if(placementPolicy == CACHING_ALGORITHM :: FIFO)
        consoleToFile <<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tFully Associative Placement Policy - FIFO\n";

    consoleToFile <<"\t\t\t\t\t\t\t\t\t\t------------------------------------------------------------------------------\n";
}

// -------------------------------------------------------------------------------------------
// Produce and display metrics
void SetAssociated :: Data()
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
    html << "<td># of Ways = " << this -> ways << " Bytes" << "</td>";
    html << "<td>Offset Size = " << this -> offsetSize  << " Bits" << "</td>";
    html << "<td>Ram Size = " <<  this -> mainMemorySize << " Bytes" << "</td>";
    html << "</tr>";
    html << "<tr>";
    html << "<td>Word Size = " << this -> wordSize << " Bytes" << "</td>";
    html << "<td>Word Quantity = " << this -> wordQuantity  << " Bytes" << "</td>";
    html << "<td>Tag Size = " <<  this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes" << "</td>";
    html << "</tr>";
    html << "<tr>";
    html << "<td>Index Size = " << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes" << "</td>";
    html << "</tr>";
    html << "</table>";
    html << "</div>";
    
    // ------------------------ Create data for console ------------------------
    
    console << "\n\t\t\t\t\t\t\t\t\t\tCache Size = "          << this -> cacheSize                    << " Bytes\t\tBlock Size = "  << this -> blockSize    << " Bytes"
    
    << "\t\t# of Blocks = "                   << this -> blockQuantity                << " Bytes"
    
    << "\n\n\t\t\t\t\t\t\t\t\t\t# of Ways = "         << this -> ways                         << " Bytes\t\t\tOffset Size = " << this -> offsetSize  << " Bits"
    
    << "\t\tRam Size = "                      << this -> mainMemorySize               << " Bytes" << "\n\n\t\t\t\t\t\t\t\t\t\tWord Size  = "
    
    << this -> wordSize                       << " Bytes\t\t# of Words = "            << this -> wordQuantity
    
    << " Bytes"                               << "\t\tTag Size = "                    << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes\n\n"
    
    << "\t\t\t\t\t\t\t\t\t\tIndex Size = "  << this -> indexSize << "\n\n";
    
    // ------------------------ data title for spreadsheet ------------------------
    
    spreadsheet << "\nCache Size," << "Block Size," << "# of Blocks," << "# of Ways," << "Offset Size,"  << "Ram Size," << "Word Size," << "# of Words," << "Tag Size\n";
    
    spreadsheet << this -> cacheSize << " Bytes" << ',' << this -> blockSize << " Bytes"  << ',' << this -> blockQuantity << " Bytes" << ',' << this -> ways << " Bytes" << ','
    
    << this -> offsetSize << " Bits" << ',' << this -> mainMemorySize << " Bytes" << ',' << this -> wordSize << " Bytes" << ',' << this -> wordQuantity << " Bytes"
    
    << ',' << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes" << "\n\n";
    
    // ------------------------ data title for console file ------------------------

    consoleToFile << "\n\t\t\t\t\t\t\t\t\t\tCache Size = "          << this -> cacheSize                    << " Bytes\t\tBlock Size = "  << this -> blockSize    << " Bytes"
    
    << "\t\t# of Blocks = "                         << this -> blockQuantity                << " Bytes"
    
    << "\n\n\t\t\t\t\t\t\t\t\t\t# of Ways = "               << this -> ways                         << " Bytes\t\t\tOffset Size = " << this -> offsetSize  << " Bits"
    
    << "\t\tRam Size = "                            << this -> mainMemorySize               << " Bytes" << "\n\n\t\t\t\t\t\t\t\t\t\tWord Size  = "
    
    << this -> wordSize                             << " Bytes\t\t# of Words = "            << this -> wordQuantity
    
    << " Bytes"                                     << "\t\tTag Size = "                    << this -> addressSize - this -> indexSize - std::floor(log2(blockSize)) << " Bytes\n\n"
    
    << "\t\t\t\t\t\t\t\t\t\tIndex Size = "  << this -> indexSize << "\n\n";
    
}

// -------------------------------------------------------------------------------------------
// Create Header
void SetAssociated :: Header()
{
    // Predefine header
    std::string header[] = { "Address", "Index", "Way", "Tag", "Offset", "Hit_Miss", "Word", "instruction", "Evictions" };
    
    // Include html logic
    html << "<table>";
    html << "<tr>";
    
    // Display Header banner
    console << "\n\t\t------------------------------------------------------------ Set Associative Cache Table ------------------------------------------------------------\n\n";

    spreadsheet << "------------------------------------------------------ Set Associative Cache Table ------------------------------------------------------\n\n";
    
    consoleToFile << "\n\t\t------------------------------------------------------------ Set Associative Cache Table ------------------------------------------------------------\n\n";
    
    // Display header
    for(int i = 0; i < sizeof(header) / sizeof(header[0]); i++)
        CreateHeader(FindHeader(header[i]));
    
}

// -------------------------------------------------------------------------------------------
// Produce column header
void SetAssociated :: CreateHeader(COLUMNS c)
{
    switch(c)
    {
        case ADDRESS :
            
            // Display each address
            if(this -> mainMemorySize == 8)
            {
                
                html << "<th>Address</th>";
                
                console << "\t\tAddress";
                
                spreadsheet << "Address,";
                
                consoleToFile << "\t\tAddress";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                
                html << "<th>Address</th>";

                console << "\t\t\tAddress\t";
                
                spreadsheet << "Address,";
                
                consoleToFile << "\t\t\tAddress\t";
            }
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            
            break;
            
        case INDEX :
            
            // Display each address
            if(this -> mainMemorySize == 8)
            {
                html << "<th>Set</th>";
                
                console << "\t\tSet #";
                
                spreadsheet << "Set #,";
                
                consoleToFile << "\t\tSet #";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Set</th>";
                
                console << "\t\t\tSet #\t";
                
                spreadsheet << "Set #,";
                
                consoleToFile << "\t\t\tSet #";
            }
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case WAY :
            
            // Display each way
            if(this -> mainMemorySize == 8)
            {
                for(int i = 0; i < this -> ways; i++)
                {
                    html << "<th>" << "Data[" << i << "] " << "</th>";
                    
                    console << "\t\tData[" << i << "]  ";
                    
                    spreadsheet << "Data[" << i << "],";
                    
                    consoleToFile << "\t\tData[" << i << "]  ";
                }
            }
            
            else if(this -> mainMemorySize == 16)
            {
                for(int i = 0; i < this -> ways; i++)
                {
                    html << "<th>" << "Data[" << i << "] " << "</th>";
                    
                    console << "\t\t\tData[" << i << "] ";
                    
                    spreadsheet << "Data[" << i << "],";
                    
                    consoleToFile << "\t\t\tData[" << i << "] ";
                }
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            break;
            
        case TAG :
            
            // Display each tag
            if(this -> mainMemorySize == 8)
            {
                html << "<th>Tag</th>";
                
                console << "\t\t Tag";
                
                spreadsheet << "Tag,";
                
                consoleToFile << "\t\t Tag";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Tag</th>";
                
                console << "\t\t\tTag";
                
                spreadsheet << "Tag,";
                
                consoleToFile << "\t\t\tTag";
            }
            
            else
                throw std::invalid_argument("\nError - Invalid memory size\n\n");
            
            
            break;
            
        case OFFSET :
            
            // Display each offset
            if(this -> mainMemorySize == 8)
            {
                html << "<th>Offset</th>";
                
                console << "\t\tOffset";
                
                spreadsheet << "Offset,";
                
                consoleToFile << "\t\tOffset";
            }
            
            else if(this -> mainMemorySize == 16)
            {
                html << "<th>Offset</th>";
                
                console << "\t\t\t\tOffset";
                
                spreadsheet << "Offset,";
                
                consoleToFile << "\t\t\t\tOffset";
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
// Make each string lower case
std::string SetAssociated :: toLower(std::string header)
{
    for(int i = 0; i < header.size(); i++)
        header[i] = std::tolower(header[i]);
    
    return header;
}

// -------------------------------------------------------------------------------------------
// Find header for each column
COLUMNS SetAssociated :: FindHeader (std::string header)
{
    if(toLower(header) == "address")
        return COLUMNS :: ADDRESS;
    
    else if (toLower(header) == "index")
        return COLUMNS :: INDEX;
    
    else if (toLower(header) == "way")
        return COLUMNS :: WAY;
    
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
// Display table
void SetAssociated :: Table()
{
    // Predefine table
    std::string table[] = { "Address", "Index", "Way", "Tag", "Offset", "Hit_Miss", "Word", "instruction", "Evictions" };
    
    // Include html logic
    html << "<tr>";
    
    // Traverse through each category for each individual subscript of Fully_Associative_Vector
    for(this -> global_iterator = 0; this -> global_iterator < Set_Associative_Vector.size(); this -> global_iterator++)
        for(int j = 0; j < sizeof(table) / sizeof(table[0]); j++)
            CreateTable(FindColumn(table[j]));
}

// -------------------------------------------------------------------------------------------
// End html logic
void SetAssociated :: EndHTML()
{
    html << "</table>";
    html << "</div>";
    html << "</div>";
    html << "</div>";
    html << "</body>";
    html << "</html>";
}

// -------------------------------------------------------------------------------------------
// Produce rows and columns in table
void SetAssociated :: CreateTable(COLUMNS columns)
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
            html << "<td>" << Set_Associative_Vector[global_iterator].address << "</td>";

            console << "\t\t" << Set_Associative_Vector[global_iterator].address << " | ";
            
            spreadsheet << "=\""  << Set_Associative_Vector[global_iterator].address << "\",";
            
            consoleToFile << "\t\t" << Set_Associative_Vector[global_iterator].address << " | ";
            
            break;
        }
            
        case INDEX :
        {
            html << "<td>" << Set_Associative_Vector[global_iterator].setIndex << "</td>";

            console << "\t" << this -> Set_Associative_Vector[global_iterator].setIndex << "\t|";
            
            spreadsheet << "=\""   << this -> Set_Associative_Vector[global_iterator].setIndex << "\",";
            
            consoleToFile << "\t" << this -> Set_Associative_Vector[global_iterator].setIndex << "\t|";
        }
            
            break;
            
        case WAY :
            
            // Assign value to Hash table object
            this -> table = FindTable("Index");
            
            // Assign each tag queue and address to its designated hash index
            AssignHashIndex();
            
            // Declare queue to hold data for each way
            wayQueue = indexTable[hashIndex].second;
            
            // Display data stored in each individual way (LRU)
            for(int i = 0; i < this -> ways; i++)
            {
                if(mainMemorySize == 8)
                {
                    if(!indexTable[hashIndex].second.empty())
                    {
                        html << "<td>" << indexTable[hashIndex].second.front() << "</td>";
                        
                        console << "\t" << indexTable[hashIndex].second.front() << "\t|";
                        
                        spreadsheet << "=\""  << indexTable[hashIndex].second.front() << "\",";
                        
                        consoleToFile << "\t" << indexTable[hashIndex].second.front() << "\t|";
                        
                        indexTable[hashIndex].second.pop();
                    }
                    
                    else
                    {
                        html << "<td>" << '-' << "</td>";
                        
                        console << "\t\t" << '-' << "\t\t|";
                        
                        spreadsheet << "=\""  << '-' << "\",";
                        
                        consoleToFile << "\t\t" << '-'  << "\t\t|";
                    }
                }
                
                else if(mainMemorySize == 16)
                {
                    if (!indexTable[hashIndex].second.empty())
                    {
                        html << "<td>" << indexTable[hashIndex].second.front() << "</td>";
                        
                        console << "  " << indexTable[hashIndex].second.front() << " |";
                        
                        spreadsheet << "=\"" << indexTable[hashIndex].second.front() << "\",";
                        
                        consoleToFile <<  "  " << indexTable[hashIndex].second.front() << " |";
                        
                        indexTable[hashIndex].second.pop();
                    }
                    else
                    {
                        html << "<td>" << '-' << "</td>";
                        
                        console << std::setw(10) << '-' << std::setw(10) << "|";
                        
                        spreadsheet << "=\"" << '-' << "\",";
                        
                        consoleToFile << std::setw(10) << '-' << std::setw(10) << "|";
                    }
                }
            }
            
            indexTable[hashIndex].second = wayQueue;
            
            break;
            
        case TAG :
        {
            html << "<td>" << this -> Set_Associative_Vector[global_iterator].tag << "</td>";
        
            console << "\t" << this -> Set_Associative_Vector[global_iterator].tag << "\t|";
            
            spreadsheet << "=\""   << this -> Set_Associative_Vector[global_iterator].tag << "\",";
            
            consoleToFile << "\t" << this -> Set_Associative_Vector[global_iterator].tag << "\t|";
        }
            
            break;
            
        case OFFSET :
        {
            html << "<td>" << this -> Set_Associative_Vector[global_iterator].offset << "</td>";
            
            console << "\t  " << this -> Set_Associative_Vector[global_iterator].offset << " \t| ";
            
            spreadsheet << "=\""  << this -> Set_Associative_Vector[global_iterator].offset << "\",";
            
            consoleToFile << "\t  " << this -> Set_Associative_Vector[global_iterator].offset << " \t| ";
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
                    html << "<td>" << Set_Associative_Vector[global_iterator].instructionMap[wordVector[i]] << "</td>";
                    
                    console << Set_Associative_Vector[global_iterator].instructionMap[wordVector[i]] << " | ";
                    
                    spreadsheet << "=\"" << Set_Associative_Vector[global_iterator].instructionMap[wordVector[i]] << "\",";
                    
                    consoleToFile << Set_Associative_Vector[global_iterator].instructionMap[wordVector[i]] << " | ";
                }
            }
        }
            
            break;
            
        case INSTRUCTION_RETREIVED :
        {
            html << "<td>" << this -> Set_Associative_Vector[global_iterator].instruction << "</td>";
            
            console << "      " << this -> Set_Associative_Vector[global_iterator].instruction << "\t\t|";
            
            spreadsheet << "=\""  << this -> Set_Associative_Vector[global_iterator].instruction << "\",";
            
            consoleToFile << "      " << this -> Set_Associative_Vector[global_iterator].instruction << "\t\t|";
        }
            
            break;
            
        case EVICTIONS :
            
            if(!this -> Set_Associative_Vector[global_iterator].addressEvicted.empty())
            {
                html << "<td>" << this -> Set_Associative_Vector[global_iterator].addressEvicted << "</td>";
                
                console  << "\t\t\t" << this -> Set_Associative_Vector[global_iterator].addressEvicted << '\n';
                
                spreadsheet << this -> Set_Associative_Vector[global_iterator].addressEvicted << '\n';
                
                consoleToFile  << "\t\t\t" << this -> Set_Associative_Vector[global_iterator].addressEvicted << '\n';
                
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
// Find column for each row
COLUMNS SetAssociated :: FindColumn (std::string column)
{
    if(toLower(column) == "address")
        return COLUMNS :: ADDRESS;
    
    else if (toLower(column) == "index")
        return COLUMNS :: INDEX;
    
    else if (toLower(column) == "way")
        return COLUMNS :: WAY;
    
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
HASH_TABLE SetAssociated :: FindTable (std::string table)
{
    if(toLower(table) == "address" || toLower(table) == "address table")
        return HASH_TABLE :: ADDRESS_TABLE;
    
    else if(toLower(table) == "index" || toLower(table) == "index table")
        return HASH_TABLE :: INDEX_TABLE;
    
    return HASH_TABLE :: HASH_TABLE_ERROR;
}

void SetAssociated :: Print()
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

// -------------------------------------------------------------------------------------------
// Contains each placement policy algoirthm
void SetAssociated :: PlacementPolicy(enum HASH_TABLE table)
{
    switch(placementPolicy)
    {
        case LRU:
        {
            Least_Recently_Used();
            
            break;
        }
            
        case LFU:
        {
            Least_Frequently_Used();

            break;
        }
            
        case FIFO:
        {
            First_In_First_Out();
                
            break;
                    
        }
            
        case ALGORITHMIC_ERROR:
            {
                throw std::invalid_argument("\n\nError - Invalid algorithm\n\nPlease re-enter selection.\n\n");
                break;
            }
            
            
        }
    }

// -------------------------------------------------------------------------------------------
// Least Recently Used Algorithm
void SetAssociated :: Least_Recently_Used()
{
    // Retrieve hashed index and assign it to addressTable
    this -> hashIndex = GetHashIndex(Set_Associative_Vector[global_iterator].indexHashCode);
    
    if(indexTable[hashIndex].first.empty() && indexTable[hashIndex].second.empty())
    {
        // Declare queue using to store binary addresses
        std::queue<binary> binaryQueue;
        
        // Insert address into binaryQueue
        binaryQueue.push(Set_Associative_Vector[global_iterator].address);
        
        // Insert tag and queue pair to tagTable
        indexTable[hashIndex] = { Set_Associative_Vector[global_iterator].setIndex, binaryQueue };
    }
    
    else if(indexTable[hashIndex].first == Set_Associative_Vector[global_iterator].setIndex)
    {
        // Declare temporary queue used for traversing
        std::queue <binary> binaryQueue(indexTable[hashIndex].second);
        
        // Declare temporary queue used for storage
        std::queue <binary> storageQueue;
        
        // Declare string that is inserted to the back of the binary queue
        binary lastString = "";
        
        // Determine if address was found in queue
        boolean addressFound = false;
        
        
        // Traverse through queue
        while(!binaryQueue.empty())
        {
            if(binaryQueue.front() == Set_Associative_Vector[global_iterator].address)
            {
                lastString = binaryQueue.front();
                
                binaryQueue.pop();
                
                addressFound = true;
            }
            
            else
            {
                storageQueue.push(binaryQueue.front());
                
                binaryQueue.pop();
            }
        }
        
        if(!addressFound)
        {
            
            if(storageQueue.size() >= this -> ways)
            {
                // Collect evicted address
                Set_Associative_Vector[global_iterator].addressEvicted = storageQueue.front();
                
                // remove front address from storageQueue
                storageQueue.pop();
            }
            
            else
                Set_Associative_Vector[global_iterator].addressEvicted = "";
            
            storageQueue.push(Set_Associative_Vector[global_iterator].address);
            
            indexTable[hashIndex].second = storageQueue;
        }
        
        else
        {
            storageQueue.push(lastString);
            
            indexTable[hashIndex].second = storageQueue;
        }
    }
}

// -------------------------------------------------------------------------------------------
// Least Frequently Used Algorithm
void SetAssociated :: Least_Frequently_Used()
{
    // Retrieve hashed index and assign it to tagTable
    this->hashIndex = GetHashIndex(Set_Associative_Vector[global_iterator].indexHashCode);

    // If cache is empty
    if (indexTable[hashIndex].first.empty() && indexTable[hashIndex].second.empty())
    {
        // Declare queue used to store binary addresses
        std::queue<binary> binaryQueue;

        // Insert address into binaryQueue
        binaryQueue.push(Set_Associative_Vector[global_iterator].address);

        // Insert tag and queue pair into tagTable
        indexTable[hashIndex] = {Set_Associative_Vector[global_iterator].setIndex, binaryQueue};

        // Track address frequency in addressDetector
        addressDetector[Set_Associative_Vector[global_iterator].setIndex] = { { Set_Associative_Vector[global_iterator].address, 1 } };
    }
    else
    {
        if (indexTable[hashIndex].first == Set_Associative_Vector[global_iterator].setIndex)
        {
            // Copy current queue of addresses
            std::queue<binary> binaryQueue = indexTable[hashIndex].second;

            // Declare temporary queue used for storage
            std::queue<binary> copyQueue;

            // Declare vector which stores value of addressDetector
            std::vector<std::pair<binary, int>> addressDetectorVec = addressDetector[indexTable[hashIndex].first];

            // Determine whether address is found
            bool addressFound = false;

            // If cache is not full
            if (binaryQueue.size() < this->ways)
            {
                while (!binaryQueue.empty())
                {
                    // Current address in binaryQueue
                    binary currentAddress = binaryQueue.front();

                    // Pop binary queue
                    binaryQueue.pop();

                    // Add current address to temporary queue
                    copyQueue.push(currentAddress);

                    // Update frequency if found
                    for (size_t i = 0; i < addressDetectorVec.size(); ++i)
                    {
                        if (currentAddress == addressDetectorVec[i].first &&
                            currentAddress == Set_Associative_Vector[global_iterator].address)
                        {
                            addressDetectorVec[i].second += 1;
                            addressFound = true;
                        }
                    }
                }

                // If address is not found, add new address and update frequency
                if (!addressFound)
                {
                    copyQueue.push(Set_Associative_Vector[global_iterator].address);
                    addressDetectorVec.push_back({Set_Associative_Vector[global_iterator].address, 1});
                }

                // Update tagTable
                indexTable[hashIndex].second = copyQueue;

                // Updated addressDetector
                addressDetector[indexTable[hashIndex].first] = addressDetectorVec;
            }
            else // Cache is full
            {
                // Search for existing address
                while (!binaryQueue.empty())
                {
                    // Declare variable which copies address in front of queue
                    binary currentAddress = binaryQueue.front();

                    // Pop binary queue
                    binaryQueue.pop();

                    // If address is found then increment the frequency
                    if (currentAddress == Set_Associative_Vector[global_iterator].address)
                    {
                        for (size_t i = 0; i < addressDetectorVec.size(); ++i)
                        {
                            if (addressDetectorVec[i].first == currentAddress)
                            {
                                addressDetectorVec[i].second += 1;
                                addressFound = true;
                                break;
                            }
                        }
                    }

                    // Add current address to temporary copyQueue
                    copyQueue.push(currentAddress);
                }

                // If the address was not found, replace least frequently used address
                if (!addressFound)
                {
                    // Track least frequently used address
                    std::pair<binary, int> leastFrequentAddress;
                    
                    leastFrequentAddress.second = INT_MAX;
                    
                    std::size_t index = 0;

                    // Find least frequently used address
                    for (size_t i = 0; i < addressDetectorVec.size(); ++i)
                    {
                        if (addressDetectorVec[i].second < leastFrequentAddress.second)
                        {
                            leastFrequentAddress = addressDetectorVec[i];
                            
                            index = i;
                        }
                    }
                    
                
                    // Collect evicted address
                    Set_Associative_Vector[global_iterator].addressEvicted = leastFrequentAddress.first;

                    // Declare temporary queue to store all addresses excluding least frequently used address
                    std::queue<binary> temporaryQueue = indexTable[hashIndex].second;

                    // Re-create queue which excludes least frequently used address and inserts new address
                    while (!temporaryQueue.empty())
                    {
                        binary temporaryAddress = temporaryQueue.front();
                        
                        temporaryQueue.pop();
                        
                        if (temporaryAddress != leastFrequentAddress.first)
                            copyQueue.push(temporaryAddress);
                    }

                    // Insert new address into the queue
                    copyQueue.push(Set_Associative_Vector[global_iterator].address);

                    // Update queue in tagTable
                    indexTable[hashIndex].second = copyQueue;

                    // Replace LFU entry in addressDetector
                    addressDetectorVec[index] = {Set_Associative_Vector[global_iterator].address, 1};
                    
                    // Update value of addressDetector[tagTable[hashIndex].first]
                    addressDetector[indexTable[hashIndex].first] = addressDetectorVec;
                }
                else
                {
                    // Update queue of tagTable
                    indexTable[hashIndex].second = copyQueue;

                    // Update frequency
                    addressDetector[indexTable[hashIndex].first] = addressDetectorVec;
                }
            }
        }
    }
}

// -------------------------------------------------------------------------------------------

// First in First out Algorithm
void SetAssociated :: First_In_First_Out()
{
        // Retrieve hashed index and assign it to addressTable
        this -> hashIndex = GetHashIndex(Set_Associative_Vector[global_iterator].indexHashCode);
        
        if(indexTable[hashIndex].first.empty() && indexTable[hashIndex].second.empty())
        {
            // Declare queue using to store binary addresses
            std::queue<binary> binaryQueue;
            
            // Insert address into binaryQueue
            binaryQueue.push(Set_Associative_Vector[global_iterator].address);
            
            // Insert tag and queue pair to tagTable
            indexTable[hashIndex] = { Set_Associative_Vector[global_iterator].setIndex, binaryQueue };
        }
        
        else if(indexTable[hashIndex].first == Set_Associative_Vector[global_iterator].setIndex)
        {
            // Declare temporary queue used for traversing
            std::queue <binary> binaryQueue(indexTable[hashIndex].second);
            
            // Declare temporary queue used for storage
            std::queue <binary> storageQueue;
            
            // Determine if address was found in queue
            boolean addressFound = false;
            
            // Traverse through queue
            while(!binaryQueue.empty())
            {
                if(binaryQueue.front() == Set_Associative_Vector[global_iterator].address)
                {
                    binaryQueue.pop();
                    
                    addressFound = true;
                }
                
                else
                {
                    storageQueue.push(binaryQueue.front());
                    
                    binaryQueue.pop();
                }
            }
            
            if(!addressFound)
            {
                
                if(storageQueue.size() >= this -> ways)
                {
                    // Collect evicted address
                    Set_Associative_Vector[global_iterator].addressEvicted = storageQueue.front();
                    
                    // remove front address from storageQueue
                    storageQueue.pop();
                }
                
                else
                    Set_Associative_Vector[global_iterator].addressEvicted = "";
                
                storageQueue.push(Set_Associative_Vector[global_iterator].address);
                
                indexTable[hashIndex].second = storageQueue;
            }
        }
}

