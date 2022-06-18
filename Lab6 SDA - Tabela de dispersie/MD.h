#pragma once
#include<vector>
#include<utility>

using namespace std;

#define CAP (int)1e+1 // capacitatea initiala a containerului (numarul de pozitii din tabela de dispersie)

typedef int TCheie;   // tipul de data al unei chei din MultiDictionar
typedef int TValoare; // tipul de data al unei valori asociate unei chei din MultiDictionar
typedef vector<TValoare> TValori; // tipul de data al valorilor asociate unei chei din MultiDictionar, fiecare valoare este de tipul TValoare
                                  // valorile unei chei vor fi memorate sub forma unui vector din STL (Standard Template Library) cu elemente de tipul TValoare

typedef std::pair<TCheie, TValoare> TElem; // tipul de data al unui element care contine o cheie si o singura valoare asociata acesteia
typedef std::pair<TCheie, TValori> TNod; // tipul de data al unui nod (pereche <cheie, valori asociate>) din container (MultiDictionar)
                                         // nod       : TNod (nod din MD)
										 // nod       = <nod.first, nod.second> (pereche de doua valori/elemente)
                                         // nod.first : TCheie (cheia asociata nodului)
                                         // nod.second: TValori (valorile asociate cheii nodului)

#define cheie first   // nod.first  == nod.cheie
#define valori second // nod.second == nod.valori

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */

	// atribute/campuri private
	int M;           // dimensiunea tabelei (numarul de pozitii din aceasta)
	TNod* elems;     // vectorul elementelor/nodurilor (informatiile utile)
	int* urm;        // vectorul legaturilor
	int primLiber;   // locatia primei pozitii neocupate din tabela
	int perechi;     // numarul de perechi <cheie, valoare> din tabela de dispersie

	// metode (functii) private
	void updatePrimLiber();              // metoda care actualizeaza prima pozitie (locatie) libera din tabela
	int hashCode(TCheie key) const;      // metoda care asociaza un hash code (cod de dispersie) unui element
	int hashing(TCheie key) const;       // metoda de dispersie a unui element (ii asociaza o locatie/pozitie (un indice) in tabela codului de dispersie aferent elementului)
	void redim();                        // metoda care redimensioneaza tabela de dispersie (ii dubleaza capacitatea) in momentul in care nu mai exista pozitii libere
	void rehashing(TNod* old_elems); // metoda care redisperseaza elementele vechi in noua tabela dupa redimensionarea tabelei de dispersie

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();

	// elimina o cheie impreuna cu toate valorile sale
	// returneaza un vector cu valorile care au fost anterior asociate acestei chei (si au fost eliminate)
	vector<TValoare> stergeValoriPentruCheie(TCheie cheie);

};