#pragma once

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

/**
typedef struct nodetype{
	TElem key;
	struct nodetype* next;
} TNode;
**/

// structura pentru reprezentarea unui nod dintr-o LSI (lista simplu inlantuita)
struct TNode {
	TElem key;   // cheia (valoarea) nodului curent
	TNode* next; // referinta catre urmatorul nod din inlantuire (sau pointer la NULL daca nodul curent este ultimul din lista)
};

class Multime {

	friend class IteratorMultime;

private:
	/* aici e reprezentarea */

	// pointer la primul element (nod) din lista
	TNode* head;

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();

	// returneaza diferenta dintre valoarea maxima si cea minima (presupunem valori intregi)
	// daca multimea este vida, se returneaza -1
	int diferentaMaxMin() const;

};
