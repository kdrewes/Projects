#ifndef Miscellaneous_Data_h
#define Miscellaneous_Data_h

#include<iostream>
#include<sstream>
#include<vector>

// ------------------------------- Enums --------------------------------

// Cache Placement Policies in enum format
enum PLACEMENT_POLICY
{ FULLY_ASSOCIATED, SET_ASSOCIATED, DIRECT_MAPPED, EXIT, POLICY_ERROR };

// Stores all data in enum format
enum INPUT
{ CACHE_SIZE, BLOCK_SIZE, WAYS, MAIN_MEMORY, CACHING_ALGORITHM, INPUT_ERROR};

// Caching algorithms in enum format
enum CACHING_ALGORITHM
{ LRU, LFU, FIFO, ALGORITHMIC_ERROR };

#endif
