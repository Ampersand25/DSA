#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <cmath> // #include <math.h>

#define MODUL(a) \
	((a) > 0 ? (a) : -(a))

using namespace std;

// *Analiza complexitatii timp (de executie/rulare)*
// Fie M - capacitatea curenta a tabelei (la intrarea in functie, adica in momentul apelului)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
void MD::rehashing(TNod* old_elems) {
	for (auto i{ 0 }; i < M >> 1; ++i) // for (auto i{ 0 }; i < M / 2; ++i)
	{
		auto key{ old_elems[i].cheie };

		for (auto value : old_elems[i].valori)
			adauga(key, value); // this->adauga(key, value);
	}

	delete[] old_elems;
}


// *Analiza complexitatii timp (de executie/rulare)*
// Fie M - capacitatea curenta a tabelei (la intrarea in functie, adica in momentul apelului)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Fie new_capacity = 2 * M
// Caz favorabil = caz defavorabil = caz mediu = Theta(2 * new_capacity + M) = Theta(5 * M)
// Complexitate generala (Overall Complexity) = Theta(5 * M) - complexitate liniara
// => Algoritm in-place (nu foloseste memorie aditionala)
void MD::redim() {
	auto new_capacity{ M << 1 }; // auto new_capacity{ M * 2 };

	auto new_elems{ new TNod[new_capacity] };
	auto new_urm{ new int[new_capacity] };

	for (auto i{ 0 }; i < new_capacity; ++i)
	{
		// new_elems[i].cheie = -1;
		// new_elems[i].valori.clear();

		new_urm[i] = -1;
	}

	auto old_elems{ new TNod[M] };

	for (auto i{ 0 }; i < M; ++i)
	{
		old_elems[i].cheie = elems[i].cheie;
		old_elems[i].valori = elems[i].valori;
	}

	M = new_capacity;

	primLiber = perechi = 0;

	delete[] elems;
	delete[] urm;

	elems = new_elems;
	urm = new_urm;

	/*
	for (auto i{ 0 }; i < M >> 1; ++i) // for (auto i{ 0 }; i < M / 2; ++i)
	{
		auto key{ old_elems[i].cheie };

		for (auto value : old_elems[i].valori)
			adauga(key, value);
	}

	delete[] old_elems;
	*/

	rehashing(old_elems); // this->rehashing(old_elems);
}


// *Analiza complexitatii timp (de executie/rulare)*
// Fie M - capacitatea curenta a tabelei (la intrarea in functie, adica in momentul apelului)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
void MD::updatePrimLiber() {
	/*
	for (++primLiber; primLiber < M && !elems[primLiber].valori.empty(); ++primLiber);
	*/
	
	//if(primLiber < M)
	//	++primLiber;
	
	++primLiber;

	while (primLiber < M && elems[primLiber].valori.size())
		++primLiber;

	if (primLiber == M) // if (primLiber >= M)
		redim();
		//throw exception("Overflow: Tabela de dispersie plina!\n"); // throw exception{ "Overflow: Tabela de dispersie plina!\n" };
}


// *Analiza complexitatii timp (de executie/rulare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) amortizat - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
int MD::hashCode(TCheie key) const {
	return MODUL(key); // return abs(key);
}


// *Analiza complexitatii timp (de executie/rulare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
int MD::hashing(TCheie key) const {
	return hashCode(key) % M;
}


// *Analiza complexitatii timp (de executie/rulare)*
// Fie m - dimensiunea curenta a tabelei de dispersie
// (m - numarul de pozitii/indici din tabela de dispersie (hash table))
// Caz favorabil = Theta(1) - cheia cautata c se afla la locatia hashing(c), unde hashing este functia de dispersie (hash function) (hashing(c) este valoarea de dispersie a cheii c)
// Caz defavorabil = Theta(m) - cheia cautata c nu se afla in tabela
// Caz mediu = Theta(m)
// Complexitate generala (Overall Complexity) = O(m) - complexitate liniara
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
MD::MD() {
	/* de adaugat */
	M = CAP;

	elems = new TNod[M];
	urm = new int[M];

	for (auto i{ 0 }; i < M; ++i)
	{
		// elems[i].cheie = -1;
		// elems[i].valori.clear();

		urm[i] = -1;
	}

	primLiber = 0;
	perechi = 0;
}


