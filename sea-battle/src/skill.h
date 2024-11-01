#ifndef SKILL_H
#define SKILL_H

#include "field.h"
#include "shipManager.h"

class Skill
{
protected:
    Field& enemyField;
    shipManager& enemyManager; 
    int coord_x;
    char coord_y;
    void getCoordinates();
public:
    Skill(Field& field, shipManager& manager);
    virtual void useSkill();
    virtual void printSkillName() const;
};

#endif