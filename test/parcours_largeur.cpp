#include <cstddef>
#include <iostream>
#include <vector>

// Un noeud contient directement ses enfants : plus besoin de map.
struct Noeud {
    char nom;
    std::vector<Noeud> enfants;
};

Noeud construire_arbre() {
    // Les accolades imbriquees montrent la forme de l'arbre.
    return {'c', {
        {'b', {{'a', {}}, {'s', {}}}},
        {'d', {{'e', {}}}},
        {'f', {}},
        {'g', {}}
    }};
}

void parcours_largeur(const Noeud& racine) {
    // On garde les adresses des noeuds a visiter, sans les copier.
    std::vector<const Noeud*> en_attente{&racine};
    std::vector<char> ordre;
    int etape = 1;

    while (!en_attente.empty()) {
        // Version naive : retirer le premier element du vector.
        const Noeud* courant = en_attente.front();
        en_attente.erase(en_attente.begin());
        ordre.push_back(courant->nom);

        // Les enfants passent a la fin, dans leur ordre dans l'arbre.
        for (const Noeud& enfant : courant->enfants) {
            en_attente.push_back(&enfant);
        }

        std::cout << "Etape " << etape++ << " : noeud " << courant->nom
                  << ", enfants ";
        if (courant->enfants.empty()) {
            std::cout << '-';
        } else {
            for (std::size_t i = 0; i < courant->enfants.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << courant->enfants[i].nom;
            }
        }

        // Noeud traite + noeuds encore en attente (exemple : cbdfg).
        std::cout << " : " << courant->nom;
        for (const Noeud* suivant : en_attente) std::cout << suivant->nom;
        std::cout << '\n';
    }

    std::cout << "Etape " << etape << " : -\nOrdre du parcours :";
    for (char nom : ordre) std::cout << ' ' << nom;
    std::cout << '\n';
}

int main() {
    Noeud arbre = construire_arbre();
    parcours_largeur(arbre);
}
