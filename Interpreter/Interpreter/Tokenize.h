

#ifndef Tokenize_hpp
#define Tokenize_hpp
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "removeComments.h"

// Rename string data types for organizational purposes
typedef std::string fileName, tokenType, token, dataType;

// Rename integer data types for organization purposes
typedef int iterator, position;

// Rename bool data types for organization purposes
typedef bool boolean, integer_bool, value_bool, printf_bool, procedure_bool;

// Create enums which are used as a labeling techiques for token types
enum TOKEN_TYPE {
    IDENTIFIER,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_BRACE,
    RIGHT_BRACE,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    SEMICOLON,
    COMMA,
    ASSIGNMENT_OPERATOR,
    PLUS,
    MINUS,
    ASTERISK,
    DIVIDE,
    MODULO,
    CARET,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    BOOLEAN_AND,
    BOOLEAN_OR,
    BOOLEAN_NOT,
    BOOLEAN_EQUAL,
    BOOLEAN_NOT_EQUAL,
    STRING,
    INTEGER,
    BNF_IN_PROCESS,
    NON_BNF
};




class Tokenize
{
private:
    
    // Test file vector
    std::vector<fileName> TestFiles;
    
    
    std::vector<dataType> stringCollector,    // Collects string data type
    integerCollector;   // Collects int data type
    
    
    // Vector used to collect tokens from each file
    std::vector<std::vector<std::pair<tokenType,token>>>TokenVector;
    
    // Contains index of integer/string variable found
    position integer_index;
    
    // Count the amount of character being used within printf statement
    iterator count_characters;
    
    // Variable used to collect character for each individual token
    token syntax;
    
    // ----------------------------------------------------------------------
    
    // Indicates an integer variable was detected
    
    // first = integer datatype was detected
    // second = variable was detected
    // third = assignment operator was detected
    
    struct INTEGER_HANDLER
    {
        // Enums used to represent each property of a particular VALUE_HANDLER component
        enum INTEGER_ENUM
        {
            DATA_TYPE,
            VALUE,
            ASSIGNMENT_OPERATOR,
            RESET,
            ERROR
        };
        
        integer_bool is_data_type,
                     is_value,
                     is_assignment_operator;
        
        INTEGER_HANDLER() :
        is_data_type(false),
        is_value(false),
        is_assignment_operator(false) {}
        
