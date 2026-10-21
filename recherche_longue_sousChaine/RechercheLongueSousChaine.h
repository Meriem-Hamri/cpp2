#ifndef RECHERCHE_LONGUE_SOUS_CHAINE_H
#define RECHERCHE_LONGUE_SOUS_CHAINE_H

#include <cstddef>
#include <string>
#include <vector>

class RechercheLongueSousChaine {
public:
    bool charger(const std::string& nomFichier);
    bool rechercher();

    std::size_t nombreMots() const;
    const std::string& sousChaineCommune() const;
    const std::string& premierMotTemoin() const;
    const std::string& deuxiemeMotTemoin() const;
    std::size_t nombreMotsContenant() const;
    double tempsMicrosecondes() const;

private:
    std::string calculerSousSequenceCommune(
        const std::string& mot1,
        const std::string& mot2
    ) const;
    bool contientSousSequence(const std::string& mot, const std::string& sequence) const;
    void explorer(const std::string& court, const std::string& longMot,
                  std::size_t i, std::size_t position,
                  std::string& candidate, std::string& meilleure) const;

    std::vector<std::string> mots;
    std::string resultatCommun;
    std::string motTemoin1;
    std::string motTemoin2;
    std::size_t nombreContenant = 0;
    double dureeMicrosecondes = 0.0;
};

#endif
