#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>
#include <cstdlib>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
    // TComparabil = TElement
    // Rel = <=
    return e1 <= e2;

    //	if (e1 <= e2) {
    //		return true;
    //	}
    //	else {
    //		return false;
    //	}
}

Multime::Multime() {
    /* de adaugat */

    // instantierea unui obiect de clasa Multime (initial nu exista elemente in multime, deci multimea este vida)
    this->head = NULL;
}


bool Multime::adauga(TElem elem) {
    /* de adaugat */

    TNode* new_node = (TNode*)malloc(sizeof(TNode)); // cream un nou nod care sa aiba ca si cheie valoarea elem
                                                     // alocam memorie pe heap in mod dinamic pentru nodul nou creat
    if (new_node == NULL) // nu mai exista spatiu pe heap
    {
        cerr << "Heap Overflow!";
        exit(-1);
    }
    // populam nodul nou creat
    new_node->key = elem; // cheia nodului va fi elementul elem
    new_node->next = NULL; // elementul urmator va fi NULL
    if (vida()) // multimea este vida (nu avem elemente in ea)
    {
        this->head = new_node; // nodul nou creat devine primul din lista (inlantuire)
        return true; // elementul a fost adaugat cu succes in multime
    }
    if (rel(elem, this->head->key)) // adaugare la inceputul listei
    {
        if (elem == this->head->key) // nu putem avea duplicate (valori/elemente) care se repeta in multime
        {
            free(new_node); // eliberam nodul nou creat de pe heap deoarece acesta nu va fi introdus in lista (multime)
            return false; // adaugarea nu a avut loc
        }
        new_node->next = this->head; // facem nodul nou creat sa pointeze/puncteze la primul nod din lista
        this->head = new_node; // primul nod din lista devine nodul nou creat
        return true; // elementul a fost adaugat cu succes in multime
    }
    TNode* pred = this->head, * curr = this->head->next; // la fiecare pas (iteratie) retinem curent si pe cel precedent (anterior)
    while (curr != NULL) // iteram multimea element cu element (o parcurgem crescator)
    {
        if (rel(elem, curr->key)) // elementul cautat (elem) respecta relatia multimii in raport cu cheia nodului curent
        {
            if (elem == curr->key) // nu putem avea duplicate (valori/elemente) care se repeta in multime
            {
                free(new_node); // eliberam nodul nou creat de pe heap deoarece acesta nu va fi introdus in lista (multime)
                return false; // adaugarea nu a avut loc
            }
            // modificam relatiile/legaturile de la nivelul inlantuirii
            // inseram nodul nou creat new_node intre nodurile pred (precedent) si curr (curent)
            pred->next = new_node; // nodul precedent va avea ca si nod urmator pe nodul nou creat
            new_node->next = curr; // nodul nou creat va avea ca si nod urmator pe nodul curent
            return true; // elementul a fost adaugat cu succes in multime
        }
        // trecem la urmatorul nod si actualizam curentul si precedentul
        pred = curr; // nodul precedent devine nodul curent
        curr = curr->next; // nodul curent devine nodul urmator
    }
    pred->next = new_node; // adaugam nodul la finalul/sfarsitul listei
    return true; // elementul a fost adaugat cu succes in multime
}


bool Multime::sterge(TElem elem) {
    /* de adaugat */

    if (this->head == NULL) // lista/multimea este vida
        return false; // stergerea nu a avut loc
    if (this->head->key == elem) // elementul cautat este pe prima pozitie in multime (este primul nod din lista)
    {
        TNode* deleted = this->head;
        this->head = this->head->next; // stergere logica (modificarea legaturilor de la nivelul inlantuirii astfel incat nodul "sters" sa nu mai poata fi accesat din cadrul listei)
        free(deleted); // stergere fizica (dealocarea memoriei nodului eliminat din lista)
        return true; // stergerea a avut loc
    }
    // stergere din mijlocul sau finalul/sfarsitul listei
    TNode* pred = this->head, * curr = pred->next; // retinem nodul curent si pe cel precedent/anterior pentru a putea realiza stergerea
    while (curr != NULL) // iteram lista pana la ultimul element/nod
    {
        if (curr->key == elem) // am gasit elementul cautat in lista
        {
            pred->next = curr->next; // facem nodul precedent nodului curent sa refere/pointeze la nodul urmator fata de nodul curent (stergere logica, nodul curent devine inaccesibil = nu mai avem referinta la el din cadrul listei)
                                     // fie next = curr->next
                                     // inainte de stergere: pred > curr > next
                                     // dupa stergere:       pred > next
            free(curr); // eliberam/curatam nodul din memoria heap (stergere fizica)
            return true; // stergerea a avut loc
        }
        // actualizam nodul curent si pe cel precedent (trecem la urmatorul nod/element din lista)
        pred = curr; // nodul precedent devine nodul curent
        curr = curr->next; // nodul curent devine nodul urmator
    }
    return false; // stergerea nu a avut loc
}


