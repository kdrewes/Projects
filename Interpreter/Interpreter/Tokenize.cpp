#include <fstream>
#include <cstring>
#include <exception>
#include "Tokenize.h"
#include "removeComments.h"

Tokenize :: Tokenize(std::vector<std::string> TestFiles)
{
    this -> TestFiles = TestFiles;
    
    this -> integer_index = 0;
    
    this -> string_index = 0;
    
    this -> char_index = 0;
    
    this -> integer_arg_index = 0;
    
    this -> string_arg_index = 0;
    
    this -> char_arg_index = 0;
    
    this -> procedure_index = 0;
    
    this -> count_characters = 0;
    
    this -> procedureTester = false;
    
    this -> procedureCounter = 0;
    
    this -> syntax = "";
}

// ------------------------------------------------------------------
// Initiates process of collecting content of each file
void Tokenize :: Execute()
{
    // Loop operation
    for(std::vector<std::string>::size_type i = 0; i < 1; i++)
    {
        
        /* --------- Input validation --------- */
        try
        {
            // Read each file
            this -> read.open(TestFiles[1],std::ios::in);
            
            // Collect tokens from current file being read
            this -> TokenVector.push_back(ReadFile());
        }
        
        // Display error message
        catch(std::invalid_argument e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    
}
// ------------------------------------------------------------------
// Clear memory from ADT'S
void Tokenize :: Clear()
{
    this -> TestFiles.clear();
    
    this -> integerCollector.clear();
    
    this -> stringCollector.clear();
    
    this -> charCollector.clear();
    
    this -> integerArgCollector.clear();
    
    this -> stringArgCollector.clear();
    
    this -> charArgCollector.clear();
    
    this -> procedureCollector.clear();
    
    this -> TokenVector.clear();
}

// ------------------------------------------------------------------
// Reads contents of each individual file and extracts tokens from content
std::vector<std::pair<tokenType,token>> Tokenize :: ReadFile()
{
    // Used to collect each individual token
    std::vector<std::pair<tokenType,token>>Tokens;
    
    if(!this->read)
        throw std::invalid_argument("Unable to open file\n");
    else
    {
        for(char character = '\0'; !this->read.eof();  this->read >> std::noskipws >> character )
        {
            /*
            // Test output
            if(character != '\n')
                std::cout << character;
            else
                std::cout << std::endl;
            */
            
            if(character != ' ' && character != '\n' && character != '\0')
            {
                this->syntax += Configure_Token(character);
                
                if(isToken(isTokenHelper()))
                {
                    Tokens.push_back(Token_Handler(Read_Token()));
                    
                    this->syntax = "";
                }
            }
            
            else if(isPrintF(strdup("scan string")))
                this -> syntax += character;
            
            else
                this->syntax = "";
        }
    }

    read.close();
    
    return Tokens;
}
// ------------------------------------------------------------------
// Verifies that each character is legally allowed to use
char Tokenize :: Configure_Token(char character)
{
    return (Configure_Token_Helper(character));
}
// ------------------------------------------------------------------
// Handles input validation with Read_Character function
char Tokenize :: Configure_Token_Helper(char character)
{
    // Input validation for integer handler
    //Configure_Integer(character);
    
    // Input validation for isValue handler
    //Configure_Value(character);
    
    // Input validation for isString handler
    //Configure_PrintF(character);
    
    // Input validation for procedure handler
    Configure_Procedure(character);
    
    return character;
}
// ------------------------------------------------------------------
// Checks if isInteger boolean variable is currently set as 'true'
/*
void Tokenize :: Configure_Integer(char character)
{
    if(!isProcedure())
    {
        if(isInteger(strdup("datatype")))
        {
            if (this->syntax.size() == 0 && !isalpha(character))
                throw std::invalid_argument("\n\nError - incorrect character " + std::string(1,character) + " used on integer variable\n\n");
            
            if((!isalpha(character) && !isnumber(character)) && this->syntax.size() > 0 && !isInteger(strdup("value")))
                throw std::invalid_argument("\n\nError - incorrect character " + std::string(1,character) + " used on integer variable\n\n");
        }
        else if(isInteger(strdup("value")))
            isInteger("reset");
    }
    
}
// ------------------------------------------------------------------
// Checks if isValue boolean variable is currently set as 'true'
void Tokenize :: Configure_Value(char character)
{
    
    if(!isProcedure())
    {
        if(isValue(strdup("=")))
        {
            if(character == '=')
            {
                if(read.peek() == ' ' || isnumber(this->read.peek()))
                    isValue("integer");
            }
            
            else if (character != '=' &&
                     character != '+' &&
                     character != '-' )
                std::invalid_argument("\n\nError - Invalid character " + std::string(1,character) + " detected\n\n");
            
            
            else if((syntax[0] == '+' || syntax[0] == '-') &&
                    (character != '=' && syntax.size() > 0) &&
                    !isnumber(character))
                std::invalid_argument("\n\nError - Invalid character " + std::string(1,character) + " detected\n\n");
            
            else if(isnumber(this->read.peek()))
                isValue("integer");
            
        }
        else if(isValue(strdup("integer")))
        {
            
            if(!isnumber(character) &&
               (character != '=' && character != '-' && character != '+') &&
               this -> syntax.size() == 0)
                
                throw std::invalid_argument("\n\nError - invalid character " + std::string(1,character) + " detected.  Must be integer.\n\n");
            
            else if(character != '-' && this -> syntax.size() != 0)
            {
                if(isnumber(character))
                {
                    if(this->read.peek() == ' ' || this->read.peek() == ';')
                        isValue(";");
                    else
                    {
                        if(!isnumber(this->read.peek()))
                            std::invalid_argument("\n\nError - Invalid character " + std::string(1,character) + " detected\n\n");
                        
                    }
                }
            }
        }
        else if(isValue(strdup(";")))
        {
            if(character == ';')
                isValue("reset");
            else
                throw(std::invalid_argument("\n\nError - invalid character detected\n\ncharacter must be ';' not " + character + '+'));
        }
    }
    
}

// ------------------------------------------------------------------
// Check if isPrintf boolean variable is currently set as 'true'
void Tokenize :: Configure_PrintF(char character)
{
    if(!isProcedure())
    {
        if(isPrintF(strdup("printf")))
        {
            if(character == '(')
                isPrintF("(");
            
            else
                throw(std::invalid_argument(&"\n\nError - invalid character detected\n\ncharacter must be '(' not " [ character]));
        }
        
        else if(isPrintF(strdup("(")))
        {
            if(character == '"')
                isPrintF("beginning quotation");
            
            else
                throw std::invalid_argument("\n\nError - Invalid character detected, character must contain quotation mark\n");
        }
        
        else if(isPrintF(strdup("beginning quotation")))
            isPrintF("scan string");
        
        else if(isPrintF(strdup("scan string")))
        {
            if(this->read.peek() == '"' && character != '\\')
                isPrintF("end scanning");
            
            if((count_characters += 1) > 30)
            {
                this -> count_characters = 0;
                throw(std::invalid_argument("\n\nError - printf statement contains too many characters\n\nNo quotation mark detected.\n"));
            }
        }
        
        else if(isPrintF(strdup("end scanning")))
        {
            if(character == '"')
                isPrintF("end quotation");
        }
        
        else if(isPrintF(strdup("end quotation")))
        {
            if(character == ')')
                isPrintF(")");
            
            else if(character == ',')
                isPrintF(",");
            
            else
                throw std::invalid_argument("\n\nError - Invalid character " + std::string(1, character) + " detected.\n");
        }
        
        else if(isPrintF(strdup(",")))
        {
            // First character of variable is not an alphabetic character
            if(this -> syntax.size() == 0)
                if(!isalpha(character))
                    throw std::invalid_argument("\n\nError - Invalid character " + std::string(1, this->read.peek()) + " used in variable.\n");
            
            if(this->read.peek() == ' ' || this->read.peek() == ')')
            {
                // Declare temporary syntax variable used as backup storage
                token tempSyntax = this -> syntax;
                
                // Add character to syntax to make it temporarily complete
                this -> syntax += character;
                
                // Determine if variable (syntax) exists.  If not, throw an exception
                if(!findInteger())
                    throw(std::invalid_argument("\n\nError - " + this -> syntax + " does not exist\n" ));
                
                // Re-assign this -> syntax its original value
                this -> syntax = tempSyntax;
                
                // Activate is_right_paranthesis variable
                isPrintF(")");
            }
        }
        
        else if(isPrintF(strdup(")")))
        {
            if(character == ';')
                isPrintF(";");
            
            else if (this->read.peek() == ';')
                isPrintF(";");
            
            else if(this->read.peek() != ';' &&  this->read.peek() != ' ')
                throw std::invalid_argument("\n\nError - Invalid character " + std::string(1, this->read.peek()) + " detected ahead.  Character must be ';'\n");
            
            else if(character != ';')
            {
                throw std::invalid_argument("\n\nError - Invalid character " + std::string(1, this->read.peek()) + " detected.  Character must be ';'\n");
            }
        }
        
        else if(isPrintF(strdup(";")))
            isPrintF("reset");
    }
}
 */
//------------------------------------------------------------------
// Check if isProecedure boolean varaible is currently set as 'true'
void Tokenize :: Configure_Procedure(char character)
{
    // Determines procedure type (ex - main or regular procedure)
    if(isProcedure(strdup("is procedure")))
    {
        if(this->syntax.size() == 0 && !isalpha(character))
            throw std::invalid_argument("\n\nError - incorrect character " + std::string(1,character) + " used on procedure name\n\n");
        
        else if((!isalpha(character) &&
                 !isnumber(character)) &&
                 this->syntax.size() > 0)
            throw std::invalid_argument("\n\nError - incorrect character " + std::string(1,character) + " used on procedure name\n\n");
        
        else if (this -> read.peek() == '(')
        {
            token tempToken = this -> syntax + character;
            
            if(tempToken == "main")
            {
                
                isProcedure("is main");
                
                isProcedure("left parenthesis detected");
            }
            
            else
            {
                isProcedure("regular function");
                
                isProcedure("left parenthesis detected");
                
                procedureCollector.push_back
                (this -> syntax + character);
            }
        }
        
        else if (this -> read.peek() == ' ')
        {
            token tempToken = this -> syntax + character;
            
            if(tempToken == "main")
            {
                isProcedure("is main");
                
                isProcedure("searching for left parenthesis");
            }
            
            else
            {
                isProcedure("regular function");
                
                isProcedure("searching for left parenthesis");
                
                procedureCollector.push_back
                (this -> syntax + character);
            }
        }
    }
    
    else if(isProcedure(strdup("is regular function")))
    {
        if (isProcedure(strdup("left parenthesis detected")))
        {
            if(character == '(')
                isProcedure("(");
        }
        
        else if(isProcedure(strdup("searching for left parenthesis")))
        {
            if(character == '(')
                isProcedure("(");
        
            else
                throw std::invalid_argument("\n\nError - character must be ( not " + std::string(1,character) + "\n\n");
        }
        
        else if(isProcedure(strdup("(")))
        {
            // --------------- Input Validation ---------------
            
            
            
            // -------------------- Logic ---------------------
            
            if((this -> syntax + character == "int" ||
               this -> syntax + character == "char" ||
               this -> syntax + character == "string") &&
               read.peek() == ' ')
            {
                if(this -> syntax + character == "int")
                    isProcedure("datatype int");
                
                else if(this -> syntax + character == "char")
                    isProcedure("datatype char");
                
                else if(this -> syntax + character == "string")
                    isProcedure("datatype string");
            }
            
            else if(character == ')' && this -> syntax.size() == 0)
                isProcedure(")");
            
            else if((this -> syntax.size() > 0) && (read.peek() == ')'))
            {
                std::string tempString = this -> syntax + character;
                
                throw std::invalid_argument("\n\nError - " + tempString + " is invalid syntax\n\n");
            }
        }
        
        else if(isProcedure(strdup("is detecting variable")))
        {
            // Perform input validation on first character of this -> syntax
            if(!isalpha(character) && this -> syntax.size() == 0)
                throw std::invalid_argument("\n\nError - first character of variable must be an alphabetic character\n");
            
            // Perform input validation on all character after first character of this -> syntax
            else if(ispunct(character) && this -> syntax.size() > 0)
                throw std::invalid_argument("\n\nError - character must not be puncuation\n");
                
            if(read.peek() == ')')
            {
                std::string variable = "variable " + this->syntax + character;
                
                isProcedure(variable);
                
                assignVector();
                
                isProcedure("right parenthesis detected");
                
            }
           
            else if(read.peek() == ',')
                isProcedure(",");
            
            else if(read.peek() == ' ')
                isProcedure("searching for right parenthesis");

        }
        
        else if(isProcedure(strdup("right parenthesis detected")))
                isProcedure(")");
        
        else if(isProcedure(strdup("searching for right parenthesis")))
        {
            
            if(read.peek() == ')')
            {
                std::string variable = "variable "
                + this->syntax + character;

                isProcedure(variable);
                
                assignVector();
                
                isProcedure("right parenthesis detected");
            }
            
            else if(read.peek() == ',')
                isProcedure(",");
            
            else
                throw std::invalid_argument("\n\nError - " + std::string(0,character) + " is an valid character, ) must be used\n");
                
        }
        
        else if(isProcedure(strdup(",")))
        {
            if(character == ',')
                isProcedure("comma detected");
            
            else
                throw std::invalid_argument("\n\nError - character must be comma, " + std::string(1,character) + " is not a valid character.\n");
        }
        
        else if(isProcedure(strdup(")")))
        {
            if(character == '{')
                isProcedure("reset");
        
            else
                throw std::invalid_argument("\n\nError - " + std::string(0,character) + " is an valid character, { must be used\n");
        }
    }
    
    else if(isProcedure(strdup("is main")))
    {
        if (isProcedure(strdup("left parenthesis detected")))
        {
            if(character == '(')
                isProcedure("(");
            
            else
                throw std::invalid_argument("\n\nError - character must be ( not " + std::string(1,character) + "\n\n");
        }
        
        else if(isProcedure(strdup("searching for left parenthesis")))
        {
            if(character == '(')
                isProcedure("(");

            else
                throw std::invalid_argument("\n\nError - character must be ( not " + std::string(1,character) + "\n\n");
        }
        else if(isProcedure(strdup("(")))
        {
            // --------------- Input Validation ---------------
            
            if(character != 'v' && this -> syntax.size() == 0)
                throw std::invalid_argument("\n\nError - " + std::string(1,character) + " is an invalid character\n\nparameter must be void\n");
            
            else if(!isalpha(character) && this -> syntax.size() != 0)
                throw std::invalid_argument("\n\nError - " + std::string(1,character) + " is an invalid character\n\nparameter must be void\n");
            
            else if(this -> syntax.size() > 4)
                throw std::invalid_argument("\n\nError - " + std::string(1,character) + " is an invalid character\n\nparameter must be void\n");
            
            // ------------------- logic -------------------

            if(this -> syntax + character == "void")
                isProcedure("void");
            
            else if(this -> syntax + character != "void" && this -> syntax.size() == 3 )
                throw std::invalid_argument("\n\nError - " + std::string(this -> syntax + character) + " is an invalid parameter\n\nparameter must be void\n");
        }
        
        else if(isProcedure(strdup("is void")))
        {
            if(character == ')')
                isProcedure(")");
        
            else
                throw std::invalid_argument("\n\nError - " + std::string(1,character) + " is an invalid character\n");
        }
        
        else if(isProcedure(strdup(")")))
        {
            if(character == '{')
                isProcedure("reset");

            else
                throw std::invalid_argument("\n\nError - " + std::string(1,character) + " is an invalid character\n\ncharacter must be {\n");
        }
    }
}
//------------------------------------------------------------------
// Assigns vector from PROCEDURE_HANDLER to private vectors located in Tokenize class
void Tokenize :: assignVector()
{
    // Declare variables for organization purposes
    std::string datatype = isProcedure.storeDataType;
    
    switch(dataType(datatype))
    {
        case INTEGER:
            
            if(!isProcedure.integerCollector.empty())
            {
                std::vector <std::string> intVector = isProcedure.integerCollector;
                
                integerArgCollector.assign(intVector.begin(),intVector.end());
            }
            
            else
                throw std::invalid_argument("\n\nError - Attempting to access data from empty vector - integerCollector\n");
                    
            break;
            
        case STRING:
            
            if(!isProcedure.stringCollector.empty())
            {
                std::vector <std::string> stringVector = isProcedure.stringCollector;
                
                stringArgCollector.assign(stringVector.begin(),stringVector.end());
            }
            
            else
                throw std::invalid_argument("\n\nError - Attempting to access data from empty vector - stringCollector\n");
            
            break;
            
        case CHAR:
            
            if(!isProcedure.charCollector.empty())
            {
                std::vector <std::string> charVector = isProcedure.charCollector;
                
                charArgCollector.assign(charVector.begin(), charVector.end());
            }
            
            else
                throw std::invalid_argument("\n\nError - Attempting to access data from empty vector - charCollector\n");
            
            break;

        case ERROR:
            throw std::invalid_argument("\n\nError - " + std::string(isProcedure.storeDataType) + " is an invalid data type " + "\n\n");
    }
}

// ------------------------------------------------------------------
// Determines if file text is an identifier
bool Tokenize :: isIdentifier()
{
    if(syntax == "void")
        return true;
    
    else if(this->syntax == "printf")
        return true;
    
    else if(syntax == "if")
    {
        //this -> isIf = {true,false};
        return true;
    }
    else if(syntax == "else")
        return true;
    
    else if(syntax == "else if")
        return true;
    
    else if(syntax == "for")
        return true;
    
    else if(syntax == "while")
        return true;
    
    else if(syntax == "do")
        return true;
    
    else if(syntax == "function")
        return true;
    
    else if(syntax == "procedure")
        return true;
    
    else if(syntax == "main")
        return true;
    
    else if(syntax == "void")
        return true;
    
    else if(syntax == "int")
    {
        if(this->read.peek() == ' ')
            return true;
        else
            std::invalid_argument("\n\nError - invalid syntax detected.\n");
    }
    
    else if(isInteger(strdup("datatype")))
    {
        if(this->read.peek() == ';' && this->syntax.size() != 0)
            return true;
        
        else if(this->read.peek() == ' ' && this->syntax.size() != 0)
            return true;
        
        else if(this->syntax == ";")
            return true;
        
    }
    
    else if(findInteger())
        return true;
    
    else if(findString())
        return true;
    
    else if(findChar())
        return true;
    
    else if(findIntegerArg())
        return true;
    
    else if(findStringArg())
        return true;
    
    else if(findCharArg())
        return true;
    
    else if(findProcedure())
        return true;
    
    else if(findProcedure())
        return true;
    
    return false;
}
// ------------------------------------------------------------------
// Determines if file text is an identifier, used specifically for bool isToken
bool Tokenize :: tokenIdentifier()
{
    if(this->syntax == "void")
        return true;
    
    else if(this->syntax == "printf")
        return true;
    
    else if(this->syntax == "if")
    {
        //this -> isIf = {true,false};
        return true;
    }
    
    else if(syntax == "else")
        return true;
    
    else if(syntax == "else if")
        return true;
    
    else if(syntax == "for")
        return true;
    
    else if(syntax == "while")
        return true;
    
    else if(syntax == "do")
        return true;
    
    else if(syntax == "function")
        return true;
    
    else if(syntax == "procedure")
        return true;
    
    else if(syntax == "main")
        return true;
    
    else if(syntax == "void")
        return true;
    
    else if(syntax == "int")
    {
        if(this->read.peek() == ' ')
            return true;
        else
            std::invalid_argument("\n\nError - Invalid syntax " + this -> syntax + " detected\n\n");
        
    }
    
    else if(isInteger(strdup("datatype")))
    {
        if(this->read.peek() == ';' && this->syntax.size() != 0)
            return true;
        
        else if(this->read.peek() == ' ' && this->syntax.size() != 0)
            return true;
        
        else if(this->syntax == ";")
            return true;
        
    }
    
    else if(findInteger())
        return true;
    
    else if(findString())
        return true;
    
    else if(findChar())
        return true;
    
    else if(findIntegerArg())
        return true;
    
    else if(findStringArg())
        return true;
    
    else if(findCharArg())
        return true;
    
    else if(findProcedure())
        return true;
    
    return false;
}
// ------------------------------------------------------------------
// Determines if BNF token was detected
bool Tokenize :: isToken(TOKEN_TYPE token)
{
    if(token == TOKEN_TYPE :: NON_BNF ||
       token == TOKEN_TYPE :: BNF_IN_PROCESS)
        return false; return true;
}
// ------------------------------------------------------------------
// Determines if an integer variable is present within an operation/equation
bool Tokenize :: findInteger()
{
        if(!integerCollector.empty())
            for(std::vector <std::string> :: size_type i = 0; i < integerCollector.size(); i++)
            {
                if(this->syntax == integerCollector[i])
                {
                    this -> integer_index = i;
                    return true;
                }
            }
    
    return false;
}
//------------------------------------------------------------------
// Determines if a string variable is present within an operation/equation
bool Tokenize :: findString()
{
    if(!stringCollector.empty())
        for(std::vector <std::string> :: size_type i = 0; i < stringCollector.size(); i++)
        {
            if(this->syntax == stringCollector[i])
            {
                this -> string_index = i;
                
                return true;
            }
        }

    return false;
}
//------------------------------------------------------------------
// Determines if a char variable is present within an operation/equation
bool Tokenize :: findChar()
{
    if(!charCollector.empty())
        for(std::vector <std::string> :: size_type i = 0; i < charCollector.size(); i++)
        {
            if(this->syntax == charCollector[i])
            {
                this -> char_index = i;
                
                return true;
            }
        }

    return false;
}
//------------------------------------------------------------------
// Determines if an integer argument variable is present within a procedure
bool Tokenize :: findIntegerArg()
{
        if(!integerArgCollector.empty())
            for(std::vector <std::string> :: size_type i = 0; i < integerArgCollector.size(); i++)
            {
                if(this->syntax == integerArgCollector[i])
                {
                    this -> integer_arg_index = i;
                    
                    return true;
                }
            }
    
    return false;
}
//------------------------------------------------------------------
// Determines if an string argument variable is present within a procedure
    bool Tokenize :: findStringArg()
    {
        if(!stringArgCollector.empty())
            for(std::vector <std::string> :: size_type i = 0; i < stringArgCollector.size(); i++)
            {
                if(this->syntax == stringArgCollector[i])
                {
                    this -> string_arg_index = i;
                    
                    return true;
                }
            }
        
        return false;
    }
//------------------------------------------------------------------
// Determines if an char argument variable is present within a procedure
    bool Tokenize :: findCharArg()
    {
        if(!charArgCollector.empty())
            for(std::vector <std::string> :: size_type i = 0; i < charArgCollector.size(); i++)
            {
                if(this->syntax == charArgCollector[i])
                {
                    this -> char_arg_index = i;
                    
                    return true;
                }
            }
                
        return false;
    }
    //------------------------------------------------------------------
// Determines if a procedure is present within an operation/equation
bool Tokenize :: findProcedure()
{
   
        if(!procedureCollector.empty())
        {
            for(std::vector <std::string> :: size_type i = 0; i < procedureCollector.size(); i++)
            {
                if(this->syntax == procedureCollector[i])
                {
                    this -> procedure_index = i;
                    
                    return true;
                }
            }
        }
    
    return false;
}
// ------------------------------------------------------------------
// Determines which token is currently being read
TOKEN_TYPE Tokenize :: Read_Token()
{
    
    if(isIdentifier() &&
       !isValue() &&
       !isPrintF(strdup("end scanning")))
    {
        if(this->syntax == "int" && !isProcedure())
        {
            /*****************************************/
            
            // UNCOMMENT WHEN DONE
           // isInteger("datatype");
            
            /*****************************************/
            return TOKEN_TYPE :: IDENTIFIER;
        }
    
        else if(isInteger() && !isProcedure())
        {
            if(isInteger(strdup("datatype")))
            {
                if((this->read.peek() == ';') &&
                   this->syntax.size() != 0)
                {
                    isInteger("value");
                    integerCollector.push_back(this -> syntax);
                    return TOKEN_TYPE :: IDENTIFIER;
                }
                else if((this -> read.peek() == '=' ||
                         this -> read.peek() == ' ') &&
                        this->syntax.size() != 0)
                {
                    isInteger("=");
                    return TOKEN_TYPE :: IDENTIFIER;
                }
                else if(this->read.peek() == ',' && this->syntax.size() != 0)
                    return TOKEN_TYPE :: IDENTIFIER;
                else if(this->syntax == ";")
                {
                    isInteger("reset");
                    return TOKEN_TYPE :: SEMICOLON;
                }
                else if(syntax == ",")
                    return TOKEN_TYPE :: COMMA;
                else
                    throw std::invalid_argument("\n\nError - Invalid character detected.");
            }
        }
        
        else if(this -> syntax == "printf" && !isPrintF())
        {
            isPrintF("printf");
            
            return TOKEN_TYPE :: IDENTIFIER;
        }
        
        else if(this -> syntax == "procedure" && !isProcedure())
        {
            isProcedure("procedure");
            
            return TOKEN_TYPE :: IDENTIFIER;
        }

        else if(findInteger())
        {
            if(!isPrintF())
                isValue("=");
        }
        
        /******************************
         
         Add all the other FIND VARAIBLES as well
        
         **************************************************/
        
        else if(findProcedure())
            return TOKEN_TYPE :: IDENTIFIER;
        
        return TOKEN_TYPE :: IDENTIFIER;
    }
    else if(isPrintF(strdup("end scanning")))
        return TOKEN_TYPE :: STRING;
    
    else if(this->syntax == "(")
        return TOKEN_TYPE :: LEFT_PARENTHESIS;
    
    else if(this->syntax == ")")
        return TOKEN_TYPE :: RIGHT_PARENTHESIS;
    
    else if(this->syntax == "[")
        return TOKEN_TYPE :: LEFT_BRACKET;
    
    else if(this->syntax == "]")
        return TOKEN_TYPE :: RIGHT_BRACKET;
    
    else if(this->syntax == "{")
        return TOKEN_TYPE :: LEFT_BRACE;
    
    else if(this->syntax == "}")
        return TOKEN_TYPE :: RIGHT_BRACE;
    
    else if(this->syntax == "\"")
        return TOKEN_TYPE :: DOUBLE_QUOTE;
    
    else if(this->syntax == "'")
        return TOKEN_TYPE :: SINGLE_QUOTE;
    
    else if(this->syntax == ";")
        return TOKEN_TYPE :: SEMICOLON;
    
    else if(this->syntax == ",")
        return TOKEN_TYPE :: COMMA;
    
    else if(this->syntax == "=")
        return TOKEN_TYPE :: ASSIGNMENT_OPERATOR;
    
    else if(syntax == "+")
        return TOKEN_TYPE :: PLUS;
    
    else if(syntax == "-")
        
        if(!isValue(strdup("integer")))
            return TOKEN_TYPE :: MINUS;
    
        else
            return TOKEN_TYPE :: BNF_IN_PROCESS;
    
    else if(syntax == "*")
        return TOKEN_TYPE :: ASTERISK;
    
    else if(syntax == "/")
        return TOKEN_TYPE :: DIVIDE;
    
    else if(syntax == "%")
        return TOKEN_TYPE :: MODULO;
    
    else if(syntax == "^")
        return TOKEN_TYPE :: CARET;
    
    else if(syntax == "<")
        return TOKEN_TYPE :: LESS_THAN;
    
    else if(syntax == "<=")
        return TOKEN_TYPE :: LESS_THAN_OR_EQUAL;
    
    else if(syntax == ">")
        return TOKEN_TYPE :: GREATER_THAN;
    
    else if(syntax == ">=")
        return TOKEN_TYPE :: GREATER_THAN_OR_EQUAL;
    
    else if(syntax == "&&")
        return TOKEN_TYPE :: BOOLEAN_AND;
    
    else if(syntax == "||")
        return TOKEN_TYPE :: BOOLEAN_OR;
    
    else if(syntax == "!")
        return TOKEN_TYPE :: BOOLEAN_NOT;
    
    else if(syntax == "==")
        return TOKEN_TYPE :: BOOLEAN_EQUAL;
    
    else if(syntax == "!=")
        return TOKEN_TYPE :: BOOLEAN_NOT_EQUAL;
    
    else if(isValue(strdup(";")))
           return TOKEN_TYPE :: INTEGER;
    
    return TOKEN_TYPE :: NON_BNF;
    
}
// ------------------------------------------------------------------
bool Tokenize :: FilterProcedure(std::string text)
{
    std::string tempSyntax = "";
    
    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] == ' ' || text[i] == '\0')
            continue;
        else
            tempSyntax += text[i];

    }
    
    if(tempSyntax == "procedure")
        return true; return false;
}
// ------------------------------------------------------------------
// Determines if a token is currently being read
TOKEN_TYPE Tokenize :: isTokenHelper()
{
    if(isPrintF(strdup("scan string")))
        return BNF_IN_PROCESS;
    
    if(
       tokenIdentifier() &&
       !isValue() &&
       !isPrintF(strdup("end scanning")))
    {
        if(this->syntax == "int")
            return TOKEN_TYPE :: IDENTIFIER;
        
        else if(isInteger(strdup("datatype")))
        {
            if((this->read.peek() == ';') &&
               this->syntax.size() != 0)
                return TOKEN_TYPE :: IDENTIFIER;
            
            else if((this->read.peek() == '=' ||
                     this->read.peek() == ' ') &&
                    this->syntax.size() != 0)
                return TOKEN_TYPE :: IDENTIFIER;
            
            else if(this->read.peek() == ',' && syntax.size() != 0)
                return TOKEN_TYPE :: IDENTIFIER;
            
            else if(this->syntax == ";")
                return TOKEN_TYPE :: SEMICOLON;
            
            else
                std::invalid_argument("\n\nError - Invalid syntax " + this -> syntax + " detected\n\n");
        }
        else if(isInteger(strdup("=")))
        {
            if(this->syntax == "=" && read.peek() == ',')
                return TOKEN_TYPE :: ASSIGNMENT_OPERATOR;
            
            else if(this->syntax == "=")
                return TOKEN_TYPE :: ASSIGNMENT_OPERATOR;
            
        }
        
        return TOKEN_TYPE :: IDENTIFIER;
    }
    
    else if(isPrintF(strdup("end scanning")))
        return TOKEN_TYPE :: STRING;
    
    else if(syntax == "(")
        return TOKEN_TYPE :: LEFT_PARENTHESIS;
    
    else if(syntax == ")")
        return TOKEN_TYPE :: RIGHT_PARENTHESIS;
    
    else if(syntax == "[")
        return TOKEN_TYPE :: LEFT_BRACKET;
    
    else if(syntax == "]")
        return TOKEN_TYPE :: RIGHT_BRACKET;
    
    else if(syntax == "{")
        return TOKEN_TYPE :: LEFT_BRACE;
    
    else if(syntax == "}")
        return TOKEN_TYPE :: RIGHT_BRACE;
    
    else if(syntax == "\"")
        return TOKEN_TYPE :: DOUBLE_QUOTE;
    
    else if(syntax == "'")
        return TOKEN_TYPE :: SINGLE_QUOTE;
    
    else if(syntax == ";")
        return TOKEN_TYPE :: SEMICOLON;
    
    else if(syntax == ",")
        return TOKEN_TYPE :: COMMA;
    
    else if(syntax == "=")
        return TOKEN_TYPE :: ASSIGNMENT_OPERATOR;
    
    else if(syntax == "+")
        return TOKEN_TYPE :: PLUS;
    
    else if(syntax == "-")
        if(!isValue(strdup("integer")))
            return TOKEN_TYPE :: MINUS;
        else
            return TOKEN_TYPE :: BNF_IN_PROCESS;
    
    else if(syntax == "*")
        return TOKEN_TYPE :: ASTERISK;
    
    else if(syntax == "/")
        return TOKEN_TYPE :: DIVIDE;
    
    else if(syntax == "%")
        return TOKEN_TYPE :: MODULO;
    
    else if(syntax == "^")
        return TOKEN_TYPE :: CARET;
    
    else if(syntax == "<")
        return TOKEN_TYPE :: LESS_THAN;
    
    else if(syntax == "<=")
        return TOKEN_TYPE :: LESS_THAN_OR_EQUAL;
    
    else if(syntax == ">")
        return TOKEN_TYPE :: GREATER_THAN;
    
    else if(syntax == ">=")
        return TOKEN_TYPE :: GREATER_THAN_OR_EQUAL;
    
    else if(syntax == "&&")
        return TOKEN_TYPE :: BOOLEAN_AND;
    
    else if(syntax == "||")
        return TOKEN_TYPE :: BOOLEAN_OR;
    
    else if(syntax == "!")
        return TOKEN_TYPE :: BOOLEAN_NOT;
    
    else if(syntax == "==")
        return TOKEN_TYPE :: BOOLEAN_EQUAL;
    
    else if(syntax == "!=")
        return TOKEN_TYPE :: BOOLEAN_NOT_EQUAL;
    
    else if(isValue(strdup(";")))
        return TOKEN_TYPE :: INTEGER;
    
    else if(isPrintF(strdup("end scanning")))
        return TOKEN_TYPE :: STRING;
    
    return TOKEN_TYPE :: NON_BNF;
    
}
// ------------------------------------------------------------------
// Determine datatype being used for the purpose of selecting which collector vector to utilize
TOKEN_TYPE Tokenize :: dataType(std::string command)
{
    if(command == "int")
        return TOKEN_TYPE :: INTEGER;
    
    if(command == "char")
        return TOKEN_TYPE :: CHAR;
    
    if(command == "string")
        return TOKEN_TYPE :: STRING;
    
    return TOKEN_TYPE :: ERROR;
}

