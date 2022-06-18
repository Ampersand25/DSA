#pragma once
#include "Multime.h"

typedef int TElem;

class IteratorMultime
{
	friend class Multime;

private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);

	//contine o referinta catre containerul pe care il itereaza
	const Multime& mult;

	/* aici e reprezentarea  specifica a iteratorului */

	// atribute/campuri private (nu pot fi accesate din exteriorul clasei, ci doar din interiorul acesteia)
	TElem* values; // vector (tablou unidimensional in care retinem/stocam valorile/cheile din arbore)
	int dim;       // variabila de tip contor in care retinem numarul de noduri din ABC
	int idx;       // variabila de tip index in care retinem nodul curent din ABC (parcurs in inordine)

	// metode private
	void inOrder(int node); // metoda recursiva/recurenta cu care parcurgem in inordine ABC-ul (Arborele Binar de Cautare) si populam vectorul values cu cheile din nodurile acestuia
	void inOrderIter();

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//modifica elementul curent referit de iterator ca fiind elementul anterior
	//din multime, sau, in cazul in care elementul curent a fost primul, transforma iteratorul in unul navalid
	//arunca exceptie in cazul in care iteratorul nu este valid
	void anterior();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;

	//destructorul unui obiect de clasa IteratorMultime
	//facem dealocarea memoriei alocate pe heap (in mod dinamic)
	~IteratorMultime();
};