#include <chrono>   // Mesure les durees d'insertion et de recherche.
#include <iomanip>  // Permet de limiter le nombre de decimales affichees.
#include <iostream> // Affiche les resultats dans le terminal.
#include <map>      // Fournit std::map, un conteneur aux cles triees.

// Choisit automatiquement l'unite de temps la plus facile a lire.
void afficherDuree(long long nanosecondes) {
    if (nanosecondes < 1000) {
        std::cout << nanosecondes << " ns";
    } else if (nanosecondes < 1000000) {
        std::cout << std::fixed << std::setprecision(3)
                  << nanosecondes / 1000.0 << " us";
    } else if (nanosecondes < 1000000000) {
        std::cout << std::fixed << std::setprecision(3)
                  << nanosecondes / 1000000.0 << " ms";
    } else {
        std::cout << std::fixed << std::setprecision(3)
                  << nanosecondes / 1000000000.0 << " s";
    }
    std::cout << std::defaultfloat;
}

int main() {
    // La cle est le nombre insere. La valeur true indique sa presence.
    // Une meme cle ne peut apparaitre qu'une fois dans la map.
    std::map<int, bool> arbre;

    const int nombreValeurs = 32300; // Meme taille que dans main.cpp.
    const int limiteAffichage = 20; // Nombre maximal de valeurs a montrer.

    // On chronometre l'insertion des nombres de 1 a nombreValeurs.
    auto debutInsertion = std::chrono::steady_clock::now();
    for (int valeur = 1; valeur <= nombreValeurs; ++valeur) {
        arbre.emplace(valeur, true);
    }
    auto finInsertion = std::chrono::steady_clock::now();

    // find renvoie end() si la cle recherchee n'existe pas.
    auto debutRecherche = std::chrono::steady_clock::now();
    bool trouve = arbre.find(nombreValeurs) != arbre.end();
    auto finRecherche = std::chrono::steady_clock::now();

    // Conversion des durees mesurees en nanosecondes.
    auto tempsInsertion = std::chrono::duration_cast<std::chrono::nanoseconds>(
        finInsertion - debutInsertion).count();
    auto tempsRecherche = std::chrono::duration_cast<std::chrono::nanoseconds>(
        finRecherche - debutRecherche).count();

    std::cout << "Insertion de 1 a " << nombreValeurs << " avec std::map\n";
    std::cout << "Nombre de valeurs : " << arbre.size() << '\n';
    std::cout << "Temps total d'insertion : ";
    afficherDuree(tempsInsertion);
    std::cout << '\n';
    std::cout << "Recherche de " << nombreValeurs << " : "
              << (trouve ? "trouve" : "absent") << '\n';
    std::cout << "Temps de recherche : ";
    afficherDuree(tempsRecherche);
    std::cout << '\n';

    // La map parcourt ses cles dans l'ordre croissant.
    // Sa structure interne (branches et hauteur) n'est pas accessible.
    std::cout << "\nPremieres valeurs :\n";
    int affichees = 0;
    for (const auto& element : arbre) {
        if (affichees >= limiteAffichage) break;
        std::cout << element.first << '\n'; // first est la cle.
        ++affichees;
    }
    if (arbre.size() > static_cast<std::size_t>(limiteAffichage)) {
        std::cout << "... (affichage limite a " << limiteAffichage
                  << " valeurs)\n";
    }
}
