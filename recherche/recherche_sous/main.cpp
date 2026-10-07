#include "RechercheSousChaine.h"

#include <iostream>
#include <string>

int main() {
    RechercheSousChaine recherche;
    std::string nomFichier;
    std::string sousChaine;

    std::cout << "Entrez le nom du fichier : ";
    std::cin >> nomFichier;

    if (!recherche.charger(nomFichier)) {
        std::cout << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return 1;
    }

    std::cout << "Nombre de mots charges : "
              << recherche.nombreMots() << std::endl;

    std::cout << "Entrez la sous-chaine a rechercher : ";
    std::cin >> sousChaine;

    std::size_t nombre = recherche.compter(sousChaine);

    std::cout << "Nombre de mots contenant la sous-chaine \""
              << sousChaine << "\" : " << nombre << std::endl;

    std::cout << "Temps d'execution de la recherche : "
              << recherche.tempsMicrosecondes()
              << " microsecondes" << std::endl;

    std::cout << "STL utilisee : std::count_if et std::string::find"
              << std::endl;
    std::cout << "Complexite :" << std::endl;
    std::cout << "- Dans tous les cas, les n mots sont examines" << std::endl;
    std::cout << "- Pire cas : O(n * L * m)" << std::endl;
    std::cout << "  n = nombre de mots, L = longueur moyenne d'un mot," << std::endl;
    std::cout << "  m = longueur de la sous-chaine" << std::endl;

    return 0;
}
