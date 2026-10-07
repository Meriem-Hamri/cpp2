#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Export.h"

#include <string>

BIBLIOTHEQUE_API bool correspondent(char ouvrant, char fermant);
BIBLIOTHEQUE_API bool estOperateur(char caractere);
BIBLIOTHEQUE_API bool verifierExpression(
    const std::string& expression,
    std::string& erreur
);

#endif
