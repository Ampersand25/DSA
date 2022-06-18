#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}

	// return e1 <= e2;
}

/*
* Analiza complexitatii:
* Fie n - numarul de noduri din arbore (elemente din multime)
*     h - inaltimea arborelui (h ~ log2(n))
* Caz favorabil = Caz defavorabil = Caz mediu = θ(new_capacity) 
* Complexitate generala (Overall Complexity) = O(h)
*/
void Multime::redim(int new_capacity) {
	// primLiber = capacity;

	TElem* new_elems = new TElem[new_capacity];
	int* new_left    = new int[new_capacity];
	int* new_right   = new int[new_capacity];
	bool* new_nil    = new bool[new_capacity];

	for (auto i{ 0 }; i < new_capacity; ++i)
	{
		if (i < capacity)
		{
			new_elems[i] = elems[i];
			new_left[i]  = left[i];
			new_right[i] = right[i];
			new_nil[i]   = nil[i];
		}
		else {
			new_left[i]  = -1;
			new_right[i] = -1;
			new_nil[i]   = true;
		}
	}

	delete[] elems;
	delete[] left;
	delete[] right;
	delete[] nil;

	elems = new_elems;
	left  = new_left;
	right = new_right;
	nil   = new_nil;

	capacity = new_capacity;
}

/*
* Analiza complexitatii:
* Fie n - capacitatea arborelui (capacity), adica numarul maxim de noduri care pot fi adaugate/inserate in ABC
* Caz favorabil   = θ(1) - nodul primLiber + 1 este nil (nu exista un element la pozitia respectiva in tablou/multime)
* Caz mediu       = θ(n) - primul nod liber din ABC se afla la indicele primLiber + 1, primLiber + 2, ..., capacity - 1 sau nu exista nod liber (capacity iteratii)
* Caz defavorabil = θ(n) - nu exista pozitii/locatii libere in tablou
* Complexitate generala (Overall Complexity) = O(n)
*/
void Multime::updatePrimLiber() {
	++primLiber;

	while (primLiber < capacity && !nil[primLiber])
		++primLiber;

	if (primLiber == capacity)
		redim(capacity << 1); // redim(capacity * 2);

	/*for(++primLiber; primLiber < capacity && !nil[primLiber]; ++primLiber);

	if (primLiber == capacity)
		redim(capacity << 1);*/
}

/*
* Analiza complexitatii:
* CAP este o constanta simbolica (nu afecteaza complexitatea algoritmului)
* Caz favorabil   = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = O(1) - complexitate constanta
*/
Multime::Multime() {
	/* de adaugat */

	capacity = CAP;

	elems = new TElem[capacity];
	left  = new int[capacity];
	right = new int[capacity];
	nil   = new bool[capacity];

	for (auto i{ 0 }; i < CAP; ++i)
	{
		left[i]  = -1;
		right[i] = -1;
		nil[i]   = true;
	}

	head      = 0;
	primLiber = 0;
	cont      = 0;
}


/*
* Analiza complexitatii:
* Fie n - numarul de noduri din arbore (elemente din multime)
*     h - inaltimea arborelui (h ~ log2(n))
* Caz favorabil   = θ(log2(n)) - arborele este perfect echilibrat (|numarNoduriSubarboreStang(node) - numarNoduriSubarboreDrept(node)| <= 1, pentru orice nod node <- 1, (n - 1), unde node este un nod arbitrar din ABC)
* Caz mediu       = θ(h)       - arborele este relativ echilibrat
* Caz defavorabil = θ(n)       - arborele are aspectul unei liste (simplu) inlantuite
* Complexitate generala (Overall Complexity) = O(h)
*/
bool Multime::adauga(TElem elem) {
	/* de adaugat */

	auto curr{ head };
	auto found{ false };

	if (nil[head]) // if (!primLiber)
		           // if (!cont)
		found = true;

	while (!found)
	{
		if (elems[curr] == elem)
			return false;

		if (rel(elem, elems[curr]))
		{
			if (left[curr] == -1)
			{
				left[curr] = primLiber;

				found = true;
			}
			else
				curr = left[curr];
		}
		else {
			if (right[curr] == -1)
			{
				right[curr] = primLiber;

				found = true;
			}
			else
				curr = right[curr];
		}
	}

	elems[primLiber] = elem;
	left[primLiber]  = -1;
	right[primLiber] = -1;
	nil[primLiber]   = false;

	updatePrimLiber();
	++cont;

	return true;
}


