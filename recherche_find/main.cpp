#include "RechercheFind.h"

#include <iostream>
#include <string>

int main() {
    RechercheFind recherche;
    std::string mot1;
    std::string mot2;

    std::cout << "Entrez le premier mot : ";
    std::cin >> mot1;

    std::cout << "Entrez le deuxieme mot : ";
    std::cin >> mot2;

    if (recherche.rechercher(mot1, mot2)) {
        std::cout << mot2 << " se trouve dans " << mot1 << std::endl;
    } else {
        std::cout << mot2 << " ne se trouve pas dans " << mot1 << std::endl;
    }

    std::cout << "Temps de recherche : "
              << recherche.tempsMicrosecondes()
              << " microsecondes" << std::endl;

    return 0;
}
