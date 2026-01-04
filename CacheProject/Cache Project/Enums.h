#ifndef Enums_h
#define Enums_h

#include<iostream>
#include<sstream>
#include<vector>

// ------------------------------- Enums --------------------------------

// Configuration in enum format
enum CONFIGURATION
{ MANUAL, AUTOMATED, CONFIGURATION_ERROR };

// Cache Placement Policies in enum format
enum PLACEMENT_POLICY
{ FULLY_ASSOCIATED, SET_ASSOCIATED, DIRECT_MAPPED, EXIT, POLICY_ERROR };

// Stores all input data in enum format
enum INPUT
{ CACHE_SIZE, BLOCK_SIZE, WAYS, MAIN_MEMORY, CACHING_ALGORITHM, INPUT_ERROR };

// Caching algorithms in enum format
enum CACHING_ALGORITHM
{ LRU, LFU, FIFO, ALGORITHMIC_ERROR };

// Fully Associative, Set associative and Direct Mapped column headers used in table
enum COLUMNS
{ ADDRESS, WAY, TAG, INDEX, OFFSET, HIT_MISS, WORD, INSTRUCTION_RETREIVED, EVICTIONS, COLUMN_ERROR };

// Hash table enum
enum HASH_TABLE
{ ADDRESS_TABLE, TAG_TABLE, INDEX_TABLE, HASH_TABLE_ERROR };

#endif

// -------------------------------------------------------------------------
