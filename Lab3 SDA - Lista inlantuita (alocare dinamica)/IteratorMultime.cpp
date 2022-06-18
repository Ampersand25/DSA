#include "IteratorMultime.h"
#include "Multime.h"

#include <cstdlib>

IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	/* de adaugat */

	// initializam iteratorul cu adresa primului nod din inlantuire pentru a putea itera lista/multimea
	this->curr = this->mult.head;
}

TElem IteratorMultime::element() const {
	/* de adaugat */

	if (valid()) // verificam validitatea iteratorului
		return this->curr->key; // returnam cheia elementului/nodului din lista/multime pe care il refera iteratorul (in cazul in care iteratorul este valid)
	throw "Iteratorul nu este valid!"; // aruncam exceptie daca iteratorul nu este valid (este NULL)
}

bool IteratorMultime::valid() const {
	/* de adaugat */

	// daca iteraotrul este NULL atunci acesta nu mai este valid (nu refera un element din multime)
	// pentru ca iteratorul sa fie valid acesta trebuie sa pointeze (puncteze) catre/spre un nod din lista (adica sa fie diferit de pointerul NULL)
	return this->curr != NULL;

	//	if(this->curr != NULL)
	//        return true;
	//	return false;
}

void IteratorMultime::urmator() {
	/* de adaugat */

	if (valid()) // verificam daca iteratorul este valid
		this->curr = this->curr->next; // daca iteratorul este valid atunci trecem la urmatorul nod din lista (element din multimea mul)
	else throw "Iteratorul nu este valid!"; // daca iteratorul nu este valid aruncam (ridicam) exceptie cu mesajul "Iteratorul nu este valid!"
}

void IteratorMultime::prim() {
	/* de adaugat */

	// resetam iteratorul (il facem sa refere primul nod/element din multime)
	this->curr = this->mult.head;
}
