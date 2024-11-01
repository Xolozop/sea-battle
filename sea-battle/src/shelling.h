#ifndef SHELLING_H
#define SHELLING_H

#include "skill.h"
#include "field.h"
#include "shipManager.h"

class Shelling : public Skill {
public:
    Shelling(Field& field, shipManager& manager);
    void useSkill() override;
    void printSkillName() const override;
};

#endif