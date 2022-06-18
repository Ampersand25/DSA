#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;


int main() {



	testAll();
	testAllExtins();

	cout << "End";
	_CrtDumpMemoryLeaks();
}
