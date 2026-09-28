#include "Expression.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string expression;
    std::string erreur;

    std::cout << "Entrez une expression mathematique : ";
    std::getline(std::cin, expression);

    // Seul l'appel a la DLL est chronometre, apres la saisie.
    const auto debut = std::chrono::steady_clock::now();
    const bool estValide = verifierExpression(expression, erreur);
    const auto fin = std::chrono::steady_clock::now();

    const double dureeMicrosecondes =
        std::chrono::duration<double, std::micro>(fin - debut).count();
    const double dureeMillisecondes =
        std::chrono::duration<double, std::milli>(fin - debut).count();

    if (estValide) {
        std::cout << "Expression valide" << std::endl;
    } else {
        std::cout << "Expression invalide : " << erreur << std::endl;
    }

    std::cout << std::fixed << std::setprecision(6)
              << "Temps de reponse : " << dureeMicrosecondes
              << " microsecondes ("
              << std::fixed << std::setprecision(6)
              << dureeMillisecondes << " ms)" << std::endl;
    std::cout << "Complexite temporelle (pire cas) : O(n), avec n = "
              << expression.size() << " caracteres" << std::endl;

    return 0;
}
