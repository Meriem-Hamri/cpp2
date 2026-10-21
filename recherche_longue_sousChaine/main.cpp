#include "RechercheLongueSousChaine.h"

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    RechercheLongueSousChaine recherche;
    std::string nomFichier;

    std::cout << "Entrez le nom du fichier : ";
    std::cin >> nomFichier;

    if (!recherche.charger(nomFichier)) {
        std::cout << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return 1;
    }

    std::cout << "Nombre de mots charges : "
              << recherche.nombreMots() << std::endl;

    bool trouve = recherche.rechercher();

    if (!trouve) {
        std::cout << "Aucune sous-sequence commune entre deux mots differents."
                  << std::endl;
    } else {
        std::cout << "Plus longue sous-sequence commune du fichier : "
                  << recherche.sousChaineCommune() << std::endl;
        std::cout << "Longueur : "
                  << recherche.sousChaineCommune().length() << std::endl;
        std::cout << "Premier mot temoin : "
                  << recherche.premierMotTemoin() << std::endl;
        std::cout << "Deuxieme mot temoin : "
                  << recherche.deuxiemeMotTemoin() << std::endl;
        std::cout << "Nombre de mots qui la contiennent : "
                  << recherche.nombreMotsContenant() << std::endl;
    }

    double temps = recherche.tempsMicrosecondes();
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Temps d'execution : ";

    if (temps >= 1000000.0) {
        std::cout << temps / 1000000.0 << " secondes" << std::endl;
    } else {
        std::cout << temps << " microsecondes" << std::endl;
    }

    std::cout << "STL utilisee : std::string et std::vector" << std::endl;
    std::cout << "Methode : vector, find lettre par lettre et retour arriere" << std::endl;
    std::cout << "Au plus u * (u - 1) / 2 paires, avec arrets anticipes" << std::endl;
    std::cout << "Essais coupes lorsqu'ils ne peuvent plus battre le record" << std::endl;
    std::cout << "Pire cas exponentiel par paire (choix garder ou ignorer)" << std::endl;
    std::cout << "Memoire : O(n * L), mots conserves dans le vecteur" << std::endl;
    std::cout << "n = nombre total de mots, u = nombre de mots differents," << std::endl;
    std::cout << "L = longueur maximale d'un mot" << std::endl;

    return 0;
}
