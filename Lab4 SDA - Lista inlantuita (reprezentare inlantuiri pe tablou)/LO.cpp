#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat
void LO::initSpatiuLiber() {
	// alocam memorie pe heap pentru vectorii (array-urile) interne
	this->elems = new TElement[this->cp]; // alocam un bloc contigua de memorie de cp elemente de tipul TElement pe heap
	this->prec = new int[this->cp];       // alocam un bloc contigua de memorie de cp elemente de tipul int pe heap
	this->urm = new int[this->cp];        // alocam un bloc contigua de memorie de cp elemente de tipul int pe heap
	
	for (auto i{ 0 }; i < this->cp; ++i)  // parcurgem fiecare nod din lista
	{
		if (i) // if (i != 0)
			// nodul i nu este primul din lista
			this->prec[i] = i - 1; // precedentul nodului/elementului i va fi nodul/elementul i - 1
		if (i + 1 != this->cp) // if (i != this->cp - 1)
			// nodul i nu este ultimul din lista
			this->urm[i] = i + 1;  // succesorul nodului/elementului i va fi nodul/elementul i + 1
	
	}

	this->prec[0] = NULL_TELEMENT;           // primul nod/element din lista nu are predecesor
	this->urm[this->cp - 1] = NULL_TELEMENT; // ultimul nod/element din lista nu are succesor
}

// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat
LO::LO(Relatie r) {
	/* de adaugat */

	// constructorul clasei LO (Lista Ordonata)
	// populam atributele/campurile private ale obiectului nou creat de clasa LO
	this->rel = r;                  // retinem functia (functor/predicat) r (de tipul Relatie) in atributul/campul rel al obiectului
	this->primElem = NULL_TELEMENT; // lista este vida (initial nu contine niciun nod/element)
	this->initSpatiuLiber();        // initializam lista spatiului liber
	this->primLiber = 0;            // referinta spre prima pozitie libera din lista
}

// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp constanta
int LO::aloca() {
	// se trece pozitia i in lista spatiului liber
	auto i{ this->primLiber };                    // i ia valoarea primului nod/element liber din lista
	if(i != NULL_TELEMENT)
		this->primLiber = this->urm[this->primLiber]; // primul element liber din lista devine urmatorul
	return i;                                         // returnam nodul/elementul alocat din lista
}

// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp constanta
void LO::dealoca(int i) {
	// se sterge/elimina primul element/nod din lista spatiului liber
	this->urm[i] = this->primLiber; // succesorul nodului/elementului i devine primul nod/element liber din lista
	this->primLiber = i;            // primul nod/element liber din lista devine nodul i
}

// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat
void LO::redim() {
	const auto new_capacity{ this->cp << 1 }; // dublam capacitatea actuala

	TElement* new_elems = new TElement[new_capacity]; // alocam un nou array pentru informatiile utile de new_capacity elemente de tipul TElement
	int* new_urm = new int[new_capacity];             // alocam un nou array pentru succesorii fiecarui nod/element de new_capacity elemente de tipul int
	int* new_prec = new int[new_capacity];            // alocam un nou array pentru predecesorii fiecarui nod/element de new_capacity elemente de tipul int

	for (auto i{ 0 }; i < this->cp; ++i) // parcurgem vechile tablouri
	{
		// facem copierea vechilor blocuri de memorie in cele noi
		*(new_elems + i) = this->elems[i]; // mutam elementul de pe pozitia i din vechiul bloc elems in noul bloc new_elems
		*(new_urm + i) = this->urm[i];     // mutam elementul de pe pozitia i din vechiul bloc urm in noul bloc new_urm
		*(new_prec + i) = this->prec[i];   // mutam elementul de pe pozitia i din vechiul bloc prec in noul bloc new_prec
	}

	// initializam noile blocuri de memorie de pe heap
	for (auto i{ this->cp }; i < new_capacity; ++i)
	{
		new_prec[i] = i - 1; // setam predecesorul nodului i ca fiind nodul i - 1
		if (i + 1 != new_capacity) // nodul i este diferit de ultimul nod
			new_urm[i] = i + 1;  // setam succesorul nodului i ca fiind nodul i + 1
	}

	new_urm[new_capacity - 1] = NULL_TELEMENT; // succesorul nodului new_capacity - 1 este NULL_TELEMENT (nu are succesor)

	delete[] this->elems; // dealocam vechiul bloc de memorie pentru informatiile utile ale nodurilor
	delete[] this->urm;   // dealocam vechiul bloc de memorie pentru succesorii nodurilor
	delete[] this->prec;  // dealocam vechiul bloc de memorie pentru predecesorii nodurilor
	
	this->elems = new_elems; // actualizam array-ul (vectorul) de informatii utile
	this->urm = new_urm;     // actualizam array-ul (vectorul) de succesori
	this->prec = new_prec;   // actualizam array-ul (vectorul) de predecesori

	this->primLiber = this->cp; // marcam primul element liber ca fiind elementul de pe pozitia corespunzatoare vechii capacitati
	this->cp = new_capacity;    // actualizam noua capacitate
}

// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat
int LO::creeazaNod(TElement e) {
	auto nou{ this->aloca() }; // cream un nou nod in lista
	
	if (nou == NULL_TELEMENT)  // verificam daca nodul s-a creat cu succes (exista spatiu in lista)
	{
		// s-a atins capacitatea maxima
		this->redim();       // facem redimensionarea vectorilor (array-urilor) interne pentru a acomoda noi noduri/element in lista/container
		nou = this->aloca(); // cream un nou nod in lista redimensionata
	}
	
	this->elems[nou] = e;            // informatia utila a nodului nou creat (nou) este valoarea parametrului de intrare e
	this->urm[nou] = NULL_TELEMENT;  // succesorul nodului nou creat (nou) este NULL_TELEMENT (acesta nu are succesor)
	this->prec[nou] = NULL_TELEMENT; // predecesorul nodului nou creat (nou) este NULL_TELEMENT (acesta nu are predecesor)

	return nou;                      // returnam nodul nou creat
}

// returnare dimensiune
//returneaza numarul de perechi (cheie, valoare) din dictionar
// Complexitate timp de executie (rulare)
// Fie n - numarul de elemente/noduri din lista (container)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(n)
// Complexitate generala (Overall Complexity) = Theta(n) - complexitate timp liniara
int LO::dim() const {
	/* de adaugat */

	// Metoda I - parcurgere fara iterator
	/*
	auto curent{ this->primElem };
	auto cont{ 0 };
	
	while (curent != NULL_TELEMENT)
	{
		++cont;
		curent = this->urm[curent];
	}
	
	return cont;
	*/

	// Metoda II - parcurgere cu iterator
	auto it{ this->prim() }; // obtinem un iterator la inceputul containerului (pozitionat pe primul element din acesta)
	auto cont{ 0 };          // variabila contor (de numarare) in care vom contoriza numarul de elemente/noduri din container/lista
	
	while (it.valid()) // parcurgem lista de la primul la ultimul nod inclusiv (pana cand iteratorul devine invalid, adica o sa fie pozitionat dupa ultimul element din container)
	{
		++cont;       // incrementam numarul de noduri din lista
		it.urmator(); // pozitionam iteratorul pe urmatorul element/nod din container
	}
	
	return cont; // intoarcem prin numele functiei (subprogramului/subrutinei) de tip operand/rezultat dimensiunea (fizica a) listei
}

// verifica daca LO e vida
// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp constanta
bool LO::vida() const {
	/* de adaugat */

	if (this->primElem != NULL_TELEMENT) // verificam primul element din container (lista)
		// daca primul element/nod din lista este diferit de elementul NULL_TELEMENT (<> NIL) atunci inseamna ca lista nu este vida
		return false; // lista nu este vida (contine cel putin un nod/element)
	return true; // lista este vida (nu contine noduri/elemente)

	// return this->primElem == NULL_TELEMENT;
}

