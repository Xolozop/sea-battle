#ifndef TERM_LOGGER_H
#define TERM_LOGGER_H

#include <iostream>

#include "../../base/game.h"

#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"
#define TERM_DEF "\033[0m"

class termLogger {
public:
    void printAll(Game game);

    void printAtackRes(atackResults res, std::string newSkill);

    void printMes(std::string mes);
    void printHooray(std::string hooray);
    void printBad(std::string bad);
    void printError(std::string error);
};

#endif