        // Modifies boolean values specifically for INTEGER_HANDLER
        void operator()(std::string command)
        {
            Configure_Flags(Enum_Handler(command));
        }
        // ----------------------------------------------------------
        // Determine if boolean property exists in INTEGER_HANDLER
        bool operator()(char * command)
        {
            return Verify_Flag(Enum_Handler(command), command);
        }
        // ----------------------------------------------------------
        // Determine if there is a true boolean member within INTEGER_HANDLER
        bool operator()()
        {
            return isTrue();
        }
        // ----------------------------------------------------------
        // Used to determine the correct enum object to utilize
        INTEGER_ENUM Enum_Handler(std::string command)
        {
            // Prevents command from being case sensetive
            LowerCase(command);
            
            if(command == "is datatype" || command == "datatype" || command == "data type")
                return INTEGER_ENUM :: DATA_TYPE;
            
            else if(command == "is value" || command == "value")
                return INTEGER_ENUM :: VALUE;
            
            else if(command == "=" || command == "assignment operator" || command == "equal")
                return INTEGER_ENUM :: ASSIGNMENT_OPERATOR;
            
            else if(command == "reset")
                return INTEGER_ENUM :: RESET;
            
            return INTEGER_ENUM :: ERROR;
            
        }
        // ----------------------------------------------------------
        // Used for the purpose of configuring the values of each flag.
        void Configure_Flags(INTEGER_ENUM enum_property)
        {
            switch(enum_property)
            {
                case DATA_TYPE:
                
                    if(!this -> is_data_type)
                    {
                        Reset();
                        this -> is_data_type = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_data_type is already set to true\n");
                    
                    break;
                
                    
                case VALUE:
                
                    if(!this -> is_value)
                    {
                        Reset();
                        is_value = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_value is already set to true\n");
                    
                    break;
                
                    
                case ASSIGNMENT_OPERATOR:
                
                    if(!this -> is_assignment_operator)
                    {
                        Reset();
                        is_assignment_operator = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_assignment_operator is already set to true\n");
                    
                    break;
                
                case RESET:
                    
                    Reset();
                    
                    break;
                    
                    
                case ERROR:
                    throw std::invalid_argument("\nError - configuration not found\n");
            }
        }
        // ----------------------------------------------------------
        // Used to verify the status of each flag.
        bool Verify_Flag(INTEGER_ENUM enum_propery, char * command)
        {
            switch(enum_propery)
            {
                    
                case DATA_TYPE:
                
                    if(is_data_type)
                        return true; return false;
                
                    
                case VALUE:
                
                    if(is_value)
                        return true; return false;
                
                    
                case ASSIGNMENT_OPERATOR:
                
                    if(is_assignment_operator)
                        return true; return false;
                
                    
                case RESET:
                    
                    Reset();
                    break;
                    
                case ERROR:
                    throw std::invalid_argument("\nError - boolean command " + std::string(command) + " not detected\n");
            }
            
            return false;
        }
        // ----------------------------------------------------------
        // Used to prevent command from being case sensetive
        void LowerCase(std::string &command)
        {
            for(int i = 0; i < command.size(); i++)
                command[i] = tolower(command[i]);
        }
        
        // ----------------------------------------------------------
        // Used to reset values of all flags
        void Reset()
        {
            this -> is_data_type = false;
            this -> is_value = false;
            this -> is_assignment_operator = false;
        }
        
        // ----------------------------------------------------------

        // Determines if VALUE_HANDLER contains any true boolean variables
        bool isTrue()
        {
            // Declare array which holds all flags
            printf_bool integerArray [] = {
                this -> is_data_type,
                this -> is_value,
                this -> is_assignment_operator
            };
            
            for(int i = 0; i < sizeof(integerArray)/sizeof(integerArray[0]); i++)
                if(integerArray[i] == true)
                    return true;
            
            return false;
        }

        // Deconstructor
        ~ INTEGER_HANDLER() = default;
        
    }isInteger;
    
    // ----------------------------------------------------------------------
    // Indicates a variable was detected and converts value into token
    struct VALUE_HANDLER
    {
        
        // Enums used to represent each property of a particular VALUE_HANDLER component
        enum VALUE_ENUM
        {
            ASSIGNMENT_OPERATOR,
            INTEGER,
            SEMICOLON,
            RESET,
            ERROR
        };
        
        // ----------------------------------------------------------

        // Declare boolean variable for VALUE_HANDLER
        value_bool is_equal,
                   is_integer,
                   is_semicolon;
        
        // ----------------------------------------------------------

        VALUE_HANDLER() : is_equal(false),
        is_integer(false),
        is_semicolon(false) {}
        
        // ----------------------------------------------------------
        
        // Modifies boolean values which belong to VALUE_HANDLER
        void operator()(std::string command)
        {
            Configure_Flags(Enum_Handler(command));
        }
        // ----------------------------------------------------------
        
        // Determine if boolean property is exists in VALUE_HANDLER
        bool operator()(char * command)
        {
            return Verify_Flag(Enum_Handler(command), command);
        }
        // ----------------------------------------------------------
        
        // Determine if there is a true boolean member contained in VALUE_HANDLER
        bool operator()()
        {
            return isTrue();
        }
        // ----------------------------------------------------------
        
        // Used to determine the correct enum object to utilize
        VALUE_ENUM Enum_Handler(std::string command)
        {
            // Prevents command from being case sensetive
            LowerCase(command);
            
            if(command == "is equal" || command == "equal" || command == "=")
                return VALUE_ENUM :: ASSIGNMENT_OPERATOR;
            
            else if(command == "is integer" || command == "integer")
                return VALUE_ENUM :: INTEGER;
            
            else if(command == "is semicolon" || command == "semicolon" || command == ";")
                return VALUE_ENUM :: SEMICOLON;
            
            else if(command == "reset")
                return VALUE_ENUM :: RESET;
            
            return VALUE_ENUM :: ERROR;
            
        }
        // ----------------------------------------------------------
        
        // Used for the purpose of configuring the values of each flag.
        void Configure_Flags(VALUE_ENUM enum_property)
        {
            switch(enum_property)
            {
                case ASSIGNMENT_OPERATOR:
                
                    if(!this -> is_equal)
                    {
                        Reset();
                        is_equal = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_equal is already set to true\n");
                    
                    break;
                
                    
                case INTEGER:
                
                    if(!this -> is_integer)
                    {
                        Reset();
                        is_integer = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_integer is already set to true\n");
                    
                    break;
                
                    
                case SEMICOLON:
                
                    if(!this -> is_semicolon)
                    {
                        Reset();
                        is_semicolon = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_semicolon is already set to true\n");
                    
                    break;
                
                case RESET:
                    
                    Reset();
                    
                    break;
                    
                    
                case ERROR:
                    throw std::invalid_argument("\nError - configuration not found\n");
            }
        }
        // ----------------------------------------------------------
        
        // Used to verify the status of each flag.
        bool Verify_Flag(VALUE_ENUM enum_propery, char * command)
        {
            switch(enum_propery)
            {
                    
                case ASSIGNMENT_OPERATOR:
                
                    if(is_equal)
                        return true; return false;
                
                    
                case INTEGER:
                
                    if(is_integer)
                        return true; return false;
                
                    
                case SEMICOLON:
                
                    if(is_semicolon)
                        return true; return false;
                
                    
                case RESET:
                    
                    Reset();
                    break;
                    
                case ERROR:
                    throw std::invalid_argument("\nError - boolean command " + std::string(command) + " not detected\n");
            }
            
            return false;
        }
        // ----------------------------------------------------------
        
        // Used to prevent command from being case sensetive
        void LowerCase(std::string &command)
        {
            for(int i = 0; i < command.size(); i++)
                command[i] = tolower(command[i]);
        }
        
        // ----------------------------------------------------------
        
        // Used to reset values of all flags
        void Reset()
        {
            this -> is_equal = false;
            this -> is_integer = false;
            this -> is_semicolon = false;
        }
        // ----------------------------------------------------------
        
        // Determines if VALUE_HANDLER contains any true boolean variables
        bool isTrue()
        {
            // Declare array which holds all flags
            printf_bool valueArray [] = {
                this -> is_equal,
                this -> is_integer,
                this -> is_semicolon
            };
            
            for(int i = 0; i < sizeof(valueArray)/sizeof(valueArray[0]); i++)
                if(valueArray[i] == true)
                    return true;
            
            return false;
        }
        
    }isValue;
    // ----------------------------------------------------------------------
    // Facilitates the boolean mechanics anytime a procedure is detected
    // Indicates aa printf command was detected.
    // Content in quotation marks will return a string.
    
    struct PRINTF_HANDLER
    {
        // Enums used to represent each property of a particular print f component
        enum PRINTF_ENUM
        {
            PRINT_F,
            LEFT_PARENTHESIS,
            BEGINNING_QUOTATION,
            SCANNING_STRING,
            END_SCANNING,
            END_QUOTATION,
            RIGHT_PARENTHESIS,
            COMMA,
            SEMICOLON,
            RESET,
            ERROR
            
        };
        
        // ----------------------------------------------------------

        // Declare all flags used in the Printf Handler operation
        printf_bool is_print_f,
        is_left_paranthesis,
        is_beginning_quotation,
        is_scanning_string,
        end_scanning,
        is_end_quotation,
        is_right_paranthesis,
        is_comma,
        is_semicolon;
        
        // ----------------------------------------------------------

        // Execute default constructor
        PRINTF_HANDLER() :
        is_print_f(false),
        is_left_paranthesis(false),
        is_beginning_quotation(false),
        is_scanning_string(false),
        end_scanning(false),
        is_end_quotation(false),
        is_right_paranthesis(false),
        is_comma(false),
        is_semicolon(false) {};
        
        // ----------------------------------------------------------
        // Modifies boolean values which belong to PRINTF_HANDLER
        void operator()(std::string command)
        {
            Configure_Flags(Enum_Handler(command));
        }
        
        // ----------------------------------------------------------
        // Determine if boolean property is exists in PRINTF_HANDLER
        bool operator()(char * command)
        {
            return Verify_Flag(Enum_Handler(command), command);
        }
        // ----------------------------------------------------------
        // Determine if there is a true boolean member contained in PRINTF_HANDLER
        bool operator()()
        {
            return isTrue();
        }
        // ----------------------------------------------------------
        // Used to determine the correct enum object to utilize
        PRINTF_ENUM Enum_Handler(std::string command)
        {
            // Used to prevent command from being case sensetive
            LowerCase(command);
            
            // Determine correct enum to use
            if(command == "printf")
                return PRINTF_ENUM :: PRINT_F;
            
            else if(command == "(")
                return PRINTF_ENUM :: LEFT_PARENTHESIS;
            
            else if(command == "beginning quotation")
                return PRINTF_ENUM :: BEGINNING_QUOTATION;
            
            else if(command == "scan string")
                return PRINTF_ENUM :: SCANNING_STRING;
            
            else if(command == "end scanning")
                return PRINTF_ENUM :: END_SCANNING;
            
            else if(command == "end quotation")
                return PRINTF_ENUM :: END_QUOTATION;
            
            else if(command == ")")
                return PRINTF_ENUM :: RIGHT_PARENTHESIS;
            
            else if(command == ",")
                return PRINTF_ENUM :: COMMA;
            
            else if(command == ";")
                return PRINTF_ENUM :: SEMICOLON;
            
            else if(command == "reset")
                return PRINTF_ENUM :: RESET;
            
            return PRINTF_ENUM :: ERROR;
            
        }
        
        // ----------------------------------------------------------
        // Used for the purpose of configuring the values of each flag.
        void Configure_Flags(PRINTF_ENUM enum_propery)
        {
            switch(enum_propery)
            {
                case PRINT_F:
                    
                    if(this -> is_print_f == false)
                    {
                        Reset();
                        this -> is_print_f = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_print_f is already set to true\n");
                    
                    break;
                    
                case LEFT_PARENTHESIS:
                    
                    if(this -> is_left_paranthesis == false)
                    {
                        Reset();
                        this -> is_left_paranthesis = true;
                    }
                    else
                        throw std::invalid_argument("\nError - is_left_paranthesis is already set to true\n");
                    
                    break;
                    
                case BEGINNING_QUOTATION:
                    
                    if(this -> is_beginning_quotation == false)
                    {
                        Reset();
                        this -> is_beginning_quotation = true;
                    }
                    
                    else
                        throw std::invalid_argument("\nError - is_beginning_quotation is already set to true\n");
                    
                    break;
                    
                case SCANNING_STRING:
                    
                    if(this -> is_scanning_string == false)
                    {
                        Reset();
                        this -> is_scanning_string = true;
                    }
                    
                    else
                        throw std::invalid_argument("\nError - is_scanning_string is already set to true\n");
                    
                    break;
                    
                case END_QUOTATION:
                    
                    if(this -> is_end_quotation == false)
                    {
                        Reset();
                        this -> is_end_quotation = true;
                    }
                    
                    else
                        throw std::invalid_argument("\nError - is_end_quotation is already set to true\n");
                    break;
                    
                    
                case END_SCANNING:
                    
                    if(this -> end_scanning == false)
                    {
                        Reset();
                        this -> end_scanning = true;
                    }
                    
                    else
                        throw std::invalid_argument("\nError - end_scanning is already set to true\n");
                    break;
                    
                    
                case RIGHT_PARENTHESIS:
                    
                    if(this -> is_right_paranthesis == false)
                    {
                        Reset();
                        this -> is_right_paranthesis = true;
                    }
                    
                    else
                        throw std::invalid_argument("\nError - is_right_paranthesis is already set to true\n");
                    
                    break;
                    
                case COMMA:
                    
                    if(this -> is_comma == false)
                    {
                        Reset();
                        this -> is_comma = true;
                    }
                    
                    else
                        throw std::invalid_argument("\nError - is_comma is already set to true\n");
                    
                    break;
                    
                case SEMICOLON:
                    
                    if( this -> is_semicolon == false)
                    {
                        Reset();
                        this -> is_semicolon = true;
                    }
                    
                    else
                        throw std::invalid_argument("\nError - is_semicolon is already set to true\n");
                    
                    break;
                    
                case RESET:
                    
                    Reset();
                    
                    break;
                    
                case ERROR:
                    throw std::invalid_argument("\nError - configuration not found\n");
                    
            }
        }
        // ----------------------------------------------------------
        // Used to verify the boolean status of each flag.
        bool Verify_Flag(PRINTF_ENUM enum_propery, char * command)
        {
            switch(enum_propery)
            {
                case PRINT_F:
                    
                    if(is_print_f)
                        return true; return false;
                    
                case LEFT_PARENTHESIS:
                    
                    if(is_left_paranthesis)
                        return true; return false;
                    
                case BEGINNING_QUOTATION:
                    
                    if(is_beginning_quotation)
                        return true; return false;
                    
                case SCANNING_STRING:
                    
                    if(is_scanning_string)
                        return true; return false;
                    
                case END_SCANNING:
                    
                    if(end_scanning)
                        return true; return false;
                    
                case END_QUOTATION:
                    
                    if(is_end_quotation)
                        return true; return false;
                    
                case RIGHT_PARENTHESIS:
                    
                    if(is_right_paranthesis)
                        return true; return false;
                    
                case COMMA:
                    
                    if(is_comma)
                        return true; return false;
                    
                case SEMICOLON:
                    
                    if(is_semicolon)
                        return true; return false;
                    
                case ERROR:
                    throw std::invalid_argument("\nError - boolean command " + std::string(command) + " not detected\n");
            }
            
            return false;
        }
        // ----------------------------------------------------------
        // Used to prevent command from being case sensetive
        void LowerCase(std::string &command)
        {
            for(int i = 0; i < command.size(); i++)
                command[i] = tolower(command[i]);
        }
        
        // ----------------------------------------------------------
        // Used to reset values of all flags
        void Reset()
        {
            this -> is_print_f = false;
            this -> is_left_paranthesis = false;
            this -> is_beginning_quotation = false;
            this -> is_scanning_string = false;
            this -> end_scanning = false;
            this -> is_end_quotation = false;
            this -> is_right_paranthesis = false;
            this -> is_comma = false;
            this -> is_semicolon = false;
            
        }
        // ----------------------------------------------------------
        // Determines if PRINTF_HANDLER contains any true boolean variables
        bool isTrue()
        {
            // Declare array which holds all flags
            printf_bool printf_array [] = {
                is_print_f,
                is_left_paranthesis,
                is_beginning_quotation,
                is_scanning_string,
                end_scanning,
                is_end_quotation,
                is_right_paranthesis,
                is_comma,
                is_semicolon,
            };
            
            for(int i = 0; i < sizeof(printf_array)/sizeof(printf_array[0]); i++)
                if(printf_array[i] == true)
                    return true;
            
            return false;
        }
        
        // Deconstructor
        ~ PRINTF_HANDLER() = default;
        
    }isPrintF;
    
    // ----------------------------------------------------------------------------------------------------
    // Facilitates the boolean mechanics anytime a procedure is detected
    struct PROCEDURE_HANDLER
    {
        // Enums used to represent each property of a particular procedure
        enum PROCEDURE_PROPERTIES
        {
            PROCEDURE_NAME,
            
            MAIN,
            VOID,
            
            LEFT_PARENTHESIS,
            DATA_TYPE,
            VARIABLE,
            COMMA,
            RIGHT_PARENTHESIS
        };
        
        // Declare boolean varialble when procedure is found
        procedure_bool found_procedure;
        
        // Determines if a regular procedure or a main procedure was detected
        procedure_bool is_procedure, is_main;
        
        // Declare boolean variables used for regular procedure and main procedure
        procedure_bool found_left_parenthesis, found_procedure_name, found_right_parenthesis;
        
        // Declare boolean variables used for regular procedure
        procedure_bool found_data_type, found_variable, found_comma;
        
        // Declare boolean variables used for main procedure
        procedure_bool found_main, found_void;
        
        // Default Constructor
        PROCEDURE_HANDLER() :
        
        // Determines if a 'procedure' was detected
        found_procedure(false),
        
        // Determines if a main or regular procedure has been detected
        is_procedure(false),
        is_main(false),
        
        // Declare boolean variables used for customized procedure and main procedure
        found_procedure_name(false),
        found_left_parenthesis(false),
        found_data_type(false),
        found_variable(false),
        found_comma(false),
        found_right_parenthesis(false),
        found_main(false),
        found_void(false) {}
        
        // --------------------------------------------------------------------
        // Splits command into two separate parts
        std::pair<std::string,std::string> Execute_Command(std::string command)
        {
            // Used to collect each half of string
            std::string collectString = "";
            
            // Determines if more than one split is identified
            bool isSplit = false;
            
            // Pair which contains procedure type and type of property to execute
            std::pair<std::string,std::string> procedureCommand;
            
            for(int i = 0; i < command.size(); i++)
            {
                if(command[i] != ' ')
                    collectString += command[i];
                else if (command[i] == ' ')
                {
                    if(!isSplit)
                    {
                        isSplit = true;
                        procedureCommand.first = collectString;
                        collectString = "";
                    }
                    else
                        throw std::invalid_argument("\nError - invalid command\n\n");
                }
                else if(command.size() - i == 1)
                    procedureCommand.second = collectString;
                
            }
            return procedureCommand;
        }
        
        // Return enum value of paramater type
        PROCEDURE_PROPERTIES Procedure_Type(std::string parmaterType)
        {
            if(parmaterType == "main" || parmaterType == "Main")
                return PROCEDURE_PROPERTIES :: MAIN;
            
            return PROCEDURE_PROPERTIES :: PROCEDURE_NAME;
        }
        
        // Return enum value of what procedure property to activate
        // PROCEDURE_PROPERTIES Paramater_Property(std::string property)
        // {
        
        // }
        
        // Assign value to procedure properties
        
        //Initiates found_procedure variable
        void operator()(bool found_procedure)
        {
            this -> found_procedure = found_procedure;
        }
        
        // Used to dictate which type of procedure is being utilized (paramaterized or main)
        void operator()(std::string command)
        {
            // command must begin with paramaterized or main followed by the bool variable it wishes to activated
            
        }
        
        
        
        
        // Determines if PROCEDURE_HANDLER contains any true boolean variables
        /*
         bool isTrue()
         {
         std::vector<bool>procedure_vector
         = {first,second,third,forth,fifth};
         
         for(int i = 0; i < 5; i++)
         if(procedure_vector[i])
         return true;
         
         return false;
         }
         */
        
        // Deconstructor
        ~ PROCEDURE_HANDLER() = default;
        
    }procedure_handler;
    
    // ----------------------------------------------------------------------
    
public:
    
    // Tokenization constructor
    Tokenize(std::vector<std::string> TestFiles);
    
    // Initates tokenization process
    void Execute();
    
    // Clear memory from all ADT'S
    void Clear();
    
    // Determines if file text is an identifier
    bool isIdentifier(std::ifstream &read);
    
    // Determines if file text is an identifier
    bool tokenIdentifier(std::ifstream &read);
    
    // Determines if a BNF token was read
    bool isToken(TOKEN_TYPE token);
    
    // Used to find if a string or int variable is present within an operation/equation
    bool findVariable(TOKEN_TYPE token);
    
    // Checks if isInteger boolean variable is currently set as 'true'
    void checkInteger(char character, std::ifstream &read);
    
    // Checks if isEqual boolean variable is currently set as 'true'
    void checkIsEqual(char character, std::ifstream &read);
    
    // Checks if isValue boolean variable is currently set as 'true'
    void checkIsValue(char character, std::ifstream &read);
    
    // Check if isPrintf boolean variable is currently set as 'true'
    void checkPrintF(char character, std::ifstream &read);
    
    // Check if isProecedure boolean varaible is currently set as 'true'
    void checkProcedure(char character, std::ifstream &read);
    
    // Verifies that each character is legally allowed to use
    char Verify_Character(char character, std::ifstream &read);
    
    // Handles input validation with Read_Character function
    char Verify_Character_Helper(char character, std::ifstream &read);
    
    // Reads characters to determine if a token is detected
    std::vector<std::pair<tokenType,token>> ReadFile(std::ifstream &read);
    
    // Determines if a token being read
    TOKEN_TYPE Read_Token(std::ifstream &read);
    
    // Determines if a token is being read, used specifically for bool isToken
    TOKEN_TYPE isTokenHelper(std::ifstream &read);
    
    // Consists of all necessary handlers
    std::pair<std::string, std::string> Token_Handler(TOKEN_TYPE token, std::ifstream &read);
    
    // Output Tokenize object
    friend std::ostream & operator << (std::ostream &, Tokenize &);
    
};

#endif
