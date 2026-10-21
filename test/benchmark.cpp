#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Mots = std::vector<std::string>;
using Horloge = std::chrono::steady_clock;

// Les tailles sont utilisees apres chaque essai pour rendre le travail observable.
volatile std::size_t controle = 0;

template <typename Operation>
double mesurer(Operation operation) {
    std::array<double, 3> temps{};
    for (double& duree : temps) {
        const auto debut = Horloge::now();
        const std::size_t taille = operation();
        const auto fin = Horloge::now();
        controle += taille;
        duree = std::chrono::duration<double, std::milli>(fin - debut).count();
    }
    std::sort(temps.begin(), temps.end());
    return temps[1]; // Mediane de trois mesures.
}

template <typename Preparation, typename Operation>
double mesurer_prepare(Preparation preparer, Operation operation) {
    std::array<double, 3> temps{};
    for (double& duree : temps) {
        auto conteneur = preparer();
        const auto debut = Horloge::now();
        const std::size_t resultat = operation(conteneur);
        const auto fin = Horloge::now();
        controle += resultat;
        duree = std::chrono::duration<double, std::milli>(fin - debut).count();
    }
    std::sort(temps.begin(), temps.end());
    return temps[1];
}

void afficher(const std::string& nom, double millisecondes) {
    std::cout << std::left << std::setw(24) << nom << std::right
              << std::setw(12) << millisecondes << " ms\n";
}

// Recherche lineaire : examiner chaque mot jusqu'a trouver la cible.
template <typename Conteneur>
bool recherche_lineaire(const Conteneur& conteneur, const std::string& cible) {
    for (const auto& mot : conteneur) {
        if (mot == cible) return true;
    }
    return false;
}

template <typename Conteneur>
double mesurer_recherche(const Conteneur& conteneur,
                        const std::vector<std::string>& requetes) {
    return mesurer([&] {
        std::size_t trouves = 0;
        for (const auto& cible : requetes) {
            if (recherche_lineaire(conteneur, cible)) {
                ++trouves;
            }
        }
        return trouves;
    });
}

template <typename Conteneur>
double mesurer_recherche_hache(const Conteneur& conteneur,
                              const std::vector<std::string>& requetes) {
    return mesurer([&] {
        std::size_t trouves = 0;
        for (const auto& cible : requetes) {
            if (conteneur.find(cible) != conteneur.end()) ++trouves;
        }
        return trouves;
    });
}

