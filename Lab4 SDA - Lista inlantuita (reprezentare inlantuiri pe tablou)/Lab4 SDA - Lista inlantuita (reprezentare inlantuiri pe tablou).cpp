#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib> // #include <stdlib.h>
#include <crtdbg.h>

int main() {
    testAll();
    testAllExtins();
    std::cout << "Finished LI Tests!" << std::endl;
    
    _CrtDumpMemoryLeaks(); // testam aplicatia de memory leaks (leak-uri/scurgeri de memorie)
}