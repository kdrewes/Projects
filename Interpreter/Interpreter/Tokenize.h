

#ifndef Tokenize_hpp
#define Tokenize_hpp
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <stack>
#include "removeComments.h"

// Rename string data types for organizational purposes
typedef std::string fileName, tokenType, token;

// Rename integer data types for organization purposes
typedef int iterator, position;

// Rename bool data types for organization purposes
typedef bool boolean, integer_bool, value_bool, printf_bool, procedure_bool;

// Rename ifstream data type for organizational purposes
typedef std::ifstream readDataType;

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
    INTEGER,
    STRING,
    CHAR,
    BNF_IN_PROCESS,
    NON_BNF,
    ERROR
};

class Tokenize
{
private:
    
    // Test file vector
    std::vector<fileName> TestFiles;
    
    // Collects int datatype
    std::vector <std::string> integerCollector,
    
    // Collects string datatype
    stringCollector,
    
    // Collects char datatype
    charCollector,
    
    // Collects int arguments from procedure
    integerArgCollector,
    
    // Collects string arguments from procedure
    stringArgCollector,
    
    // Collects char arguments from procedure
    charArgCollector,
    
    // Collects procedures/functions
    procedureCollector;
    
    // Vector used to collect tokens from each file
    std::vector<std::vector<std::pair<std::string,std::string>>>TokenVector;
    
    // Contains index of integer variable found
    position integer_index;
    
    // Contains index of string variable found
    position string_index;
    
    // Contains index of char variable found
    position char_index;
    
    // Contains index of integer argument found
    position integer_arg_index;
    
    // Contains index of string argument found
    position string_arg_index;
    
    // Contains index of char argument found
    position char_arg_index;
    
    // Contains index of procedure found
    position procedure_index;
    
    // Count the amount of character being used within printf statement
    iterator count_characters;
    
    // Variable used to collect character for each individual token
    token syntax;
    
    // Read variable used to read content from each file
    readDataType read;
    
    // For test purposes
    bool procedureTester;
    
    int procedureCounter;
    
    // -----------------------------------------------------------------------
    
    // Indicates an integer variable was detected
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
        
        bool is_data_type,
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
        
        // -----------------------------------------------------------------------
        // Determine if boolean property exists in INTEGER_HANDLER
        integer_bool operator()(char * command)
        {
            return Verify_Flag(Enum_Handler(command), command);
        }
        
        // -----------------------------------------------------------------------
        // Determine if there is a true boolean member within INTEGER_HANDLER
        integer_bool operator()()
        {
            return ContainsTrueFlag();
        }
        
        // -----------------------------------------------------------------------
        // Used to determine the correct enum object to utilize
        INTEGER_ENUM Enum_Handler(std::string command)
        {
            // Prevents command from being case sensetive
            //LowerCase(command);
            
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
        
        // -----------------------------------------------------------------------
        // Used for the purpose of configuring the values of each flag.
        void Configure_Flags(INTEGER_ENUM enumObject)
        {
            switch(enumObject)
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
        
        // -----------------------------------------------------------------------
        // Used to verify the status of each flag.
        integer_bool Verify_Flag(INTEGER_ENUM enum_propery, char * command)
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
                    
                case ERROR:
                    throw std::invalid_argument("\nError - boolean command " + std::string(command) + " not detected\n");
            }
            
            return false;
        }
        // -----------------------------------------------------------------------
        // Used to prevent command from being case sensetive
        void LowerCase(std::string &command)
        {
            for(int i = 0; i < command.size(); i++)
                command[i] = tolower(command[i]);
        }
        
        // -----------------------------------------------------------------------
        // Used to reset values of all flags
        void Reset()
        {
            this -> is_data_type = false;
            this -> is_value = false;
            this -> is_assignment_operator = false;
        }
        
