#ifndef RECHERCHE_SCRATCH_H
#define RECHERCHE_SCRATCH_H

#include <string>

class RechercheScratch {
public:
    bool rechercher(const std::string& mot1, const std::string& mot2);
    double tempsMicrosecondes() const;

private:
    double dureeMicrosecondes = 0.0;
};

#endif
