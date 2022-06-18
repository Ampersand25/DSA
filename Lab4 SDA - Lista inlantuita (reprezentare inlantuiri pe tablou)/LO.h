#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

// definim capacitatea maxima a vectorilor interni
#define CAPACITY 1e+1

class LO {
private:
	friend class Iterator;

	/* aici reprezentarea */
	
	// *atribute/campuri private*

	int cp{ (int)CAPACITY };

	// vector (array) dinamic (alocat pe heap) de elemente de tipul TElement (cu spatiu de memorare - MAX_CAPACITY)
	TElement* elems;

	// vector (array) dinamic (alocat pe heap) pentru a retine pentru fiecare nod din lista succesorul sau (nodul urmator)
	int* urm;

	// vector (array) dinamic (alocat pe heap) pentru a retine pentru fiecare nod din lista predecesorul sau (nodul anterior/precedent)
	int* prec;

	// referinta catre primul nod din lista (primul element al containerului)
	int primElem;

	// referinta catre primul nod din lista spatiului liber (primul nod liber din lista)
	int primLiber;

	// relatia de ordine a listei, care este un functor/predicat (functie care returneaza o valoare logica/booleana) care primeste doi parametrii (doua argumente) de tipul TElement
	Relatie rel;

	// *metode (functii specifice obiectelor de clasa LO) private*

	// metoda privata care initializeaza lista spatiului liber
	void initSpatiuLiber();

	// metoda privata care redimensioneaza array-urile interne in momentul in care se atinge capacitatea maxima
	void redim();

	// metoda privata pentru alocarea/dealocarea unui spatiu liber
	// se returneaza pozitia unui spatiu liber in lista
	int aloca();

	// metoda privata care dealoca spatiul de indice i
	void dealoca(int i);

	// metoda privata care creeaza un nod in lista dublu inlantuita ordonata
	int creeazaNod(TElement e);

	// metoda privata care adauga un element/nod avand informatia utila e inaintea nodului p din lista
	void adaugaInainte(int p, TElement e);

	// metoda privata care adauga un element/nod avand informatia utila e la finalul/sfarsitul listei (dupa ultimul nod/element din container)
	void adaugaFinal(TElement e);

public:
	// constructor
	LO(Relatie r);

	// returnare dimensiune
	int dim() const;

	// verifica daca LO e vida
	bool vida() const;

	// prima pozitie din LO
	Iterator prim() const;

	// returnare element de pe pozitia curenta
	//arunca exceptie daca poz nu e valid
	TElement element(Iterator poz) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	void adauga(TElement e);

	// sterge element de pe o pozitie poz si returneaza elementul sters
	//dupa stergere poz e pozitionat pe elementul de dupa cel sters
	//arunca exceptie daca poz nu e valid
	TElement sterge(Iterator& poz);

	// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
	Iterator cauta(TElement e) const;

	// returneaza ultimul index al unui element dat
	// daca elementul nu este in lista returneaza un Iterator nevalid
	Iterator ultimulIndex(TElement elem) const;

	//destructor
	~LO();

};