/*
* Analiza complexitatii:
* Fie n - numarul de noduri din subarborele stang al nodului node
* Caz favorabil   = Caz defavorabil = Caz mediu = θ(n)
* Complexitate generala (Overall Complexity) = O(n) - complexitate liniara
*/
int Multime::minNode(int node, int& prec) const {
	if (left[node] == -1) // if (nil[left[node]])
		return node;

	return minNode(left[node], node);

	// return (nil[left[node]]) ? (node) : (minNode(left[node], node));
}


/*
* Analiza complexitatii:
* Fie n - numarul de noduri din arbore (elemente din multime)
*     h - inaltimea arborelui (h ~ log2(n))
* Caz favorabil   = θ(log2(n)) - arborele este perfect echilibrat (|numarNoduriSubarboreStang(node) - numarNoduriSubarboreDrept(node)| <= 1, pentru orice nod node <- 1, (n - 1), unde node este un nod arbitrar din ABC)
* Caz mediu       = θ(h)       - arborele este relativ echilibrat
* Caz defavorabil = θ(n)       - arborele are aspectul unei liste (simplu) inlantuite
* Complexitate generala (Overall Complexity) = O(h)
*/
bool Multime::sterge(TElem elem) {
	/* de adaugat */

	auto prec{ -1 };
	auto curr{ head };

	while (!nil[curr])
	{
		if (elems[curr] == elem)
		{
			auto deleted{ curr };

			if (isLeafNode(curr))
			{
				// nodul curr nu are nici subarbore stang si nici subarbore drept
				// nodul curr este un nod terminal/extern (de tip frunza)

				if (prec != -1) // if (curr != head)
				{
					// nodul curr nu este radacina arborelui

					if (left[prec] == curr)
						left[prec] = -1;
					else
						right[prec] = -1;
				}

				deleted = curr;
			}
			else if (left[curr] != -1 && right[curr] != -1) // else if (!nil[left[curr]] && !nil[right[curr]])
			{
				// nodul curr are atat subarbore stang cat si subarbore drept

				auto prec{ curr };
				auto minim{ minNode(right[curr], prec) };

				elems[curr] = minim;

				if(prec == curr)
					right[prec] = right[minim]; // right[curr] = right[minim];
				else
					left[prec] = right[minim];

				deleted = minim;
			}
			else {
				// nodul curr are sau subarbore stang sau subarbore drept

				if (left[curr] != -1) // else if (!nil[left[curr]])
				{
					// nodul curr are doar subarbore stang

					if (prec == -1) // if (head == curr)
						if(left[curr] != -1)
							head = left[curr];


					if (prec != -1 && left[prec] == curr)
						left[prec] = left[curr];
					else if(prec != -1 && right[prec] == curr)
						right[prec] = left[curr];

					left[curr] = -1;

					deleted = curr;
				}
				else {
					// nodul curr are doar subarbore drept

					if (prec == -1) // if (head == curr)
						if (right[curr] != -1)
							head = right[curr];

					if (prec != -1 && left[prec] == curr)
						left[prec] = right[curr];
					else if(prec != -1 && right[prec] == curr)
						right[prec] = right[curr];

					right[curr] = -1;

					deleted = curr;
				}
			}

			// left[deleted] = right[deleted] = -1;

			nil[deleted] = true;

			primLiber = deleted;

			--cont;

			return true;
		}

		prec = curr;

		if (rel(elem, elems[curr]))
			curr = left[curr];
		else
			curr = right[curr];
	}

	return false;
}

