#include <iostream>

#include "scanner.h"

#define TERM_DEF "\033[0m"
#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"

Scanner::Scanner(Field& field, shipManager& manager) : Skill(field, manager) { }

void Scanner::useSkill() {
    printSkillName();
    while(1) {
        try {
            getCoordinates();
            break;
        } catch (const std::exception& myExc) {
            std::cerr << TERM_RED << myExc.what() << TERM_DEF;
        }
    }

    int x = coord_x - 1;
    int y = (int)coord_y - 96 - 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (enemyField.isShip(x+i, y+j)) {
                std::cout << "Selected area " << TERM_GREEN << "INCLUDE" << TERM_DEF " ship." << std::endl;
                return;
            }
        }
    }
    std::cout << "Selected area does " << TERM_RED "NOT" << TERM_DEF << " include ship." << std::endl;
}


void Scanner::printSkillName() const {
    std::cout << "Using Scanner..." << std::endl;
}