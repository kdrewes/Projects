#include <fstream>
#include <cstring>
#include <exception>
#include "Tokenize.h"
#include "removeComments.h"

Tokenize :: Tokenize(std::vector<std::string> TestFiles)
{
    this -> TestFiles = TestFiles;
    
    this -> integer_index = 0;
    
    this -> count_characters = 0;
    
    this -> syntax = "";
}

// ------------------------------------------------------------------
// Initiates process of collecting content of each file
void Tokenize :: Execute()
{
    for(std::vector<std::string>::size_type i = 0; i < 1; i++){
        
        try
        {
            // Read file
            std::ifstream read(TestFiles[0],std::ios::in);
            
            // Collect tokens from current file being read
            this -> TokenVector.push_back(ReadFile(read));
        }
        catch(std::invalid_argument e)
        {
            // Display error message
            std::cout << e.what() << std::endl;
        }
        
    }
    
    Clear();
    
}
// ------------------------------------------------------------------
// Clear memory from ADT'S
void Tokenize :: Clear()
{
    this -> TestFiles.clear();
    this -> integerCollector.clear();
    this -> stringCollector.clear();
    this -> TokenVector.clear();
}

// ------------------------------------------------------------------
// Reads contents of each individual file and extracts tokens from content
std::vector<std::pair<tokenType,token>> Tokenize :: ReadFile(std::ifstream &read)
{
    // Used to collect each individual token
    std::vector<std::pair<tokenType,token>>Tokens;
    
    if(!read)
        throw std::invalid_argument("Unable to open file\n");
    else
    {
        for(char character = '\0'; !read.eof();  read >> std::noskipws >> character )
        {
            
            if(character != '\n')
                std::cout << character;
            else
                std::cout << std::endl;

            if(character != ' ' && character != '\n')
            {
                this->syntax += Verify_Character(character,read);
                
                if(isToken(isTokenHelper(read)))
                {
                    Tokens.push_back(Token_Handler(Read_Token(read), read));
                    this->syntax = "";
                }
            }
            else if(isPrintF(strdup("scan string")))
                this -> syntax += character;
            else
                this->syntax = "";
            
        }
    }
    
    for(std::vector<std::pair<tokenType,token>> :: size_type i = 0; i < Tokens.size(); i++)
    {
        std::cout << "Token Type: " << Tokens[i].first << std::endl;
        std::cout << "Token: " << Tokens[i].second << std::endl << std::endl;
    }
    
    read.close();
    
    return Tokens;
}
// ------------------------------------------------------------------
// Verifies that each character is legally allowed to use
char Tokenize :: Verify_Character(char character, std::ifstream &read)
{
    return (Verify_Character_Helper(character, read));
}
// ------------------------------------------------------------------
// Handles input validation with Read_Character function
char Tokenize :: Verify_Character_Helper(char character, std::ifstream &read)
{
    // Input validation for integer handler
    checkInteger(character,read);
    
    // Input validation for isValue handler
    checkIsValue(character,read);
    
    // Input validation for isString handler
    checkPrintF(character, read);
    
    // Input validation for procedure handler
    checkProcedure(character, read);
    
    return character;
}
// ------------------------------------------------------------------
// Checks if isInteger boolean variable is currently set as 'true'
void Tokenize :: checkInteger(char character, std::ifstream &read)
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
// ------------------------------------------------------------------
// Checks if isValue boolean variable is currently set as 'true'
void Tokenize :: checkIsValue(char character, std::ifstream &read)
{
    
    if(isValue(strdup("=")))
    {
        if(character == '=')
        {
            if(read.peek() == ' ' || isnumber(read.peek()))
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
        
        else if(isnumber(read.peek()))
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
                if(read.peek() == ' ' || read.peek() == ';')
                    isValue(";");
                else
                {
                    if(!isnumber(read.peek()))
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
            throw(std::invalid_argument("Error - invalid character detected\n\ncharacter must be ';' not " + character + '+'));
    }
    
}

// ------------------------------------------------------------------
// Check if isPrintf boolean variable is currently set as 'true'
void Tokenize :: checkPrintF(char character, std::ifstream &read)
{
    if(isPrintF(strdup("printf")))
    {
        if(character == '(')
            isPrintF("(");
        
        else
            throw(std::invalid_argument(&"Error - invalid character detected\n\ncharacter must be '(' not " [ character]));
    }
    
    else if(isPrintF(strdup("(")))
    {
        if(character == '"')
            isPrintF("beginning quotation");
        else
            throw std::invalid_argument("\n Error - Invalid character detected, character must contain quotation mark\n");
    }
    
    else if(isPrintF(strdup("beginning quotation")))
        isPrintF("scan string");
    
    else if(isPrintF(strdup("scan string")))
    {
        if(read.peek() == '"' && character != '\\')
            isPrintF("end scanning");
        
        if((count_characters += 1) > 30)
        {
            this -> count_characters = 0;
            throw(std::invalid_argument("Error - printf statement contains too many characters\n\nNo quotation mark detected.\n"));
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
            throw std::invalid_argument("Error - Invalid character " + std::string(1, character) + " detected.\n");
    }
    
    else if(isPrintF(strdup(",")))
    {
        // First character of variable is not an alphabetic character
        if(this -> syntax.size() == 0)
            if(!isalpha(character))
                throw std::invalid_argument("Error - Invalid character " + std::string(1, read.peek()) + " used in variable.\n");
        
        if(read.peek() == ' ' || read.peek() == ')')
        {
            // Declare temporary syntax variable used as backup storage
            token tempSyntax = this -> syntax;
            
            // Add character to syntax to make it temporarily complete
            this -> syntax += character;
            
            // Determine if variable (syntax) exists.  If not, throw an exception
            if(!findVariable(TOKEN_TYPE :: INTEGER))
                throw(std::invalid_argument("Error - " + this -> syntax + " does not exist\n" ));
            
            // Re-assign this -> syntax original value
            this -> syntax = tempSyntax;
            
            isPrintF(")");
        }
    }
    
    else if(isPrintF(strdup(")")))
    {
        if(character == ';')
            isPrintF(";");
        
        else if (read.peek() == ';')
            isPrintF(";");
        
        else if(read.peek() != ';' &&  read.peek() != ' ')
            throw std::invalid_argument("\n\nError - Invalid character " + std::string(1, read.peek()) + " detected ahead.  Character must be ';'\n");
        
        else if(character != ';')
        {
            std::cout << "\n\nCHARACTER " << character << std::endl;
            throw std::invalid_argument("\n\nError - Invalid character " + std::string(1, read.peek()) + " detected.  Character must be ';'\n");
        }
        
    }
    
    else if(isPrintF(strdup(";")))
        isPrintF("reset");
    
}
// ------------------------------------------------------------------
// Check if isProecedure boolean varaible is currently set as 'true'

void Tokenize :: checkProcedure(char character, std::ifstream &read)
{
    
    if(procedure_handler.found_procedure_name)
    {
        if(this -> syntax.size() == 0 && !isalpha(character))
            throw(std::invalid_argument("\n\nError - invalid character detected for procedure name\n"));
        
        else if(this -> syntax.size() > 0 && ((isalpha(character)) || isnumber(character)))
        {
            if(read.peek() == ' ' || read.peek() == '(')
            {
                if(this -> syntax == "main")
                {
                    // Conduct operation
                    //isProcedure(false,true,false,false,false);
                }
                else
                {
                    
                }
            }
        }
    }
}

// ------------------------------------------------------------------
// Determines if file text is an identifier
bool Tokenize :: isIdentifier(std::ifstream &read)
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
        if(read.peek() == ' ')
            return true;
        else
            std::invalid_argument("Error - invalid syntax detected.\n");

        
    }
    else if(isInteger(strdup("datatype")))
    {
        if(read.peek() == ';' && this->syntax.size() != 0)
            return true;
        
        else if(read.peek() == ' ' && this->syntax.size() != 0)
            return true;
        
        else if(this->syntax == ";")
            return true;
        
    }
    
    else if(findVariable(TOKEN_TYPE :: INTEGER))
        return true;
    
    return false;
}
// ------------------------------------------------------------------
// Determines if file text is an identifier, used specifically for bool isToken
bool Tokenize :: tokenIdentifier(std::ifstream &read)
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
        if(read.peek() == ' ')
            return true;
        else
            std::invalid_argument("\n\nError - Invalid syntax " + this -> syntax + " detected\n\n");
        
    }
    else if(isInteger(strdup("datatype")))
    {
        if(read.peek() == ';' && this->syntax.size() != 0)
            return true;
        
        else if(read.peek() == ' ' && this->syntax.size() != 0)
            return true;
        
        else if(this->syntax == ";")
            return true;
        
    }
    else if(findVariable(TOKEN_TYPE :: INTEGER))
        return true;
    
    return false;
}
// ------------------------------------------------------------------
// Determines if BNF token was detected
bool Tokenize :: isToken(TOKEN_TYPE token)
{
    if(token == TOKEN_TYPE :: NON_BNF || token == TOKEN_TYPE :: BNF_IN_PROCESS)
        return false; return true;
}
// ------------------------------------------------------------------
bool Tokenize :: findVariable(TOKEN_TYPE token)
{
    switch(token)
    {
        case INTEGER:
            if(!integerCollector.empty())
                for(std::vector<dataType> :: size_type i = 0; i < integerCollector.size(); i++)
                    if(this->syntax == integerCollector[i])
                    {
                        this -> integer_index = i;
                        return true;
                    }
    }
    
    return false;
}
// ------------------------------------------------------------------
// Determines which token is currently being read
TOKEN_TYPE Tokenize :: Read_Token(std::ifstream &read)
{
    
    if(isIdentifier(read) &&
       !isValue() &&
       !isPrintF(strdup("end scanning")))
    {
        if(this->syntax == "int")
        {
            isInteger("datatype");
            return TOKEN_TYPE :: IDENTIFIER;
        }
        else if(isInteger())
        {
            if(isInteger(strdup("datatype")))
            {
                if((read.peek() == ';') &&
                   this->syntax.size() != 0)
                {
                    isInteger("value");
                    integerCollector.push_back(syntax);
                    return TOKEN_TYPE :: IDENTIFIER;
                }
                else if((read.peek() == '=' ||
                         read.peek() == ' ') &&
                        this->syntax.size() != 0)
                {
                    isInteger("=");
                    return TOKEN_TYPE :: IDENTIFIER;
                }
                else if(read.peek() == ',' && this->syntax.size() != 0)
                    return TOKEN_TYPE :: IDENTIFIER;
                else if(this->syntax == ";")
                {
                    isInteger("reset");
                    return TOKEN_TYPE :: SEMICOLON;
                }
                else if(syntax == ",")
                    return TOKEN_TYPE :: COMMA;
                else
                    throw std::invalid_argument("Error - Invalid character detected.");
            }
        }
        
        else if(this -> syntax == "printf" && !isPrintF())
        {
            isPrintF("printf");
            
            return TOKEN_TYPE :: IDENTIFIER;
        }
        
        else if(this -> syntax == "procedure")
        {
            procedure_handler(true);
            
            return TOKEN_TYPE :: IDENTIFIER;
        }
        else if(findVariable(TOKEN_TYPE :: INTEGER))
        {
            if(!isPrintF())
            {
                std::cout << "\n\nNAME OF PROPERTY: " << this -> syntax << std::endl;
                isValue("=");
            }
            
            return TOKEN_TYPE :: IDENTIFIER;
            
        }
        
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
// Determines if a token is currently being read
TOKEN_TYPE Tokenize :: isTokenHelper(std::ifstream &read)
{
    if(isPrintF(strdup("scan string")))
        return BNF_IN_PROCESS;
    
    if(
       tokenIdentifier(read) &&
       !isValue() &&
       !isPrintF(strdup("end scanning")))
    {
        if(this->syntax == "int")
            return TOKEN_TYPE :: IDENTIFIER;
        
        else if(isInteger(strdup("datatype")))
        {
            if((read.peek() == ';') &&
               this->syntax.size() != 0)
                return TOKEN_TYPE :: IDENTIFIER;
            
            else if((read.peek() == '=' ||
                     read.peek() == ' ') &&
                    this->syntax.size() != 0)
                return TOKEN_TYPE :: IDENTIFIER;
            
            else if(read.peek() == ',' && syntax.size() != 0)
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
std::pair<std::string, std::string> Tokenize :: Token_Handler(TOKEN_TYPE token, std::ifstream &read)
{
    switch(token)
    {
        case IDENTIFIER:
            // std::cout << " We have reached the identifier case\n";
            //std::cout << syntax << " has been identified " << token << std::endl;
            //exit(0);
            if(syntax == "procedure")
                return {"IDENTIFIER", "procedure"};
            
            else if(syntax == "main")
                return {"IDENTIFIER", "main"};
            
            else if(syntax == "void")
                return {"IDENTIFIER", "void"};
            
            else if(findVariable(TOKEN_TYPE :: INTEGER))
            {
                position tempIndex = this ->integer_index; this -> integer_index = 0;
                return {"IDENTIFIER", this -> integerCollector[tempIndex]};
                
            }
            else
                return {"IDENTIFIER", syntax};
            
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