/*
* Analiza complexitatii:
* Fie n - numarul de noduri din arbore (elemente din multime)
*     h - inaltimea arborelui (h ~ log2(n))
* Caz favorabil   = θ(log2(n)) - arborele este perfect echilibrat (|numarNoduriSubarboreStang(node) - numarNoduriSubarboreDrept(node)| <= 1, pentru orice nod node <- 1, (n - 1), unde node este un nod arbitrar din ABC)
* Caz mediu       = θ(h)       - arborele este relativ echilibrat
* Caz defavorabil = θ(n)       - arborele are aspectul unei liste (simplu) inlantuite
* Complexitate generala (Overall Complexity) = O(h)
*/
bool Multime::searchRec(int node, TElem elem) const {
	if (nil[node]) // if (nil[node] == true)
		return false;

	if (elems[node] == elem)
		return true;

	if (rel(elem, elems[node]))
		return searchRec(left[node], elem);
	
	return searchRec(right[node], elem);
}

/*
* Analiza complexitatii:
* Fie n - numarul de noduri din arbore (elemente din multime)
*     h - inaltimea arborelui (h ~ log2(n))
* Caz favorabil   = θ(log2(n)) - arborele este perfect echilibrat (|numarNoduriSubarboreStang(node) - numarNoduriSubarboreDrept(node)| <= 1, pentru orice nod node <- 1, (n - 1), unde node este un nod arbitrar din ABC)
* Caz mediu       = θ(h)       - arborele este relativ echilibrat
* Caz defavorabil = θ(n)       - arborele are aspectul unei liste (simplu) inlantuite
* Complexitate generala (Overall Complexity) = O(h)
*/
bool Multime::cauta(TElem elem) const {
	/* de adaugat */

	// Cautare iterativa
	/*auto curr{ head };

	while (!nil[curr])
	{
		if (elems[curr] == elem)
			return true;

		if (rel(elem, elems[curr]))
			curr = left[curr];
		else
			curr = right[curr];
	}
	
	return false;*/

	// Cautare recursiva/recurenta
	return searchRec(head, elem);
}


/*
* Analiza complexitatii:
* Fie n - numarul de noduri din arbore (elemente din multime)
* Caz favorabil = Caz defavorabil = Caz mediu = θ(n)
* Complexitate generala (Overall Complexity) = θ(n) - complexitate liniara
*/
int Multime::countNodes(int node) const {
	if (nil[node]) // if (nil[node] == true)
		return 0;

	auto numberOfNodesLeft{ 0 };
	auto numberOfNodesRight{ 0 };

	if (left[node] != -1) // if (!nil[left[node]])
		numberOfNodesLeft = countNodes(left[node]);

	if (right[node] != -1) // if (!nil[right[node]])
		numberOfNodesRight = countNodes(right[node]);

	return 1 + numberOfNodesLeft + numberOfNodesRight;

	/*if (!nil[node]) // if (nil[node] == false)
		return 1 + countNodes(left[node]) + countNodes(right[node]);

	return 0;*/
}

/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
int Multime::dim() const {
	/* de adaugat */

	// return countNodes(head);

	return cont;
}


/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
bool Multime::isLeafNode(int node) const {
	/*if (left[node] == -1 && right[node] == -1)
		return true;

	return false;*/

	return left[node] == -1 && right[node] == -1; // return nil[left[node]] && nil[right[node]];
	                                              // return nil[left[node]] & nil[right[node]];
												  // return nil[left[node]] * nil[right[node]];
}


/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
bool Multime::vida() const {
	/* de adaugat */

	/*if (nil[head] == true)
		return true;

	return false;*/

	return nil[head]; // return !primLiber;
	                  // return !cont;
}

/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}


/*
* Analiza complexitatii:
* Caz favorabil = Caz defavorabil = Caz mediu = θ(1)
* Complexitate generala (Overall Complexity) = θ(1) - complexitate constanta
*/
Multime::~Multime() {
	/* de adaugat */

	delete[] elems;
	delete[] left;
	delete[] right;
	delete[] nil;

	head      = -1;
	primLiber = -1;
	cont      = -1;
}