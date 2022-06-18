#pragma once

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

#define CAP (unsigned)1e1 // capacitatea initiala a tablourilor interne (vectorilor interni)

class Multime {

	friend class IteratorMultime;

private:
	/* aici e reprezentarea */

	// atribute (campuri) private
	TElem* elems;  // vector in care retinem informatiile utile (elementele multimii)
	int* left;     // vector in care pentru fiecare nod din ABC retinem fiul (descendentul direct) stang
	int* right;    // vector in care pentru fiecare nod din ABC retinem fiul (descendentul direct) drept
	bool* nil;     // vector in care pentru fiecare nod din ABC retinem daca este sau nu nil (0), adica nodul respectiv nu se afla in ABC
	int head;      // variabila simpla de lucru in care memoram (stocam) radacina arborelui
	int primLiber; // variabila simpla de lucru in care memoram (stocam) primul nod liber node (nil[node] == false) din ABC
	int cont;      // variabila de tip contor in care numaram nodurile din ABC (numarul de elemente din multime <=> cardinalul multimii)
	int capacity;  // variabila simpla de lucru in care retinem capacitatea curenta a tablourilor interne (elems, left, right si nil)

	// metode (functii) private
	void redim(int new_capacity);               // metoda de redimensioanare (resize) a containerului (se actualizeaza capacitatea curenta a tablourilor interne: noua capacitate va fi new_capacity)
	void updatePrimLiber();                     // metoda care actualizeaza primul nod liber din ABC (prima pozitie neocupata din tablou)
	int countNodes(int node) const;             // metoda care contorizeaza in mod recursiv/recurent numarul de noduri din arborele a carui radacina este nodul node
	bool isLeafNode(int node) const;            // metoda care verifica daca un nod node este sau nu nod extern/terminal (de tip frunza)
	bool searchRec(int node, TElem elem) const; // metoda care cauta recursiv/recurent un element elem in subarborele care are nodul node ca si radacina
	int minNode(int node, int& prec) const;     // metoda care pentru un nod node determina nodul cu cea mai mica valoare (cel mai mic element) din arborele a carui radacina este nodul node (prec este nodul precedent nodului minim returnat de catre functie)

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

};