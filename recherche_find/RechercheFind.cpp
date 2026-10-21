#include "RechercheFind.h"

#include <chrono>

bool RechercheFind::rechercher(
    const std::string& mot1,
    const std::string& mot2
) {
    std::size_t positionRecherche = 0;
    bool trouve = true;

    auto debut = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < mot2.length(); ++i) {
        std::size_t positionTrouvee =
            mot1.find(mot2[i], positionRecherche);

        if (positionTrouvee == std::string::npos) {
            trouve = false;
            break;
        }

        positionRecherche = positionTrouvee + 1;
    }

    auto fin = std::chrono::high_resolution_clock::now();
    dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();

    return trouve;
}

double RechercheFind::tempsMicrosecondes() const {
    return dureeMicrosecondes;
}