// ------------------------------------------------------------------

std::pair<std::string, std::string> Tokenize :: Token_Handler(TOKEN_TYPE token)
{
    switch(token)
    {
        case IDENTIFIER:

            if(syntax == "procedure")
                return {"IDENTIFIER", "procedure"};
            
            else if(syntax == "main")
                return {"IDENTIFIER", "main"};
            
            else if(syntax == "void")
                return {"IDENTIFIER", "void"};
            
            else if(findInteger() && !isProcedure())
            {
                position tempIndex = this -> integer_index;
                
                this -> integer_index = 0;
                
                return {"IDENTIFIER", this -> integerCollector[tempIndex]};
                
            }
            
            else if(findString() && !isProcedure())
            {
                position tempIndex = this -> string_index;
                
                this -> string_index = 0;
                
                return {"IDENTIFIER", this -> stringCollector[tempIndex]};
                
            }
            
            else if(findChar() && !isProcedure())
            {
                position tempIndex = this -> char_index;
                
                this -> char_index = 0;
                
                return {"IDENTIFIER", this -> charCollector[tempIndex]};
                
            }
            
            else if(findIntegerArg() && isProcedure())
            {
                position tempIndex = this -> integer_arg_index;
                
                this -> integer_arg_index = 0;
                
                return {"IDENTIFIER", this -> integerArgCollector[tempIndex]};
            }
            
            else if(findStringArg() && isProcedure())
            {
                position tempIndex = this -> string_arg_index;
                
                this -> string_arg_index = 0;
                
                return {"IDENTIFIER", this -> stringArgCollector[tempIndex]};
            }
            
            else if(findCharArg() && isProcedure())
            {
                position tempIndex = this -> char_arg_index;
                
                this -> char_arg_index = 0;
                
                return {"IDENTIFIER", this -> charArgCollector[tempIndex]};
            }
            
            else if(findProcedure() && isProcedure(strdup("is regular procedure")))
            {
                position tempIndex = this -> procedure_index;
                
                this -> procedure_index = 0;
                
                return {"IDENTIFIER", this -> procedureCollector[tempIndex]};
            }
            
            else
                return {"IDENTIFIER", this -> syntax};
            
        case LEFT_PARENTHESIS:
            return {"LEFT_PARENTHESIS", "("};
            
        case RIGHT_PARENTHESIS:
            return {"RIGHT_PARENTHESIS", ")"};
            
        case LEFT_BRACKET:
            return {"LEFT_BRACKET", "["};
            
        case RIGHT_BRACKET:
            return {"RIGHT_BRACE", "]"};
            
        case LEFT_BRACE:
            return {"LEFT_BRACE", "{"};
            
        case RIGHT_BRACE:
            return {"RIGHT_BRACE", "}"};
            
        case DOUBLE_QUOTE:
            return {"DOUBLE_QUOTE", "\""};
            
        case SINGLE_QUOTE:
            return {"SINGLE_QUOTE", "'"};
            
        case SEMICOLON:
            return {"SEMICOLON", ";"};
            
        case COMMA:
            return {"COMMA", ","};
            
        case ASSIGNMENT_OPERATOR:
            return {"ASSIGNMENT", "="};
            
        case PLUS:
            if(!isValue())
                return {"PLUS", "+"};
            
        case MINUS:
            if(!isValue())
                return {"MINUS", "-"};
            
            break;
            
        case ASTERISK:
            return {"ASTERISK", "*"};
            
        case DIVIDE:
            return {"DIVIDE", "/"};
            
        case MODULO:
            return {"MODULO", "%"};
        case CARET:
            return {"CARET", "^"};
            
        case LESS_THAN:
            return {"LESS_THAN", "<"};
            
        case LESS_THAN_OR_EQUAL:
            return {"LESS_THAN_OR_EQUAL", "<="};
            
        case GREATER_THAN:
            return {"GREATER_THAN", ">"};
            
        case GREATER_THAN_OR_EQUAL:
            return {"GREATER_THAN_OR_EQUAL", ">="};
            
        case BOOLEAN_AND:
            return {"BOOBLEAN_AND", "&&"};
            
        case BOOLEAN_OR:
            return {"BOOBLEAN_OR", "||"};
            
        case BOOLEAN_NOT:
            return {"BOOBLEAN_NOT", "!"};
            
        case BOOLEAN_EQUAL:
            return {"BOOBLEAN_EQUAL", "=="};
            
        case BOOLEAN_NOT_EQUAL:
            return {"BOOBLEAN_NOT_EQUALL", "!="};
            
        case STRING:
            return {"STRING", syntax};
            
        case INTEGER:
            return {"INTEGER", syntax};
    }
    
    return {"UNDEFINED","UNDEFINED"};
}
// ------------------------------------------------------------------
// Return value of TokenVector
std::vector<std::vector<std::pair<std::string,std::string>>> & Tokenize :: GetTokenVector()
{
    return TokenVector;
}
// ------------------------------------------------------------------
// Output Tokenize object
std::ostream & operator << (std::ostream &output, Tokenize &token)
{
    // Execute operation
    token.Execute();
    
    // Display output and finalize operation
    return Print(output,token);
    
}
// ------------------------------------------------------------------
// std::ostream & operator helper function
std::ostream & Print(std::ostream &output, Tokenize &token)
{
    // Display results
    for(const auto &tokenVector : token.GetTokenVector())
    {
        for(const auto & [tokenType,token] : tokenVector)
        {
            output << "Token Type: " << tokenType << std::endl;
            
            output << "Token: " << token << std::endl << std::endl;
        }
    }
    
    return output;
}
