#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>

// Chaque noeud possede son nom et ses enfants dans l'ordre de visite.
struct Noeud {
    char nom;
    std::vector<Noeud> enfants;
};

// L'arbre est construit une seule fois et ne change pas pendant le parcours.
Noeud construire_arbre() {
    return {'c', {
        {'b', {{'a', {}}, {'s', {}}}},
        {'d', {{'e', {}}}},
        {'f', {}},
        {'g', {}}
    }};
}

// Le parametre est passe par valeur : on recoit une copie de la file.
// La copie contient des adresses de noeuds, pas des copies des noeuds.
void afficher_attente(std::queue<const Noeud*> copie) {
    // On affiche en FIFO : lire le premier, puis le retirer de la copie.
    // La file principale reste intacte pour la prochaine etape.
    while (!copie.empty()) {
        std::cout << copie.front()->nom;
        copie.pop();
    }
}

void parcours_largeur(const Noeud& racine) {
    // queue est un adaptateur FIFO (base sur deque par defaut).
    // Au depart, seule l'adresse de la racine attend d'etre visitee.
    std::queue<const Noeud*> en_attente;
    en_attente.push(&racine);

    // ordre garde les noms deja visites pour le resultat final.
    std::vector<char> ordre;
    int etape = 1;

    // Le parcours s'arrete lorsque plus aucun noeud n'est en attente.
    while (!en_attente.empty()) {
        // FIFO : le premier entre est le premier traite.
        // pop retire son adresse de la file, pas le noeud de l'arbre.
        const Noeud* courant = en_attente.front();
        en_attente.pop();
        ordre.push_back(courant->nom);

        // Les enfants sont ajoutes a la fin, de gauche a droite.
        // On garde leurs adresses : l'arbre lui-meme n'est pas copie.
        for (const Noeud& enfant : courant->enfants) {
            en_attente.push(&enfant);
        }

        // Afficher le noeud courant et la liste de ses enfants.
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

        // Exemple : apres c, la file contient b, d, f, g ; on affiche cbdfg.
        // afficher_attente vide seulement sa copie de la file.
        std::cout << " : " << courant->nom;
        afficher_attente(en_attente);
        std::cout << '\n';
    }

    // La file est vide : tous les noeuds ont ete visites.
    std::cout << "Etape " << etape << " : -\nOrdre du parcours :";
    for (char nom : ordre) std::cout << ' ' << nom;
    std::cout << '\n';
}

int main() {
    // La racine reste en vie pendant tout le parcours.
    Noeud arbre = construire_arbre();
    parcours_largeur(arbre);
}