        // -----------------------------------------------------------------------
        // Determines if VALUE_HANDLER contains any true boolean variables
        integer_bool ContainsTrueFlag()
        {
            // Declare array which holds all flags
            integer_bool integerArray [] =
            {
                
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
    
    // -----------------------------------------------------------------------
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
        
        // -----------------------------------------------------------------------
        // Declare boolean variable for VALUE_HANDLER
        value_bool is_equal,
        is_integer,
        is_semicolon;
        
        // -----------------------------------------------------------------------
        // Declare paramatarized constructor
        VALUE_HANDLER() :
        is_equal(false),
        is_integer(false),
        is_semicolon(false) {}
        
        // -----------------------------------------------------------------------
        // Modifies boolean values which belong to VALUE_HANDLER
        void operator()(std::string command)
        {
            Configure_Flags(Enum_Handler(command));
        }
        
        // -----------------------------------------------------------------------
        // Determine if boolean property is exists in VALUE_HANDLER
        value_bool operator()(char * command)
        {
            return Verify_Flag(Enum_Handler(command), command);
        }
        
        // -----------------------------------------------------------------------
        // Determine if there is a true boolean member contained in VALUE_HANDLER
        value_bool operator()()
        {
            return ContainsTrueFlag();
        }
        
        // -----------------------------------------------------------------------
        // Used to determine the correct enum object to utilize
        VALUE_ENUM Enum_Handler(std::string command)
        {
            // Prevents command from being case sensetive
            //LowerCase(command);
            
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
        
        // -----------------------------------------------------------------------
        // Used for the purpose of configuring the values of each flag.
        void Configure_Flags(VALUE_ENUM enumObject)
        {
            switch(enumObject)
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
        
        // -----------------------------------------------------------------------
        // Used to verify the status of each flag.
        value_bool Verify_Flag(VALUE_ENUM enumObject, char * command)
        {
            switch(enumObject)
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
        
        // -----------------------------------------------------------------------
        // Used to prevent command from being case sensetive
        void LowerCase(std::string &command)
        {
            for(int i = 0; i < command.size(); i++)
                command[i] = tolower(command[i]);
        }
        
        // -----------------------------------------------------------------------
        // Used to reset values of all flags
        void Reset()
        {
            this -> is_equal = false;
            this -> is_integer = false;
            this -> is_semicolon = false;
        }
        
        // -----------------------------------------------------------------------
        // Determines if VALUE_HANDLER contains any true boolean variables
        value_bool ContainsTrueFlag()
        {
            // Declare array which holds all flags
            value_bool valueArray [] = {
                
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
    
    // -----------------------------------------------------------------------
    /*  Facilitates the boolean mechanics anytime a procedure is detected
     Indicates aa printf command was detected.
     Content in quotation marks will return a string.
     */
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
        
        // -----------------------------------------------------------------------
        
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
        
        // -----------------------------------------------------------------------
        
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
        
        // -----------------------------------------------------------------------
        // Modifies boolean values which belong to PRINTF_HANDLER
        void operator()(std::string command)
        {
            Configure_Flags(Enum_Handler(command));
        }
        
        // -----------------------------------------------------------------------
        // Determine if boolean property is exists in PRINTF_HANDLER
        printf_bool operator()(char * command)
        {
            return Verify_Flag(Enum_Handler(command), command);
        }
        
        // -----------------------------------------------------------------------
        // Determine if there is a true boolean member contained in PRINTF_HANDLER
        printf_bool operator()()
        {
            return ContainsTrueFlag();
        }
        
        // -----------------------------------------------------------------------
        // Determines correct enum object to utilize
        PRINTF_ENUM Enum_Handler(std::string command)
        {
            // Used to prevent command from being case sensetive
            // LowerCase(command);
            
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
        
        // -----------------------------------------------------------------------
        // Used for the purpose of configuring the values of each flag.
        void Configure_Flags(PRINTF_ENUM enumObject)
        {
            switch(enumObject)
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
        
        // -----------------------------------------------------------------------
        // Used to verify the boolean status of each flag
        printf_bool Verify_Flag(PRINTF_ENUM enumObject, char * command)
        {
            switch(enumObject)
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
        
        // -----------------------------------------------------------------------
        // Used to prevent command from being case sensetive
        void LowerCase(std::string &command)
        {
            for(int i = 0; i < command.size(); i++)
                command[i] = tolower(command[i]);
        }
        
        // -----------------------------------------------------------------------
        // Resets values of all flags
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
        
        // -----------------------------------------------------------------------
        // Determines if PRINTF_HANDLER contains any true boolean variables
        printf_bool ContainsTrueFlag()
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
        enum PROCEDURE_ENUM
        {
            PROCEDURE,
            REGULAR_PROCEDURE,
            MAIN,
            VOID,
            LEFT_PARENTHESIS,
            RIGHT_PARENTHESIS,
            LEFT_PARENTHESIS_MAIN,
            RIGHT_PARENTHESIS_MAIN,
            DATA_TYPE,
            INTEGER,
            CHAR,
            STRING,
            VARIABLE,
            COMMA,
            RESET,
            IN_PROCESS,
            SEARCHING_FOR_LEFT_PARENTHESIS,
            SEARCHING_FOR_RIGHT_PARENTHESIS,
            LEFT_PARENTHESIS_DETECTED,
            RIGHT_PARENTHESIS_DETECTED,
            SEARCHING_FOR_LEFT_PARENTHESIS_MAIN,
            SEARCHING_FOR_RIGHT_PARENTHESIS_MAIN,
            LEFT_PARENTHESIS_DETECTED_MAIN,
            RIGHT_PARENTHESIS_DETECTED_MAIN,
            ERROR
        };
        
        // Declare boolean varialble when procedure is found
        bool is_procedure;
        
        // Declare boolean variables used for regular procedure and main procedure
        bool is_regular_procedure,
             is_left_parenthesis,
             is_data_type,
             is_variable,
             is_comma,
             is_right_parenthesis;
        
        // Declare boolean variables used for main procedure
        bool is_main,
             is_void,
             is_left_parenthesis_main,
             is_right_parenthesis_main;
        
        // Declare boolean variable used to determine tenetive outcomes for regular procedure
        bool searching_for_left_parenthesis,
             searching_for_right_parenthesis,
             left_parenthesis_detected,
             right_parenthesis_detected;
        
        // Declare boolean variable used to determine tenetive outcomes for main procedure
        bool searching_for_left_parenthesis_main,
             searching_for_right_parenthesis_main,
             left_parenthesis_detected_main,
             right_parenthesis_detected_main;
        
        
        // Record the last datatype used when PROCEDURE_ENUM :: DATA_TYPE is detected
        std::string saveDataType;
        
        // Record name of argument when PROCEDURE_ENUM :: VARIABLE is detected
        std::string argument;
        
        // Default Constructor
        PROCEDURE_HANDLER() :
        
        // Determines if a main or regular procedure has been detected
        is_procedure(false),
        is_main(false),
        
        // Declare boolean variables used for customized procedure and main procedure
        is_regular_procedure(false),
        is_left_parenthesis(false),
        is_right_parenthesis(false),
        is_left_parenthesis_main(false),
        is_right_parenthesis_main(false),
        is_data_type(false),
        is_variable(false),
        is_comma(false),
        is_void(false),
        
        // Declare boolean variables used for tenetive scenarios in regular function
        searching_for_left_parenthesis(false),
        searching_for_right_parenthesis(false),
        left_parenthesis_detected(false),
        right_parenthesis_detected(false),
        
        // Declare boolean variables used for tenetive scenarios in main function
        searching_for_left_parenthesis_main(false),
        searching_for_right_parenthesis_main(false),
        left_parenthesis_detected_main(false),
        right_parenthesis_detected_main(false),
        
        // Initialize tenetive variables
        saveDataType(""),
        argument("")
        
        {}
        
        // Collects int datatype
        std::vector <std::string> integerCollector,
        
        // Collects string datatype
        stringCollector,
        
        // Collects char datatype
        charCollector;
        
        //-----------------------------------------------------------------------
        // Modifies boolean values which belong to PROCEDURE_HANDLER
        void operator()(std::string command)
        {

            return Configure(Enum_Handler(command), command);
        }
        
        // -----------------------------------------------------------------------
        // Determines correct enum object to use
        PROCEDURE_ENUM Enum_Handler(std::string command)
        {
            // Prevents 'command' from being case sensetive
            // LowerCase(command);
            
            if(command == "is procedure" ||
               command == "procedure" ||
               command == "function")
                return PROCEDURE_ENUM :: PROCEDURE;
            
            else if(command == "procedure name" ||
                    command == "name" ||
                    command == "is regular function" ||
                    command == "regular function" ||
                    command == "is regular procedure")
                return PROCEDURE_ENUM :: REGULAR_PROCEDURE;
            
            else if(command == "is main" ||
                    command == "main")
                return PROCEDURE_ENUM :: MAIN;
            
            else if((command == "is void" ||
                     command == "void") &&
                     is_main)
                return PROCEDURE_ENUM :: VOID;
            
            else if((command == "(" ||
                     command == "left parenthesis" ||
                     command == "comma detected") &&
                     is_regular_procedure)
                return PROCEDURE_ENUM :: LEFT_PARENTHESIS;
            
            else if((command == "(" ||
                     command == "left parenthesis") &&
                     is_main)
                return PROCEDURE_ENUM :: LEFT_PARENTHESIS_MAIN;
            
            else if((command == ")" ||
                     command == "right parenthesis")  &&
                     is_regular_procedure)
                return PROCEDURE_ENUM :: RIGHT_PARENTHESIS;
            
            else if((command == ")" ||
                     command == "right parenthesis") &&
                     is_main)
                return PROCEDURE_ENUM :: RIGHT_PARENTHESIS_MAIN;
            
            else if(((command == "is data type" ||
                      command == "is datatype" ||
                      command == "is detecting variable" ||
                      command == "detecting variable") ||
                      searchForDataType(command)) &&
                      is_regular_procedure)
                return PROCEDURE_ENUM :: DATA_TYPE;
            
            else if(((command == "is variable" ||
                      command == "variable") ||
                      searchForVariable(command)) &&
                      is_regular_procedure)
                return PROCEDURE_ENUM :: VARIABLE;
            
            else if((command == "," ||
                     command == "comma") &&
                     is_regular_procedure)
                return PROCEDURE_ENUM :: COMMA;
            
            else if((command == "scanning for left parenthesis" ||
                    command == "searching for left parenthesis" ||
                    command == "scanning for (" ||
                    command == "searching for (") &&
                    is_regular_procedure)
                return PROCEDURE_ENUM :: SEARCHING_FOR_LEFT_PARENTHESIS;
            
            
            else if((command == "scanning for right parenthesis" ||
                    command == "searching for right parenthesis" ||
                    command == "scanning for )" ||
                    command == "searching for )") &&
                    is_regular_procedure)
                return PROCEDURE_ENUM :: SEARCHING_FOR_RIGHT_PARENTHESIS;
            
            else if((command == "found left parenthesis" ||
                    command == "left parenthesis detected" ||
                    command == "found (") &&
                    is_regular_procedure)
                return PROCEDURE_ENUM :: LEFT_PARENTHESIS_DETECTED;
            
            else if((command == "found right parenthesis" ||
                    command == "right parenthesis detected" ||
                    command == "found )") &&
                    is_regular_procedure)
                return PROCEDURE_ENUM :: RIGHT_PARENTHESIS_DETECTED;
            
            else if((command == "scanning for left parenthesis" ||
                    command == "searching for left parenthesis" ||
                    command == "scanning for (" ||
                    command == "searching for (") &&
                    is_main)
                return PROCEDURE_ENUM :: SEARCHING_FOR_LEFT_PARENTHESIS_MAIN;
            
            else if((command == "scanning for right parenthesis" ||
                    command == "searching for right parenthesis" ||
                    command == "scanning for )" ||
                    command == "searching for )") &&
                    is_main)
                return PROCEDURE_ENUM :: SEARCHING_FOR_RIGHT_PARENTHESIS_MAIN;
            
            else if((command == "found left parenthesis" ||
                    command == "left parenthesis detected" ||
                    command == "found (") &&
                    is_main)
                return PROCEDURE_ENUM :: LEFT_PARENTHESIS_DETECTED_MAIN;
            
            else if((command == "found right parenthesis" ||
                    command == "right parenthesis detected" ||
                    command == "found )") &&
                    is_main)
                return PROCEDURE_ENUM :: RIGHT_PARENTHESIS_DETECTED_MAIN;
            
            
            else if(command == "reset")
                return PROCEDURE_ENUM :: RESET;
            
            return PROCEDURE_ENUM :: ERROR;
        }
        
        // -----------------------------------------------------------------------
        // Determines type of procedure being utilized (ex - regular function or main)
        PROCEDURE_ENUM ProcedureType()
        {
            if(is_procedure)
                return PROCEDURE_ENUM :: PROCEDURE;
            
            else if(is_main)
                return PROCEDURE_ENUM :: MAIN;
            
            else if(is_regular_procedure)
                return PROCEDURE_ENUM :: REGULAR_PROCEDURE;
            
            return PROCEDURE_ENUM :: IN_PROCESS;
            
        }
        
        // -----------------------------------------------------------------------
        // Determine the correct data type utlized
        PROCEDURE_ENUM dataType(std::string command)
        {
            if(command == "int")
                return PROCEDURE_ENUM :: INTEGER;
            
            if(command == "char")
                return PROCEDURE_ENUM :: CHAR;
            
            if(command == "string")
                return PROCEDURE_ENUM :: STRING;
            
            return PROCEDURE_ENUM :: ERROR;
        }
        
        // -----------------------------------------------------------------------
        // Determine if boolean property is exists in PROCEDURE_HANDLER
        procedure_bool operator()(char * command)
        {
            return Verify_Flag(Enum_Handler(command), ProcedureType() ,command);
        }
        
        // -----------------------------------------------------------------------
        // Determine if there is a true boolean member contained in PROCEDURE_HANDLER
        procedure_bool operator()()
        {
            return ContainsTrueFlag();
        }
        
        // -----------------------------------------------------------------------
        // Used to modify boolean flags
        void Configure(PROCEDURE_ENUM enumObject, std::string command)
        {
            // Stores boolean members specifically related to is_procedure property
            ConfigureProcedure (enumObject, command);
            
            // Stores boolean members specifically related to is_void_function property
            ConfigureProcedureFunction (enumObject, command);
            
            // Stores boolean members specifically related to is_main property
            ConfigureMain (enumObject, command);
        }
        
        // -----------------------------------------------------------------------
        // Stores boolean members specifically related to is_procedure property
        void ConfigureProcedure(PROCEDURE_ENUM enumObject, std::string command)
        {
            if(!is_regular_procedure && !is_main)
            {
                switch(enumObject)
                {
                    case PROCEDURE:
                        
                        if(!is_procedure)
                            is_procedure = true;
                        
                        else
                            throw std::invalid_argument("\nError - is_procedure is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case MAIN:
                        
                        if(!is_main)
                        {
                            Reset();
                            
                            is_main = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_main is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case REGULAR_PROCEDURE:
                        
                        if(!is_regular_procedure)
                        {
                            Reset();
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_void_function is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case ERROR:
                        
                        throw std::invalid_argument("\nError - " + command + " is not a valid command\n");
                        
                        break;
                        
                }
            }
        }
        
        // -----------------------------------------------------------------------
        // Stores boolean members specifically related to is_void_function property
        void ConfigureProcedureFunction(PROCEDURE_ENUM enumObject, std::string command)
        {
            if(is_regular_procedure)
            {
                switch(enumObject)
                {
                    case LEFT_PARENTHESIS:
                        
                        if(!is_left_parenthesis)
                        {
                            Reset();
                            
                            is_left_parenthesis = true;
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_left_parenthesis is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case DATA_TYPE:
                        
                        if(!is_data_type)
                        {
                            Reset();
                            
                            this -> saveDataType = disectDataType(command).second;
                            
                            is_data_type = true;
                            
                            is_regular_procedure = true;
                        }
                        else
                            throw std::invalid_argument("\nError - is_data_type is already set to true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case VARIABLE:
                        
                        if(!is_variable)
                        {
                            Reset();
                            
                            is_variable = true;
                            
                            is_regular_procedure = true;
                            
                            storeArgument();
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_variable is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case COMMA:
                        
                        if(!is_comma)
                        {
                            Reset();
                            
                            is_comma = true;
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_comma is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS:
                        
                        if(!is_right_parenthesis)
                        {
                            Reset();
                            
                            is_right_parenthesis = true;
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_right_parenthesis is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_LEFT_PARENTHESIS:
                        
                        if(!searching_for_left_parenthesis)
                        {
                            Reset();
                            
                            searching_for_left_parenthesis = true;
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - searching_for_left_parenthesis is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_RIGHT_PARENTHESIS:
                        
                        if(!searching_for_right_parenthesis)
                        {
                            Reset();
                            
                            searching_for_right_parenthesis = true;
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - searching_for_right_parenthesis is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case LEFT_PARENTHESIS_DETECTED:
                        
                        if(!left_parenthesis_detected)
                        {
                            Reset();
                            
                            left_parenthesis_detected = true;
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - left_parenthesis_detected is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS_DETECTED:
                        
                        if(!right_parenthesis_detected)
                        {
                            Reset();
                            
                            right_parenthesis_detected = true;
                            
                            is_regular_procedure = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - right_parenthesis_detected is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case RESET:
                        
                        Reset();
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case ERROR:
                        
                        throw std::invalid_argument("\n\nError - " + command + " is not a valid command\n");
                        
                }
            }
        }
        
        // -----------------------------------------------------------------------
        // Stores boolean members specifically related to is_main property
        void ConfigureMain(PROCEDURE_ENUM enumObject, std::string command)
        {
            if(is_main)
            {
                switch(enumObject)
                {
                    case LEFT_PARENTHESIS_MAIN:
                        
                        if(!is_left_parenthesis_main)
                        {
                            Reset();
                            
                            is_left_parenthesis_main = true;
                            
                            is_main = true;
                            
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_left_parenthesis_main is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case VOID:
                        
                        if(!is_void)
                        {
                            Reset();
                            
                            is_void = true;
                            
                            is_main = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_void is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS_MAIN:
                        
                        if(!is_right_parenthesis_main)
                        {
                            Reset();
                            
                            is_right_parenthesis_main = true;
                            
                            is_main = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - is_right_parenthesis_main is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_LEFT_PARENTHESIS_MAIN:
                        
                        if(!searching_for_left_parenthesis_main)
                        {
                            Reset();
                            
                            searching_for_left_parenthesis_main = true;
                            
                            is_main = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - searching_for_left_parenthesis_main is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_RIGHT_PARENTHESIS_MAIN:
                        
                        if(!searching_for_right_parenthesis_main)
                        {
                            Reset();
                            
                            searching_for_right_parenthesis_main = true;
                            
                            is_main = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - searching_for_right_parenthesis_main is already true\n");
                        
                        break;
                        // -------------------------------------------------
                        
                    case LEFT_PARENTHESIS_DETECTED_MAIN:
                        
                        if(!left_parenthesis_detected_main)
                        {
                            Reset();
                            
                            left_parenthesis_detected_main = true;
                            
                            is_main = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - left_parenthesis_detected_main is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS_DETECTED_MAIN:
                        
                        if(!right_parenthesis_detected_main)
                        {
                            Reset();
                            
                            right_parenthesis_detected_main = true;
                            
                            is_main = true;
                        }
                        
                        else
                            throw std::invalid_argument("\nError - right_parenthesis_right_parenthesis_detected_main detected is already true\n");
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case RESET:
                        
                        Reset();
                        
                        break;
                        
                        // -------------------------------------------------
                        
                    case ERROR:
                        
                        throw std::invalid_argument("\nError - " + command + " is not a valid command\n");
                        
                        // -------------------------------------------------
                }
            }
        }
        
        // -----------------------------------------------------------------------
        // Collects argument of applicable datatype
        void storeArgument()
        {
            switch(dataType(this -> saveDataType))
            {
                case INTEGER:

                    integerCollector.push_back(argument);
                    
                    break;
                    
                case STRING:
                    
                    stringCollector.push_back(argument);
                    
                    break;
                    
                case CHAR:
                    
                    charCollector.push_back(argument);
                    
                    break;

                case ERROR:
                    throw std::invalid_argument("\n\nError - " + std::string(this -> saveDataType) + " is an invalid data type " + "\n\n");

            }
            
            argument = "";
        }
        // -----------------------------------------------------------------------
        // Used to verify the boolean status of each flag.
        bool Verify_Flag(PROCEDURE_ENUM enumObject, PROCEDURE_ENUM procedureType, std::string command)
        {
            switch(procedureType)
            {
                case PROCEDURE:
                    
                    if(VerifyProcedure(enumObject, command))
                        return true; return false;
                    
                case REGULAR_PROCEDURE:
                    
                    if(VerifyRegularFunction(enumObject, command))
                        return true; return false;
                    
                case MAIN:
                    
                    if(VerifyMain(enumObject, command))
                        return true; return false;
            }
            
            return false;
        }
        
        // -----------------------------------------------------------------------
        // Used to verify the boolean status related to is_procedure property
        procedure_bool VerifyProcedure(PROCEDURE_ENUM enumObject, std::string command)
        {
            if(!is_regular_procedure && !is_main)
            {
                switch(enumObject)
                {
                    case PROCEDURE:
                        
                        if(is_procedure)
                            return true; return false;
                        
                        
                    case ERROR:
                        
                        throw std::invalid_argument("\nError - " + command + " is not a valid boolean command\n");
                }
            }
            
            return false;
        }
        
        // -----------------------------------------------------------------------
        // Used to verify the boolean status related to is_void_function property
        procedure_bool VerifyRegularFunction(PROCEDURE_ENUM enumObject, std::string command)
        {
            if(is_regular_procedure)
            {
                switch(enumObject)
                {
                    case REGULAR_PROCEDURE:
                        
                        if(is_regular_procedure)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case LEFT_PARENTHESIS:
                        
                        if(is_left_parenthesis)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case DATA_TYPE:
                        
                        if(is_data_type)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case VARIABLE:
                        
                        if(is_variable)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case COMMA:
                        
                        if(is_comma)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS:
                        
                        if(is_right_parenthesis)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_LEFT_PARENTHESIS:
                        
                        if(searching_for_left_parenthesis)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_RIGHT_PARENTHESIS:
                        
                        if(searching_for_right_parenthesis)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case LEFT_PARENTHESIS_DETECTED:
                        
                        if(left_parenthesis_detected)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS_DETECTED:
                        
                        if(right_parenthesis_detected)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case ERROR:
                        
                        throw std::invalid_argument("\nError - " + command + " is not a valid boolean command\n");
                        
                        // -------------------------------------------------
                }
            }
            
            return false;
        }
        // -----------------------------------------------------------------------
        // Used to verify the boolean status related to is_main property
        procedure_bool VerifyMain(PROCEDURE_ENUM enumObject, std::string command)
        {
            if(is_main)
            {
                switch(enumObject)
                {
                    case MAIN:
                        
                        if(is_main)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case LEFT_PARENTHESIS_MAIN:
                        
                        if(is_left_parenthesis_main)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case VOID:
                        
                        if(is_void)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS_MAIN:
                        
                        if(is_right_parenthesis_main)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_LEFT_PARENTHESIS_MAIN:
                        
                        if(searching_for_left_parenthesis_main)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case SEARCHING_FOR_RIGHT_PARENTHESIS_MAIN:
                        
                        if(searching_for_right_parenthesis_main)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case LEFT_PARENTHESIS_DETECTED_MAIN:
                        
                        if(left_parenthesis_detected_main)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case RIGHT_PARENTHESIS_DETECTED_MAIN:
                        
                        if(right_parenthesis_detected_main)
                            return true; return false;
                        
                        // -------------------------------------------------
                        
                    case ERROR:
                        
                        throw std::invalid_argument("\nError - " + command + " is not a valid boolean command\n");
                        
                        // -------------------------------------------------
                }
            }
            
            return false;
        }
        
        // -----------------------------------------------------------------------
        // Used to prevent command from being case sensetive
        void LowerCase(std::string &command)
        {
            for(int i = 0; i < command.size(); i++)
                command[i] = tolower(command[i]);
        }
        
        // -----------------------------------------------------------------------
        // Resets values of all flags
        void Reset()
        {
            // Resets all values except is_procedure and is_main
            this -> is_procedure = false;
            
            // boolean members related to regular procedure
            this -> is_regular_procedure = false;
            this -> is_left_parenthesis = false;
            this -> is_right_parenthesis = false;
            this -> is_data_type = false;
            this -> is_variable = false;
            this -> is_comma = false;
            
            // boolean members related to main procedure
            this -> is_main = false;
            this -> is_left_parenthesis_main = false;
            this -> is_right_parenthesis_main = false;
            this -> is_void = false;
            
            // boolean members used for tenetive scenarios in regular function
            this -> searching_for_left_parenthesis = false;
            this -> searching_for_right_parenthesis = false;
            this -> left_parenthesis_detected = false;
            this -> right_parenthesis_detected = false;
            
            // boolean members used for tenetive scenarios in main function
            this -> searching_for_left_parenthesis_main = false;
            this -> searching_for_right_parenthesis_main = false;
            this -> left_parenthesis_detected_main = false;
            this -> right_parenthesis_detected_main = false;
            
        }
        
        // -----------------------------------------------------------------------
        // Determines if PROCEDURE_HANDLER contains any true boolean variables
        procedure_bool ContainsTrueFlag()
        {
            // Declare array which holds all flags
            procedure_bool procedure_array [] =
            {
                
                is_procedure,
                is_regular_procedure,
                is_left_parenthesis,
                is_data_type,
                is_variable,
                is_comma,
                is_right_parenthesis,
                is_main,
                is_left_parenthesis_main,
                is_void,
                is_right_parenthesis_main,
                searching_for_left_parenthesis,
                searching_for_right_parenthesis,
                left_parenthesis_detected,
                right_parenthesis_detected,
                searching_for_left_parenthesis_main,
                searching_for_right_parenthesis_main,
                left_parenthesis_detected_main,
                right_parenthesis_detected_main
            };
            
            for(int i = 0; i < sizeof(procedure_array)/sizeof(procedure_array[0]); i++)
                if(procedure_array[i] == true)
                    return true;
            
            return false;
        }
        
        // -----------------------------------------------------------------------
        // Determine if a datatype is present or not
        bool searchForDataType(std::string command)
        {
            std::string tempString = "";
            
            for(int i = 0; i < command.size(); i++)
            {
                if(command[i] == ' ')
                {
                    if(tempString == "datatype" || tempString == "data type")
                        return true;
                    
                    else
                        break;
                }
                
                tempString += std::tolower(command[i]);
            }
            
            return false;
        }
        
        // -----------------------------------------------------------------------
        // Determine if variable is present or not
        // If variable is found then modify its value
        bool searchForVariable(std::string command)
        {
            std::string tempString = "";
            
            int index = 0;
            
            bool isVariable = false;
            
            for(int i = 0; i < command.size(); i++)
            {
                if(command[i] == ' ')
                {
                    if(tempString == "variable")
                    {
                        tempString = "";
                        index = i + 1;
                        isVariable = true;
                        break;
                    }
                    
                    else
                        break;
                }
                
                tempString += std::tolower(command[i]);
            }
            
            // If variable is found then modify its value
            if(isVariable)
            {
                for(int i = index; i < command.size(); i++)
                    tempString += std::tolower(command[i]);
                
                this -> argument = tempString;;
                
                return true;
            }
            
            return false;
        }
        
        //-----------------------------------------------------------------------
        // Determins if string is data type
        std::pair<std::string, std::string> disectDataType(std::string command)
        {
            std::string tempString = "";
            
            std::pair<std::string, std::string> pairString;
            
            // Determines if the searchingForDataType condition should be executed
            bool searchingForDataType = true;
            
            // Determines if there is a space after datatype is detected
            bool isSpace = false;
            
            // Determines if actual datatype is being read
            bool isDataType = false;
            
            for(int i = 0; i < command.size(); i++)
            {
                if(command[i] != ' ')
                    tempString += command[i];
                
                if((tempString == "datatype" || tempString == "data type") && searchingForDataType)
                {
                    pairString.first = tempString;
                    tempString = "";
                    isSpace = true;
                    searchingForDataType = false;
                }
                
                else if(isSpace)
                {
                    if(command[i] == ' ')
                    {
                        isSpace = false;
                        continue;
                    }
                    else
                    {
                        throw std::invalid_argument("\n\nError - Space is not detected\n\n");
                    }
                    
                }
                
            }
            
            // Generate lowercase letters
            for(int i = 0; i < tempString.size(); i++)
                tempString[i] = std::tolower(tempString[i]);
            
            if(tempString == "int" || tempString == "char" || tempString == "string")
                isDataType = true;
            
            if(isDataType)
                pairString.second = tempString;
            
            else
                throw std::invalid_argument("\n\nError - " + std::string(tempString) + " is not a datatype\n\n");
            
            return pairString;
        }
        
        // Deconstructor
        ~ PROCEDURE_HANDLER() = default;
        
    }isProcedure;
    //-----------------------------------------------------------------------
    
public:
    
    // Tokenization constructor
    Tokenize(std::vector<std::string> TestFiles);
    
    // Initates tokenization process
    void Execute();
    
    // Clear memory from all ADT'S
    void Clear();
    
    // Determines if file text is an identifier
    bool isIdentifier();
    
    // Determines if file text is an identifier
    bool tokenIdentifier();
    
    // Determines if a BNF token was read
    bool isToken(TOKEN_TYPE token);
    
    // Determines if an integer variable is present within an operation/equation
    bool findInteger();
    
    // Determines if an string variable is present within an operation/equation
    bool findString();
    
    // Determines if an char variable is present within an operation/equation
    bool findChar();
    
    // Determines if an integer argument variable is present within a procedure
    bool findIntegerArg();
    
    // Determines if a string argument variable is present within a procedure
    bool findStringArg();
    
    // Determines if a char argument variable is present within a procedure
    bool findCharArg();
    
    // Determines if a procedure is present within an operation/equation
    bool findProcedure();
    
    // Checks if isInteger boolean variable is currently set as 'true'
    //void Configure_Integer(char character);
    
    // Checks if isValue boolean variable is currently set as 'true'
    //void Configure_Value(char character);
    
    // Check if isPrintf boolean variable is currently set as 'true'
    //void Configure_PrintF(char character);
    
    // Check if isProecedure boolean varaible is currently set as 'true'
    void Configure_Procedure(char character);
    
    // Assigns vector from PROCEDURE_HANDLER to private vectors located in Tokenize class
    void assignVector();
    
    // Filters out any syntax that contains the word 'procedure', used soely for test purposes
    bool FilterProcedure(std::string syntax);
    
    // Verifies that each character is legally allowed to use
    char Configure_Token(char character);
    
    // Handles input validation with Read_Character function
    char Configure_Token_Helper(char character);
    
    // Reads characters to determine if a token is detected
    std::vector<std::pair<tokenType,token>> ReadFile();
    
    // Determines if a token being read
    TOKEN_TYPE Read_Token();
    
    // Determines if a token is being read, used specifically for bool isToken
    TOKEN_TYPE isTokenHelper();
    
    // Determine datatype being used for the purpose of selecting which collector vector to utilize
    TOKEN_TYPE dataType(std::string command);
    
    // Consists of all necessary handlers
    std::pair<std::string, std::string> Token_Handler(TOKEN_TYPE token);
    
    // Return value of TokenVector
    std::vector<std::vector<std::pair<std::string,std::string>>>& GetTokenVector();
    
    // Output Tokenize object
    friend std::ostream & operator << (std::ostream &o, Tokenize &t);
    
    // std::ostream & operator helper function
    friend std::ostream & Print(std::ostream &output, Tokenize &token);
    
    // Allow PROCEDURE_HANDLER the authority to access class membersfrom Tokenize
    friend struct PROCEDURE_HANDLER;
    
};

#endif
