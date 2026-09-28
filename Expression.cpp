#include "Expression.h"
#include "Pile.h"

#include <cctype>

bool correspondent(char ouvrant, char fermant) {
    return (ouvrant == '(' && fermant == ')') ||
           (ouvrant == '[' && fermant == ']') ||
           (ouvrant == '{' && fermant == '}');
}

bool estOperateur(char caractere) {
    return caractere == '+' || caractere == '-' || caractere == '*' ||
           caractere == '/' || caractere == '^';
}

bool verifierExpression(const std::string& expression, std::string& erreur) {
    PileListe<char> ouvrants;
    bool attendOperande = true;
    bool contientElement = false;

    for (std::size_t i = 0; i < expression.size();) {
        char caractere = expression[i];

        if (std::isspace(static_cast<unsigned char>(caractere))) {
            ++i;
            continue;
        }

        contientElement = true;

        if (std::isalpha(static_cast<unsigned char>(caractere)) || caractere == '_') {
            if (!attendOperande) {
                erreur = "Operateur manquant a la position " + std::to_string(i + 1);
                return false;
            }

            do {
                ++i;
            } while (i < expression.size() &&
                     (std::isalnum(static_cast<unsigned char>(expression[i])) ||
                      expression[i] == '_'));
            attendOperande = false;
        }
        else if (std::isdigit(static_cast<unsigned char>(caractere))) {
            if (!attendOperande) {
                erreur = "Operateur manquant a la position " + std::to_string(i + 1);
                return false;
            }

            while (i < expression.size() &&
                   std::isdigit(static_cast<unsigned char>(expression[i]))) {
                ++i;
            }

            if (i < expression.size() && expression[i] == '.') {
                ++i;
                if (i == expression.size() ||
                    !std::isdigit(static_cast<unsigned char>(expression[i]))) {
                    erreur = "Nombre decimal incomplet";
                    return false;
                }
                while (i < expression.size() &&
                       std::isdigit(static_cast<unsigned char>(expression[i]))) {
                    ++i;
                }
            }
            attendOperande = false;
        }
        else if (caractere == '(' || caractere == '[' || caractere == '{') {
            if (!attendOperande) {
                erreur = "Operateur manquant avant le groupe";
                return false;
            }
            ouvrants.empiler(caractere);
            ++i;
        }
        else if (caractere == ')' || caractere == ']' || caractere == '}') {
            if (attendOperande) {
                erreur = "Operande manquant avant le fermant";
                return false;
            }
            if (ouvrants.estVide() || !correspondent(ouvrants.sommet(), caractere)) {
                erreur = "Parentheses ou delimiteurs mal ordonnes";
                return false;
            }
            ouvrants.depiler();
            attendOperande = false;
            ++i;
        }
        else if (estOperateur(caractere)) {
            if (attendOperande) {
                erreur = "Operande manquant avant l'operateur";
                return false;
            }
            attendOperande = true;
            ++i;
        }
        else {
            erreur = "Caractere non autorise a la position " + std::to_string(i + 1);
            return false;
        }
    }

    if (!contientElement) {
        erreur = "Expression vide";
        return false;
    }
    if (attendOperande) {
        erreur = "Expression incomplete";
        return false;
    }
    if (!ouvrants.estVide()) {
        erreur = "Un delimiteur ouvrant n'est pas ferme";
        return false;
    }
    return true;
}
