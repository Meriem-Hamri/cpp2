#include "RechercheFichier.h"

#include <iostream>
#include <string>

int main() {
    RechercheFichier recherche;
    std::string nomFichier;
    std::string motRecherche;

    std::cout << "Entrez le nom du fichier : ";
    std::cin >> nomFichier;

    if (!recherche.charger(nomFichier)) {
        std::cout << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return 1;
    }

    std::cout << "Nombre de mots charges : "
              << recherche.nombreMots() << std::endl;

    std::cout << "Entrez le mot a rechercher : ";
    std::cin >> motRecherche;

    if (recherche.rechercher(motRecherche)) {
        std::cout << "Mot trouve." << std::endl;
        std::cout << "Position dans le vecteur : "
                  << recherche.positionTrouvee() << std::endl;
    } else {
        std::cout << "Mot non trouve." << std::endl;
    }

    std::cout << "Temps de recherche : "
              << recherche.tempsMicrosecondes()
              << " microsecondes" << std::endl;

    std::cout << "Complexite :" << std::endl;
    std::cout << "- Meilleur cas : O(1)" << std::endl;
    std::cout << "- Pire cas : O(n)" << std::endl;

    return 0;
}
