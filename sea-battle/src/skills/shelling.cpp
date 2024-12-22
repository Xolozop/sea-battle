#include <iostream>

#include "shelling.h"
#include "../base/exceptions.h"

#define TERM_DEF "\033[0m"
#define TERM_RED "\033[31m"

bool Shelling::useSkill(Field& field, shipManager& manager, bool& DAFlag, char y='a', int x=0) {
    try {
        int* indexes = manager.getRandomUndamagedShip();
        Ship& ship = manager.getShip(indexes[0]+1, indexes[1]+1);
        ship.shellAtack();
        delete indexes;
        return true;
    } catch(const shellingException& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;
        // if there's no undamaged ships left
        bool doShot = true;
        while(doShot) {
            int x = std::rand()%4 + 1; // 1 to 5
            int y = std::rand()%manager.getShipIndex(x) + 1; // 1 to max_index of len
            Ship& ship = manager.getShip(x, y);
            try {
                int i = std::rand()%x + 1;
                ship.atack(i);
                return true;
            } catch (const alreadyDestroyedException& myExc) { }
        }
    }
    return true;
}

std::string Shelling::getName() const {
    return "Shelling";
}


skillIDs Shelling::getId() {
    return id;
}