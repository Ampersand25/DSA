#pragma once
#include "MD.h"

class MD;

class IteratorMD
{
	friend class MD;

private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMD(const MD& c);

	//contine o referinta catre containerul pe care il itereaza
	const MD& md;

	/* aici e reprezentarea  specifica a iteratorului */

	int idx; // locatia (indice) in tabela de dispersie
	int pos; // pozitia valorii curente asociate cheii de la pozitia/locatia idx din tabela

	void deplasare(); // metoda privata care pozitioneaza indicele idx pe urmatoarea pozitie ocupata din tabela (prima pozitie ocupata dupa pozitia pe care se afla iteratorul in container)

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
	TElem element() const;
};