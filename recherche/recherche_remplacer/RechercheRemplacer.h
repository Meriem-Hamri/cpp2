#ifndef RECHERCHE_REMPLACER_H
#define RECHERCHE_REMPLACER_H

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class RechercheRemplacer {
public:
    bool charger(const std::string& nomFichier);
    std::size_t remplacer(
        const std::string& sousChaine,
        const std::string& nouvelleSousChaine
    );

    std::size_t nombreMots() const;
    std::size_t nombreMotsModifies() const;
    const std::vector<std::pair<std::string, std::string>>& exemples() const;
    double tempsMicrosecondes() const;

private:
    std::vector<std::string> mots;
    std::vector<std::pair<std::string, std::string>> exemplesModifications;
    std::size_t motsModifies = 0;
    double dureeMicrosecondes = 0.0;
};

#endif
