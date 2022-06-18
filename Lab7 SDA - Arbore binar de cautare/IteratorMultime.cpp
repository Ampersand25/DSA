#include "IteratorMultime.h"
#include "Multime.h"

#include <exception>
#include <iostream>

using std::exception;

/*
* Analiza complexitatii:
* Fie n - numarul de noduri din subarborele din ABC care are nodul node ca si radacina
* Caz favorabil = Caz defavorabil = Caz mediu = θ(n) - complexitate liniara
* Complexitate generala (Overall Complexity) = θ(n)
*/
void IteratorMultime::inOrder(int node) {
	// parcurgem in inordine arborele binar de cautare
	// node - nodul curent din arbore (radacina unui subarbore al arborelui initial cu radacina in nodul 0)
	// 1. procesam subarborele stang al nodului radacina node (arborele care are ca si radacina fiul (descendentul direct) stang al nodului node)
	// 2. procesam radacina subarborelui (adica nodul node)
	// 3. procesam subarborele drept al nodului radacina node (arborele care are ca si radacina fiul (descendentul direct) drept al nodului node)

	if (!mult.nil[node])
	{
		inOrder(mult.left[node]);         // stanga (procesam subarborele stang)
		values[idx++] = mult.elems[node]; // radacina (procesam radacina subarborelui curent)
		inOrder(mult.right[node]);        // dreapta (procesam subarborele drept)
	}

	/*if (mult.nil[node]) // if (idx == dim + 1)
		return;

	inOrder(mult.left[node]);
	values[idx++] = mult.elems[node];
	inOrder(mult.right[node]);*/
}

/*
* Analiza complexitatii:
* Fie n - numarul de noduri din ABC (numarul de elemente din multime)
* Caz favorabil = Caz defavorabil = Caz mediu = θ(n)
* Complexitate generala (Overall Complexity) = θ(n) - complexitate liniara
* Complexitatea constructorului este complexitatea metodei inOrder apelata pentru radacina arborelui
* Restul operatiilor sunt constante ca si timp de executie/rulare
*/
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	/* de adaugat */

	dim = mult.dim();

	values = new TElem[dim];
	
	inOrder(mult.head);

	idx = 0;
}

/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
TElem IteratorMultime::element() const {
	/* de adaugat */

	if (!valid()) // if (!this->valid())
		throw exception("Iterator invalid!\n"); // throw std::exception{"Iterator invalid!\n"};

	return values[idx]; // return idx[values];
}

/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
bool IteratorMultime::valid() const {
	/* de adaugat */
	/*if (idx < dim)
		return true;

	return false;*/

	return idx < dim;
}

/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
void IteratorMultime::urmator() {
	/* de adaugat */

	if (!valid()) // if (!this->valid())
		throw exception("Iterator invalid!\n"); // throw std::exception{"Iterator invalid!\n"};

	++idx;
}

/*
* - Analiza complexitatii timp de executie/rulare:
* Caz favorabil = Caz mediu = Caz defavorabil = θ(1)
* Complexitate generala (Overall Complexity) = θ(1)
* 
* - Analiza complexitatii spatiu de memorie/memorare
* Caz favorabil = Caz mediu = Caz defavorabil = θ(1)
* Complexitate generala (Overall Complexity) = θ(1)
* => algoritm in-place (nu foloseste memorie aditionala neconstanta, adica nu utilizeaza tablouri)
* 
* Date de intrare: iterator - obiect de clasa IteratorMultime
* Preconditii: iterator trebuie sa fie valid (pozitionat pe un element din container)
* Date de iesire (rezultate): iterator' - obiect de clasa IteratorMultime
* Postconditii: iterator' este un iterator pozitionat pe elementul precedent din multime (relativ la iterator) sau iteratorul invalid (nevalid) daca iterator era pozitionat pe primul element din container
* Metoda arunca/ridica exceptie de clasa exception (din namespaceul std (standard)) daca nu sunt respectate preconditiile (iterator nu este un obiect de clasa IteratorMultime valid)
* mesajul de eroare/exceptie este "Iterator invalid!\n"
* 
* - Descriere algoritm pseudocod:
* Subalgoritm anterior(it) este:
* @pre : it: IteratorMultime
*        iteratorul it este valid (valid(it) = true)
* @post: it': IteratorMultime
*        iteratorul it' este nevalid sau pozitionat pe elementul precedent (anterior) din Multime
*        valid(it') = false OR element(it') < element(it)
*        metoda arunca/ridica exceptie daca nu sunt respectate preconditiile
* Daca valid(it) = false atunci:
*	@arunca exceptie
* SfDaca
* Daca [this].idx = 0 atunci:
*	[this].idx <- [this].dim
* Altfel
*	[this].idx <- [this].idx - 1
* SfDaca
* SfSubalgoritm
*/
void IteratorMultime::anterior() {
	if(!this->valid()) // if (!valid())
		throw exception("Iterator invalid!\n"); // throw std::exception{"Iterator invalid!\n"};

	if (!this->idx) // if (!idx)
		this->idx = this->dim; // idx = dim;
	else
		--this->idx; // --idx;
}

/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
void IteratorMultime::prim() {
	/* de adaugat */

	idx = 0;
}

/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
IteratorMultime::~IteratorMultime() {
	delete[] values;

	dim = -1;
	idx = -1;
}