#include "RechercheSousChaine.h"

#include <algorithm>
#include <chrono>
#include <fstream>

bool RechercheSousChaine::charger(const std::string& nomFichier) {
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

std::size_t RechercheSousChaine::compter(const std::string& sousChaine) {
    auto debut = std::chrono::high_resolution_clock::now();

    auto nombreOccurrences = std::count_if(
        mots.cbegin(),
        mots.cend(),
        [&sousChaine](const std::string& mot) {
            return mot.find(sousChaine) != std::string::npos;
        }
    );

    auto fin = std::chrono::high_resolution_clock::now();
    dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();

    return static_cast<std::size_t>(nombreOccurrences);
}

std::size_t RechercheSousChaine::nombreMots() const {
    return mots.size();
}

double RechercheSousChaine::tempsMicrosecondes() const {
    return dureeMicrosecondes;
}
