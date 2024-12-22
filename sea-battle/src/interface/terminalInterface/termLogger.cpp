#include "termLogger.h"

void termLogger::printAtackRes(atackResults res, std::string newSkill) {
    switch(res) {
        case atackResults::segDamaged:
            printHooray("Congrats! You are damaged ship!");
            break;
        case atackResults::segDestroyed:
            printHooray("Congrats! You are destroyed a ship segment!");
            break;
        case atackResults::shipDestroyed:
            printHooray("Congrats! You are  destroyed a ship!!!!");
            printMes("New skill obtained: ");
            printHooray(newSkill);
            break;
        case atackResults::missed:
            printMes("Missed.");
            break;
    }
}

void termLogger::printMes(std::string mes) {
    std::cout << mes << std::endl;
}

void termLogger::printHooray(std::string hooray) {
    std::cout << TERM_GREEN << hooray << TERM_DEF << std::endl;
}

void termLogger::printBad(std::string bad) {
    std::cout << TERM_RED << bad << TERM_DEF << std::endl;
}

void termLogger::printError(std::string error) {
    std::cerr << TERM_RED << error << TERM_DEF << std::endl;
    bool err = std::cin.fail();
    std::cin.clear();
    if (err)
        std::cin.ignore();
}