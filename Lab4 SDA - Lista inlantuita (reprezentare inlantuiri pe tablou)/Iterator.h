#pragma once

#include "LO.h"

class Iterator {
	friend class LO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const LO& lo);

	//contine o referinta catre containerul pe care il itereaza
	const LO& lo;

	/* aici e reprezentarea  specifica a iteratorului */

	int curent; // retinem pozitia curenta in interiorul listei - referinta la nodul curent din lista asociata

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElement element() const;
};