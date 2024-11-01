#include <iostream>
#include <climits>

#include "skill.h"
#include "exceptions.h"

Skill::Skill(Field& field, shipManager& manager) : enemyField{field}, enemyManager{manager} { }

void Skill::getCoordinates() {
    char y;
    int x;
    std::cout << "Input coordinates to use on with skill: ";
    while (1) {
        if (!(std::cin >> y >> x) || !isalpha(y)) {
            std::cin.clear();
            std::cin.ignore(LONG_MAX, '\n');
            throw improperInputException();
        }

        y = tolower(y);

        try {
            enemyField.validateCoords(y, x);
        } catch (const outOfFieldException& myExc) {
            throw myExc;
            // coords out of field
        }

        std::cin.ignore(LONG_MAX, '\n');
        coord_x = x;
        coord_y = y;
        break;
    }
}

void Skill::useSkill() { }

void Skill::printSkillName() const { }