// *Analiza complexitatii timp (de executie/rulare)*
// Fie M - capacitatea curenta a tabelei (la intrarea in functie, adica in momentul apelului)
// Cazul amortizat
// Fie n - numarul de elemente din container
// Caz favorabil = Theta(1) - locatia hashing(c) din tabela este libera, unde hashing este functia de dispersie (hash function) (hashing(c) este valoarea de dispersie a cheii c)
// Caz defavorabil = Theta(n) - locatia hashing(c) este ocupata (exista un element (pereche <cheie, valoare>) la aceasta pozitie in tabela) lista inlantuita care incepe la pozitia hashing(c) in tabela contine n elemente (elementul <c, e> va fi adaugat la finalul/sfarsitul acestei liste in tabela)
// Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = O(m) - complexitate medie
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
void MD::adauga(TCheie c, TValoare v) {
	/* de adaugat */

	++perechi;

	auto i{ hashing(c) };
	auto ii{ i };
	auto j{ -1 };

	/*
	while (i != -1)
	{
		if (elems[i].cheie == c)
		{
			elems[i].valori.push_back(v);

			return;
		}

		j = i;
		i = urm[i];
	}
	*/

	while (i != -1 && elems[i].cheie != c)
	{
		j = i;
		i = urm[i];
	}

	if(i != -1) // inseamna ca elems[i].cheie == c
	{
		elems[i].valori.push_back(v);

		if (i == primLiber)
			updatePrimLiber();

		return;
	}

	i = ii;

	if (elems[i].valori.empty())
	{
		elems[i].cheie = c;
		elems[i].valori.push_back(v);

		if (i == primLiber)
			updatePrimLiber();

		return;
	}

	elems[primLiber].cheie = c;
	elems[primLiber].valori.push_back(v);

	urm[j] = primLiber;

	updatePrimLiber();
}


// *Analiza complexitatii timp (de executie/rulare)*
// Cazul amortizat
// Fie n - numarul de elemente din container
// Caz favorabil = Theta(1) - elementul sters se afla la locatia hashing(c)
// Caz defavorabil = Theta(n) - elementul sters nu se afla in container
// Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = O(m) - complexitate liniara
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
bool MD::sterge(TCheie c, TValoare v) {
	/* de adaugat */

	if (vid()) // if (!dim())
		return false;

	auto i{ hashing(c) };
	auto pre_i{ -1 };

	while (i != -1 && elems[i].cheie != c)
	{
		pre_i = i;
		i = urm[i];
	}

	if (i == -1)
		return false;

	auto& vec{ elems[i].valori };
	auto iter{ find(vec.begin(), vec.end(), v) };

	if (iter == vec.end())
		return false;

	vec.erase(iter);

	if (!vec.size()) // if (vec.empty())
	{
		auto done{ false };

		while (!done)
		{
			auto j{ i };
			auto pre_j{ pre_i };

			while (j != -1)
			{
				pre_j = j;
				j = urm[j];

				if (j == -1)
				{
					done = true;

					break;
				}

				auto key{ elems[j].cheie };
				auto values{ elems[j].valori };

				if (hashing(key) == i)
				{
					elems[i].cheie = key;
					// elems[i].valori.clear();
					elems[i].valori = values;

					pre_i = pre_j;
					i = j;

					break;
				}
			}
		}
		
		/*
		auto pre_i{ hashing(c) };

		while (pre_i != -1)
		{
			if (urm[pre_i] == i)
				break;

			pre_i = urm[pre_i];
		}
		*/

		if (pre_i != -1)
			urm[pre_i] = urm[i];

		elems[i].valori.clear();
		urm[i] = -1;
	}

	--perechi;

	return true;
}


// *Analiza complexitatii timp (de executie/rulare)*
// Cazul amortizat
// Fie n - numarul de elemente din container
// Caz favorabil = Theta(1) - cheia cautata c se afla la locatia hashing(c), unde hashing este functia de dispersie (hash function) (hashing(c) este valoarea de dispersie a cheii c)
// Caz defavorabil = Theta(n) - cheia cautata c nu se afla in tabela
// Caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = O(m) - complexitate liniara
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
vector<TValoare> MD::cauta(TCheie c) const {
	/* de adaugat */

	if (vid()) // if (!dim())
		return vector<TValoare>();

	auto i{ hashing(c) };

	while (i != -1)
	{
		if (elems[i].cheie == c)
			return elems[i].valori;

		i = urm[i];
	}

	return vector<TValoare>();
}


// *Analiza complexitatii timp (de executie/rulare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
int MD::dim() const {
	/* de adaugat */

	/*
	auto cont{ 0 };

	for (auto i{ 0 }; i < M; ++i)
		cont += elems[i].valori.size();

	return cont;
	*/

	return perechi;
}


// *Analiza complexitatii timp (de executie/rulare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
bool MD::vid() const {
	/* de adaugat */

	/*
	for (auto i{ 0 }; i < M; ++i)
		if (elems[i].valori.size()) // if (!elems[i].valori.empty())
									// if (elems[i].valori.empty() == false)
									// if (elems[i].valori.size() != 0)
			return false;

	return true;
	*/

	return !perechi; // return perechi == 0;
	                 // return !dim();
}


// *Analiza complexitatii timp (de executie/rulare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


