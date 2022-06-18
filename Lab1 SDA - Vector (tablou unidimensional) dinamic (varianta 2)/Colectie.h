#pragma once
#include "IteratorColectie.h"

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

// in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {
	friend class IteratorColectie;

private:
	/* aici e reprezentarea */

	// tipul de data al unui element
	typedef struct {
		TElem element; // valoarea (cheia) elementului
		int frecventa; // frecventa (numarul de aparitii) a elementului in colectie
	} TPereche;

	// capacitatea colectiei (marimea fizica)
	int cp;

	// dimensiunea colectiei (marimea logica)
	int n;

	// elementele colectiei
	TPereche* c;

public:
	// constructorul implicit
	Colectie();

	// dubleaza capacitatea daca s-a atins capacitatea maxima pentru a acomoda noi elemente in colectie
	void ensureCapacity();

	// adauga un element in colectie
	void adauga(TElem e);

	// sterge o aparitie a unui element din colectie
	// returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	// verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	// returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;

	// intoarce numarul de elemente din colectie;
	int dim() const;

	// verifica daca colectia e vida;
	bool vida() const;

	// returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();
};

