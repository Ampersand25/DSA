#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */

	// instantierea iteratorului
	// pregatim iteratorul pentru a itera o colectie c
	curent = 0; // ne pozitionam pe primul element in colectie
}

TElem IteratorColectie::element() const {
	/* de adaugat */

	// validam iteratorul
	if (!valid()) /// if(curent >= col.dim())
		throw "Iteratorul nu e valid!"; // aruncam exceptie daca iteratorul nu este valid
	return col.c[curent].element; // returnam elementul din colectie de pe pozitia curenta corespunzatoare iteratorului
}

bool IteratorColectie::valid() const {
	/* de adaugat */

	return curent < col.n; // pentru ca iteratorul sa fie valid acesta trebuie sa refere un element din colectie

//	if(curent < col.n)
//        return true;
//	return false;
}

void IteratorColectie::urmator() {
	/* de adaugat */

	if (!valid()) // iteratorul nu este valid
		throw "Iteratorul nu e valid!"; // aruncam/ridicam exceptie cu mesajul de eroare "Iteratorul nu e valid!"
	++curent; // pozitionam iteratorul pe urmatorul element din colectie
}

void IteratorColectie::prim() {
	/* de adaugat */

	curent = 0; // repozitionam cursorul/indicatorul colectiei pe primul element
}
