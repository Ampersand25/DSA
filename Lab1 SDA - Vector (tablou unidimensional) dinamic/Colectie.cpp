#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
    /* de adaugat */

    // TComparabil (Tip de data comparabil) = TElem (tip de data element)
    // R (relatia de ordine): <= (mai mic sau egal intre chei/elemente (valori))
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
    cp = 1;

    // alocam spatiu de memorare de cp (= 1) elemente de tipul TPereche pentru colectie
    // alocare dinamica a memoriei pe heap
    c = new TPereche[cp];

    // setam numarul initial de elemente
    n = 0;
}

void Colectie::adauga(TElem e) {
    /* de adaugat */

    // daca s-a atins capacitatea maxima, redimensionam vectorul alocat dinamic
    if (n == cp)
    {
        // dublam capacitatea curenta (complexitate Theta(1) amortizat)
        cp <<= 1; /// cp *= 2;

        // alocam un bloc de memorie de capacitate noua
        TPereche* cNou = new TPereche[cp];

        // copiem vechile valori (elemente) in noua zona de memorie
        for (int i = 0; i < n; ++i)
            cNou[i] = c[i];

        // eliberam vechea zona de pe heap
        delete[] c;

        // vectorul indica spre noua zona (schimbam referinta)
        c = cNou;
    }

    bool gasit = false;
    int i = 0, frecv = 1;
    while (i < n && !gasit)
        if (rel(e, c[i].element))
        {
            for (int j = n; j > i; --j)
            {
                c[j] = c[j - 1];
                if (c[j].element == e)
                {
                    ++c[j].frecventa;
                    frecv = c[j].frecventa;
                }
            }
            gasit = true;
        }
        else ++i;

    // adaugam elementul e pe pozitia i in vector
    c[i].element = e;
    c[i].frecventa = frecv;
    ++n; // incrementam numarul curent de elemente din colectie (dimensiunea)
}


bool Colectie::sterge(TElem e) {
    /* de adaugat */

    for (int i = 0; i < n; ++i)
        if (c[i].element == e)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (c[j].element == e)
                    --c[j].frecventa;
                c[j - 1] = c[j];
            }
            --n;
            return true;
        }
    return false;
}


bool Colectie::cauta(TElem elem) const {
    /* de adaugat */

    for (int i = 0; i < n; ++i) // parcurgerea colectiei
        if (c[i].element == elem) // verificam daca elementul curent din colectie este elementul cautat
            return true; // elem se afla in colectie
    return false; // elem nu se afla in colectie
}


int Colectie::nrAparitii(TElem elem) const {
    /* de adaugat */

    for (int i = 0; i < n; ++i) // parcurgem (iteram) colectia de la primul la ultimul element
        if (c[i].element == elem) // verificam daca elementul curent din colectie este elementul cautat
            return c[i].frecventa; // am gasit elementul cautat in colectie (apare de c[i].frecventa ori)
    return 0; // elementul elem nu se afla in colectie (apare de 0 ori)
}



int Colectie::dim() const {
    /* de adaugat */

    // returnam numarul de elemente din colectie (dimensiunea colectiei)
    return n;
}


bool Colectie::vida() const {
    /* de adaugat */

    // colectia este vida daca nu avem elemente in ea (dimensiunea este nula, adica 0)
    return !n;

    //	if(n)
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
    delete[] c;
}
