#include "RechercheFichierFind.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iterator>

bool RechercheFichierFind::charger(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open()) {
        return false;
    }

    mots.clear();
    std::string mot;

    while (fichier >> mot) {
        mots.push_back(mot);
    }

    return true;
}

bool RechercheFichierFind::rechercher(const std::string& motRecherche) {
    auto debut = std::chrono::high_resolution_clock::now();

    // Algorithme generique de la STL.
    auto resultat = std::find(mots.cbegin(), mots.cend(), motRecherche);

    auto fin = std::chrono::high_resolution_clock::now();
    dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();

    if (resultat == mots.cend()) {
        return false;
    }

    position = static_cast<std::size_t>(
        std::distance(mots.cbegin(), resultat)
    );
    return true;
}

std::size_t RechercheFichierFind::nombreMots() const {
    return mots.size();
}

std::size_t RechercheFichierFind::positionTrouvee() const {
    return position;
}

double RechercheFichierFind::tempsMicrosecondes() const {
    return dureeMicrosecondes;
}
