#ifndef SKILL_H
#define SKILL_H

#include <string>

#include "../base/field.h"
#include "../base/shipManager.h"

enum skillIDs {doubleAtack, scanner, shelling};

class Skill
{
public:
    virtual bool useSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x) = 0;
    virtual std::string getName() const = 0;
    virtual skillIDs getId() = 0;
};

#endif