// prima pozitie din LO
// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp constanta
Iterator LO::prim() const {
	/* de adaugat */

	return Iterator(*this); // returnam un iterator pentru container (iteratorul va fi pozitionat pe primul nod/element din lista/containter)
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp constanta
TElement LO::element(Iterator poz) const {
	/* de adaugat */

	if (!poz.valid()) // validam iteratorul poz
		// poz nu reprezinta un iterator valid (este pozitionat dupa ultimul nod/element din lista)
		throw exception("poz nu e valid!\n"); // aruncam/ridicam exceptie (obiect de clasa std::exception) cu mesajul "poz nu e valid!\n"
	return poz.element(); // returnam valoarea elementului/nodului pe care este pozitionat iteratorul poz
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp constanta
TElement LO::sterge(Iterator& poz) {
	/* de adaugat */

	if (!poz.valid()) // iteratorul poz nu este valid (este invalid)
		throw exception("poz nu e valid!\n"); // aruncam/ridicam un obiect de clasa std::exception (exceptie) cu mesajul de eroare/exceptie "poz nu e valid!\n"
	
	auto p{ poz.curent }; // retinem in variabila p nodul pe care dorim sa il stergem/eliminam din lista
	poz.urmator(); // pozitionam iteratorul poz pe elementul urmator (dupa elementul sters)
	
	auto elem{ this->elems[p] }; // stocam in variabila elem informatia utila a nodului pe care vrem sa il stergem/eliminam
	
	if (p == this->primElem) // stergem primul nod/element din lista
		this->primElem = this->urm[p]; // primul nod din lista devine al doilea (urmatorul)
	else {
		auto q{ this->prec[p] };
		this->urm[q] = this->urm[p];
		if(this->urm[p] != NULL_TELEMENT)
			this->prec[this->urm[p]] = q;

		/*
		auto q{this->primElem}; // initializam variabila q cu primul nod din lista
		while (this->urm[q] != p) // iteram containerul pana la nodul care il are ca si succesor pe nodul p (ne pozitionam cu variabila q pe nodul precedent nodului pe care dorim sa il eliminam)
			// q - nodul curent/actual din lista
			q = this->urm[q]; // trecem la urmatorul nod din lista (mutam variabila q pe nodul ei succesor)
		this->urm[q] = this->urm[p]; // succesorul nodului q devine succesorul nodului p
		if(this->urm[p] != NULL_TELEMENT)
			// daca nodul sters nu este ultimul din lista atunci ii actualizam succesorul
			this->prec[this->urm[p]] = q; // predecesorul succesorului nodului p devine nodul q
		*/
	}

	dealoca(p);  // dealocam nodul p (il stergem, marcandu-l ca liber)
	
	return elem; // returnam informatia utila a nodului sters
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
// Complexitate timp de executie (rulare)
// Fie n - numarul de elemente/noduri din lista (container)
// Caz favorabil = Theta(1) - elementul cautat (e) se afla pe prima pozitie in container (lista), este minimul (primul element) din lista
// Caz defavorabil = Theta(n) - elementul cautat (e) nu se afla in container (lista)
// Caz mediu = Theta(n) - elementul cautat (e) se afla pe o pozitie aleatoare in container (lista)
// Complexitate generala (Overall Complexity) = O(n) - complexitate timp liniara
Iterator LO::cauta(TElement e) const {
	/* de adaugat */

	auto it{ this->prim() }; // obtinem un iteraotor la inceputul containerului (pozitionat pe primul nod din lista)
	
	while (it.valid()) // parcurgem/iteram lista folosind iteratorul it
	{
		if (this->rel(e, it.element()))
			if (e == it.element()) // comparam informatia utila cautata (e) cu informatia utila a nodului referit de iteratorul it
				return it; // returnam/intoarcem/furnizam un iterator pozitionat pe nodul cu informatia utila e din lista
		it.urmator(); // pozitionam iteraotrul pe urmatorul nod din lista (element din container)
	}
	
	// cazul in care nu gasim un nod avand informatia utila e in lista
	return it; // returnam un iterator invalid (pozitionat dupa ultimul nod din lista)
}

// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp liniara
void LO::adaugaInainte(int p, int nou) {
	if(p == this->primElem) // adaugare la inceputul containerului
	{
		this->urm[nou] = p;   // legam nodul nou creat de primul nod din lista
		this->prec[p] = nou;  // legam primul nod din lista de nodul nou creat
		this->primElem = nou; // actualizam primul nod din lista
	}
	else { // adaugare la mijlocul containerului (inainte de nodul p <=> intre nodurile prec[p] si p)
		this->urm[nou] = p;              // legam nodul nou creat (nou) de nodul p
		this->prec[nou] = this->prec[p]; // legam nodul nou creat (nou) de predecesorul nodului p (prec[p])
		this->urm[this->prec[p]] = nou;  // legam predecesorul nodului p (prec[p]) de nodul nou creat (nou)
		this->prec[p] = nou;             // legam nodul p de nodul nou creat (nou)
	}
}

// Complexitate timp de executie (rulare)
// Fie n - numarul de elemente/noduri din lista (container)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(n)
// Complexitate generala (Overall Complexity) = Theta(n) - complexitate timp liniara
void LO::adaugaFinal(int nou) {
	auto p{ this->primElem }; // initializam variabila p cu primul nod din lista
	
	while (this->urm[p] != NULL_TELEMENT) // parcurgem containerul pana la ultimul element (ultimul nod din lista)
		// p - nodul curent din lista
		p = this->urm[p]; // trecem la urmatorul nod din lista
	
	this->urm[p] = nou;  // legam ultimul nod din lista (p) de nodul nou creat (nou)
	this->prec[nou] = p; // legam nodul nou creat (nou) de ultimul nod din lista (p)
	// nodul nou creat (nou) devine ultimul nod din lista
}

// adaugare element in LO
// Complexitate timp de executie (rulare)
// Fie n - numarul de elemente/noduri din lista (container)
// Caz favorabil = Theta(1) - elementul va fi inserat/adaugat la inceputul listei/containerului
// Caz defavorabil = Theta(n) - elementul va fi inserat/adaugat la sfarsitul/finalul listei/containerului
// Caz mediu = Theta(n) - elementul va fi inserat pe o pozitie aleatoare
// Complexitate generala (Overall Complexity) = O(n) - complexitate timp liniara
void LO::adauga(TElement e) {
	/* de adaugat */
	
	auto nou{ this->creeazaNod(e) }; // cream un nou nod care sa contina informatia utila e
	auto it{ this->prim() }; // obtinem un iterator la primul nod din lista
	
	if (!it.valid()) // lista vida
	{
		this->primElem = nou; // actualizam primul nod din lista (nodul nou creat devine primul)
		return; // iesire fortata din procedura
	}

	do { // iteram containerul de date (lista ordonata) folosind iteratorul it
		if (this->rel(e, it.element()))
			break;
		it.urmator(); // trecem la nodul urmator din lista
	} while (it.valid());
	
	if (!it.valid())
		this->adaugaFinal(nou); // adaugam nodul nou la finalul listei
	else
		this->adaugaInainte(it.curent, nou); // adaugam nodul nou inainte de nodul it.curent (inainte de nodul referit de iteratorului it)
}

/*
* Analiza complexitatii (timp de executie/rulare)
* Fie n - dimensiunea listei (numarul de noduri din aceasta, respectiv de elemente din container)
* Caz favorabil         = Theta(1) - elementul cautat se afla pe prima pozitie in container si este unic (apare o singura data)
* Caz defavorabil       = Theta(n) - elementul cautat nu se afla in container
* Caz mediu (statistic) = Theta(n)
* Complexitatea generala (Overall Complexity) = O(n), unde O reprezinta BIG O NOTATION (BIG OH)
* => complexitate timp de executie liniara
* Date de intrare: elem - variabila de tipul TElement = Tip Element (tip de data generic)
* Preconditii: -
* Date de iesire (rezultate): un obiect de clasa Iterator (iterator al containerului)
* Postconditii: ultimulIndex = iterator pozitionat pe ultima aparitie a elementului elem din lista (container), in cazul in care elementul elem apare in lista
*                              iterator invalid (nevalid) pozitionat dupa ultimul element in container, in cazul in care elementul elem nu apare in lista
* 
* Algoritm pseudocod (varianta I):
* Subalgoritm ultimulIndex(elem: TElem, iter: Iterator):
*   // pre : elem
*	// post: iter
*	it <- [this].prim()
*	Daca [it].valid() = false atunci:
*		iter <- it
*	SfDaca
*	it    <- [it].urmator()
*	gasit <- [this].prim()
*	Cattimp [it].valid() executa:
*		Daca [this].rel([it].element(), elem) atunci:
*			gasit <- [gasit].urmator()
*		Altfel Daca [gasit].valid() si [gasit].element() = elem atunci:
*			iter <- gasit
*		SfDaca
*		it <- [it].urmator()
*	SfCattimp
*	Daca [gasit].valid() si [gasit].element() = elem atunci:
*		iter <- gasit
*	Altfel:
*		iter <- it
*	SfDaca
* SfSubalgoritm
*/
Iterator LO::ultimulIndex(TElement elem) const {
	Iterator it{ this->prim() }; // obtinem un iterator pozitionat pe primul element din container (sau iteratorul invalid/nevalid daca containerul de date este gol/vid)
	if (!it.valid()) // daca iteratorul instantiat este invalid (nu este valid), atunci lista nu contine niciun nod (nu exista elemente in container)
		return it; // intoarcem un iterator invalid
	it.urmator(); // mutam iteratorul in container (il pozitionam pe urmatorul element din lista pe care o refera)
	Iterator gasit{ this->prim() }; // facem instantierea unui nou iterator a containerului (pozitionat pe primul element)
	while (it.valid())
	{
		// gasit - iterator pozitionat pe elementul precedent (fata de elementul din container referit de iteratorul it)
		// it    - iterator pozitionat pe elementul curent
		if (this->rel(it.element(), elem)) // elementul curent satisface relatie de oridine rel fata de elementul cautat
			gasit.urmator(); // mutam iteratorul gasit in container (il pozitionam pe elementul elem referit de iteratorul it)
		else if(gasit.valid() && gasit.element() == elem) // iteratorul gasit este valid si este pozitionat pe un element avand valoarea elem
			return gasit; // returnam un iterator pozitionat pe ultima aparitei a elementului elem in lista
		it.urmator(); // mutam iteratorul it in container (il repozitionam pe urmatorul nod din lista)
	}
	// containerul contine doar 2 elemente sau elementul elem nu se afla/regaseste in lista
	if (gasit.valid() && gasit.element() == elem) // containerul contine 2 elemente iar primul este cel cautat (al doilea difera)
		return gasit; // returnam un iterator pozitionat pe primul element din container
	else // elementul elem nu se afla in lista
		return it; // returnam un iterator invalid (pozitionat dupa ultimul element din container)
}

//destructor
// Complexitate timp de executie (rulare)
// Caz favorabil = Caz defavorabil = Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate timp constanta
LO::~LO() {
	/* de adaugat */

	// destructorul clasei LO (Lista Ordonata)
	// dealocam memoria de pe heap pentru cele 3 tablouri (array-uri)
	delete[] this->elems; // dealocam memorie pentru atributul elems
	delete[] this->prec;  // dealocam memorie pentru atributul prec
	delete[] this->urm;   // dealocam memorie pentru atributul urm
}