#include <iostream>

#include "doubleAtack.h"

#define TERM_RED "\033[31m"
#define TERM_DEF "\033[0m"


doubleAtack::doubleAtack(Field& field, shipManager& manager) : Skill(field, manager) { }

void doubleAtack::useSkill() {
    printSkillName();
    bool prev = enemyField.isMine;
    while(1) {
        try {
            getCoordinates();
            enemyField.shoot(coord_y, coord_x, enemyManager);
            break;
        } catch (const std::exception& myExc) {
            std::cerr << TERM_RED << myExc.what() << TERM_DEF;
        }
    }
    try {
        enemyField.isMine = true;
        enemyField.shoot(coord_y, coord_x, enemyManager);
    } catch (...) {  } // temporary solution, need for skip shoot if segment is already destroyed
    enemyField.isMine = prev;
}

void doubleAtack::printSkillName() const {
    std::cout << "Using Double Atack..." << std::endl;
}

