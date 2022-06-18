#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

bool rel(TElem e1, TElem e2) {
    /* de adaugat */

    // TComparabil = TElem
    // R = <=
    return e1 <= e2; // primul element (e1) trebuie sa fie mai mic sau egal fata de al doilea (e2)

//	if(e1 <= e2)
//        return true;
//	return false;
}

Colectie::Colectie() {
    /* de adaugat */

    // instantiarea unui obiect de clasa Colectie (constructor)
    // populam campurile (componentele) obiectului cu valori default

    // setam capacitatea initiala
    this->cp = 1;

    // alocam spatiu de memorare de cp (= 1) elemente de tipul TPereche pentru colectie
    // alocare dinamica a memoriei pe heap
    this->c = (TPereche*)malloc(this->cp * sizeof(TPereche));
    if (this->c == NULL)
    {
        perror("Heap Overflow!"); /// fputs("Heap Overflow!", stderr);
                                  /// fprintf(stderr, "Heap Overflow!");
                                  /// cerr << "Heap Overflow";
        exit(-1);
    }

    // setam numarul initial de elemente
    this->n = 0;
}

void Colectie::ensureCapacity() {
    // daca s-a atins capacitatea maxima, redimensionam vectorul alocat dinamic
    if (this->n == this->cp)
    {
        // dublam capacitatea curenta (complexitate Theta(1) amortizat)
        this->cp <<= 1; /// this->cp *= 2;

        // alocam un bloc de memorie de capacitate noua
        this->c = (TPereche*)realloc(this->c, this->cp * sizeof(TPereche));
        if (this->c == NULL)
        {
            perror("Heap Overflow!"); /// fputs("Heap Overflow!", stderr);
                                      /// fprintf(stderr, "Heap Overflow!");
                                      /// cerr << "Heap Overflow!";
            exit(-2);
        }
    }
}

void Colectie::adauga(TElem e) {
    /* de adaugat */

    ensureCapacity();

    bool gasit;
    int i, cont;
    for (i = 0, cont = 1, gasit = false; i < this->n && !gasit; ++i)
        if (rel(e, this->c[i].element))
        {
            for (int j = this->n; j > i; --j)
            {
                this->c[j] = this->c[j - 1];
                if (this->c[j].element == e)
                    cont = ++this->c[j].frecventa;
            }
            gasit = true;
        }

    if (gasit)
        --i;

    // adaugam elementul e pe pozitia i in vector
    this->c[i].element = e;
    this->c[i].frecventa = cont;
    ++this->n; // incrementam numarul curent de elemente din colectie (dimensiunea)
}


bool Colectie::sterge(TElem e) {
    /* de adaugat */

    for (int i = 0; i < this->n; ++i)
        if (this->c[i].element == e)
        {
            for (int j = i + 1; j < this->n; ++j)
            {
                if (this->c[j].element == e)
                    --this->c[j].frecventa;
                this->c[j - 1] = this->c[j];
            }
            --this->n;
            return true;
        }
    return false;
}


bool Colectie::cauta(TElem elem) const {
    /* de adaugat */

    for (int i = 0; i < this->n; ++i) // parcurgerea colectiei
        if (this->c[i].element == elem) // verificam daca elementul curent din colectie este elementul cautat
            return true; // elem se afla in colectie
    return false; // elem nu se afla in colectie
}


int Colectie::nrAparitii(TElem elem) const {
    /* de adaugat */

    for (int i = 0; i < this->n; ++i) // parcurgem (iteram) colectia de la primul la ultimul element
        if (this->c[i].element == elem) // verificam daca elementul curent din colectie este elementul cautat
            return this->c[i].frecventa; // am gasit elementul cautat in colectie (apare de c[i].frecventa ori)
    return 0; // elementul elem nu se afla in colectie (apare de 0 ori)
}



int Colectie::dim() const {
    /* de adaugat */

    // returnam numarul de elemente din colectie (dimensiunea colectiei)
    return this->n;
}


bool Colectie::vida() const {
    /* de adaugat */

    // colectia este vida daca nu avem elemente in ea (dimensiunea este nula, adica 0)
    return !this->n;

    //	if(this->n)
    //        return false;
    //	return true;
}


IteratorColectie Colectie::iterator() const {
    // obtinem un iterator pentru colectia curenta
    // cu ajutorul acestui iterator vom parcurge colectia
    return IteratorColectie(*this);
}


Colectie::~Colectie() {
    /* de adaugat */

    // eliberam zona de memorie ocupata de colectia c de pe heap (destructorul colectiei)
    free(this->c);
}
