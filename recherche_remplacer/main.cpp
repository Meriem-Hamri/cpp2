#include "RechercheRemplacer.h"

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    RechercheRemplacer recherche;
    std::string nomFichier;
    std::string sousChaine;
    std::string nouvelleSousChaine;

    std::cout << "Entrez le nom du fichier : ";
    std::cin >> nomFichier;

    if (!recherche.charger(nomFichier)) {
        std::cout << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return 1;
    }

    std::cout << "Nombre de mots charges : "
              << recherche.nombreMots() << std::endl;

    std::cout << "Entrez la sous-chaine a remplacer : ";
    std::cin >> sousChaine;

    std::cout << "Entrez la nouvelle sous-chaine : ";
    std::cin >> nouvelleSousChaine;

    std::size_t nombreRemplacements =
        recherche.remplacer(sousChaine, nouvelleSousChaine);

    std::cout << "Nombre de mots modifies : "
              << recherche.nombreMotsModifies() << std::endl;
    std::cout << "Nombre total de remplacements : "
              << nombreRemplacements << std::endl;

    if (!recherche.exemples().empty()) {
        std::cout << "Exemples de modifications dans le vecteur :"
                  << std::endl;

        for (const auto& exemple : recherche.exemples()) {
            std::cout << "- " << exemple.first
                      << " -> " << exemple.second << std::endl;
        }
    }

    double temps = recherche.tempsMicrosecondes();

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Temps d'execution du remplacement : ";

    if (temps >= 1000000.0) {
        std::cout << temps / 1000000.0 << " secondes" << std::endl;
    } else {
        std::cout << temps << " microsecondes" << std::endl;
    }

    std::cout << "STL utilisee : std::for_each, std::string::find et "
              << "std::string::replace" << std::endl;
    std::cout << "Complexite :" << std::endl;
    std::cout << "- Tous les mots du vecteur sont examines" << std::endl;
    std::cout << "- Pire cas : O(n * L^2)" << std::endl;
    std::cout << "  n = nombre de mots, L = longueur moyenne d'un mot"
              << std::endl;

    std::cout << "Le fichier original n'a pas ete modifie." << std::endl;

    return 0;
}
