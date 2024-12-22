#include "doubleAtack.h"

bool doubleAtack::useSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x) {
    DAFlag = true;
    return true;
}

std::string doubleAtack::getName() const {
    return "Double Atack";
}

skillIDs doubleAtack::getId() {
    return id;
}