#ifndef RECHERCHE_FICHIER_FIND_H
#define RECHERCHE_FICHIER_FIND_H

#include <cstddef>
#include <string>
#include <vector>

class RechercheFichierFind {
public:
    bool charger(const std::string& nomFichier);
    bool rechercher(const std::string& motRecherche);

    std::size_t nombreMots() const;
    std::size_t positionTrouvee() const;
    double tempsMicrosecondes() const;

private:
    std::vector<std::string> mots;
    std::size_t position = 0;
    double dureeMicrosecondes = 0.0;
};

#endif
