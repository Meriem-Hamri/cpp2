#ifndef RECHERCHE_SOUS_CHAINE_H
#define RECHERCHE_SOUS_CHAINE_H

#include <cstddef>
#include <string>
#include <vector>

class RechercheSousChaine {
public:
    bool charger(const std::string& nomFichier);
    std::size_t compter(const std::string& sousChaine);

    std::size_t nombreMots() const;
    double tempsMicrosecondes() const;

private:
    std::vector<std::string> mots;
    double dureeMicrosecondes = 0.0;
};

#endif
