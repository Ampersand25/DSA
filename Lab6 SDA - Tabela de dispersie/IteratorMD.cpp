#include "IteratorMD.h"
#include "MD.h"

using namespace std;

// *Analiza complexitatii timp (de executie/rulare)*
// Fie m - dimensiunea tabelei de dispersie asociata containerului pe care iteratorul il itereaza
// (m - numarul de locatii din tabela de dispersie (hash table))
// Caz favorabil = Theta(1) - locatia idx din tabela de dispersie referita de iterator este ocupata (memoreaza un element)
// Caz defavorabil = Theta(m) - tabela de dispersie este goala (toate locatiile sunt libere)
// Caz mediu = Theta(m)
// Complexitate generala (Overall Complexity) = O(m) - complexitate liniara
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
void IteratorMD::deplasare() {
	while (idx < md.M && md.elems[idx].valori.empty())
		++idx;
}


// *Analiza complexitatii timp (de executie/rulare)*
// Fie m - dimensiunea tabelei de dispersie asociata containerului pe care iteratorul il itereaza
// (m - numarul de locatii din tabela de dispersie (hash table))
// Caz favorabil = Theta(1) - locatia idx din tabela de dispersie referita de iterator este ocupata (memoreaza un element)
// Caz defavorabil = Theta(m) - tabela de dispersie este goala (toate locatiile sunt libere)
// Caz mediu = Theta(m)
// Complexitate generala (Overall Complexity) = O(m) - complexitate liniara
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
// Complexitatea constructorului este aceeasi ca si complexitatea metodei private deplasare
IteratorMD::IteratorMD(const MD& _md) : md(_md) {
	/* de adaugat */

	idx = 0;
	pos = 0;

	deplasare();
}


// *Analiza complexitatii timp (de executie/rulare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
TElem IteratorMD::element() const {
	/* de adaugat */
	
	if (!valid())
		throw exception{ "Iterator invalid!\n" }; // throw std::exception("Iterator invalid!\n");

	return TElem{ md.elems[idx].cheie, md.elems[idx].valori.at(pos) };
}


// *Analiza complexitatii timp (de executie/rulare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
bool IteratorMD::valid() const {
	/* de adaugat */

	return idx < md.M && pos < md.elems[idx].valori.size();
}


// *Analiza complexitatii timp (de executie/rulare)*
// Fie m - dimensiunea tabelei de dispersie asociata containerului pe care iteratorul il itereaza
// (m - numarul de locatii din tabela de dispersie (hash table))
// Caz favorabil = Theta(1) - locatia idx din tabela de dispersie referita de iterator este ocupata (memoreaza un element)
// Caz defavorabil = Theta(m) - tabela de dispersie este goala (toate locatiile sunt libere)
// Caz mediu = Theta(m)
// Complexitate generala (Overall Complexity) = O(m) - complexitate liniara
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
// Complexitatea metodei publice (din interfata iteratorului) urmator este aceeasi ca si complexitatea metodei private deplasare
void IteratorMD::urmator() {
	/* de adaugat */
	
	if (!valid())
		throw exception{ "Iterator invalid!\n" }; // throw std::exception("Iterator invalid!\n");
	
	++pos;

	if (pos >= md.elems[idx].valori.size())
	{
		++idx;
		pos = 0;

		deplasare();
	}
}


// *Analiza complexitatii timp (de executie/rulare)*
// Fie m - dimensiunea tabelei de dispersie asociata containerului pe care iteratorul il itereaza
// (m - numarul de locatii din tabela de dispersie (hash table))
// Caz favorabil = Theta(1) - locatia idx din tabela de dispersie referita de iterator este ocupata (memoreaza un element)
// Caz defavorabil = Theta(m) - tabela de dispersie este goala (toate locatiile sunt libere)
// Caz mediu = Theta(m)
// Complexitate generala (Overall Complexity) = O(m) - complexitate liniara
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
// Complexitatea metodei publice (din interfata iteratorului) prim este aceeasi ca si complexitatea metodei private deplasare
void IteratorMD::prim() {
	/* de adaugat */

	idx = 0;
	pos = 0;

	deplasare();
}