// *Analiza complexitatii timp (de executie/rulare)*
// Presupunem ca complexitatea metodei delete este Theta(1)
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// *Analiza complexitatii spatiu (de memorie/memorare)*
// Caz favorabil = caz defavorabil = caz mediu = Theta(1)
// Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
// => Algoritm in-place (nu foloseste memorie aditionala)
MD::~MD() {
	/* de adaugat */

	delete[] elems;
	delete[] urm;

	// M = 0;
	// primLiber = -1;
	// perechi = -1;
}


/*
* - Analiza complexitatii timp de executie/rulare
* Pentru cazul amortizat
* Fie n - numarul de elemente din container
* Caz favorabil = Theta(1) - elementul sters se afla la locatia hashing(c)
* Caz defavorabil = Theta(n) - elementul sters nu se afla in container
* Caz mediu = Theta(1)
* Complexitate generala (Overall Complexity) = O(n) - complexitate liniara
* 
* - Analiza complexitatii spatiu de memorie/memorare
* Caz favorabil = caz defavorabil = caz mediu = Theta(1)
* Complexitate generala (Overall Complexity) = Theta(1) - complexitate constanta
* => Algoritm in-place (nu foloseste memorie aditionala)
* 
* - Specificatii:
* Date de intrare: cheie - element de tipul TCheie
* Preconditii: cheie apartine multimii elementelor de tip TCheie
*              cheie este cheia care trebuie stearsa/eliminata din MD (daca aceasta exista in container)
* Date de iesire: vec - vector (TAD Lista) cu elemente de tipul TValoare
* Postconditii: vec este vectorul asociat cheii cheie din MD de dinainte de stergere, daca cheia se afla in container (si a fost deci stearsa cu succes) sau un vector vid in caz contrar (cheia cheie nu exista in MultiDictionar)
*               vec este o lista care contine elemente de tipul TValoare (valori asociate unei chei din container)
* 
* - Descriere algoritm pseudocod:
* Functia stergeValoriPentruCheie(cheie: TCheie, vec: TLista) este
*	@ pre : cheie
*	@ post: vec
* 
*	Daca vid([this]) = true atunci
*		vec <- TLista[]
*		@ returneaza vec
*	SfDaca
* 
*	i     <- hashing([this], cheie)
*	pre_i <- -1
* 
*	Cattimp i <> -1 SI [this].elems[i].cheie <> cheie executa
*		pre_i <- i
*		i     <- [this].urm[i]
*	SfCattimp
* 
*	Daca i = -1 atunci
*		vec <- TLista[]
*		@ returneaza vec
*	SfDaca
* 
*	vec <- [this].elems[i].valori
* 
*	clear([this].elems[i].valori)
* 
*	done <- false
* 
*	Cattimp done = false executa
*		j     <- i
*		pre_j <- pre_i
*		
*		Cattimp j <> -1 executa
*			pre_j <- j
*			j     <- [this].urm[j]
*			
*			Daca j = -1 atunci
*				done <- true
*				
*				intrerupe
*				@ break
*			SfDaca
*			
*			key    <- [this].elems[j].cheie
*			values <- [this].elems[j].valori
* 
*			Daca hashing([this], key) = i atunci
*				[this].elems[i].cheie  <- key
*				[this].elems[i].valori <- values
*				
*				pre_i <- pre_j
*				i     <- j
* 
*				intrerupe
*				@ break
*			SfDaca
*		SfCattimp
*		
*		Daca pre_i <> -1 atunci
*			[this].urm[pre_i] <- [this].urm[i]
*		SfDaca
*		
*		clear([this].elems[i].valori)
*		[this].urm[i] <- -1
*	SfCattimp
* 
*	[this].perechi <- [this].perechi - size(vec)
* 
*	@ returneaza vec
* SfFunctia
*/
vector<TValoare> MD::stergeValoriPentruCheie(TCheie cheie) {
	/* de adaugat */

	if (vid()) // if (!dim())
		return vector<TValoare>();

	auto i{ hashing(cheie) };
	auto pre_i{ -1 };

	while (i != -1 && elems[i].cheie != cheie)
	{
		pre_i = i;
		i = urm[i];
	}

	if (i == -1)
		return vector<TValoare>();
	
	auto vec{ elems[i].valori };

	elems[i].valori.clear(); // elems[i].valori.resize(0);

	auto done{ false };

	while (!done)
	{
		auto j{ i };
		auto pre_j{ pre_i };

		while (j != -1)
		{
			pre_j = j;
			j = urm[j];

			if (j == -1)
			{
				done = true;

				break;
			}

			auto key{ elems[j].cheie };
			auto values{ elems[j].valori };

			if (hashing(key) == i)
			{
				elems[i].cheie = key;
				// elems[i].valori.clear();
				elems[i].valori = values;

				pre_i = pre_j;
				i = j;

				break;
			}
		}

		if (pre_i != -1)
			urm[pre_i] = urm[i];

		elems[i].valori.clear();
		urm[i] = -1;
	}

	perechi -= vec.size();

	return vec;
}