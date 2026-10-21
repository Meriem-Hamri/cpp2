#include "RechercheRemplacer.h"

#include <algorithm>
#include <chrono>
#include <fstream>

bool RechercheRemplacer::charger(const std::string& nomFichier) {
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

std::size_t RechercheRemplacer::remplacer(
    const std::string& sousChaine,
    const std::string& nouvelleSousChaine
) {
    motsModifies = 0;
    exemplesModifications.clear();

    if (sousChaine.empty()) {
        dureeMicrosecondes = 0.0;
        return 0;
    }

    std::size_t nombreRemplacements = 0;
    auto debut = std::chrono::high_resolution_clock::now();

    std::for_each(mots.begin(), mots.end(), [&](std::string& mot) {
        const std::string motAvant = mot;
        std::size_t position = 0;
        std::size_t remplacementsDansMot = 0;

        while ((position = mot.find(sousChaine, position))
               != std::string::npos) {
            mot.replace(position, sousChaine.length(), nouvelleSousChaine);
            position += nouvelleSousChaine.length();
            ++remplacementsDansMot;
        }

        if (remplacementsDansMot > 0) {
            ++motsModifies;
            nombreRemplacements += remplacementsDansMot;

            if (exemplesModifications.size() < 5) {
                exemplesModifications.emplace_back(motAvant, mot);
            }
        }
    });

    auto fin = std::chrono::high_resolution_clock::now();
    dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();

    return nombreRemplacements;
}

std::size_t RechercheRemplacer::nombreMots() const {
    return mots.size();
}

std::size_t RechercheRemplacer::nombreMotsModifies() const {
    return motsModifies;
}

const std::vector<std::pair<std::string, std::string>>&
RechercheRemplacer::exemples() const {
    return exemplesModifications;
}

double RechercheRemplacer::tempsMicrosecondes() const {
    return dureeMicrosecondes;
}
