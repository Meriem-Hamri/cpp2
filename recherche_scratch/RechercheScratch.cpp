#include "RechercheScratch.h"

#include <chrono>

bool RechercheScratch::rechercher(
    const std::string& mot1,
    const std::string& mot2
) {
    std::size_t i = 0;
    std::size_t j = 0;

    auto debut = std::chrono::high_resolution_clock::now();

    while (i < mot1.length() && j < mot2.length()) {
        if (mot1[i] == mot2[j]) {
            ++j;
        }

        ++i;
    }

    auto fin = std::chrono::high_resolution_clock::now();
    dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();

    return j == mot2.length();
}

double RechercheScratch::tempsMicrosecondes() const {
    return dureeMicrosecondes;
}
