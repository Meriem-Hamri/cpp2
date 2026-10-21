#include "RechercheFichier.h"

#include <chrono>
#include <fstream>

bool RechercheFichier::charger(const std::string& nomFichier) {
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

bool RechercheFichier::rechercher(const std::string& motRecherche) {
    bool trouve = false;

    auto debut = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < mots.size(); ++i) {
        if (mots[i] == motRecherche) {
            trouve = true;
            position = i;
            break;
        }
    }

    auto fin = std::chrono::high_resolution_clock::now();
    dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();

    return trouve;
}

std::size_t RechercheFichier::nombreMots() const {
    return mots.size();
}

std::size_t RechercheFichier::positionTrouvee() const {
    return position;
}

double RechercheFichier::tempsMicrosecondes() const {
    return dureeMicrosecondes;
}
