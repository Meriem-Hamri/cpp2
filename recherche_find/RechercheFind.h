#ifndef RECHERCHE_FIND_H
#define RECHERCHE_FIND_H

#include <string>

class RechercheFind {
public:
    bool rechercher(const std::string& mot1, const std::string& mot2);
    double tempsMicrosecondes() const;

private:
    double dureeMicrosecondes = 0.0;
};

#endif
