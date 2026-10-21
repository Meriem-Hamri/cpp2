#include "RechercheLongueSousChaine.h"

#include <algorithm>
#include <chrono>
#include <fstream>

bool RechercheLongueSousChaine::charger(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        return false;
    }
    mots.clear();
    std::string mot;
    while (fichier >> mot) {
        mots.push_back(mot);
    }
    return true;
}

bool RechercheLongueSousChaine::rechercher() {
    auto debut = std::chrono::high_resolution_clock::now();
    resultatCommun.clear();
    motTemoin1.clear();
    motTemoin2.clear();
    nombreContenant = 0;

    // Conserver les repetitions dans mots pour le comptage final.
    // Trier sur place evite de copier les millions de repetitions.
    std::sort(mots.begin(), mots.end());
    std::vector<std::string> motsTries;
    for (const std::string& mot : mots) {
        if (motsTries.empty() || mot != motsTries.back()) {
            motsTries.push_back(mot);
        }
    }
    std::sort(motsTries.begin(), motsTries.end(),
        [](const std::string& a, const std::string& b) {
            if (a.length() != b.length()) {
                return a.length() > b.length();
            }
            return a < b;
        });

    for (std::size_t i = 0; i < motsTries.size(); ++i) {
        if (motsTries[i].length() <= resultatCommun.length()) {
            break;
        }
        for (std::size_t j = i + 1; j < motsTries.size(); ++j) {
            // Les mots suivants sont encore plus courts : aucun ne peut ameliorer.
            if (motsTries[j].length() <= resultatCommun.length()) {
                break;
            }
            std::string commune = calculerSousSequenceCommune(motsTries[i], motsTries[j]);
            if (commune.length() > resultatCommun.length()) {
                resultatCommun = commune;
                motTemoin1 = motsTries[i];
                motTemoin2 = motsTries[j];
            }
        }
    }

    if (!resultatCommun.empty()) {
        // Les repetitions sont voisines : une seule verification par mot different.
        for (std::size_t i = 0; i < mots.size();) {
            std::size_t finGroupe = i + 1;
            while (finGroupe < mots.size() && mots[finGroupe] == mots[i]) {
                ++finGroupe;
            }
            if (contientSousSequence(mots[i], resultatCommun)) {
                nombreContenant += finGroupe - i;
            }
            i = finGroupe;
        }
    }

    auto fin = std::chrono::high_resolution_clock::now();
    dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();
    return !resultatCommun.empty();
}

std::string RechercheLongueSousChaine::calculerSousSequenceCommune(
    const std::string& mot1,
    const std::string& mot2
) const {
    const std::string& court = mot1.length() <= mot2.length() ? mot1 : mot2;
    const std::string& longMot = mot1.length() <= mot2.length() ? mot2 : mot1;
    // Si le mot court entier apparait dans l'ordre, on ne peut pas faire mieux.
    if (contientSousSequence(longMot, court)) {
        return court;
    }
    std::string candidate;
    std::string meilleure;
    candidate.reserve(court.length());
    meilleure.reserve(court.length());
    explorer(court, longMot, 0, 0, candidate, meilleure);
    return meilleure;
}

bool RechercheLongueSousChaine::contientSousSequence(
    const std::string& mot, const std::string& sequence
) const {
    if (sequence.length() > mot.length()) {
        return false;
    }
    std::size_t position = 0;
    for (char lettre : sequence) {
        position = mot.find(lettre, position);
        if (position == std::string::npos) {
            return false;
        }
        ++position;
    }
    return true;
}

void RechercheLongueSousChaine::explorer(
    const std::string& court, const std::string& longMot,
    std::size_t i, std::size_t position,
    std::string& candidate, std::string& meilleure
) const {
    if (candidate.length() > meilleure.length()) {
        meilleure = candidate;
    }
    const std::size_t record = std::max(meilleure.length(), resultatCommun.length());
    const std::size_t restantes = std::min(court.length() - i, longMot.length() - position);
    // Meme en ajoutant toutes les lettres possibles, ce choix ne bat pas le record.
    if (candidate.length() + restantes <= record) {
        return;
    }

    // Si les deux prochaines lettres sont identiques, les garder est toujours optimal.
    if (court[i] == longMot[position]) {
        candidate.push_back(court[i]);
        explorer(court, longMot, i + 1, position + 1, candidate, meilleure);
        candidate.pop_back();
        return;
    }

    // Essayer de garder la lettre. Sa premiere occurrence laisse le plus de place.
    std::size_t trouvee = longMot.find(court[i], position);
    if (trouvee != std::string::npos) {
        candidate.push_back(court[i]);
        explorer(court, longMot, i + 1, trouvee + 1, candidate, meilleure);
        candidate.pop_back();
    }
    // Essayer aussi de l'ignorer : la garder peut empecher une meilleure suite.
    explorer(court, longMot, i + 1, position, candidate, meilleure);
}

std::size_t RechercheLongueSousChaine::nombreMots() const {
    return mots.size();
}

const std::string& RechercheLongueSousChaine::sousChaineCommune() const {
    return resultatCommun;
}

const std::string& RechercheLongueSousChaine::premierMotTemoin() const {
    return motTemoin1;
}

const std::string& RechercheLongueSousChaine::deuxiemeMotTemoin() const {
    return motTemoin2;
}

std::size_t RechercheLongueSousChaine::nombreMotsContenant() const {
    return nombreContenant;
}

double RechercheLongueSousChaine::tempsMicrosecondes() const {
    return dureeMicrosecondes;
}
