#ifndef SCANNER_H
#define SCANNER_H

#include "skill.h"
#include "field.h"
#include "shipManager.h"

class Scanner : public Skill {
public:
    Scanner(Field& field, shipManager& manager);
    void useSkill() override;
    void printSkillName() const override;
};

#endif