#include "Iterator.h"
#include "LO.h"

#include <exception>

using std::exception; // folosim clasa exception din namespace-ul standard (std)

// *Complexitate timp (de executie/rulare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Complexitatea spatiu (de memorie/memorare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
Iterator::Iterator(const LO& lo) : lo(lo) {
	/* de adaugat */

	// constructorul clasei Iterator
	// instantierea unui obiect de clasa Iterator
	// pozitionam iteratorul creat pe primul element/nod din containerul (lista) primita ca si parametru
	this->curent = lo.primElem; // curent = lo.primElem;
}

// *Complexitate timp (de executie/rulare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Complexitatea spatiu (de memorie/memorare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
void Iterator::prim() {
	/* de adaugat */
	
	// pozitionam iteratorul pe primul element/nod din containerul pe care acesta il refera
	this->curent = this->lo.primElem; // curent = lo.primElem;
}

// *Complexitate timp (de executie/rulare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Complexitatea spatiu (de memorie/memorare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
void Iterator::urmator() {
	/* de adaugat */

	if (!this->valid()) // if (this->curent == NULL_TELEMENT)
		                // if (!valid())
		// iterator invalid (pozitionat dupa ultimul element/nod din lista)
		throw exception("Iterator invalid!\n"); // aruncam/ridicam exceptie cu mesajul "Iterator invalid!\n" in cazul in care iteratorul nu este valid (este invalid)
	// mutam iteratorul in container (il pozitionam pe urmatorul nod/element din lista)
	this->curent = this->lo.urm[this->curent]; // curent = lo.urm[curent];
}

// *Complexitate timp (de executie/rulare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Complexitatea spatiu (de memorie/memorare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
bool Iterator::valid() const {
	/* de adaugat */

	if (this->curent != NULL_TELEMENT) // if (curent != NULL_TELEMENT)
		return true; // iterator valid (pozitionat pe un element/nod din lista)
	return false; // iterator invalid (pozitionat dupa ultimul element/nod din lista)

	// return this->curent != NULL_TELEMENT;
}

// *Complexitate timp (de executie/rulare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Complexitatea spatiu (de memorie/memorare)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
TElement Iterator::element() const {
	/* de adaugat */

	if (!this->valid()) // if (this->curent == NULL_TELEMENT)
		                // if (!valid())
		// iterator invalid (pozitionat dupa ultimul element/nod din lista)
		throw exception("Iterator invalid!\n"); // aruncam/ridicam exceptie cu mesajul "Iterator invalid!\n" in cazul in care iteratorul nu este valid (este invalid)
	// daca iteratorul este valid atunci returnam informatia utila a nodului pe care acesta este pozitionat
	return this->lo.elems[this->curent]; // return lo.elems[curent];
}