int main(int argc, char* argv[]) {
    try {
        if (argc > 3) {
            throw std::invalid_argument("Usage : benchmark [fichier] [nombre_de_mots]");
        }

        const std::string chemin = argc > 1 ? argv[1] : "test4.txt";
        std::size_t limite = 100000;
        if (argc > 2) {
            std::size_t caracteres_lus = 0;
            if (argv[2][0] == '-') {
                throw std::invalid_argument("Le nombre de mots doit etre un entier positif.");
            }
            limite = std::stoull(argv[2], &caracteres_lus);
            if (caracteres_lus != std::string(argv[2]).size() || limite == 0) {
                throw std::invalid_argument("Le nombre de mots doit etre un entier positif.");
            }
        }

        std::ifstream fichier(chemin);
        if (!fichier && argc == 1) {
            fichier.open("../test4.txt"); // Execution depuis le dossier test.
        }
        if (!fichier) {
            throw std::runtime_error("Impossible d'ouvrir " + chemin);
        }

        Mots mots;
        mots.reserve(limite);
        std::string mot;
        while (mots.size() < limite && fichier >> mot) {
            mots.push_back(mot);
        }
        if (mots.empty()) {
            throw std::runtime_error("Le fichier ne contient aucun mot.");
        }

        const std::size_t n = mots.size();
        const std::size_t operations = std::min<std::size_t>(n, 1000);
        const std::vector<std::string> v_recherche(mots.begin(), mots.end());
        const std::list<std::string> l_recherche(mots.begin(), mots.end());
        const std::deque<std::string> d_recherche(mots.begin(), mots.end());
        std::cout << "Fichier : " << chemin << " | mots charges : " << n << "\n"
                  << "Conteneurs initiaux : " << n << " mots ; " << operations
                  << " operations par essai d'insertion/modification/suppression.\n"
                  << "Temps median de 3 essais (chargement du fichier exclu).\n"
                  << "Copies initiales et reserve prealable exclus des temps CRUD.\n"
                  << std::fixed << std::setprecision(3);

        std::cout << "\nINSERTION AU DEBUT\n";
        afficher("vector", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            for (std::size_t i = 0; i < operations; ++i) v.insert(v.begin(), mots[i]);
            return v.size();
        }));
        afficher("list", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            for (std::size_t i = 0; i < operations; ++i) l.push_front(mots[i]);
            return l.size();
        }));
        afficher("deque", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            for (std::size_t i = 0; i < operations; ++i) d.push_front(mots[i]);
            return d.size();
        }));

        std::cout << "\nINSERTION AU MILIEU\n";
        afficher("vector", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            for (std::size_t i = 0; i < operations; ++i)
                v.insert(v.begin() + v.size() / 2, mots[i]);
            return v.size();
        }));
        afficher("list (recherche incluse)", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            for (std::size_t i = 0; i < operations; ++i) {
                auto milieu = l.begin();
                std::advance(milieu, l.size() / 2);
                l.insert(milieu, mots[i]);
            }
            return l.size();
        }));
        afficher("deque", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            for (std::size_t i = 0; i < operations; ++i)
                d.insert(d.begin() + d.size() / 2, mots[i]);
            return d.size();
        }));

        std::cout << "\nINSERTION A LA FIN\n";
        afficher("vector", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            for (std::size_t i = 0; i < operations; ++i) v.push_back(mots[i]);
            return v.size();
        }));
        afficher("vector + reserve", mesurer_prepare([&] {
            auto v = v_recherche;
            v.reserve(n + operations);
            return v;
        }, [&](auto& v) {
            for (std::size_t i = 0; i < operations; ++i) v.push_back(mots[i]);
            return v.size();
        }));
        afficher("list", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            for (std::size_t i = 0; i < operations; ++i) l.push_back(mots[i]);
            return l.size();
        }));
        afficher("deque", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            for (std::size_t i = 0; i < operations; ++i) d.push_back(mots[i]);
            return d.size();
        }));

        // La construction est hors chronometre : seule la recherche est mesuree.
        std::vector<std::string> requetes;
        requetes.reserve(100);
        for (int i = 0; i < 100; ++i) {
            std::string absent = "__MOT_ABSENT_DU_TEST4__" + std::to_string(i);
            while (std::find(mots.begin(), mots.end(), absent) != mots.end()) {
                absent += '_';
            }
            requetes.push_back(std::move(absent));
        }

        std::vector<std::string> requetes_presentes;
        requetes_presentes.reserve(100);
        for (std::size_t i = 0; i < 100; ++i) {
            requetes_presentes.push_back(mots[i * n / 100]);
        }

        std::cout << "\nCONSTRUCTION D'UN INDEX DE RECHERCHE\n";
        afficher("unordered_set", mesurer([&] {
            std::unordered_set<std::string> index(mots.begin(), mots.end());
            return index.size();
        }));
        afficher("unordered_map", mesurer([&] {
            std::unordered_map<std::string, std::size_t> frequences;
            for (const auto& s : mots) ++frequences[s];
            return frequences.size();
        }));
        const std::unordered_set<std::string> index(mots.begin(), mots.end());
        std::unordered_map<std::string, std::size_t> frequences;
        for (const auto& s : mots) ++frequences[s];
        std::cout << "Mots distincts : " << index.size() << '\n';

        std::cout << "\nRECHERCHE D'UN MOT ABSENT (100 recherches)\n";
        afficher("vector", mesurer_recherche(v_recherche, requetes));
        afficher("list", mesurer_recherche(l_recherche, requetes));
        afficher("deque", mesurer_recherche(d_recherche, requetes));
        afficher("unordered_set", mesurer_recherche_hache(index, requetes));
        afficher("unordered_map", mesurer_recherche_hache(frequences, requetes));

        std::cout << "\nRECHERCHE D'UN MOT PRESENT (100 recherches)\n";
        afficher("vector", mesurer_recherche(v_recherche, requetes_presentes));
        afficher("list", mesurer_recherche(l_recherche, requetes_presentes));
        afficher("deque", mesurer_recherche(d_recherche, requetes_presentes));
        afficher("unordered_set", mesurer_recherche_hache(index, requetes_presentes));
        afficher("unordered_map", mesurer_recherche_hache(frequences, requetes_presentes));

        std::cout << "\nMODIFICATION DU MOT AU MILIEU (" << operations << " fois)\n";
        afficher("vector", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            for (std::size_t i = 0; i < operations; ++i) v[v.size() / 2] = mots[i];
            return v[v.size() / 2].size();
        }));
        afficher("list (recherche incluse)", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            for (std::size_t i = 0; i < operations; ++i) {
                auto milieu = l.begin();
                std::advance(milieu, l.size() / 2);
                *milieu = mots[i];
            }
            auto milieu = l.begin();
            std::advance(milieu, l.size() / 2);
            return milieu->size();
        }));
        afficher("deque", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            for (std::size_t i = 0; i < operations; ++i) d[d.size() / 2] = mots[i];
            return d[d.size() / 2].size();
        }));

        std::cout << "\nSUPPRESSION AU DEBUT\n";
        afficher("vector", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !v.empty(); ++i) {
                total += v.front().size();
                v.erase(v.begin());
            }
            return total;
        }));
        afficher("list", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !l.empty(); ++i) {
                total += l.front().size();
                l.pop_front();
            }
            return total;
        }));
        afficher("deque", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !d.empty(); ++i) {
                total += d.front().size();
                d.pop_front();
            }
            return total;
        }));

        std::cout << "\nSUPPRESSION AU MILIEU\n";
        afficher("vector", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !v.empty(); ++i) {
                auto milieu = v.begin() + v.size() / 2;
                total += milieu->size();
                v.erase(milieu);
            }
            return total;
        }));
        afficher("list (recherche incluse)", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !l.empty(); ++i) {
                auto milieu = l.begin();
                std::advance(milieu, l.size() / 2);
                total += milieu->size();
                l.erase(milieu);
            }
            return total;
        }));
        afficher("deque", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !d.empty(); ++i) {
                auto milieu = d.begin() + d.size() / 2;
                total += milieu->size();
                d.erase(milieu);
            }
            return total;
        }));

        std::cout << "\nSUPPRESSION A LA FIN\n";
        afficher("vector", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !v.empty(); ++i) {
                total += v.back().size();
                v.pop_back();
            }
            return total;
        }));
        afficher("list", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !l.empty(); ++i) {
                total += l.back().size();
                l.pop_back();
            }
            return total;
        }));
        afficher("deque", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            std::size_t total = 0;
            for (std::size_t i = 0; i < operations && !d.empty(); ++i) {
                total += d.back().size();
                d.pop_back();
            }
            return total;
        }));

        // reserve change uniquement la capacite ; resize ajoute des chaines vides.
        const std::size_t nouvelle_taille = n * 2;
        std::cout << "\nAGRANDISSEMENT APRES CRUD (" << n << " -> "
                  << nouvelle_taille << ")\n";
        afficher("vector reserve", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            v.reserve(nouvelle_taille);
            return v.capacity();
        }));
        afficher("vector resize", mesurer_prepare([&] { return v_recherche; }, [&](auto& v) {
            v.resize(nouvelle_taille);
            return v.size();
        }));
        afficher("list resize", mesurer_prepare([&] { return l_recherche; }, [&](auto& l) {
            l.resize(nouvelle_taille);
            return l.size();
        }));
        afficher("deque resize", mesurer_prepare([&] { return d_recherche; }, [&](auto& d) {
            d.resize(nouvelle_taille);
            return d.size();
        }));

        auto exemple_reserve = v_recherche;
        const std::size_t capacite_initiale = exemple_reserve.capacity();
        exemple_reserve.reserve(nouvelle_taille);
        std::cout << "vector reserve : taille " << n << " -> " << exemple_reserve.size()
                  << ", capacite " << capacite_initiale << " -> "
                  << exemple_reserve.capacity() << '\n';
        auto exemple_resize = v_recherche;
        exemple_resize.resize(nouvelle_taille);
        std::cout << "vector resize  : taille " << n << " -> " << exemple_resize.size()
                  << ", capacite " << exemple_resize.capacity() << '\n';

        std::cout << "\nCRUD : C=insertion, R=recherche, U=modification, D=suppression\n"
                  << "COMPLEXITE THEORIQUE DES INSERTIONS (n = taille courante)\n"
                  << "Position   vector             list                  deque\n"
                  << "Debut      O(n)               O(1)                  O(1)\n"
                  << "Milieu     O(n)               O(1) si position      O(n)\n"
                  << "                              connue ; O(n) pour\n"
                  << "                              trouver le milieu\n"
                  << "Fin        O(1) amorti        O(1)                  O(1)\n"
                  << "\nSur n insertions : O(n^2) pour les cas O(n), O(n) pour\n"
                  << "les cas O(1). reserve prepare la capacite de vector ;\n"
                  << "resize ajoute des chaines vides a la taille demandee.\n"
                  << "Recherche lineaire : O(n) dans les trois conteneurs\n"
                  << "au pire (mot absent). La taille ne change pas.\n"
                  << "Modification par indice au milieu : vector/deque O(1),\n"
                  << "list O(n) pour atteindre la position.\n"
                  << "Suppression : debut vector O(n), list/deque O(1) ;\n"
                  << "milieu vector/deque O(n), list O(n) avec recherche\n"
                  << "(O(1) si l'iterateur est connu) ; fin O(1) pour tous.\n"
                  << "unordered_set/map : recherche O(1) en moyenne,\n"
                  << "mais construction O(n) et espace supplementaire O(u),\n"
                  << "u = nombre de mots distincts. Ces index ne suivent pas\n"
                  << "automatiquement les modifications des conteneurs.\n"
                  << "Agrandir de n a 2n : vector reserve O(n) si allocation\n"
                  << "necessaire ; vector resize O(n) ; list/deque resize\n"
                  << "O(n) pour creer n nouveaux elements. list et deque\n"
                  << "n'exposent pas de methode capacity().\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << '\n';
        return 1;
    }
}
