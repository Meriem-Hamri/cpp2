#include <chrono>   // Permet de mesurer la duree des operations.
#include <iomanip>  // Permet de limiter le nombre de decimales affichees.
#include <iostream> // Permet d'afficher les resultats dans la console.
#include <string>   // Permet de construire les branches de l'arbre a afficher.

// Chaque element de l'arbre est un noeud.
struct Noeud {
    int valeur;     // Nombre stocke dans ce noeud.
    Noeud* gauche;  // Enfant qui contient une valeur plus petite.
    Noeud* droite;  // Enfant qui contient une valeur plus grande.
};

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

// Insere une valeur et renvoie la racine, qui peut changer si l'arbre etait vide.
Noeud* inserer(Noeud* racine, int valeur) {
    // Une place vide a ete trouvee : on y cree un nouveau noeud.
    if (racine == nullptr) {
        return new Noeud{valeur, nullptr, nullptr};
    }

    // Les petites valeurs vont dans le sous-arbre gauche.
    if (valeur < racine->valeur) {
        racine->gauche = inserer(racine->gauche, valeur);
    }
    // Les grandes valeurs vont dans le sous-arbre droit.
    else if (valeur > racine->valeur) {
        racine->droite = inserer(racine->droite, valeur);
    }

    // Si la valeur est egale, aucun appel n'a lieu : le doublon est ignore.
    // On renvoie la racine pour reconnecter ce sous-arbre a son parent.
    return racine;
}

// Recherche une valeur en partant de la racine.
// Renvoie true si elle existe, false sinon.
bool rechercher(const Noeud* racine, int valeur) {
    const Noeud* courant = racine; // Noeud que l'on examine actuellement.

    // Tant qu'il reste un noeud a examiner, on poursuit la recherche.
    while (courant != nullptr) {
        // La valeur est trouvee : on peut arreter immediatement.
        if (valeur == courant->valeur) return true;

        // Plus petit : gauche. Plus grand : droite.
        courant = valeur < courant->valeur ? courant->gauche : courant->droite;
    }

    // Une place vide a ete atteinte sans trouver la valeur.
    return false;
}

// Calcule le nombre de niveaux du sous-arbre qui commence a ce noeud.
int hauteur(const Noeud* noeud) {
    // Un sous-arbre vide a une hauteur de zero.
    if (noeud == nullptr) return 0;

    // On calcule d'abord la hauteur des deux enfants.
    int hauteurGauche = hauteur(noeud->gauche);
    int hauteurDroite = hauteur(noeud->droite);

    // Le niveau actuel ajoute 1 au plus grand des deux sous-arbres.
    return 1 + (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurDroite);
}

// Supprime tous les noeuds crees avec new.
void liberer(Noeud* noeud) {
    // Il n'y a rien a supprimer dans un sous-arbre vide.
    if (noeud == nullptr) return;

    // On supprime les enfants avant leur parent.
    liberer(noeud->gauche);
    liberer(noeud->droite);
    delete noeud;
}

// Affiche un sous-arbre, mais s'arrete des que la limite est atteinte.
void afficherSousArbre(const Noeud* noeud, const std::string& marge,
                      bool dernier, int& affiches, int limite, bool& tronque) {
    if (noeud == nullptr) return;

    // Un noeud existe encore, mais on ne doit plus ajouter de ligne.
    if (affiches >= limite) {
        tronque = true;
        return;
    }

    // |-- marque une branche suivie d'une autre ; `-- marque la derniere.
    std::cout << marge << (dernier ? "`-- " : "|-- ") << noeud->valeur << '\n';
    ++affiches;

    // La marge garde les traits verticaux des branches encore ouvertes.
    std::string margeEnfants = marge + (dernier ? "    " : "|   ");

    // On affiche le cote gauche avant le cote droit.
    if (noeud->gauche != nullptr) {
        afficherSousArbre(noeud->gauche, margeEnfants,
                          noeud->droite == nullptr, affiches, limite, tronque);
    }
    if (noeud->droite != nullptr) {
        afficherSousArbre(noeud->droite, margeEnfants,
                          true, affiches, limite, tronque);
    }
}

// Affiche la racine, puis au maximum "limite" noeuds au total.
void afficherArbre(const Noeud* racine, int limite) {
    if (racine == nullptr) {
        std::cout << "(arbre vide)\n";
        return;
    }

    int affiches = 1; // La racine compte comme premiere ligne.
    bool tronque = false;
    std::cout << racine->valeur << '\n';

    if (racine->gauche != nullptr) {
        afficherSousArbre(racine->gauche, "", racine->droite == nullptr,
                          affiches, limite, tronque);
    }
    if (racine->droite != nullptr) {
        afficherSousArbre(racine->droite, "", true,
                          affiches, limite, tronque);
    }

    // On signale que le reste de l'arbre n'a pas ete affiche.
    if (tronque) std::cout << "... (affichage limite a " << limite << " noeuds)\n";
}

int main() {
    Noeud* racine = nullptr; // Au debut, l'arbre est vide.
    const int nombreValeurs = 1000; // Changer ce nombre pour essayer une autre taille.
    const int limiteAffichage = 20; // Ne pas remplir le terminal avec tout l'arbre.

    // On prend l'heure avant la premiere insertion.
    auto debutInsertion = std::chrono::steady_clock::now();

    // On insere les nombres dans l'ordre croissant.
    for (int valeur = 1; valeur <= nombreValeurs; ++valeur) {
        racine = inserer(racine, valeur);
    }

    // On prend l'heure apres la derniere insertion.
    auto finInsertion = std::chrono::steady_clock::now();

    // On mesure separement la recherche de la derniere valeur inseree.
    auto debutRecherche = std::chrono::steady_clock::now();
    bool trouve = rechercher(racine, nombreValeurs);
    auto finRecherche = std::chrono::steady_clock::now();

    // On transforme les deux durees en nanosecondes (ns).
    // Ces durees peuvent varier d'une execution a l'autre.
    auto tempsInsertion = std::chrono::duration_cast<std::chrono::nanoseconds>(
        finInsertion - debutInsertion).count();
    auto tempsRecherche = std::chrono::duration_cast<std::chrono::nanoseconds>(
        finRecherche - debutRecherche).count();

    // Dans cet ordre, l'arbre penche a droite et sa hauteur vaut nombreValeurs.
    std::cout << "Insertion de 1 a " << nombreValeurs << '\n';
    std::cout << "Hauteur (nombre de niveaux) : " << hauteur(racine) << '\n';
    std::cout << "Temps total d'insertion : ";
    afficherDuree(tempsInsertion);
    std::cout << '\n';

    // La recherche de la derniere valeur traverse tous les noeuds.
    std::cout << "Recherche de " << nombreValeurs << " : "
              << (trouve ? "trouve" : "absent") << '\n';
    std::cout << "Temps de recherche : ";
    afficherDuree(tempsRecherche);
    std::cout << '\n';

    // On ne montre que les premieres lignes de l'arbre.
    std::cout << "\nPremiers noeuds de l'arbre :\n";
    afficherArbre(racine, limiteAffichage);

    // Avant de terminer, on rend la memoire occupee par les noeuds.
    liberer(racine);
}
