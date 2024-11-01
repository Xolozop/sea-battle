#include <iostream>

#include "shelling.h"
#include "exceptions.h"

#define TERM_DEF "\033[0m"
#define TERM_RED "\033[31m"

Shelling::Shelling(Field& field, shipManager& manager) : Skill(field, manager) { }

void Shelling::useSkill() {
    printSkillName();
    try {
        int* indexes = enemyManager.getRandomUndamagedShip();
        Ship& ship = enemyManager.getShip(indexes[0]+1, indexes[1]+1);
        ship.shellAtack();
        delete indexes;
    } catch(const shellingException& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;
        while(1) {
            int x = std::rand()%4 + 1; // 1 to 5
            int y = std::rand()%enemyManager.getShipIndex(x) + 1; // 1 to max_index of len
            Ship& ship = enemyManager.getShip(x, y);
            try {
                int i = std::rand()%x + 1;
                ship.atack(i);
                return;
            } catch (const alreadyDestroyedException& myExc) { }
        }
    }
}

void Shelling::printSkillName() const {
    std::cout << "Using Shelling..." << std::endl;
}