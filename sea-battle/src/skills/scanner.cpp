#include "scanner.h"
#include "../base/exceptions.h"

bool Scanner::useSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x) {
    int dx = x - 1;
    int dy = (int)y - 96 - 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            try {
                if (field.isShip(dy+i, dx+j))
                    return true;
            } catch (const outOfFieldException& lenExc) { }
        }
    }
    return false;
}

std::string Scanner::getName() const {
    return "Scanner";
}

skillIDs Scanner::getId() {
    return id;
}