bool Multime::cauta(TElem elem) const {
    /* de adaugat */

    TNode* node = this->head; // retinem primul nod din lista (primul element din multime)
    while (node != NULL) // iteram multimea incepand cu primul element
    {
        if (node->key == elem) // cheia nodului curent este egala cu elem - elementul cautat
            return true; // am gasit elementul cautat in multime
        node = node->next; // trecem la urmatorul nod din lista (element din multime)
    }
    return false; // elementul cautat nu se afla in multime
}


int Multime::dim() const {
    /* de adaugat */

    int cont = 0; // dimensiunea listei (numarul de elemente din multime = cardinalul multimii)

//	for(TNode* node = this->head; node != NULL; ++cont, node = node->next);

    TNode* node = this->head; // retinem primul nod din lista (capul listei) pentru a putea sa iteram multimea fara sa modificam pointerul la primul element
    while (node != NULL) // lista mai contine elemente (nu s-a ajuns la pointerul NULL care marcheaza sfarsitul listei)
    {
        ++cont; // contorizam numarul de elemente din multime (incrementam variabila cont de tip contor)
        node = node->next; // trecem la nodul urmator
    }

    return cont; // returnam/intoarcem prin numele functiei dimensiunea multimii
}



bool Multime::vida() const {
    /* de adaugat */

    // multimea este vida daca pointerul la capul listei (primul nod/element din lista) este NULL (nu avem elemente introduse in multime)
    return this->head == NULL;

    //	if(this->head != NULL)
    //        return false;
    //	return true;
}

IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}


Multime::~Multime() {
    /* de adaugat */
    
    while (this->head != NULL) // parcurgem lista pana la ultimul nod/element
    {
        TNode* curr = this->head; // retinem nodul curent din inlantuire
        this->head = this->head->next; // trecem la urmatorul nod din lista
        free(curr); // dealocam spatiul de memorare pentru nodul curent (il eliberam de pe heap)
    }
}

// Analiza complexitate:
// Fie n numarul de elemente din multime (adica numarul de noduri din lista simplu inlantuita)
// Caz favorabil = caz defavorabil = caz mediu (statistic) = Teta(n)
// Complexitatea generala (Overall Complexity) = Teta(n)

// Idee (1): se parcurge lista incepand cu primul nod si pana la ultimul (cattimp nodul curent este diferit de pointerul NULL)
// la fiecare iteratie (nod din lista) se compara cheia curenta cu valoarea minima globala si cu valoarea maxima globala
// daca minimul global este mai mare (strict) decat cheia (valoarea) nodului curent atunci se actualizeaza minimul global
// analog pentru maximul global din multime (lista)

// Idee (2): cum multimea este ordonata in raport cu relatia <= cea mai mica valoare din multime este prima, iar cea mai mare ultima
// parcurgem multimea pana la ultimul element ca sa obtinem valoarea maxima (pana la ultimul nod din lista, adica nodul care are ca si atribut urmator (next) un pointer la NULL)
// la final se returneaza prin numele functiei (functia fiind una de tip operand = rezultat) diferenta dintre valoarea maxima si cea minima

// Schitarea implementarii in Pseudocod (pentru varianta 2):
/*
* Functia diferentaMaxMin():
*   curr <- m.head
*   eMin <- curr.key
*   Cattimp curr.next <> NIL:
*       curr <- curr.next
*   SfCattimp
*   eMax <- curr.key
*   diferentaMaxMin <- eMax - eMin
* SfFunctia
*/
int Multime::diferentaMaxMin() const {
    // Specificatii:
    // Date de intrare: -
    // Preconditii: multimea trebuie sa fie nevida
    // Date de iesire: int (integer) = intreg cu semn (signed)
    // Postconditii: diferentaMaxMin() = -1, daca nu sunt respectate preconditiile (multimea este vida <=> nu exista noduri in lista)
    //                                    k, unde k reprezinta diferenta dintre valoarea maxima si cea minima din multime

    if (this->vida()) // if (this->head == NULL)
        return -1;

    // Varianta 1
    /**
    int eMin, eMax;
    eMin = this->head->key;
    eMax = this->head->key;
    
    TNode* curr = this->head;
    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
    #define MAX(a, b) (((a) > (b)) ? (a) : (b))
    while (curr != NULL)
    {
        int curr_key = curr->key;

        eMin = MIN(eMin, curr_key);
        eMax = MAX(eMax, curr_key);

        //if (eMin > curr_key)
        //    eMin = curr_key;
        //if (eMax < curr_key)
        //    eMax = curr_key;

        curr = curr->next;
    }
    #undef MIN
    #undef MAX
    return eMax - eMin;
    **/

    // Varianta 2
    int eMin;
    int eMax;

    TNode* curr = this->head;
    eMin = curr->key;
    while (curr->next != NULL)
        curr = curr->next;
    eMax = curr->key;
    
    return eMax - eMin;
}
