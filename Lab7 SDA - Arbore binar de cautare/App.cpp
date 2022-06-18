#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib> // #include <stdlib.h>
#include <crtdbg.h>

using namespace std;


int main() {
	// Timp total executie: 20 secunde (20.058 s)

	{
		testAll();
		testAllExtins();

		cout << "End";
	}

	_CrtDumpMemoryLeaks(); // testam aplicatia de memory leaks (leak-uri/scurgeri de memorie)
}