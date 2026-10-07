#include "Pile.h"

#include <stdexcept>
#include <string>

// Implémentation de PileTableau.
template <typename T>
PileTableau<T>::PileTableau()
    : elements(new T[2]), taille(0), capacite(2) {}

template <typename T>
PileTableau<T>::~PileTableau() {
    delete[] elements;
}

template <typename T>
void PileTableau<T>::agrandir() {
    capacite *= 2;
    T* nouveau = new T[capacite];

    for (int i = 0; i < taille; ++i) {
        nouveau[i] = elements[i];
    }

    delete[] elements;
    elements = nouveau;
}

template <typename T>
bool PileTableau<T>::estVide() const {
    return taille == 0;
}

template <typename T>
void PileTableau<T>::empiler(const T& valeur) {
    if (taille == capacite) {
        agrandir();
    }
    elements[taille++] = valeur;
}

template <typename T>
T PileTableau<T>::depiler() {
    if (estVide()) {
        throw std::out_of_range("La pile est vide");
    }
    return elements[--taille];
}

template <typename T>
T PileTableau<T>::sommet() const {
    if (estVide()) {
        throw std::out_of_range("La pile est vide");
    }
    return elements[taille - 1];
}

// Implémentation de PileListe.
template <typename T>
PileListe<T>::PileListe() : tete(nullptr) {}

template <typename T>
PileListe<T>::~PileListe() {
    while (!estVide()) {
        depiler();
    }
}

template <typename T>
bool PileListe<T>::estVide() const {
    return tete == nullptr;
}

template <typename T>
void PileListe<T>::empiler(const T& valeur) {
    tete = new Noeud{valeur, tete};
}

template <typename T>
T PileListe<T>::depiler() {
    if (estVide()) {
        throw std::out_of_range("La pile est vide");
    }

    Noeud* ancien = tete;
    T valeur = ancien->valeur;
    tete = tete->suivant;
    delete ancien;
    return valeur;
}

template <typename T>
T PileListe<T>::sommet() const {
    if (estVide()) {
        throw std::out_of_range("La pile est vide");
    }
    return tete->valeur;
}

// Types utilisés par le programme et par les exemples.
// Avec les implementations dans un .cpp, chaque nouveau type utilise
// doit etre instancie ici, puis la DLL doit etre recompilee.
template class PileTableau<int>;
template class PileListe<char>;
template class PileListe<std::string>;
