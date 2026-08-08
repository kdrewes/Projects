#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "Parse.hpp"
#include "Media.hpp"
#include "Book.hpp"
#include "Periodical.hpp"
#include "Film.hpp"
#include "Video.hpp"
#include "Enum.hpp"

// -------------------------------------------------------------------------------------------

int main(int argc, const char * argv[])
{
    // Call parse object
    Parse p;
    
    // Output parse object
    std::cout << p;
   
    return 0;
}
