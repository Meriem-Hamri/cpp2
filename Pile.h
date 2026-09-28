#ifndef PILE_H
#define PILE_H

#include "Export.h"

// Déclaration de la pile générique utilisant un tableau dynamique.
template <typename T>
class BIBLIOTHEQUE_API PileTableau {
private:
    T* elements;
    int taille;
    int capacite;

    void agrandir();

public:
    PileTableau();
    ~PileTableau();

    PileTableau(const PileTableau&) = delete;
    PileTableau& operator=(const PileTableau&) = delete;

    bool estVide() const;
    void empiler(const T& valeur);
    T depiler();
    T sommet() const;
};

// Déclaration de la pile générique utilisant une liste chaînée.
template <typename T>
class BIBLIOTHEQUE_API PileListe {
private:
    struct Noeud {
        T valeur;
        Noeud* suivant;
    };

    Noeud* tete;

public:
    PileListe();
    ~PileListe();

    PileListe(const PileListe&) = delete;
    PileListe& operator=(const PileListe&) = delete;

    bool estVide() const;
    void empiler(const T& valeur);
    T depiler();
    T sommet() const;
};

#endif
