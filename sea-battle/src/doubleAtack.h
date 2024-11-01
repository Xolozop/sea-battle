#ifndef DOUBLE_ATACK_H
#define DOUBLE_ATACK_H

#include "skill.h"
#include "field.h"
#include "shipManager.h"

class doubleAtack : public Skill {
public:
    doubleAtack(Field& field, shipManager& manager);
    void useSkill() override;
    void printSkillName() const override;
};

#endif